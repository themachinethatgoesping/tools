from themachinethatgoesping.tools import vectorinterpolators as vip

import pytest


# define class for grouping (test sections)
class Test_tools_vectorinterpolators_nearest:
    def test_NearestInterpolator_should_perform_basic_interpolations(self):
        #X = [-10, -5, 0, 6, 12]
        #Y = [1, 0, 1, 0, -1]
        X = [-10, -5, 0, 6]
        Y = [1, 0, 1, 0]
        x_append = 12
        y_append = -1

        interpolator = vip.NearestInterpolator(X, Y)
        interpolator.append((x_append,y_append))

        # existing values should be looked up correctly
        assert interpolator.interpolate(X) == pytest.approx(Y)

        # existing values should be looked up correctly for appendet values
        assert interpolator.interpolate(x_append) == pytest.approx(y_append)

        # preset values should be interpolated correctly
        X_val = [-7.6, -7.5, -7.4, 8.9, 9.0, 9.1]
        Y_exp = [1, 0, 0, 0, -1, -1]
        assert interpolator.interpolate(X_val) == pytest.approx(Y_exp)

        # extrapolation mode fail
        interpolator = vip.NearestInterpolator(
            X, Y, extrapolation_mode=vip.t_extr_mode.fail
        )
        interpolator.append((x_append,y_append))
        with pytest.raises(IndexError):
            interpolator.interpolate(-11)
        with pytest.raises(IndexError):
            interpolator.interpolate(13)

        # extrapolation mode nearest
        interpolator = vip.NearestInterpolator(
            X, Y, extrapolation_mode=vip.t_extr_mode.nearest
        )
        interpolator.append((x_append,y_append))
        assert interpolator.interpolate(-11) == pytest.approx(Y[0])
        assert interpolator.interpolate(13) == pytest.approx(y_append)

        # extrapolation mode extrapolate
        interpolator = vip.NearestInterpolator(
            X, Y, extrapolation_mode=vip.t_extr_mode.extrapolate
        )
        interpolator.append((x_append,y_append))
        assert interpolator.interpolate(-11) == pytest.approx(Y[0])
        assert interpolator.interpolate(13) == pytest.approx(y_append)