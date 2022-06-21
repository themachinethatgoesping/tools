// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <boost/algorithm/algorithm.hpp>
#include <chrono>

#include "../../src/tools/vectorinterpolators.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::tools;

#define TESTTAG "[vectorinterpolators]"

TEST_CASE("AkimaInterpolator: should perform basic interpolations correctly", TESTTAG)
{
    // initialize test data
    // std::vector<double> x = { -10, -5, 0, 6, 12 };
    // std::vector<double> y = { 1, 0, 1, 0, -1 };
    std::vector<double> x        = { -10, -5, 0, 6 };
    std::vector<double> y        = { 1, 0, 1, 0 };
    double              x_append = 12;
    double              y_append = -1;

    vectorinterpolators::AkimaInterpolator interpolator(x, y);

    // append some data
    interpolator.append(x_append, y_append);

    SECTION("existing values should be looked up correctly")
    {
        for (unsigned int i = 0; i < x.size(); ++i)
            REQUIRE(interpolator.interpolate(x[i]) == Approx(y[i]));

        REQUIRE(interpolator.interpolate(x_append) == y_append);
    }

    SECTION("preset values should be interpolated correctly")
    {
        CHECK(interpolator.interpolate(-7.5) == Approx(0.2684859155));
        CHECK(interpolator.interpolate(-2.6) == Approx(0.5509550555));
        CHECK(interpolator.interpolate(3.0) == Approx(0.5808823529));

        CHECK(interpolator.interpolate(8) == Approx(-1. / 3.));
        CHECK(interpolator.interpolate(9.0) == Approx(-1. / 2.));
        CHECK(interpolator.interpolate(10) == Approx(-2. / 3.));
    }

    SECTION("preset value vectors should be interpolated correctly")
    {
        std::vector<double> targets_x  = { -7.5, -2.6, 3.0, 8, 9.0, 10 };
        std::vector<double> expected_y = { 0.2684859155, 0.5509550555, 0.5808823529,
                                           -1. / 3.,     -1. / 2.,     -2. / 3. };

        auto comp_y = interpolator.interpolate(targets_x);
        for (unsigned int i = 0; i < targets_x.size(); ++i)
            REQUIRE(comp_y[i] == Approx(expected_y[i]));
    }

    SECTION("extrapolation mode should cause:")
    {
        for (auto mode : vectorinterpolators::t_extr_mode_all)
        {
            interpolator.set_extrapolation_mode(mode);

            switch (mode)
            {
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
                    CHECK(interpolator.interpolate(-100) == Approx(28.0618464789));
                    CHECK(interpolator.interpolate(100) == Approx(-15 - 2 / 3.));

                    break;
            }
        }
    }
}