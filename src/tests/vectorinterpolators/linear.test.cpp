// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <boost/algorithm/algorithm.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <chrono>

#include "../../themachinethatgoesping/tools/vectorinterpolators.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::tools;

#define TESTTAG "[vectorinterpolators]"

TEST_CASE("LinearInterpolator: should perform basic interpolations correctly", TESTTAG)
{
    // initialize test data
    std::vector<double> x        = { -10, -5, 0, 6 };
    std::vector<double> y        = { 1, 0, 1, 0 };
    double              x_append = 12;
    double              y_append = -1;

    INFO("Peter 0");
    vectorinterpolators::LinearInterpolator interpolator(x, y);

    // append some data
    interpolator.append(x_append, y_append);

    INFO("Peter 1");
    SECTION("existing values should be looked up correctly")
    {
        for (unsigned int i = 0; i < x.size(); ++i)
            REQUIRE(interpolator(x[i]) == Catch::Approx(y[i]));

        REQUIRE(interpolator(x_append) == Catch::Approx(y_append));
    }

    INFO("Peter 2");
    SECTION("const interpolation should produce the same results as classic interpolation")
    {
        for (double x_val = -10; x_val <= 12; x_val += 0.1)
            REQUIRE(interpolator(x_val) == Catch::Approx(interpolator.get_y_const(x_val)));
    }

    INFO("Peter 3");
    SECTION("preset values should be interpolated correctly")
    {
        CHECK(interpolator(-7.6) == Catch::Approx(0.52));
        CHECK(interpolator(-7.5) == Catch::Approx(0.5));
        CHECK(interpolator(-7.4) == Catch::Approx(0.48));

        CHECK(interpolator(-2.6) == Catch::Approx(0.48));
        CHECK(interpolator(-2.5) == Catch::Approx(0.5));
        CHECK(interpolator(-2.4) == Catch::Approx(0.52));

        CHECK(interpolator(2) == Catch::Approx(2. / 3.));
        CHECK(interpolator(3.0) == Catch::Approx(1. / 2.));
        CHECK(interpolator(4) == Catch::Approx(1. / 3.));

        CHECK(interpolator(8) == Catch::Approx(-1. / 3.));
        CHECK(interpolator(9.0) == Catch::Approx(-1. / 2.));
        CHECK(interpolator(10) == Catch::Approx(-2. / 3.));
    }

    INFO("Peter 4");
    SECTION("preset value vectors should be interpolated correctly")
    {
        std::vector<double> targets_x  = { -2.6, -2.5, -2.4 };
        std::vector<double> expected_y = { 0.48, 0.5, 0.52 };

        REQUIRE(interpolator(targets_x) == expected_y);
    }

    INFO("Peter 5");
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
                        INFO("Peter 6 1");
                        REQUIRE_THROWS_AS(interpolator(-11), std::out_of_range);
                        REQUIRE_THROWS_AS(interpolator(13), std::out_of_range);
                        REQUIRE_THROWS_AS(interpolator.get_y_const(-11), std::out_of_range);
                        REQUIRE_THROWS_AS(interpolator.get_y_const(13), std::out_of_range);

                        INFO("Peter 6 2");
                    }
                    break;

                case vectorinterpolators::t_extr_mode::nearest:
                    SECTION(" - extrapolate nearest when set")
                    {
                        return; // test 8
                        INFO("Peter 6 3");
                        REQUIRE(interpolator(-11) == Catch::Approx(1));
                        REQUIRE(interpolator(13) == Catch::Approx(y_append));
                        REQUIRE(interpolator.get_y_const(-11) == Catch::Approx(1));
                        REQUIRE(interpolator.get_y_const(13) == Catch::Approx(y_append));
                        INFO("Peter 6 4");
                    }
                    break;

                default:
                        return; // test 8
                    INFO("Peter 6 5");
                    SECTION(" - extrapolation in all other cases")
                    REQUIRE(interpolator(-11) == Catch::Approx(1.2));
                    REQUIRE(interpolator(14) == Catch::Approx(-4 / 3.));
                    REQUIRE(interpolator.get_y_const(-11) == Catch::Approx(1.2));
                    REQUIRE(interpolator.get_y_const(14) == Catch::Approx(-4 / 3.));
                    INFO("Peter 6 6");

                    break;
            }
        }
    }
}