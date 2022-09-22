// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <boost/algorithm/algorithm.hpp>
#include <boost/random.hpp>
#include <chrono>

#include "../../themachinethatgoesping/tools/rotationfunctions/quaternions.hpp"
#include "../../themachinethatgoesping/tools/vectorinterpolators.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::tools;

#define TESTTAG "[vectorinterpolators]"

static const double to_degrees = 180. / M_PI;
static const double to_rad     = 1 / to_degrees;

TEST_CASE(
    "SlerpInterpolator: overloaded functions and vector calls should produce the same results",
    TESTTAG)
{
    // random distributions with fixed seed
    boost::random::mt19937 gen(1234567);

    boost::random::uniform_real_distribution<double> dist(-1000., 500);
    boost::random::uniform_real_distribution<double> dist1(501., 1000);
    boost::random::uniform_real_distribution<double> dist2(-1500., 1500);

    // create random data vectors
    std::vector<double>                x, x2, y, p, r, y_r, p_r, r_r;
    std::vector<std::array<double, 3>> ypr, ypr_r;
    for (unsigned int i = 0; i < 100; ++i)
    {
        auto x_  = dist(gen);  // x
        auto x2_ = dist1(gen); // x2 (>x) used for append and extend
        auto y_  = dist(gen);
        auto p_  = dist(gen);
        auto r_  = dist(gen);

        x.push_back(x_);
        x2.push_back(x2_);
        y.push_back(y_);
        p.push_back(p_);
        r.push_back(r_);
        ypr.push_back({ y_, p_, r_ });

        y_r.push_back(y_ * to_rad);
        p_r.push_back(p_ * to_rad);
        r_r.push_back(r_ * to_rad);
        ypr_r.push_back({ y_ * to_rad, p_ * to_rad, r_ * to_rad });
    }

    // sort by x (otherwise will throw exception)
    sort(x.begin(), x.end());
    sort(x2.begin(), x2.end());

    // create interpolator clases using different methods
    // input in degrees
    vectorinterpolators::SlerpInterpolator i1(x, y, p, r);
    vectorinterpolators::SlerpInterpolator i2(x, ypr);
    // input in rad
    vectorinterpolators::SlerpInterpolator i3(x, y_r, p_r, r_r, false);
    vectorinterpolators::SlerpInterpolator i4(x, ypr_r, false);

    // interpolator classes that will be appended and extended
    vectorinterpolators::SlerpInterpolator ia1(x, y, p, r);
    vectorinterpolators::SlerpInterpolator ia2(x, y, p, r);
    vectorinterpolators::SlerpInterpolator ia3(x, y_r, p_r, r_r, false);
    vectorinterpolators::SlerpInterpolator ia4(x, y_r, p_r, r_r, false);
    vectorinterpolators::SlerpInterpolator ie1(x, y, p, r);
    vectorinterpolators::SlerpInterpolator ie2(x, y, p, r);
    vectorinterpolators::SlerpInterpolator ie3(x, y_r, p_r, r_r, false);
    vectorinterpolators::SlerpInterpolator ie4(x, y_r, p_r, r_r, false);

    // append and extend some of the interpolator classes using different methods
    for (unsigned int i = 0; i < x2.size(); ++i)
    {
        ia1.append(x2[i], y[i], p[i], r[i]);
        ia2.append(x2[i], ypr[i]);
        ia3.append(x2[i], y_r[i], p_r[i], r_r[i], false);
        ia4.append(x2[i], ypr_r[i], false);
    }
    ie1.extend(x2, y, p, r);
    ie2.extend(x2, ypr);
    ie3.extend(x2, y_r, p_r, r_r, false);
    ie4.extend(x2, ypr_r, false);

    // create structure to hold vector (to test vectorized return methods)
    std::vector<double>                x_targets;
    std::vector<std::array<double, 3>> y_results, y_r_results;

    // compare interpolation results for random target xs (single function calls)
    for (unsigned int j = 0; j < 100; ++j)
    {
        auto x_target = dist2(gen);

        auto y1 = i1.ypr(x_target);
        auto y2 = i2.ypr(x_target);
        auto y3 = i3.ypr(x_target);
        auto y4 = i4.ypr(x_target);

        auto y1_e = ia1.ypr(x_target);
        auto y2_e = ia2.ypr(x_target);
        auto y3_e = ia3.ypr(x_target);
        auto y4_e = ia4.ypr(x_target);
        auto y5_e = ie1.ypr(x_target);
        auto y6_e = ie2.ypr(x_target);
        auto y7_e = ie3.ypr(x_target);
        auto y8_e = ie4.ypr(x_target);

        auto y1_r = i1.ypr(x_target, false);
        auto y2_r = i2.ypr(x_target, false);
        auto y3_r = i3.ypr(x_target, false);
        auto y4_r = i4.ypr(x_target, false);

        // push results into vectors for next comparrison
        x_targets.push_back(x_target);
        y_results.push_back(y1);
        y_r_results.push_back(y1_r);

        // test if all interpolators yield the same results
        for (unsigned int i = 0; i < y1.size(); ++i)
        {
            // default interpolators [returned degrees]
            REQUIRE(y2[i] == Approx(y1[i]));
            REQUIRE(y3[i] == Approx(y1[i]));
            REQUIRE(y4[i] == Approx(y1[i]));

            // default interpolators [returned rad]
            REQUIRE(y1_r[i] == Approx(y2_r[i]));
            REQUIRE(y2_r[i] == Approx(y3_r[i]));
            REQUIRE(y3_r[i] == Approx(y4_r[i]));

            // appended and extended interpolators
            REQUIRE(y2_e[i] == Approx(y1_e[i]));
            REQUIRE(y3_e[i] == Approx(y1_e[i]));
            REQUIRE(y4_e[i] == Approx(y1_e[i]));
            REQUIRE(y5_e[i] == Approx(y1_e[i]));
            REQUIRE(y6_e[i] == Approx(y1_e[i]));
            REQUIRE(y7_e[i] == Approx(y1_e[i]));
            REQUIRE(y8_e[i] == Approx(y1_e[i]));
        }
    }

    // test if vectorized call produces the same results as single call
    auto y1   = i1.ypr(x_targets);
    auto y1_r = i1.ypr(x_targets, false);

    for (unsigned int j = 0; j < x_targets.size(); ++j)
    {
        for (unsigned int i = 0; i < y1[j].size(); ++i)
        {
            REQUIRE(y_results[j][i] == Approx(y1[j][i]));
            REQUIRE(y_r_results[j][i] == Approx(y1_r[j][i]));
        }
    }
}

