# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

import pytest
from pytest import approx
from copy import deepcopy, copy
import numpy as np
import pickle
import os

from themachinethatgoesping.tools import vectorinterpolators as vip

test_tmp = "interpolator.tmp"

# define class for grouping (test sections)


class Test_tools_vectorinterpolators_all:
    def test_vectorinterpolators_should_be_serializable(self):
        X = [-10, -5, 0, 6, 12]
        Y = [1, 0, 1, 0, -1]
        yaw = [1, 0, 1, 0, 359]
        pitch = [1, 0, 1, 0, -1]
        roll = [1, 0, 1, 0, -1]

        nip = vip.NearestInterpolator(X, Y)
        lip = vip.LinearInterpolator(X, Y)
        aip = vip.AkimaInterpolator(X, Y)
        slerp = vip.SlerpInterpolator(X, yaw, pitch, roll)

        for ip in [nip, lip, aip, slerp]:
            binary = ip.to_binary()
            ip2 = ip.from_binary(binary)

            # write using binary
            with open(test_tmp, "wb") as ofi:
                ofi.write(binary)

            with open(test_tmp, "rb") as ifi:
                ip3 = ip.from_binary(ifi.read())

            # serialize using pickle
            with open(test_tmp, "wb") as ofi:
                pickle.dump(ip, ofi)

            with open(test_tmp, "rb") as ifi:
                ip4 = pickle.load(ifi)

            assert ip.get_data_X() == approx(ip2.get_data_X())
            assert ip.get_data_X() == approx(ip3.get_data_X())
            assert ip.get_data_X() == approx(ip4.get_data_X())

            if isinstance(ip, vip.SlerpInterpolator):
                y1 = np.array(ip.get_data_YPR())
                y2 = np.array(ip2.get_data_YPR())
                y3 = np.array(ip3.get_data_YPR())
                y4 = np.array(ip4.get_data_YPR())

                for i in range(3):
                    assert y1[:, i] == approx(y2[:, i])
                    assert y1[:, i] == approx(y3[:, i])
                    assert y1[:, i] == approx(y4[:, i])
            else:
                assert ip.get_data_Y() == approx(ip2.get_data_Y())
                assert ip.get_data_Y() == approx(ip3.get_data_Y())
                assert ip.get_data_Y() == approx(ip4.get_data_Y())

        os.remove(test_tmp)

    def test_vectorinterpolators_should_implement_common_functions(self):
        X = [-10, -5, 0, 6, 12]
        Y = [1, 0, 1, 0, -1]
        yaw = [1, 0, 1, 0, 359]
        pitch = [1, 0, 1, 0, -1]
        roll = [1, 0, 1, 0, -1]

        nip = vip.NearestInterpolator(X, Y)
        lip = vip.LinearInterpolator(X, Y)
        aip = vip.AkimaInterpolator(X, Y)
        slerp = vip.SlerpInterpolator(X, yaw, pitch, roll)

        for ip in [nip, lip, aip, slerp]:
            # for ip in [nip,lip,aip]:
            # -- copy functions --

            ip2 = ip.copy()
            ip3 = copy(ip2)
            ip4 = deepcopy(ip2)  # deepcopy does not yet work

            # assert copies are the same
            assert ip(100) == ip2(100)
            assert ip2(100) == ip3(100)
            assert ip2(100) == ip4(100)

            # assert copies are not references
            if isinstance(ip, vip.SlerpInterpolator):
                ip2.append(30, 40, 40, 40)
            else:
                ip2.append(30, 40)

            assert ip(100) != ip2(100)
            assert ip2(100) != ip3(100)
            assert ip2(100) != ip4(100)
            assert ip(100) == ip3(100)

            # -- get data functions --
            assert ip.get_data_X() == approx(X)
            assert ip2.get_data_X() == approx(X + [30])

            if isinstance(ip, vip.SlerpInterpolator):
                y1 = np.array(ip.get_data_YPR())
                y2 = np.array(ip2.get_data_YPR())

                assert y1[:, 0] == approx(yaw)
                assert y1[:, 1] == approx(pitch)
                assert y1[:, 2] == approx(roll)
                assert y2[:, 0] == approx(yaw + [40])
                assert y2[:, 1] == approx(pitch + [40])
                assert y2[:, 2] == approx(roll + [40])
            else:
                y1 = ip.get_data_Y()
                y2 = ip2.get_data_Y()
                y_exp1 = Y
                y_exp2 = y_exp1 + [40]
                assert y1 == approx(y_exp1)
                assert y2 == approx(y_exp2)

            # test that info string conversion does not crash or produce empty strings
            print(ip)
            ip.print()
            assert len(str(ip)) > 0
            assert len(ip.info_string()) > 0

    def test_VectorInterpolators_should_throw_expected_exceptions(self):
        X = [-10, -5, 0, 6, 12]
        Y = [1, 0, 1, 0, -1]
        X_wrong_order = [-5, -10, 0, 6, 12]
        Y_wrong_order = [0, 1, 1, 0, -1]
        X_duplicates = [-10, -5, -5, 0, 6, 12]
        Y_duplicates = [1, 0, 1, 1, 0, -1]
        X_nan = [np.nan, -5, 0, 6, 12]
        Y_nan = [1, 0, 1, np.inf, -1]

        for interpolatorType in [
            vip.NearestInterpolator,
            vip.LinearInterpolator,
            vip.AkimaInterpolator,
        ]:
            # check of exceptions is raised on wrong order
            with pytest.raises(ValueError):
                interpolatorType(X_wrong_order, Y_wrong_order)
                
            # check of exception is raised on duplicates
            with pytest.raises(ValueError):
                interpolatorType(X_duplicates, Y_duplicates)

            # check of exception is raised on x nan
            with pytest.raises(ValueError):
                interpolatorType(X_nan, Y)

            # check of exception is raised on x nan
            with pytest.raises(ValueError):
                interpolatorType(Y, Y_nan)

            # should not throw
            interpolator = interpolatorType(X, Y)
            orig_interpolator = interpolator.copy()
            print(interpolator)
            print(orig_interpolator)
            assert interpolator == orig_interpolator
            interpolator.append(13, -1)
            assert interpolator != orig_interpolator
            continue

            # check of exceptions are raised for appending items
            interpolator = interpolatorType(X, Y)
            with pytest.raises(ValueError):
                interpolator.append(12, -1)
            assert interpolator == orig_interpolator

            # check of exceptions are raised for appending items
            with pytest.raises(ValueError):
                interpolator.append(11, -1)
            assert interpolator == orig_interpolator

            # check of exceptions are raised for extending items
            with pytest.raises(ValueError):
                interpolator.extend([11, 12], [-1, -1])
            assert interpolator == orig_interpolator

            # check of exceptions are raised for extending items
            with pytest.raises(ValueError):
                interpolator.extend([12, 13], [-1, -1])
            assert interpolator == orig_interpolator

            # check of exceptions are raised for extending items
            with pytest.raises(ValueError):
                interpolator.extend([14, 13], [-1, -1])
            assert interpolator == orig_interpolator

            # check of exceptions are raised for extending nan x values
            with pytest.raises(ValueError):
                interpolator.extend([13, np.nan], [-1, -1])
            assert interpolator == orig_interpolator

            # check of exceptions are raised for extending nan x values
            with pytest.raises(ValueError):
                interpolator.extend([13, 14], [-1, np.nan])
            assert interpolator == orig_interpolator

            # check of exceptions are raised for extending inf x values
            with pytest.raises(ValueError):
                interpolator.extend([13, np.inf], [-1, -1])
            assert interpolator == orig_interpolator

            # check of exceptions are raised for extending inf x values
            with pytest.raises(ValueError):
                interpolator.extend([13, 14], [np.inf, -1])
            assert interpolator == orig_interpolator

            # --- inserting --- (like extending but does not have to be sorted)
            # check of exceptions are raised for inserting items
            with pytest.raises(ValueError):
                interpolator.insert([11, 12], [-2, -3])
            assert interpolator == orig_interpolator, interpolator.info_string() + "\n" + orig_interpolator.info_string()

            # check of exceptions are raised for inserting items
            with pytest.raises(ValueError):
                interpolator.insert([12, 13], [-1, -1])
            assert interpolator == orig_interpolator

            # check of exceptions are raised for inserting items
            interpolator.insert([14, 13], [1, -1])
            assert interpolator.get_data_X() == approx([-10, -5, 0, 6, 12, 13, 14])
            assert interpolator.get_data_Y() == approx([1, 0, 1, 0, -1, -1, 1])
            assert interpolator != orig_interpolator

            # check of exceptions are raised for inserting nan x values
            interpolator = interpolatorType(X, Y)
            with pytest.raises(ValueError):
                interpolator.insert([13, np.nan], [-1, -1])
            assert interpolator == orig_interpolator

            # check of exceptions are raised for inserting nan x values
            with pytest.raises(ValueError):
                interpolator.insert([13, 14], [-1, np.nan])
            assert interpolator == orig_interpolator

            # check of exceptions are raised for inserting inf x values
            with pytest.raises(ValueError):
                interpolator.insert([13, np.inf], [-1, -1])
            assert interpolator == orig_interpolator

            # check of exceptions are raised for inserting inf x values
            with pytest.raises(ValueError):
                interpolator.insert([13, 14], [np.inf, -1])
            assert interpolator == orig_interpolator

            # should not throw
            interpolator = interpolatorType(X, Y)
            interpolator.extend([13, 14], [-1, -1])
            assert interpolator != orig_interpolator

    def test_SlerpInterpolator_should_throw_expected_exceptions(self):
        """this interpolator uses different input data than the other interpolators"""
        x = [-10, -5, 0, 6, 12]
        yaw = [1, 0, 1, 0, -1]
        pitch = [1, 0, 1, 0, -1]
        roll = [1, 0, 1, 0, -1]

        interpolator = vip.SlerpInterpolator(x, yaw, pitch, roll)
        orig_interpolator = interpolator.copy()
        assert interpolator == orig_interpolator

        # interpolator should fail if double x elements are appended
        with pytest.raises(ValueError):
            interpolator.append(12, [-1, -1, -1])
        assert interpolator == orig_interpolator

        with pytest.raises(ValueError):
            interpolator.append(11, [-1, -1, -1])
        assert interpolator == orig_interpolator

        # should not fail here
        interpolator.append(13, [-1, -1, -1])
        assert interpolator != orig_interpolator

        # same behavior for vectorized calls
        interpolator.set_data_XYPR(x, yaw, pitch, roll)
        with pytest.raises(ValueError):
            interpolator.extend([12, 13], [[-1, -1, -1], [1, 1, 1]])
        assert interpolator == orig_interpolator

        with pytest.raises(ValueError):
            interpolator.extend([11, 13], [[-1, -1, -1], [1, 1, 1]])
        assert interpolator == orig_interpolator

        with pytest.raises(ValueError):
            interpolator.extend([14, 13], [[-1, -1, -1], [1, 1, 1]])
        assert interpolator == orig_interpolator

        with pytest.raises(ValueError):
            interpolator.extend([14, 14], [[-1, -1, -1], [1, 1, 1]])
        assert interpolator == orig_interpolator

        with pytest.raises(ValueError):
            interpolator.extend([np.nan, 14], [[-1, -1, -1], [1, 1, 1]])
        assert interpolator == orig_interpolator

        with pytest.raises(ValueError):
            interpolator.extend([13, 14], [[np.nan, -1, -1], [1, 1, 1]])
        assert interpolator == orig_interpolator

        # insert same behavior for vectorized calls
        with pytest.raises(ValueError):
            interpolator.insert([12, 13], [[-1, -1, -1], [1, 1, 1]])
        assert interpolator == orig_interpolator

        interpolator.insert([11, 13], [[-1, -1, -1], [1, 1, 1]])
        assert interpolator.get_data_X() == approx([-10, -5, 0, 6, 11, 12, 13])
        assert interpolator != orig_interpolator

        interpolator.set_data_XYPR(x, yaw, pitch, roll)
        interpolator.insert([14, 13], [[-1, -1, -1], [1, 1, 1]])
        assert interpolator.get_data_X() == approx([-10, -5, 0, 6, 12, 13, 14])
        assert interpolator != orig_interpolator

        interpolator.set_data_XYPR(x, yaw, pitch, roll)
        with pytest.raises(ValueError):
            interpolator.insert([14, 14], [[-1, -1, -1], [1, 1, 1]])
        assert interpolator == orig_interpolator

        with pytest.raises(ValueError):
            interpolator.insert([np.nan, 14], [[-1, -1, -1], [1, 1, 1]])
        assert interpolator == orig_interpolator

        with pytest.raises(ValueError):
            interpolator.insert([13, 14], [[np.nan, -1, -1], [1, 1, 1]])
        assert interpolator == orig_interpolator

        # should not raise here
        vip.SlerpInterpolator(x + [100], yaw + [1], pitch + [2], roll + [3])
        # interpolator should fail if double nan x elements
        with pytest.raises(ValueError):
            print(x + [np.nan])
            vip.SlerpInterpolator(x + [np.nan], yaw + [1], pitch + [2], roll + [3])
        # interpolator should fail if double nan x elements
        with pytest.raises(ValueError):
            vip.SlerpInterpolator(x + [100], yaw + [1], pitch + [np.inf], roll + [3])

        # should not fail here
        interpolator.set_data_XYPR(x, yaw, pitch, roll)
        interpolator.extend([13, 14], [[-1, -1, -1], [1, 1, 1]])
        assert interpolator != orig_interpolator

        # initialize test data (wrong order)
        x_wrong_order = [-5, -10, 0, 6, 12]

        # // throw because x is not sorted
        with pytest.raises(ValueError):
            vip.SlerpInterpolator(x_wrong_order, yaw, pitch, roll)
        with pytest.raises(ValueError):
            interpolator.set_data_XYPR(x_wrong_order, yaw, pitch, roll)

        # initialize test data (duplicates)
        x_duplicates = [-5, -10, 0, 0, 6, 12]

        with pytest.raises(ValueError):
            vip.SlerpInterpolator(x_duplicates, yaw, pitch, roll)
        with pytest.raises(ValueError):
            interpolator.set_data_XYPR(x_duplicates, yaw, pitch, roll)
