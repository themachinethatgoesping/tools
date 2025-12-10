// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <cmath>
#include <limits>
#include <type_traits>
#include <vector>

#include <xtensor/containers/xtensor.hpp>

#include "../themachinethatgoesping/tools/helper/container_intersection.hpp"

using namespace std;
using namespace themachinethatgoesping::tools::helper;

#define TESTTAG "[container_intersection]"

// ============================================================================
// Range tests
// ============================================================================

TEST_CASE("Range: construction and validity", TESTTAG)
{
    Range<double> r1(0.0, 10.0);
    REQUIRE(r1.min == 0.0);
    REQUIRE(r1.max == 10.0);
    REQUIRE(r1.is_valid());

    Range<double> r2(10.0, 0.0);
    REQUIRE(!r2.is_valid());

    Range<double> r3(5.0, 5.0);
    REQUIRE(r3.is_valid()); // Single point range is valid
}

TEST_CASE("Range: contains", TESTTAG)
{
    Range<double> r(0.0, 10.0);

    REQUIRE(r.contains(0.0));   // Boundary
    REQUIRE(r.contains(5.0));   // Middle
    REQUIRE(r.contains(10.0));  // Boundary
    REQUIRE(!r.contains(-0.1)); // Below
    REQUIRE(!r.contains(10.1)); // Above
}

TEST_CASE("Range: overlaps", TESTTAG)
{
    Range<double> r1(0.0, 10.0);
    Range<double> r2(5.0, 15.0);
    Range<double> r3(20.0, 30.0);
    Range<double> r4(10.0, 20.0);

    REQUIRE(r1.overlaps(r2));   // Partial overlap
    REQUIRE(r2.overlaps(r1));   // Symmetry
    REQUIRE(!r1.overlaps(r3));  // No overlap
    REQUIRE(r1.overlaps(r4));   // Touching at 10.0
    REQUIRE(r4.overlaps(r1));   // Symmetry for touching
}

TEST_CASE("Range: intersection", TESTTAG)
{
    Range<double> r1(0.0, 10.0);
    Range<double> r2(5.0, 15.0);

    auto inter = r1.intersection(r2);
    REQUIRE(inter.min == 5.0);
    REQUIRE(inter.max == 10.0);
    REQUIRE(inter.is_valid());

    Range<double> r3(20.0, 30.0);
    auto          no_inter = r1.intersection(r3);
    REQUIRE(!no_inter.is_valid()); // min > max when no overlap
}

TEST_CASE("Range: with float type", TESTTAG)
{
    Range<float> r(0.0f, 10.0f);
    REQUIRE(r.contains(5.0f));
    REQUIRE(r.is_valid());

    Range<float> r2(5.0f, 15.0f);
    REQUIRE(r.overlaps(r2));
}

// ============================================================================
// get_sections tests
// ============================================================================

TEST_CASE("get_sections: empty container", TESTTAG)
{
    std::vector<double> empty_vec;
    auto                result = get_sections(empty_vec, 1.0);
    REQUIRE(result.size() == 0);
}

TEST_CASE("get_sections: single element", TESTTAG)
{
    std::vector<double> single_vec = { 5.0 };
    auto                result     = get_sections(single_vec, 1.0);
    REQUIRE(result.size() == 1);
    REQUIRE(result[0].min == 5.0);
    REQUIRE(result[0].max == 5.0);
}

TEST_CASE("get_sections: no gaps - one section", TESTTAG)
{
    std::vector<double> data = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5 };
    auto                result = get_sections(data, 0.2);

    REQUIRE(result.size() == 1);
    REQUIRE(result[0].min == 0.0);
    REQUIRE(result[0].max == 0.5);
}

