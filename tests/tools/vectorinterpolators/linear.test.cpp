// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <boost/algorithm/algorithm.hpp>
#include <chrono>

#include "../../src/tools/vectorinterpolators.h"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::tools;

#define TESTTAG "[vectorinterpolators]"

TEST_CASE("LinearInterpolator: sorting and checking should work as expected",
          TESTTAG)
{
  // initialize test data (correct order)
  std::vector<double> x = { -10, -5, 0, 6, 12 };
  std::vector<double> y = { 1, 0, 1, 0, -1 };

  vectorinterpolators::LinearInterpolator interpolator(x, y);

  // initialize test data (wrong order)
  std::vector<double> x_wrong_order = { -5, -10, 0, 6, 12 };
  std::vector<double> y_wrong_order = { 0, 1, 1, 0, -1 };

  // throw because sortX is false but checkX is not false
  REQUIRE_THROWS_AS(vectorinterpolators::LinearInterpolator(
                      x_wrong_order, y_wrong_order, false, true),
                    std::runtime_error);

  // do not throw because vector is sorted this time
  vectorinterpolators::LinearInterpolator interpolator_sorted(
    x_wrong_order, y_wrong_order, true, true);

  // interpolators should be the same after sorting the elements
  REQUIRE(interpolator.get_data_XY() == interpolator.get_data_XY());

  // initialize test data (duplicates)
  std::vector<double> x_duplicates = { -5, -10, 0, 0, 6, 12 };
  std::vector<double> y_duplicates = { 0, 1, 1, 0, 1, -1 };

  // interpolator should fail if there is a double x element!
  REQUIRE_THROWS_AS(
    vectorinterpolators::LinearInterpolator(x_duplicates, y_duplicates, true, true),
    std::runtime_error);
}

TEST_CASE("LinearInterpolator: should perform basic interpolations correctly",
          TESTTAG)
{
  // initialize test data
  std::vector<double> x = { -10, -5, 0, 6, 12 };
  std::vector<double> y = { 1, 0, 1, 0, -1 };

  vectorinterpolators::LinearInterpolator interpolator(x, y);

  SECTION("existing values should be looked up correctly")
  {
    for (unsigned int i = 0; i < x.size(); ++i)
      REQUIRE(interpolator.interpolate(x[i]) == Approx(y[i]));
  }

  SECTION("preset values should be interpolated correctly")
  {
    CHECK(interpolator.interpolate(-7.6) == Approx(0.52));
    CHECK(interpolator.interpolate(-7.5) == Approx(0.5));
    CHECK(interpolator.interpolate(-7.4) == Approx(0.48));

    CHECK(interpolator.interpolate(-2.6) == Approx(0.48));
    CHECK(interpolator.interpolate(-2.5) == Approx(0.5));
    CHECK(interpolator.interpolate(-2.4) == Approx(0.52));

    CHECK(interpolator.interpolate(2) == Approx(2. / 3.));
    CHECK(interpolator.interpolate(3.0) == Approx(1. / 2.));
    CHECK(interpolator.interpolate(4) == Approx(1. / 3.));

    CHECK(interpolator.interpolate(8) == Approx(-1. / 3.));
    CHECK(interpolator.interpolate(9.0) == Approx(-1. / 2.));
    CHECK(interpolator.interpolate(10) == Approx(-2. / 3.));
  }

  SECTION("preset value vectors should be interpolated correctly")
  {
    std::vector<double> targets_x = { -2.6, -2.5, -2.4 };
    std::vector<double> expected_y = { 0.48, 0.5, 0.52 };

    REQUIRE(interpolator.interpolate(targets_x) == expected_y);
  }

  SECTION("extrapolation mode should cause:")
  {
    for (auto mode : vectorinterpolators::t_extr_mode_all) {
      interpolator.set_extrapolation_mode(mode);

      switch (mode) {
        case vectorinterpolators::t_extr_mode::fail:
          SECTION(" - fail when set to fail")
          {
            REQUIRE_THROWS_AS(interpolator.interpolate(-11) == Approx(1),
                              std::out_of_range);
            REQUIRE_THROWS_AS(interpolator.interpolate(13) == Approx(-1),
                              std::out_of_range);
          }
          break;

        case vectorinterpolators::t_extr_mode::nearest:
          SECTION(" - extrapolate nearst when set")
          {
            REQUIRE(interpolator.interpolate(-11) == Approx(1));
            REQUIRE(interpolator.interpolate(13) == Approx(-1));
          }
          break;

        default:
          SECTION(" - extrapolation in all other cases")
          REQUIRE(interpolator.interpolate(-11) == Approx(1.2));
          REQUIRE(interpolator.interpolate(14) == Approx(-4 / 3.));

          break;
      }
    }
  }
}