TEST_CASE("SlerpInterpolator: should perform basic interpolations correctly", TESTTAG)
{
    // initialize test data
    std::vector<double>   x          = { -10, -5, 0, 6 };
    std::vector<double>   y          = { 0, 45, 100, 300 };
    std::vector<double>   p          = { 0, 45, -45, 80 };
    std::vector<double>   r          = { -180, 45, 0, 170 };
    double                x_append   = 12;
    std::array<double, 3> ypr_append = { 350, -80, -170 };

    vectorinterpolators::SlerpInterpolator interpolator(x, y, p, r);

    // append some data
    interpolator.append(x_append, ypr_append);

    SECTION("existing values should be looked up correctly (if )")
    {
        for (unsigned int i = 0; i < x.size(); ++i)
        {
            auto ypr = interpolator.ypr(x[i]);
            REQUIRE(ypr[0] == Approx(y[i]));
            REQUIRE(ypr[1] == Approx(p[i]));
            REQUIRE(ypr[2] == Approx(r[i]));
        }

        {
            auto ypr = interpolator.ypr(x_append);
            CHECK(ypr[0] == Approx(ypr_append[0]));
            CHECK(ypr[1] == Approx(ypr_append[1]));
            CHECK(ypr[2] == Approx(ypr_append[2]));
        }
    }

    SECTION("preset values should be interpolated correctly")
    {
        auto ypr_1 = interpolator.ypr(-3);
        auto ypr_2 = interpolator.ypr(9);

        REQUIRE(ypr_1[0] == Approx(58.5679194066));
        REQUIRE(ypr_1[1] == Approx(5.0841237338));
        REQUIRE(ypr_1[2] == Approx(37.6730325392));

        REQUIRE(ypr_2[0] == Approx(333.5151692017));
        REQUIRE(ypr_2[1] == Approx(0.632182955));
        REQUIRE(ypr_2[2] == Approx(-158.8770719663));
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
                        REQUIRE_THROWS_AS(interpolator(-11), std::out_of_range);
                        REQUIRE_THROWS_AS(interpolator(13), std::out_of_range);
                    }
                    break;

                case vectorinterpolators::t_extr_mode::nearest:
                    SECTION(" - extrapolate nearest when set")
                    {
                        auto too_small_ypr = interpolator.ypr(-11);
                        auto too_large_ypr = interpolator.ypr(13);

                        REQUIRE(too_small_ypr[0] == Approx(y[0]));
                        REQUIRE(too_small_ypr[1] == Approx(p[0]));
                        REQUIRE(too_small_ypr[2] == Approx(r[0]));

                        REQUIRE(too_large_ypr[0] == Approx(ypr_append[0]));
                        REQUIRE(too_large_ypr[1] == Approx(ypr_append[1]));
                        REQUIRE(too_large_ypr[2] == Approx(ypr_append[2]));
                    }
                    break;

                default:
                    SECTION(" - extrapolation in all other cases")
                    {
                        auto too_small_ypr = interpolator.ypr(-11);
                        auto too_large_ypr = interpolator.ypr(13);

                        REQUIRE(too_small_ypr[0] == Approx(347.01848882));
                        REQUIRE(too_small_ypr[1] == Approx(9.3296836006));
                        REQUIRE(too_small_ypr[2] == Approx(-153.7039370777));

                        REQUIRE(too_large_ypr[0] == Approx(147.0971139354));
                        REQUIRE(too_large_ypr[1] == Approx(-72.4669510216));
                        REQUIRE(too_large_ypr[2] == Approx(34.2739577346));
                    }

                    break;
            }
        }
    }
}