TEST_CASE("get_sections: with gap - multiple sections", TESTTAG)
{
    std::vector<double> data = { 0.0, 0.1, 0.2, 0.3, 0.4,       // Section 1
                                 5.5, 5.6, 5.7, 5.8, 5.9 };     // Section 2 (gap > 1.0)

    auto result = get_sections(data, 1.0);

    REQUIRE(result.size() == 2);
    REQUIRE(result[0].min == 0.0);
    REQUIRE(result[0].max == 0.4);
    REQUIRE(result[1].min == 5.5);
    REQUIRE(result[1].max == 5.9);
}

TEST_CASE("get_sections: gap exactly at boundary", TESTTAG)
{
    // Gap exactly at max_gap should not trigger new section
    std::vector<double> data = { 0.0, 1.0, 2.0, 3.0 };

    auto result = get_sections(data, 1.0);

    // All should be one section since gaps are exactly 1.0 (not > 1.0)
    REQUIRE(result.size() == 1);
    REQUIRE(result[0].min == 0.0);
    REQUIRE(result[0].max == 3.0);
}

TEST_CASE("get_sections: multiple gaps", TESTTAG)
{
    std::vector<double> data = { 0.0, 0.1, 0.2,      // Section 1
                                 5.0, 5.1,           // Section 2
                                 10.0, 10.1, 10.2 }; // Section 3

    auto result = get_sections(data, 1.0);

    REQUIRE(result.size() == 3);
    REQUIRE(result[0].min == 0.0);
    REQUIRE(result[0].max == 0.2);
    REQUIRE(result[1].min == 5.0);
    REQUIRE(result[1].max == 5.1);
    REQUIRE(result[2].min == 10.0);
    REQUIRE(result[2].max == 10.2);
}

TEST_CASE("get_sections: NaN max_gap treats as single section", TESTTAG)
{
    std::vector<double> data = { 0.0, 0.1, 5.0, 5.1, 10.0 };
    auto result = get_sections(data, std::numeric_limits<double>::quiet_NaN());

    REQUIRE(result.size() == 1);
    REQUIRE(result[0].min == 0.0);
    REQUIRE(result[0].max == 10.0);
}

TEST_CASE("get_sections: negative max_gap treats as single section", TESTTAG)
{
    std::vector<double> data = { 0.0, 5.0, 10.0 };
    auto result = get_sections(data, -1.0);

    REQUIRE(result.size() == 1);
    REQUIRE(result[0].min == 0.0);
    REQUIRE(result[0].max == 10.0);
}

TEST_CASE("get_sections: zero max_gap treats as single section", TESTTAG)
{
    std::vector<double> data = { 0.0, 5.0, 10.0 };
    auto result = get_sections(data, 0.0);

    REQUIRE(result.size() == 1);
    REQUIRE(result[0].min == 0.0);
    REQUIRE(result[0].max == 10.0);
}

TEST_CASE("get_sections: with std::vector<float>", TESTTAG)
{
    std::vector<float> data = { 0.0f, 0.1f, 0.2f, 5.0f, 5.1f };
    auto               result = get_sections(data, 1.0);

    REQUIRE(result.size() == 2);
    REQUIRE(result[0].min == Catch::Approx(0.0f));
    REQUIRE(result[0].max == Catch::Approx(0.2f));
}

TEST_CASE("get_sections: with xt::xtensor<double, 1>", TESTTAG)
{
    xt::xtensor<double, 1> data = { 0.0, 0.1, 0.2, 5.0, 5.1, 5.2 };
    auto                   result = get_sections(data, 1.0);

    REQUIRE(result.size() == 2);
    REQUIRE(result[0].min == 0.0);
    REQUIRE(result[0].max == 0.2);
    REQUIRE(result[1].min == 5.0);
    REQUIRE(result[1].max == 5.2);
}

TEST_CASE("get_sections: with xt::xtensor<float, 1>", TESTTAG)
{
    xt::xtensor<float, 1> data = { 0.0f, 0.1f, 5.0f, 5.1f };
    auto                  result = get_sections(data, 1.0);

    REQUIRE(result.size() == 2);
}

// ============================================================================
// get_shared_sections tests
// ============================================================================

