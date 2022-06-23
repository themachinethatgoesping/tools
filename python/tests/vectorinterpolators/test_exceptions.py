import pytest

from themachinethatgoesping.tools import vectorinterpolators as vip


# define class for grouping (test sections)
class Test_tools_vectorinterpolators_all:
    def test_VectorInterpolators_should_throw_expected_exceptions(self):
        X = [-10, -5, 0, 6, 12]
        Y = [1, 0, 1, 0, -1]
        X_wrong_order = [-5, -10, 0, 6, 12]
        Y_wrong_order = [0, 1, 1, 0, -1]
        X_duplicates = [-10, -5, -5, 0, 6, 12]
        Y_duplicates = [1, 0, 1, 1, 0, -1]

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

            # should not throw
            interpolator = interpolatorType(X, Y)
            interpolator.append((13, -1))

            # check of exceptions are raised for appending items
            interpolator = interpolatorType(X, Y)
            with pytest.raises(ValueError):
                interpolator.append((12, -1))

            # check of exceptions are raised for appending items
            interpolator = interpolatorType(X, Y)
            with pytest.raises(ValueError):
                interpolator.append((11, -1))

            # check of exceptions are raised for extending items
            interpolator = interpolatorType(X, Y)
            with pytest.raises(ValueError):
                interpolator.extend([(11, -1), (12, -1)])

            # check of exceptions are raised for extending items
            interpolator = interpolatorType(X, Y)
            with pytest.raises(ValueError):
                interpolator.extend([(12, -1), (13, -1)])

            # check of exceptions are raised for extending items
            interpolator = interpolatorType(X, Y)
            with pytest.raises(ValueError):
                interpolator.extend([(14, -1), (13, -1)])

            # should not throw
            interpolator = interpolatorType(X, Y)
            interpolator.extend([(13, -1), (14, -1)])

    def test_SlerpInterpolator_should_throw_expected_exceptions(self):
        """this interpolator uses different input data than the other interpolators"""
        x = [-10, -5, 0, 6, 12]
        yaw = [1, 0, 1, 0, -1]
        pitch = [1, 0, 1, 0, -1]
        roll = [1, 0, 1, 0, -1]

        interpolator = vip.SlerpInterpolator(x, yaw, pitch, roll)

        # interpolator should fail if double x elements are appended
        with pytest.raises(ValueError):
            interpolator.append(12, [-1, -1, -1])

        interpolator.set_data_XY(x, yaw, pitch, roll)
        with pytest.raises(ValueError):
            interpolator.append(11, [-1, -1, -1])

        # should not fail here
        interpolator.set_data_XY(x, yaw, pitch, roll)
        interpolator.append(13, [-1, -1, -1])

        # same behavior for vectorized calls
        interpolator.set_data_XY(x, yaw, pitch, roll)
        with pytest.raises(ValueError):
            interpolator.extend([12, 13], [[-1, -1, -1], [1, 1, 1]])

        interpolator.set_data_XY(x, yaw, pitch, roll)
        with pytest.raises(ValueError):
            interpolator.extend([11, 13], [[-1, -1, -1], [1, 1, 1]])

        interpolator.set_data_XY(x, yaw, pitch, roll)
        with pytest.raises(ValueError):
            interpolator.extend([14, 13], [[-1, -1, -1], [1, 1, 1]])

        interpolator.set_data_XY(x, yaw, pitch, roll)
        with pytest.raises(ValueError):
            interpolator.extend([14, 14], [[-1, -1, -1], [1, 1, 1]])

        # should not fail here
        interpolator.set_data_XY(x, yaw, pitch, roll)
        interpolator.extend([13, 14], [[-1, -1, -1], [1, 1, 1]])

        # initialize test data (wrong order)
        x_wrong_order = [-5, -10, 0, 6, 12]

        # // throw because x is nort sorted
        with pytest.raises(ValueError):
            vip.SlerpInterpolator(x_wrong_order, yaw, pitch, roll)
        with pytest.raises(ValueError):
            interpolator.set_data_XY(x_wrong_order, yaw, pitch, roll)

        # initialize test data (duplicates)
        x_duplicates = [-5, -10, 0, 0, 6, 12]

        with pytest.raises(ValueError):
            vip.SlerpInterpolator(x_duplicates, yaw, pitch, roll)
        with pytest.raises(ValueError):
            interpolator.set_data_XY(x_duplicates, yaw, pitch, roll)
