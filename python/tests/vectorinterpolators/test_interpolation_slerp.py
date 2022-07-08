# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.tools import vectorinterpolators as vip

import pytest
from pytest import approx
import numpy as np


# define class for grouping (test sections)
class Test_tools_vectorinterpolators_slerp:
    def test_SlerpInterpolator_overloaded_functions_and_vector_calls_should_produce_the_same_results(
        self,
    ):
        np.random.seed(1234567)
        n_values = 100

        # init data
        x = np.random.uniform(-1000, 500, n_values)
        x2 = np.random.uniform(501, 1000, n_values)
        x.sort()
        x2.sort()

        y = np.random.uniform(-1000, 1000, n_values)
        p = np.random.uniform(-1000, 1000, n_values)
        r = np.random.uniform(-1000, 1000, n_values)

        ypr = np.stack((y, p, r), axis=1)

        y_r = np.radians(y)
        p_r = np.radians(p)
        r_r = np.radians(r)
        ypr_r = np.radians(ypr)

        # create interpolator clases using different methods
        # input in degrees
        i1 = vip.SlerpInterpolator(x, y, p, r)
        # input in rad
        i3 = vip.SlerpInterpolator(x, y_r, p_r, r_r, False)

        # interpolator classes that will be appendet and extended
        ia1 = vip.SlerpInterpolator(x, y, p, r)
        ia2 = vip.SlerpInterpolator(x, y, p, r)
        ia3 = vip.SlerpInterpolator(x, y_r, p_r, r_r, False)
        ia4 = vip.SlerpInterpolator(x, y_r, p_r, r_r, False)
        ie1 = vip.SlerpInterpolator(x, y, p, r)
        ie2 = vip.SlerpInterpolator(x, y, p, r)
        ie3 = vip.SlerpInterpolator(x, y_r, p_r, r_r, False)
        ie4 = vip.SlerpInterpolator(x, y_r, p_r, r_r, False)

        # append and extend some of the interpolator classes using different methods
        for i, _ in enumerate(x2):
            ia1.append(x2[i], y[i], p[i], r[i])
            ia2.append(x2[i], ypr[i])
            ia3.append(x2[i], y_r[i], p_r[i], r_r[i], False)
            ia4.append(x2[i], ypr_r[i], False)
        ie1.extend(x2, y, p, r)
        ie2.extend(x2, ypr)
        ie3.extend(x2, y_r, p_r, r_r, False)
        ie4.extend(x2, ypr_r, False)

        # create structure to hold vector (to test vectorized return methods)
        x_targets = []
        y1_results = []
        y1_r_results = []

        for _ in range(100):
            x_target = np.random.uniform(-1500, 1500)
            y1 = i1(x_target)
            y3 = i3(x_target)

            y1_e = ia1(x_target)
            y2_e = ia2(x_target)
            y3_e = ia3(x_target)
            y4_e = ia4(x_target)
            y5_e = ie1(x_target)
            y6_e = ie2(x_target)
            y7_e = ie3(x_target)
            y8_e = ie4(x_target)

            y1_r = i1(x_target, False)
            y3_r = i3(x_target, False)

            x_targets.append(x_target)
            y1_results.append(y1)
            y1_r_results.append(y1_r)

            # tests
            # default interpolators [returned degrees]
            assert y3 == approx(y1)

            # default interpolators [returned rad]
            assert y1_r == approx(y3_r)

            # appendet and extended interpolators
            assert y2_e == approx(y1_e)
            assert y3_e == approx(y1_e)
            assert y4_e == approx(y1_e)
            assert y5_e == approx(y1_e)
            assert y6_e == approx(y1_e)
            assert y7_e == approx(y1_e)
            assert y8_e == approx(y1_e)

        # test if vectorized call produces the same results as single call
        y1_vec = i1(x_targets)
        y1_r_vec = i1(x_targets, False)

        for y1, y1_r, y1_v, y1_r_v in zip(y1_results, y1_r_results, y1_vec, y1_r_vec):
            assert y1 == approx(y1_v)
            assert y1_r == approx(y1_r_v)

    def test_SlerpInterpolator_should_perform_basic_interpolations(self):

        # initialize test data
        X = [-10, -5, 0, 6]
        Y = [0, 45, 100, 300]
        P = [0, 45, -45, 80]
        R = [-180, 45, 0, 170]
        x_append = 12
        ypr_append = [350, -80, -170]

        interpolator = vip.SlerpInterpolator(X, Y, P, R)

        # append some data
        interpolator.append(x_append, ypr_append)

        # -- existing values should be looked up correctly
        YPR = interpolator(X)

        for ypr, y, p, r in zip(YPR, Y, P, R):
            assert ypr == approx([y, p, r])

        assert interpolator(x_append) == approx(ypr_append)

        # -- preset values should be interpolated correctly --
        ypr_1 = interpolator(-3)
        ypr_2 = interpolator(9)

        assert ypr_1[0] == approx(58.5679194066)
        assert ypr_1[1] == approx(5.0841237338)
        assert ypr_1[2] == approx(37.6730325392)

        assert ypr_2[0] == approx(333.5151692017)
        assert ypr_2[1] == approx(0.632182955)
        assert ypr_2[2] == approx(-158.8770719663)

        # -- extrapolation mode fail --
        interpolator.set_extrapolation_mode(vip.t_extr_mode.fail)
        with pytest.raises(IndexError):
            interpolator(-11)
        with pytest.raises(IndexError):
            interpolator(13)

        # -- extrapolation mode nearest --
        interpolator.set_extrapolation_mode(vip.t_extr_mode.nearest)

        assert interpolator(-11) == approx([Y[0],P[0],R[0]])
        assert interpolator(13) == approx(ypr_append)

        # -- extrapolation mode extrapolate--
        interpolator.set_extrapolation_mode(vip.t_extr_mode.extrapolate)        
        too_small_ypr = interpolator(-11)
        too_large_ypr = interpolator(13)

        assert too_small_ypr[0] == approx(347.01848882)
        assert too_small_ypr[1] == approx(9.3296836006)
        assert too_small_ypr[2] == approx(-153.7039370777)

        assert too_large_ypr[0] == approx(147.0971139354)
        assert too_large_ypr[1] == approx(-72.4669510216)
        assert too_large_ypr[2] == approx(34.2739577346)