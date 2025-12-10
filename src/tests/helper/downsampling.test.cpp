// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cmath>
#include <limits>
#include <vector>

#include <xtensor/containers/xtensor.hpp>

#include "../themachinethatgoesping/tools/helper/downsampling.hpp"

using namespace std;
using namespace themachinethatgoesping::tools::helper;

#define TESTTAG "[downsampling]"

TEST_CASE("get_index_downsampling: empty container", TESTTAG)
{
    std::vector<double> empty_vec;
    auto                result = get_index_downsampling(empty_vec, 1.0, -1.0);
    REQUIRE(result.size() == 0);
}

TEST_CASE("get_index_downsampling: single element", TESTTAG)
{
    std::vector<double> single_vec = { 0.0 };
    auto                result     = get_index_downsampling(single_vec, 1.0, -1.0);
    REQUIRE(result.size() == 1);
    REQUIRE(result(0) == 0);
}

TEST_CASE("get_index_downsampling: no downsampling with 0", TESTTAG)
{
    std::vector<double> data = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5 };

    // Use 0 downsample_interval to return all data
    auto result = get_index_downsampling(data, 0.0, -1.0);
    REQUIRE(result.size() == 6);
    for (size_t i = 0; i < 6; ++i)
    {
        REQUIRE(result(i) == i);
    }
}

TEST_CASE("get_index_downsampling: no downsampling with NaN", TESTTAG)
{
    std::vector<double> data = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5 };

    // Use NaN downsample_interval to return all data
    auto result = get_index_downsampling(data, std::numeric_limits<double>::quiet_NaN(), -1.0);
    REQUIRE(result.size() == 6);
    for (size_t i = 0; i < 6; ++i)
    {
        REQUIRE(result(i) == i);
    }
}

TEST_CASE("get_index_downsampling: no downsampling with negative", TESTTAG)
{
    std::vector<double> data = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5 };

    // Use negative downsample_interval to return all data
    auto result = get_index_downsampling(data, -1.0, -1.0);
    REQUIRE(result.size() == 6);
    for (size_t i = 0; i < 6; ++i)
    {
        REQUIRE(result(i) == i);
    }
}

TEST_CASE("get_index_downsampling: regular downsampling", TESTTAG)
{
    // Data at 0.1s intervals from 0 to 1.0
    std::vector<double> data;
    for (double t = 0.0; t <= 1.0; t += 0.1)
    {
        data.push_back(t);
    }

    // Downsample at 0.25 intervals
    auto result = get_index_downsampling(data, 0.25, -1.0);

    // Expected: 0.0, 0.3, 0.6, 0.9 (indices 0, 3, 6, 9)
    // Actually we select first, then any >= first + 0.25, etc.
    REQUIRE(result.size() >= 4);
    REQUIRE(result(0) == 0);                                           // 0.0
    REQUIRE(data[result(1)] >= data[result(0)] + 0.25 - 0.01);

    // Verify all selected data values are at least downsample_interval apart
    for (size_t i = 1; i < result.size(); ++i)
    {
        double diff = data[result(i)] - data[result(i - 1)];
        REQUIRE(diff >= 0.25 - 0.01); // Allow small floating point tolerance
    }
}

TEST_CASE("get_index_downsampling: gap detection", TESTTAG)
{
    // Data with a 5-second gap in the middle
    std::vector<double> data = { 0.0, 0.1, 0.2, 0.3, 0.4,     // First segment
                                 5.5, 5.6, 5.7, 5.8, 5.9 }; // Second segment after gap

    // Downsample at 0.25, with max_gap of 1.0
    auto result = get_index_downsampling(data, 0.25, 1.0);

    // Should have samples from both segments
    REQUIRE(result.size() >= 4);

    // First index should be 0
    REQUIRE(result(0) == 0);

    // After the gap, sampling should restart
    // The gap is between index 4 (0.4) and index 5 (5.5)
    // So index 5 should be in the result
    bool found_post_gap = false;
    for (size_t i = 0; i < result.size(); ++i)
    {
        if (result(i) == 5)
        {
            found_post_gap = true;
            break;
        }
    }
    REQUIRE(found_post_gap);
}

TEST_CASE("get_index_downsampling: gap exactly at boundary", TESTTAG)
{
    // Gap exactly at max_gap should not trigger restart
    std::vector<double> data = { 0.0, 1.0, 2.0, 3.0 };

    auto result = get_index_downsampling(data, 0.5, 1.0);

    // All should be included since gaps are exactly 1.0 (not > 1.0)
    REQUIRE(result.size() == 4);
}

