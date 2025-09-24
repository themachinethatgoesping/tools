// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <boost/algorithm/algorithm.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <chrono>

#include <themachinethatgoesping/tools/vectorinterpolators/nearestinterpolator.hpp>

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::tools;

#define TESTTAG "[vectorinterpolators]"

TEST_CASE("NearestInterpolator: should perform basic interpolations correctly", TESTTAG)
{
    // initialize test data
    std::vector<double> x        = { -10, -5, 0, 6 };
    std::vector<double> y        = { 1, 0, 1, 0 };
    double              x_append = 12;
    double              y_append = -1;

    vectorinterpolators::NearestInterpolator interpolator(x, y);

    // hashing should stay stable
    REQUIRE(interpolator.binary_hash() == 14894304295739877660ULL);

    // append some data
    interpolator.append(x_append, y_append);
    REQUIRE(interpolator.binary_hash() == 10074301266414863605ULL);

    SECTION("existing values should be looked up correctly")
    {
        for (unsigned int i = 0; i < x.size(); ++i)
            REQUIRE(interpolator(x[i]) == Catch::Approx(y[i]));

        REQUIRE(interpolator(x_append) == Catch::Approx(y_append));
    }
    REQUIRE(interpolator.binary_hash() ==
            10074301266414863605ULL); // lookup should not change the hash

    SECTION("const interpolation should produce the same results as classic interpolation")
    {
        for (double x_val = -10; x_val <= 12; x_val += 0.1)
            REQUIRE(interpolator(x_val) == Catch::Approx(interpolator.get_y(x_val)));
    }
    REQUIRE(interpolator.binary_hash() ==
            10074301266414863605ULL); // lookup should not change the hash

    SECTION("preset values should be interpolated correctly")
    {

        REQUIRE(interpolator(-7.6) == Catch::Approx(1));
        REQUIRE(interpolator(-7.5) == Catch::Approx(0));
        REQUIRE(interpolator(-7.4) == Catch::Approx(0));

        REQUIRE(interpolator(-2.6) == Catch::Approx(0));
        REQUIRE(interpolator(-2.5) == Catch::Approx(1));
        REQUIRE(interpolator(-2.4) == Catch::Approx(1));

        REQUIRE(interpolator(2.9) == Catch::Approx(1));
        REQUIRE(interpolator(3.0) == Catch::Approx(0));
        REQUIRE(interpolator(3.1) == Catch::Approx(0));

        REQUIRE(interpolator(8.9) == Catch::Approx(0));
        REQUIRE(interpolator(9.0) == Catch::Approx(-1));
        REQUIRE(interpolator(9.1) == Catch::Approx(-1));
    }
    REQUIRE(interpolator.binary_hash() ==
            10074301266414863605ULL); // lookup should not change the hash

    SECTION("preset value vectors should be interpolated correctly")
    {
        std::vector<double> targets_x  = { -2.6, -2.5, -2.4 };
        std::vector<double> expected_y = { 0, 1, 1 };

        REQUIRE(interpolator(targets_x) == expected_y);
    }
    REQUIRE(interpolator.binary_hash() ==
            10074301266414863605ULL); // lookup should not change the hash

    SECTION("extrapolation mode should cause:")
    {
        for (auto mode : vectorinterpolators::o_extr_mode::values())
        {
            interpolator.set_extrapolation_mode(mode);

            switch (mode)
            {
                case vectorinterpolators::t_extr_mode::fail:
                    SECTION(" - fail when set to fail")
                    {
                        REQUIRE_THROWS_AS(interpolator(-11), std::out_of_range);
                        REQUIRE_THROWS_AS(interpolator(13), std::out_of_range);
                        REQUIRE_THROWS_AS(interpolator.get_y(-11), std::out_of_range);
                        REQUIRE_THROWS_AS(interpolator.get_y(13), std::out_of_range);
                    }
                    break;

                default:
                    SECTION(" - nearest extrapolation in all other cases")
                    REQUIRE(interpolator(-11) == Catch::Approx(1));
                    REQUIRE(interpolator(13) == Catch::Approx(y_append));
                    REQUIRE(interpolator.get_y(-11) == Catch::Approx(1));
                    REQUIRE(interpolator.get_y(13) == Catch::Approx(y_append));
                    break;
            }
        }
    }
}