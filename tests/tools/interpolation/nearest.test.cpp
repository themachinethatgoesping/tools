// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <chrono>
#include <boost/algorithm/algorithm.hpp>

#include "../../src/tools/interpolation.h"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::tools;

#define TESTTAG "[interpolation]"

TEST_CASE("NearestInterpolator: sorting and checking should work as expected",
          TESTTAG)
{
  // initialize test data (correct order)
  std::vector<double> x = { -10, -5, 0, 6, 12 };
  std::vector<double> y = { 1, 0, 1, 0, -1 };

  interpolation::NearestInterpolator interpolator(x, y);
  
  // initialize test data (wrong order)
  std::vector<double> x_wrong_order = { -5, -10, 0, 6, 12 };
  std::vector<double> y_wrong_order = { 0, 1, 1, 0, -1 };

  //throw because sortX is false but checkX is not false
  REQUIRE_THROWS_AS(interpolation::NearestInterpolator(x_wrong_order, y_wrong_order,false, true),std::runtime_error);
  
  //do not throw because vector is sorted this time
  interpolation::NearestInterpolator interpolator_sorted(x_wrong_order, y_wrong_order,true, true);

  //interpolators should be the same after sorting the elements
  REQUIRE(interpolator.get_XY() == interpolator.get_XY());


  // initialize test data (duplicates)
  std::vector<double> x_duplicates = { -5, -10, 0, 0, 6, 12 };
  std::vector<double> y_duplicates = { 0, 1, 1, 0, 1, -1 };

  //interpolator should fail if there is a double x element!
  REQUIRE_THROWS_AS(interpolation::NearestInterpolator(x_duplicates, y_duplicates,true, true),std::runtime_error);
}

TEST_CASE("NearestInterpolator: should perform basic interpolations correctly",
          TESTTAG)
{
  // initialize test data
  std::vector<double> x = { -10, -5, 0, 6, 12 };
  std::vector<double> y = { 1, 0, 1, 0, -1 };

  interpolation::NearestInterpolator interpolator(x, y);

  SECTION("existing values should be looked up correctly")
  {
    for (unsigned int i = 0; i < x.size(); ++i)
      REQUIRE(interpolator.interpolate(x[i]) == Approx(y[i]));
  }

  SECTION("preset values should be interpolated correctly")
  {
    REQUIRE(interpolator.interpolate(-7.6) == Approx(1));
    REQUIRE(interpolator.interpolate(-7.5) == Approx(1));
    REQUIRE(interpolator.interpolate(-7.4) == Approx(0));

    REQUIRE(interpolator.interpolate(-2.6) == Approx(0));
    REQUIRE(interpolator.interpolate(-2.5) == Approx(0));
    REQUIRE(interpolator.interpolate(-2.4) == Approx(1));

    REQUIRE(interpolator.interpolate(2.9) == Approx(1));
    REQUIRE(interpolator.interpolate(3.0) == Approx(1));
    REQUIRE(interpolator.interpolate(3.1) == Approx(0));

    REQUIRE(interpolator.interpolate(8.9) == Approx(0));
    REQUIRE(interpolator.interpolate(9.0) == Approx(0));
    REQUIRE(interpolator.interpolate(9.1) == Approx(-1));
  }

  SECTION("exact 0.5 cases should be handled as expected")
  {
    interpolator.set_average_halves(false); // default mode
    REQUIRE(interpolator.interpolate(-7.5) == Approx(1));
    REQUIRE(interpolator.interpolate(-2.5) == Approx(0));
    REQUIRE(interpolator.interpolate(3.0) == Approx(1));
    REQUIRE(interpolator.interpolate(9.0) == Approx(0));

    interpolator.set_average_halves(true);
    REQUIRE(interpolator.interpolate(-7.5) == Approx(0.5));
    REQUIRE(interpolator.interpolate(-2.5) == Approx(0.5));
    REQUIRE(interpolator.interpolate(3.0) == Approx(0.5));
    REQUIRE(interpolator.interpolate(9.0) == Approx(-0.5));

    interpolator.set_average_halves(false); // switch back to default mode
    REQUIRE(interpolator.interpolate(-7.5) == Approx(1));
    REQUIRE(interpolator.interpolate(-2.5) == Approx(0));
    REQUIRE(interpolator.interpolate(3.0) == Approx(1));
    REQUIRE(interpolator.interpolate(9.0) == Approx(0));
  }

  SECTION("extrapolation should be nearest for all mode except 'fail'")
  {
    for (auto mode :
         { "none", "nearest", "extrapolate", "default", "standard" }) {

      if (!boost::iequals(mode,"none"))
        interpolator.set_extrapolation_mode(mode);

      REQUIRE(interpolator.interpolate(-11) == Approx(1));
      REQUIRE(interpolator.interpolate(13) == Approx(-1));
    }
  }

  SECTION(
    "extrapolation should fail with out_of_range exception in 'fail' mode")
  {
    // check faile exception
    interpolator.set_extrapolation_mode("fail");
    REQUIRE_THROWS_AS(interpolator.interpolate(-11) == Approx(1),
                      std::out_of_range);
    REQUIRE_THROWS_AS(interpolator.interpolate(13) == Approx(-1),
                      std::out_of_range);
  }
}