// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <boost/algorithm/algorithm.hpp>
#include <boost/random.hpp>
#include <chrono>

#include "../../themachinethatgoesping/tools/rotationfunctions/quaternions.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::tools;

#define TESTTAG "[rotationfunctions]"

// conversions
static const double to_rad     = M_PI / 180;
// static const double to_degrees = 1 / to_rad;

TEST_CASE("rotationfunctions: quaternion / ypr conversion", TESTTAG)
{
    SECTION("quaternion / ypr conversion should be reversible when within specified ranges")
    {
        // random generator. Use fixed seed to ensure repeatable results
        boost::random::mt19937 gen(123456);

        boost::random::uniform_real_distribution<double> yaw_dist(0., 360);
        boost::random::uniform_real_distribution<double> pitch_dist(-90., 90.);
        boost::random::uniform_real_distribution<double> roll_dist(-180., 180);

        for (unsigned int i = 0; i < 1000; ++i)
        {
            auto yaw   = yaw_dist(gen);
            auto pitch = pitch_dist(gen);
            auto roll  = roll_dist(gen);

            std::array<double, 3> test = { yaw, pitch, roll };

            auto q1 = rotationfunctions::quaternion_from_ypr(yaw, pitch, roll);
            auto q2 = rotationfunctions::quaternion_from_ypr(test);

            REQUIRE(rotationfunctions::ypr_from_quaternion(q1) ==
                    rotationfunctions::ypr_from_quaternion(q2));
        }
    }

    SECTION("quaternion / ypr conversion should place yaw pitch and roll into defined limiets")
    {
        std::vector<std::pair<std::array<double, 3>, std::array<double, 3>>> YPR = {
            {{ -720., 0., -720. },      { 0., 0., 0. }       }, // 0
            { { -540., -90., -540. },
             { 180., -90., -180. }                           }, // 1 //edge case -90 pitch is not handled well due to
  // quaternion conversion
            { { -360., 80., -360. },    { 0., 80., 0. }      }, // 2
            { { -270., -40., -270. },   { 90., -40., 90. }   }, // 3
            { { -180., 30., -180. },    { 180., 30., -180. } }, // 4
            { { -90., -30., -90. },     { 270., -30., -90. } }, // 5
            { { -45., -45., -45. },     { 315., -45., -45. } }, // 6
            { { 0., 0., 0. },           { 0., 0., 0. }       }, // 7
            { { 45., 45., 45. },        { 45., 45., 45. }    }, // 8
            { { 90., 80., 90. },        { 90., 80., 90. }    }, // 9
            { { 135., -80., 135. },     { 135., -80., 135. } }, // 10
            { { 180., 80., 180. },      { 180., 80., -180. } }, // 11
            { { 225., -89.9999, 225. },
             { 225., -89.9999, -135. }                       }, // 12 //edge case -90 pitch is not handled well due to
  // quaternion conversion
            { { 270., 89.9999, 270. },
             { 270., 89.9999, -90. }                         }, // 13 //edge case -90 pitch is not handled well due to
  // quaternion conversion
            { { 360., 0., 360. },       { 0., 0., 0. }       }, // 14
  // --- section for pitch larger 90
            { { 45., 100., 45. },       { 225., 80., -135. } }, // 15
            { { 45., -100., 45. },      { 225., -80., -135. }}, // 16
            { { 90., 120., 90. },       { 270., 60., -90. }  }, // 17
            { { -45., -120., -45. },    { 135., -60., 135. } }, // 18
            { { 456., 789., 456. },     { 96., 69., 96. }    }, // 19
            { { -456., -789., -456. },  { 264., -69., -96. } }, // 20
            { { -90., -300., -90. },    { 270., 60., -90. }  }, // 21
            { { -90., 300., -90. },     { 270., -60., -90. } }, // 22
            { { -90., -100., -90. },    { 90., -80., 90. }   }, // 23
            { { -90., 100., -90. },     { 90., 80., 90. }    }  // 24
        };

        for (unsigned int c = 0; c < YPR.size(); ++c)
        {
            auto ypr = YPR[c].first;
            auto e   = YPR[c].second;

            auto ypr_new =
                rotationfunctions::ypr_from_quaternion(rotationfunctions::quaternion_from_ypr(ypr));

            for (unsigned int i = 0; i < 3; ++i)
            {
                INFO("value: " << c << '/' << i << " / " << ypr[i] << " / " << ypr_new[i] << " / "
                               << e[i]);
                CHECK(ypr_new[i] == Approx(e[i]).scale(1));
            }
        }
    }

    SECTION("vectorized calls should produce the same results as single calls")
    {
        // degrees means: values are converted to/from degrees or not
        for (bool degrees : { true, false })
        {

            // random generator. Use fixed seed to ensure repeatable results
            boost::random::mt19937 gen(1234567);

            boost::random::uniform_real_distribution<double> yaw_dist(-1000., 1000);
            boost::random::uniform_real_distribution<double> pitch_dist(-1000., 1000.);
            boost::random::uniform_real_distribution<double> roll_dist(-1000., 1000);

            std::vector<std::array<double, 3>> YPR;
            std::vector<double>                Y, P, R;
            for (unsigned int i = 0; i < 1000; ++i)
            {
                auto yaw   = yaw_dist(gen);
                auto pitch = pitch_dist(gen);
                auto roll  = roll_dist(gen);

                YPR.push_back({ yaw, pitch, roll });
                Y.push_back(yaw);
                P.push_back(pitch);
                R.push_back(roll);
            }

            auto Q1          = rotationfunctions::quaternion_from_ypr(YPR, degrees);
            auto Q2          = rotationfunctions::quaternion_from_ypr(Y, P, R, degrees);
            auto YPR_result1 = rotationfunctions::ypr_from_quaternion(Q1, degrees);
            auto YPR_result2 = rotationfunctions::ypr_from_quaternion(Q2, degrees);

            for (unsigned int c = 0; c < YPR.size(); ++c)
            {
                auto q   = rotationfunctions::quaternion_from_ypr(YPR[c], degrees);
                auto ypr = rotationfunctions::ypr_from_quaternion(q, degrees);

                CHECK(Q1[c] == q);
                CHECK(Q2[c] == q);
                for (unsigned int i = 0; i < 3; ++i)
                {
                    INFO("degrees = " << degrees);
                    CHECK(YPR_result1[c][i] == Approx(ypr[i]));
                    CHECK(YPR_result2[c][i] == Approx(ypr[i]));
                }
            }
        }
    }
}
