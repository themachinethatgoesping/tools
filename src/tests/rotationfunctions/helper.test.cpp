// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <boost/algorithm/algorithm.hpp>
#include <boost/random.hpp>
#include <chrono>
#include <fmt/core.h>
#include <numbers>

#include "../../themachinethatgoesping/tools/rotationfunctions/quaternions.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::tools;

#define TESTTAG "[rotationfunctions]"

// conversions
static const float to_rad     = std::numbers::pi / 180.;
static const float to_degrees = 1 / to_rad;

TEST_CASE("compute_heading should return correct heading", TESTTAG)
{
    // degrees
    REQUIRE(rotationfunctions::compute_heading(0., 0.) == Catch::Approx(0.));     // edge case
    REQUIRE(rotationfunctions::compute_heading(1., 0.) == Catch::Approx(0.));     // north
    REQUIRE(rotationfunctions::compute_heading(1., 1.) == Catch::Approx(45.));    // north east
    REQUIRE(rotationfunctions::compute_heading(0., 1.) == Catch::Approx(90.));    // east
    REQUIRE(rotationfunctions::compute_heading(-1., 1.) == Catch::Approx(135.));  // south east
    REQUIRE(rotationfunctions::compute_heading(-1., 0.) == Catch::Approx(180.));  // south
    REQUIRE(rotationfunctions::compute_heading(-1., -1.) == Catch::Approx(225.)); // south west
    REQUIRE(rotationfunctions::compute_heading(0., -1.) == Catch::Approx(270.));  // west
    REQUIRE(rotationfunctions::compute_heading(1., -1.) == Catch::Approx(315.));  // north west

    // radians
    REQUIRE(rotationfunctions::compute_heading(0., 0., true) == Catch::Approx(0.)); // edge case
    REQUIRE(rotationfunctions::compute_heading(1., 0., true) == Catch::Approx(0.)); // north
    REQUIRE(rotationfunctions::compute_heading(1., 1., true) ==
            Catch::Approx(std::numbers::pi / 4)); // north east
    REQUIRE(rotationfunctions::compute_heading(0., 1., true) == Catch::Approx(std::numbers::pi / 2)); // east
    REQUIRE(rotationfunctions::compute_heading(-1., 1., true) ==
            Catch::Approx(std::numbers::pi * 3 / 4));                                              // south east
    REQUIRE(rotationfunctions::compute_heading(-1., 0., true) == Catch::Approx(std::numbers::pi)); // south
    REQUIRE(rotationfunctions::compute_heading(-1., -1., true) ==
            Catch::Approx(std::numbers::pi * 5 / 4)); // south west
    REQUIRE(rotationfunctions::compute_heading(0., -1., true) ==
            Catch::Approx(std::numbers::pi * 6 / 4)); // west
    REQUIRE(rotationfunctions::compute_heading(1., -1., true) ==
            Catch::Approx(std::numbers::pi * 7 / 4)); // north west
}

TEST_CASE("normalize_angles", TESTTAG)
{
    SECTION("normalize_angles_rad and normalize_angles_degrees should produce the same results")
    {
        // random generator. Use fixed seed to ensure repeatable results
        boost::random::mt19937 gen(1234567);

        boost::random::uniform_real_distribution<float> yaw_dist(-1000., 1000);
        boost::random::uniform_real_distribution<float> pitch_dist(-1000., 1000.);
        boost::random::uniform_real_distribution<float> roll_dist(-1000., 1000);

        for (unsigned int c = 0; c < 1000; ++c)
        {
            auto yaw   = yaw_dist(gen);
            auto pitch = pitch_dist(gen);
            auto roll  = roll_dist(gen);

            std::array<float, 3> ypr_deg = { yaw, pitch, roll };
            std::array<float, 3> ypr_rad = { to_rad * yaw, to_rad * pitch, to_rad * roll };

            auto ypr_deg_result = rotationfunctions::normalize_angles_degrees(ypr_deg);
            auto ypr_rad_result = rotationfunctions::normalize_angles_rad<float>(ypr_rad);

            for (unsigned int i = 0; i < 3; ++i)
            {
                INFO(fmt::format("i {} y {} p {} r {}", i, yaw, pitch, roll));
                REQUIRE_THAT(
                    ypr_deg_result[i],
                    Catch::Matchers::WithinAbs(ypr_rad_result[i] * to_degrees, 0.001));
            }
        }
    }

    SECTION("normalize_angles should place yaw pitch and roll into defined limits")
    {
        std::vector<std::pair<std::array<double, 3>, std::array<double, 3>>> YPR = {
            { { -720., 0., -720. }, { 0., 0., 0. } },          // 0
            { { -540., -90., -540. }, { 180., -90., -180. } }, // 1
            { { -360., 80., -360. }, { 0., 80., 0. } },        // 2
            { { -270., -40., -270. }, { 90., -40., 90. } },    // 3
            { { -180., 30., -180. }, { 180., 30., -180. } },   // 4
            { { -90., -30., -90. }, { 270., -30., -90. } },    // 5
            { { -45., -45., -45. }, { 315., -45., -45. } },    // 6
            { { 0., 0., 0. }, { 0., 0., 0. } },                // 7
            { { 45., 45., 45. }, { 45., 45., 45. } },          // 8
            { { 90., 80., 90. }, { 90., 80., 90. } },          // 9
            { { 135., -80., 135. }, { 135., -80., 135. } },    // 10
            { { 180., 80., 180. }, { 180., 80., -180. } },     // 11
            { { 225., -90, 225. }, { 225., -90, -135. } },     // 12
            { { 270., 90, 270. }, { 270., 90, -90. } },        // 13
            { { 360., 0., 360. }, { 0., 0., 0. } },            // 14
                                                               // --- section for pitch larger 90
            { { 45., 100., 45. }, { 225., 80., -135. } },      // 15
            { { 45., -100., 45. }, { 225., -80., -135. } },    // 16
            { { 90., 120., 90. }, { 270., 60., -90. } },       // 17
            { { -45., -120., -45. }, { 135., -60., 135. } },   //, // 18
            { { 456., 789., 456. }, { 96., 69., 96. } },       // 19
            { { -456., -789., -456. }, { 264., -69., -96. } }, // 20
            { { -90., -300., -90. }, { 270., 60., -90. } },    // 21
            { { -90., 300., -90. }, { 270., -60., -90. } },    // 22
            { { -90., -100., -90. }, { 90., -80., 90. } },     // 23
            { { -90., 100., -90. }, { 90., 80., 90. } }        // 24
        };

        for (unsigned int c = 0; c < YPR.size(); ++c)
        {
            auto ypr = YPR[c].first;
            auto e   = YPR[c].second;

            auto ypr_new = rotationfunctions::normalize_angles_degrees(ypr);

            for (unsigned int i = 0; i < 3; ++i)
            {
                INFO("value: " << c << '/' << i << " / " << ypr[i] << " / " << ypr_new[i] << " / "
                               << e[i]);
                REQUIRE(ypr_new[i] == Catch::Approx(e[i]).scale(1));
            }
        }
    }
}