TEST_CASE("get_index_downsampling: with std::vector<float>", TESTTAG)
{
    std::vector<float> data = { 0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f };

    auto result = get_index_downsampling(data, 0.25, -1.0);

    REQUIRE(result.size() >= 2);
    REQUIRE(result(0) == 0);
}

TEST_CASE("get_index_downsampling: with xt::xtensor<double, 1>", TESTTAG)
{
    xt::xtensor<double, 1> data = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };

    auto result = get_index_downsampling(data, 0.25, -1.0);

    REQUIRE(result.size() >= 4);
    REQUIRE(result(0) == 0);

    // Verify spacing
    for (size_t i = 1; i < result.size(); ++i)
    {
        double diff = data[result(i)] - data[result(i - 1)];
        REQUIRE(diff >= 0.25 - 0.01);
    }
}

TEST_CASE("get_index_downsampling: with xt::xtensor<float, 1>", TESTTAG)
{
    xt::xtensor<float, 1> data = { 0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f };

    auto result = get_index_downsampling(data, 0.25, -1.0);

    REQUIRE(result.size() >= 2);
    REQUIRE(result(0) == 0);
}

TEST_CASE("get_index_downsampling: default max_gap", TESTTAG)
{
    // Test that default max_gap is 2x downsample_interval
    std::vector<double> data = { 0.0, 0.5, 1.0, 1.5, 4.0, 4.5, 5.0 }; // Gap of 2.5 between
                                                                      // 1.5 and 4.0

    // With downsample_interval=1.0, default max_gap should be 2.0
    // Gap of 2.5 > 2.0 should trigger restart
    auto result = get_index_downsampling(data, 1.0, -1.0);

    // Should restart at index 4 (4.0)
    bool found_restart = false;
    for (size_t i = 1; i < result.size(); ++i)
    {
        if (result(i) == 4)
        {
            found_restart = true;
            break;
        }
    }
    REQUIRE(found_restart);
}

TEST_CASE("get_index_downsampling: large dataset", TESTTAG)
{
    // Create a large dataset
    std::vector<double> data;
    data.reserve(10000);
    for (double t = 0.0; t < 1000.0; t += 0.1)
    {
        data.push_back(t);
    }

    auto result = get_index_downsampling(data, 1.0, -1.0);

    // Should have approximately 1000 samples (one per second)
    REQUIRE(result.size() >= 900);
    REQUIRE(result.size() <= 1100);

    // Verify monotonicity
    for (size_t i = 1; i < result.size(); ++i)
    {
        REQUIRE(result(i) > result(i - 1));
    }
}

TEST_CASE("get_value_downsampling: basic functionality", TESTTAG)
{
    std::vector<double> data = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };

    auto result = get_value_downsampling(data, 0.25, -1.0);

    REQUIRE(result.size() >= 4);
    REQUIRE(result[0] == Catch::Approx(0.0));

    // Verify spacing
    for (size_t i = 1; i < result.size(); ++i)
    {
        double diff = result[i] - result[i - 1];
        REQUIRE(diff >= 0.25 - 0.01);
    }
}

TEST_CASE("get_value_downsampling: returns all with 0 interval", TESTTAG)
{
    std::vector<double> data = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5 };

    auto result = get_value_downsampling(data, 0.0, -1.0);

    REQUIRE(result.size() == 6);
    for (size_t i = 0; i < 6; ++i)
    {
        REQUIRE(result[i] == Catch::Approx(data[i]));
    }
}

TEST_CASE("get_value_downsampling: returns all with NaN interval", TESTTAG)
{
    std::vector<double> data = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5 };

    auto result = get_value_downsampling(data, std::numeric_limits<double>::quiet_NaN(), -1.0);

    REQUIRE(result.size() == 6);
    for (size_t i = 0; i < 6; ++i)
    {
        REQUIRE(result[i] == Catch::Approx(data[i]));
    }
}

TEST_CASE("get_value_downsampling: with xtensor", TESTTAG)
{
    xt::xtensor<double, 1> data = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };

    auto result = get_value_downsampling(data, 0.25, -1.0);

    REQUIRE(result.size() >= 4);
    REQUIRE(result[0] == Catch::Approx(0.0));
}