TEST_CASE("get_shared_sections: empty containers", TESTTAG)
{
    std::vector<std::vector<double>> containers;
    auto                             result = get_shared_sections(containers, 1.0);
    REQUIRE(result.size() == 0);
}

TEST_CASE("get_shared_sections: single container", TESTTAG)
{
    std::vector<std::vector<double>> containers = { { 0.0, 0.1, 0.2, 5.0, 5.1 } };
    auto                             result = get_shared_sections(containers, 1.0);

    REQUIRE(result.size() == 2);
    REQUIRE(result[0].min == 0.0);
    REQUIRE(result[0].max == 0.2);
    REQUIRE(result[1].min == 5.0);
    REQUIRE(result[1].max == 5.1);
}

TEST_CASE("get_shared_sections: overlapping containers", TESTTAG)
{
    // Container 1: 0-10, 20-30
    // Container 2: 5-15, 25-35
    // Shared: 5-10, 25-30
    std::vector<std::vector<double>> containers = {
        { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0,
          20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0 },
        { 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0,
          25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 33.0, 34.0, 35.0 }
    };

    auto result = get_shared_sections(containers, 2.0);

    REQUIRE(result.size() == 2);
    REQUIRE(result[0].min == 5.0);
    REQUIRE(result[0].max == 10.0);
    REQUIRE(result[1].min == 25.0);
    REQUIRE(result[1].max == 30.0);
}

TEST_CASE("get_shared_sections: no overlap", TESTTAG)
{
    std::vector<std::vector<double>> containers = {
        { 0.0, 1.0, 2.0, 3.0, 4.0 },
        { 10.0, 11.0, 12.0, 13.0 }
    };

    auto result = get_shared_sections(containers, 2.0);
    REQUIRE(result.size() == 0);
}

TEST_CASE("get_shared_sections: three containers", TESTTAG)
{
    std::vector<std::vector<double>> containers = {
        { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0 },
        { 2.0, 3.0, 4.0, 5.0, 6.0, 7.0 },
        { 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 }
    };

    auto result = get_shared_sections(containers, 2.0);

    REQUIRE(result.size() == 1);
    REQUIRE(result[0].min == 3.0);
    REQUIRE(result[0].max == 5.0);
}

TEST_CASE("get_shared_sections: with xtensor containers", TESTTAG)
{
    std::vector<xt::xtensor<double, 1>> containers = {
        xt::xtensor<double, 1>({ 0.0, 1.0, 2.0, 3.0, 4.0, 5.0 }),
        xt::xtensor<double, 1>({ 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 })
    };

    auto result = get_shared_sections(containers, 2.0);

    REQUIRE(result.size() == 1);
    REQUIRE(result[0].min == 3.0);
    REQUIRE(result[0].max == 5.0);
}

// ============================================================================
// cut_to_shared_sections tests
// ============================================================================

TEST_CASE("cut_to_shared_sections: empty containers", TESTTAG)
{
    std::vector<std::vector<double>> containers;
    auto                             result = cut_to_shared_sections(containers, 1.0);
    REQUIRE(result.size() == 0);
}

TEST_CASE("cut_to_shared_sections: simple overlap", TESTTAG)
{
    std::vector<std::vector<double>> containers = {
        { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0 },
        { 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 }
    };

    auto result = cut_to_shared_sections(containers, 2.0);

    REQUIRE(result.size() == 2);

    // Container 1: should have 3.0, 4.0, 5.0
    REQUIRE(result[0].size() == 3);
    REQUIRE(result[0](0) == Catch::Approx(3.0));
    REQUIRE(result[0](1) == Catch::Approx(4.0));
    REQUIRE(result[0](2) == Catch::Approx(5.0));

    // Container 2: should have 3.0, 4.0, 5.0
    REQUIRE(result[1].size() == 3);
    REQUIRE(result[1](0) == Catch::Approx(3.0));
    REQUIRE(result[1](1) == Catch::Approx(4.0));
    REQUIRE(result[1](2) == Catch::Approx(5.0));
}

