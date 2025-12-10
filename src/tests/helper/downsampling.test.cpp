// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <vector>

#include <xtensor/containers/xtensor.hpp>

#include "../themachinethatgoesping/tools/helper/downsampling.hpp"

using namespace std;
using namespace themachinethatgoesping::tools::helper;

#define TESTTAG "[downsampling]"

TEST_CASE("compute_downsampling_indices: empty container", TESTTAG)
{
    std::vector<double> empty_vec;
    auto                result = compute_downsampling_indices(empty_vec, 1.0, -1.0);
    REQUIRE(result.empty());
    REQUIRE(result.size() == 0);
}

TEST_CASE("compute_downsampling_indices: single element", TESTTAG)
{
    std::vector<double> single_vec = { 0.0 };
    auto                result     = compute_downsampling_indices(single_vec, 1.0, -1.0);
    REQUIRE(result.size() == 1);
    REQUIRE(result.indices[0] == 0);
}

TEST_CASE("compute_downsampling_indices: no downsampling", TESTTAG)
{
    std::vector<double> timestamps = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5 };

    // Use 0 or negative downsample_interval to disable downsampling
    auto result = compute_downsampling_indices(timestamps, 0.0, -1.0);
    REQUIRE(result.size() == 6);
    for (size_t i = 0; i < 6; ++i)
    {
        REQUIRE(result.indices[i] == i);
    }

    result = compute_downsampling_indices(timestamps, -1.0, -1.0);
    REQUIRE(result.size() == 6);
}

TEST_CASE("compute_downsampling_indices: regular downsampling", TESTTAG)
{
    // Timestamps at 0.1s intervals from 0 to 1.0
    std::vector<double> timestamps;
    for (double t = 0.0; t <= 1.0; t += 0.1)
    {
        timestamps.push_back(t);
    }

    // Downsample at 0.25s intervals
    auto result = compute_downsampling_indices(timestamps, 0.25, -1.0);

    // Expected: 0.0, 0.3, 0.6, 0.9 (indices 0, 3, 6, 9)
    // Actually we select first, then any >= first + 0.25, etc.
    REQUIRE(result.size() >= 4);
    REQUIRE(result.indices[0] == 0);                                           // 0.0
    REQUIRE(timestamps[result.indices[1]] >= timestamps[result.indices[0]] + 0.25 - 0.01);

    // Verify all selected timestamps are at least downsample_interval apart
    for (size_t i = 1; i < result.size(); ++i)
    {
        double diff = timestamps[result.indices[i]] - timestamps[result.indices[i - 1]];
        REQUIRE(diff >= 0.25 - 0.01); // Allow small floating point tolerance
    }
}

TEST_CASE("compute_downsampling_indices: gap detection", TESTTAG)
{
    // Timestamps with a 5-second gap in the middle
    std::vector<double> timestamps = { 0.0, 0.1, 0.2, 0.3, 0.4,     // First segment
                                       5.5, 5.6, 5.7, 5.8, 5.9 }; // Second segment after gap

    // Downsample at 0.25s, with max_gap of 1.0s
    auto result = compute_downsampling_indices(timestamps, 0.25, 1.0);

    // Should have samples from both segments
    REQUIRE(result.size() >= 4);

    // First index should be 0
    REQUIRE(result.indices[0] == 0);

    // After the gap, sampling should restart
    // The gap is between index 4 (0.4) and index 5 (5.5)
    // So index 5 should be in the result
    bool found_post_gap = false;
    for (size_t idx : result.indices)
    {
        if (idx == 5)
        {
            found_post_gap = true;
            break;
        }
    }
    REQUIRE(found_post_gap);
}

TEST_CASE("compute_downsampling_indices: gap exactly at boundary", TESTTAG)
{
    // Gap exactly at max_gap should not trigger restart
    std::vector<double> timestamps = { 0.0, 1.0, 2.0, 3.0 };

    auto result = compute_downsampling_indices(timestamps, 0.5, 1.0);

    // All should be included since gaps are exactly 1.0 (not > 1.0)
    REQUIRE(result.size() == 4);
}

TEST_CASE("compute_downsampling_indices: with std::vector<float>", TESTTAG)
{
    std::vector<float> timestamps = { 0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f };

    auto result = compute_downsampling_indices(timestamps, 0.25, -1.0);

    REQUIRE(result.size() >= 2);
    REQUIRE(result.indices[0] == 0);
}

TEST_CASE("compute_downsampling_indices: with xt::xtensor<double, 1>", TESTTAG)
{
    xt::xtensor<double, 1> timestamps = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };

    auto result = compute_downsampling_indices(timestamps, 0.25, -1.0);

    REQUIRE(result.size() >= 4);
    REQUIRE(result.indices[0] == 0);

    // Verify spacing
    for (size_t i = 1; i < result.size(); ++i)
    {
        double diff = timestamps[result.indices[i]] - timestamps[result.indices[i - 1]];
        REQUIRE(diff >= 0.25 - 0.01);
    }
}

TEST_CASE("compute_downsampling_indices: with xt::xtensor<float, 1>", TESTTAG)
{
    xt::xtensor<float, 1> timestamps = { 0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f };

    auto result = compute_downsampling_indices(timestamps, 0.25, -1.0);

    REQUIRE(result.size() >= 2);
    REQUIRE(result.indices[0] == 0);
}

TEST_CASE("compute_downsampling_indices: default max_gap", TESTTAG)
{
    // Test that default max_gap is 2x downsample_interval
    std::vector<double> timestamps = { 0.0, 0.5, 1.0, 1.5, 4.0, 4.5, 5.0 }; // Gap of 2.5s between
                                                                            // 1.5 and 4.0

    // With downsample_interval=1.0, default max_gap should be 2.0
    // Gap of 2.5s > 2.0s should trigger restart
    auto result = compute_downsampling_indices(timestamps, 1.0, -1.0);

    // Should restart at index 4 (4.0)
    bool found_restart = false;
    for (size_t i = 1; i < result.indices.size(); ++i)
    {
        if (result.indices[i] == 4)
        {
            found_restart = true;
            break;
        }
    }
    REQUIRE(found_restart);
}

TEST_CASE("compute_downsampling_indices: large dataset", TESTTAG)
{
    // Create a large dataset
    std::vector<double> timestamps;
    timestamps.reserve(10000);
    for (double t = 0.0; t < 1000.0; t += 0.1)
    {
        timestamps.push_back(t);
    }

    auto result = compute_downsampling_indices(timestamps, 1.0, -1.0);

    // Should have approximately 1000 samples (one per second)
    REQUIRE(result.size() >= 900);
    REQUIRE(result.size() <= 1100);

    // Verify monotonicity
    for (size_t i = 1; i < result.size(); ++i)
    {
        REQUIRE(result.indices[i] > result.indices[i - 1]);
    }
}
