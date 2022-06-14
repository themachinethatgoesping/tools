from themachinethatgoesping.tools import vectorinterpolators as vip

import pytest


#define class for grouping (test sections)
class Test_tools_vectorinterpolators_nearest:

  def test_NearestInterpolator_should_sort_and_check_lists(self):
    X = [-10, -5, 0, 6, 12]
    Y = [1, 0, 1, 0, -1]
    X_wrong_order = [-5, -10, 0, 6, 12]
    Y_wrong_order = [0, 1, 1, 0, -1]
    X_duplicates = [-10, -5, -5, 0, 6, 12]
    Y_duplicates = [1, 0, 1, 1, 0, -1]

    #check of exceptions are raise
    with pytest.raises(RuntimeError):
      vip.NearestInterpolator(X_wrong_order, Y_wrong_order)

    #check of exceptions are raise ib dyokucates
    with pytest.raises(RuntimeError):
      vip.NearestInterpolator(X_duplicates, Y_duplicates)


  def test_NearestInterpolator_should_perform_basic_interpolations(self):
    X = [-10, -5, 0, 6, 12]
    Y = [1, 0, 1, 0, -1]
    interpolator = vip.NearestInterpolator(X,Y)

    #existing values should be looked up correctly
    assert interpolator.interpolate(X) == pytest.approx(Y)

    #preset values should be interpolated correctly
    X_val = [-7.6,-7.5,-7.4,8.9,9.0,9.1]
    Y_exp = [1,0,0,0,-1,-1]
    assert interpolator.interpolate(X_val) == pytest.approx(Y_exp)

    #extrapolation mode fail
    interpolator = vip.NearestInterpolator(X,Y, extrapolation_mode=vip.t_extr_mode.fail)
    with pytest.raises(IndexError): interpolator.interpolate(-11)
    with pytest.raises(IndexError): interpolator.interpolate(13)

    #extrapolation mode nearest
    interpolator = vip.NearestInterpolator(X,Y, extrapolation_mode=vip.t_extr_mode.nearest)
    assert interpolator.interpolate(-11) == pytest.approx(Y[0])
    assert interpolator.interpolate(13) == pytest.approx(Y[-1])

    #extrapolation mode extrapolate
    interpolator = vip.NearestInterpolator(X,Y, extrapolation_mode=vip.t_extr_mode.extrapolate)
    assert interpolator.interpolate(-11) == pytest.approx(Y[0])
    assert interpolator.interpolate(13) == pytest.approx(Y[-1])