TEST_CASE("cut_to_shared_sections: no overlap returns empty", TESTTAG)
{
    std::vector<std::vector<double>> containers = {
        { 0.0, 1.0, 2.0 },
        { 10.0, 11.0, 12.0 }
    };

    auto result = cut_to_shared_sections(containers, 2.0);

    REQUIRE(result.size() == 2);
    REQUIRE(result[0].size() == 0);
    REQUIRE(result[1].size() == 0);
}

TEST_CASE("cut_to_shared_sections: preserves value type for float", TESTTAG)
{
    std::vector<std::vector<float>> containers = {
        { 0.0f, 1.0f, 2.0f, 3.0f },
        { 2.0f, 3.0f, 4.0f, 5.0f }
    };

    auto result = cut_to_shared_sections(containers, 2.0);

    static_assert(std::is_same_v<decltype(result[0]), xt::xtensor<float, 1>&>);
    REQUIRE(result[0].size() == 2);
    REQUIRE(result[0](0) == Catch::Approx(2.0f));
    REQUIRE(result[0](1) == Catch::Approx(3.0f));
}

TEST_CASE("cut_to_shared_sections: with xtensor containers", TESTTAG)
{
    std::vector<xt::xtensor<double, 1>> containers = {
        xt::xtensor<double, 1>({ 0.0, 1.0, 2.0, 3.0, 4.0, 5.0 }),
        xt::xtensor<double, 1>({ 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 })
    };

    auto result = cut_to_shared_sections(containers, 2.0);

    REQUIRE(result.size() == 2);
    REQUIRE(result[0].size() == 3);
    REQUIRE(result[1].size() == 3);
}

// ============================================================================
// get_shared_section_indices tests
// ============================================================================

TEST_CASE("get_shared_section_indices: empty containers", TESTTAG)
{
    std::vector<std::vector<double>> containers;
    auto                             result = get_shared_section_indices(containers, 1.0);
    REQUIRE(result.size() == 0);
}

TEST_CASE("get_shared_section_indices: simple overlap", TESTTAG)
{
    std::vector<std::vector<double>> containers = {
        { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0 },
        { 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 }
    };

    auto result = get_shared_section_indices(containers, 2.0);

    REQUIRE(result.size() == 2);

    // Container 1: indices 3, 4, 5 (values 3.0, 4.0, 5.0)
    REQUIRE(result[0].size() == 3);
    REQUIRE(result[0](0) == 3);
    REQUIRE(result[0](1) == 4);
    REQUIRE(result[0](2) == 5);

    // Container 2: indices 0, 1, 2 (values 3.0, 4.0, 5.0)
    REQUIRE(result[1].size() == 3);
    REQUIRE(result[1](0) == 0);
    REQUIRE(result[1](1) == 1);
    REQUIRE(result[1](2) == 2);
}

TEST_CASE("get_shared_section_indices: no overlap returns empty arrays", TESTTAG)
{
    std::vector<std::vector<double>> containers = {
        { 0.0, 1.0, 2.0 },
        { 10.0, 11.0, 12.0 }
    };

    auto result = get_shared_section_indices(containers, 2.0);

    REQUIRE(result.size() == 2);
    REQUIRE(result[0].size() == 0);
    REQUIRE(result[1].size() == 0);
}

TEST_CASE("get_shared_section_indices: with float type", TESTTAG)
{
    std::vector<std::vector<float>> containers = {
        { 0.0f, 1.0f, 2.0f, 3.0f },
        { 2.0f, 3.0f, 4.0f, 5.0f }
    };

    auto result = get_shared_section_indices(containers, 2.0);

    REQUIRE(result.size() == 2);
    REQUIRE(result[0].size() == 2); // indices 2, 3 (values 2.0, 3.0)
    REQUIRE(result[1].size() == 2); // indices 0, 1 (values 2.0, 3.0)
    REQUIRE(result[0](0) == 2);
    REQUIRE(result[0](1) == 3);
    REQUIRE(result[1](0) == 0);
    REQUIRE(result[1](1) == 1);
}

