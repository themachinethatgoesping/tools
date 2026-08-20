# SPDX-FileCopyrightText: 2022 - 2026 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

"""Regression tests for the Rotation class (tools.rotationfunctions)."""

from themachinethatgoesping.tools import rotationfunctions as rf

import numpy as np
from pytest import approx


def _R_ypr(yaw, pitch, roll):
    """Independent reference rotation matrix, R = Rz(yaw) @ Ry(pitch) @ Rx(roll), degrees."""
    y, p, r = np.radians([yaw, pitch, roll])
    Rz = np.array([[np.cos(y), -np.sin(y), 0], [np.sin(y), np.cos(y), 0], [0, 0, 1]])
    Ry = np.array([[np.cos(p), 0, np.sin(p)], [0, 1, 0], [-np.sin(p), 0, np.cos(p)]])
    Rx = np.array([[1, 0, 0], [0, np.cos(r), -np.sin(r)], [0, np.sin(r), np.cos(r)]])
    return Rz @ Ry @ Rx


class Test_tools_rotationfunctions_rotation:
    def test_default_is_identity(self):
        for Rotation in (rf.Rotation, rf.RotationD):
            r = Rotation()
            assert r.ypr() == approx([0.0, 0.0, 0.0], abs=1e-5)
            assert r.rotate(1.0, 2.0, 3.0) == approx([1.0, 2.0, 3.0], abs=1e-5)

    def test_ypr_roundtrip(self):
        rng = np.random.default_rng(42)
        for _ in range(200):
            yaw = rng.uniform(0, 360)
            pitch = rng.uniform(-89, 89)
            roll = rng.uniform(-179, 179)
            r = rf.RotationD(yaw, pitch, roll)
            assert r.ypr() == approx([yaw, pitch, roll], abs=1e-6)
            # array constructor is equivalent
            assert r == rf.RotationD([yaw, pitch, roll])
            # from_ypr factories
            assert rf.RotationD.from_ypr(yaw, pitch, roll) == r
            assert rf.RotationD.from_ypr([yaw, pitch, roll]) == r

    def test_rotate_matches_numpy_reference(self):
        # yaw +90 deg about z(down) sends forward (1,0,0) to starboard (0,1,0)
        r = rf.RotationD(90.0, 0.0, 0.0)
        assert r.rotate(1.0, 0.0, 0.0) == approx([0.0, 1.0, 0.0], abs=1e-9)

        rng = np.random.default_rng(7)
        for _ in range(100):
            yaw, pitch, roll = rng.uniform(-180, 180, 3)
            r = rf.RotationD(yaw, pitch, roll)
            R = _R_ypr(yaw, pitch, roll)
            v = rng.uniform(-10, 10, 3)
            assert r.rotate(*v) == approx(R @ v, abs=1e-9)
            assert r.rotate(list(v)) == approx(R @ v, abs=1e-9)

    def test_vectorized_rotate(self):
        rng = np.random.default_rng(11)
        yaw, pitch, roll = 37.0, -12.0, 61.0
        r = rf.RotationD(yaw, pitch, roll)
        R = _R_ypr(yaw, pitch, roll)

        points = rng.uniform(-10, 10, size=(256, 3))
        rotated = np.asarray(r.rotate(points))
        assert rotated.shape == points.shape
        # matches the independent numpy reference (rows are vectors -> points @ R^T)
        assert rotated == approx(points @ R.T, abs=1e-9)
        # matches the per-row scalar call
        for i in range(0, points.shape[0], 32):
            assert rotated[i] == approx(r.rotate(*points[i]), abs=1e-9)

    def test_compose(self):
        a = rf.RotationD(30.0, 0.0, 0.0)
        b = rf.RotationD(40.0, 0.0, 0.0)
        assert a.rotate(b).ypr()[0] == approx(70.0, abs=1e-6)
        assert (a * b).ypr()[0] == approx(70.0, abs=1e-6)

    def test_float_vs_double_agree(self):
        for yaw, pitch, roll in [(10, 20, 30), (123, -45, 67), (-90, 5, -170)]:
            rf32 = rf.Rotation(yaw, pitch, roll)
            rf64 = rf.RotationD(yaw, pitch, roll)
            assert rf32.ypr() == approx(rf64.ypr(), abs=1e-3)

    def test_copy_binary_print(self):
        r = rf.RotationD(123.0, -45.0, 67.0)

        # copy
        assert r.copy() == r

        # a quaternion and its negation are the same rotation
        w, x, y, z = r.wxyz()
        assert rf.RotationD.from_quaternion(-w, -x, -y, -z) == r

        # binary round-trip
        assert rf.RotationD.from_binary(r.to_binary()) == r

        # printing works
        assert len(r.info_string()) != 0
        assert len(str(r)) != 0
