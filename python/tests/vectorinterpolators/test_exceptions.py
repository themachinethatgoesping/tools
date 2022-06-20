from themachinethatgoesping.tools import vectorinterpolators as vip

import pytest


# define class for grouping (test sections)
class Test_tools_vectorinterpolators_all:
    def test_VectorInterpolators_should_throw_expected_exceptions(self):
        X = [-10, -5, 0, 6, 12]
        Y = [1, 0, 1, 0, -1]
        X_wrong_order = [-5, -10, 0, 6, 12]
        Y_wrong_order = [0, 1, 1, 0, -1]
        X_duplicates = [-10, -5, -5, 0, 6, 12]
        Y_duplicates = [1, 0, 1, 1, 0, -1]

        for interpolatorType in [vip.NearestInterpolator,vip.LinearInterpolator,vip.AkimaInterpolator]:

            # check of exceptions is raised on wrong order
            with pytest.raises(ValueError):
                interpolatorType(X_wrong_order, Y_wrong_order)

            # check of exception is raised on duplicates
            with pytest.raises(ValueError):
                interpolatorType(X_duplicates, Y_duplicates)

            # should not throw
            interpolator = interpolatorType(X,Y)
            interpolator.append((13,-1))

            # check of exceptions are raised for appending items
            with pytest.raises(ValueError):
                interpolator = interpolatorType(X,Y)
                interpolator.append((12,-1))

            # check of exceptions are raised for appending items
            with pytest.raises(ValueError):
                interpolator = interpolatorType(X,Y)
                interpolator.append((11,-1))

            # check of exceptions are raised for extending items
            with pytest.raises(ValueError):
                interpolator = interpolatorType(X,Y)
                interpolator.extend([(11,-1),(12,-1)])

            # check of exceptions are raised for extending items
            with pytest.raises(ValueError):
                interpolator = interpolatorType(X,Y)
                interpolator.extend([(12,-1),(13,-1)])

            # check of exceptions are raised for extending items
            with pytest.raises(ValueError):
                interpolator = interpolatorType(X,Y)
                interpolator.extend([(14,-1),(13,-1)])

            #should not throw
            interpolator = interpolatorType(X,Y)
            interpolator.extend([(13,-1),(14,-1)])