TEST_CASE("get_shared_section_indices: with xtensor containers", TESTTAG)
{
    std::vector<xt::xtensor<double, 1>> containers = {
        xt::xtensor<double, 1>({ 0.0, 1.0, 2.0, 3.0, 4.0, 5.0 }),
        xt::xtensor<double, 1>({ 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 })
    };

    auto result = get_shared_section_indices(containers, 2.0);

    REQUIRE(result.size() == 2);
    REQUIRE(result[0].size() == 3);
    REQUIRE(result[1].size() == 3);
}

// ============================================================================
// get_shared_section_values tests
// ============================================================================

TEST_CASE("get_shared_section_values: empty containers", TESTTAG)
{
    std::vector<std::vector<double>> containers;
    auto                             result = get_shared_section_values(containers, 1.0);
    REQUIRE(result.size() == 0);
}

TEST_CASE("get_shared_section_values: simple overlap - identical values", TESTTAG)
{
    std::vector<std::vector<double>> containers = {
        { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0 },
        { 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 }
    };

    auto result = get_shared_section_values(containers, 2.0);

    // Shared section is [3.0, 5.0]
    // Values from both containers in that range: 3.0, 4.0, 5.0 (unique)
    REQUIRE(result.size() == 3);
    REQUIRE(result(0) == Catch::Approx(3.0));
    REQUIRE(result(1) == Catch::Approx(4.0));
    REQUIRE(result(2) == Catch::Approx(5.0));
}

TEST_CASE("get_shared_section_values: overlap with different values", TESTTAG)
{
    std::vector<std::vector<double>> containers = {
        { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0 },
        { 2.5, 3.5, 4.5, 5.5, 6.5, 7.5 }
    };

    auto result = get_shared_section_values(containers, 2.0);

    // Shared section is [2.5, 5.0]
    // Values: 2.5, 3.0, 3.5, 4.0, 4.5, 5.0 (sorted unique)
    REQUIRE(result.size() == 6);
    REQUIRE(result(0) == Catch::Approx(2.5));
    REQUIRE(result(1) == Catch::Approx(3.0));
    REQUIRE(result(2) == Catch::Approx(3.5));
    REQUIRE(result(3) == Catch::Approx(4.0));
    REQUIRE(result(4) == Catch::Approx(4.5));
    REQUIRE(result(5) == Catch::Approx(5.0));
}

TEST_CASE("get_shared_section_values: no overlap returns empty", TESTTAG)
{
    std::vector<std::vector<double>> containers = {
        { 0.0, 1.0, 2.0 },
        { 10.0, 11.0, 12.0 }
    };

    auto result = get_shared_section_values(containers, 2.0);
    REQUIRE(result.size() == 0);
}

TEST_CASE("get_shared_section_values: single container", TESTTAG)
{
    std::vector<std::vector<double>> containers = { { 0.0, 0.1, 0.2, 5.0, 5.1 } };
    auto                             result = get_shared_section_values(containers, 1.0);

    // All values are returned (two sections, all values within)
    REQUIRE(result.size() == 5);
}

TEST_CASE("get_shared_section_values: removes duplicates", TESTTAG)
{
    std::vector<std::vector<double>> containers = {
        { 1.0, 2.0, 3.0 },
        { 1.0, 2.0, 3.0 }  // Same values
    };

    auto result = get_shared_section_values(containers, 2.0);

    // Should have unique values only
    REQUIRE(result.size() == 3);
    REQUIRE(result(0) == Catch::Approx(1.0));
    REQUIRE(result(1) == Catch::Approx(2.0));
    REQUIRE(result(2) == Catch::Approx(3.0));
}

TEST_CASE("get_shared_section_values: result is sorted", TESTTAG)
{
    std::vector<std::vector<double>> containers = {
        { 1.0, 3.0, 5.0 },
        { 2.0, 4.0, 6.0 }
    };

    auto result = get_shared_section_values(containers, 2.0);

    // Verify sorted order
    for (size_t i = 1; i < result.size(); ++i)
    {
        REQUIRE(result(i) > result(i - 1));
    }
}

TEST_CASE("get_shared_section_values: with float type", TESTTAG)
{
    std::vector<std::vector<float>> containers = {
        { 1.0f, 2.0f, 3.0f },
        { 2.0f, 3.0f, 4.0f }
    };

    auto result = get_shared_section_values(containers, 2.0);

    static_assert(std::is_same_v<decltype(result), xt::xtensor<float, 1>>);
    REQUIRE(result.size() == 2);
    REQUIRE(result(0) == Catch::Approx(2.0f));
    REQUIRE(result(1) == Catch::Approx(3.0f));
}

TEST_CASE("get_shared_section_values: with xtensor containers", TESTTAG)
{
    std::vector<xt::xtensor<double, 1>> containers = {
        xt::xtensor<double, 1>({ 0.0, 1.0, 2.0, 3.0, 4.0, 5.0 }),
        xt::xtensor<double, 1>({ 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 })
    };

    auto result = get_shared_section_values(containers, 2.0);

    REQUIRE(result.size() == 3);
    REQUIRE(result(0) == Catch::Approx(3.0));
    REQUIRE(result(1) == Catch::Approx(4.0));
    REQUIRE(result(2) == Catch::Approx(5.0));
}

TEST_CASE("get_shared_section_values: multiple sections", TESTTAG)
{
    // Two separate overlapping sections
    std::vector<std::vector<double>> containers = {
        { 0.0, 1.0, 2.0,   10.0, 11.0, 12.0 },
        { 1.0, 2.0, 3.0,   11.0, 12.0, 13.0 }
    };

    auto result = get_shared_section_values(containers, 2.0);

    // Should have values from both shared sections: [1,2] and [11,12]
    REQUIRE(result.size() == 4);
    REQUIRE(result(0) == Catch::Approx(1.0));
    REQUIRE(result(1) == Catch::Approx(2.0));
    REQUIRE(result(2) == Catch::Approx(11.0));
    REQUIRE(result(3) == Catch::Approx(12.0));
}

// ============================================================================
// Large dataset and edge case tests
// ============================================================================

TEST_CASE("get_shared_section_indices: large dataset", TESTTAG)
{
    // Create large containers
    std::vector<double> data1, data2;
    data1.reserve(10000);
    data2.reserve(10000);

    for (double t = 0.0; t < 1000.0; t += 0.1)
    {
        data1.push_back(t);
    }
    for (double t = 500.0; t < 1500.0; t += 0.1)
    {
        data2.push_back(t);
    }

    std::vector<std::vector<double>> containers = { data1, data2 };
    auto                             result = get_shared_section_indices(containers, 1.0);

    REQUIRE(result.size() == 2);
    // Shared section is [500, 1000)
    REQUIRE(result[0].size() >= 4900);  // ~5000 values in [500, 1000)
    REQUIRE(result[1].size() >= 4900);

    // Verify monotonicity of indices
    for (size_t i = 1; i < result[0].size(); ++i)
    {
        REQUIRE(result[0](i) > result[0](i - 1));
    }
}

TEST_CASE("get_sections: consecutive identical values", TESTTAG)
{
    std::vector<double> data = { 1.0, 1.0, 1.0, 1.0, 5.0, 5.0 };
    auto                result = get_sections(data, 1.0);

    REQUIRE(result.size() == 2);
    REQUIRE(result[0].min == 1.0);
    REQUIRE(result[0].max == 1.0);
    REQUIRE(result[1].min == 5.0);
    REQUIRE(result[1].max == 5.0);
}
