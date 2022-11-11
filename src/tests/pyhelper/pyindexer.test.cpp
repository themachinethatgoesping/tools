// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "../../themachinethatgoesping/tools/pyhelper/pyindexer.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::tools::pyhelper;

#define TESTTAG "[pyhelper]"

// conversions
// static const double to_rad     = M_PI / 180;
// static const double to_degrees = 1 / to_rad;

TEST_CASE("pyhelper:PyIndexer", TESTTAG)
{
    SECTION("Support basic loop iteration")
    {
        PyIndexer           indexer(10, 1, 5, 2);
        std::vector<size_t> expected_results = { 1, 3 };

        for (size_t i = 0; i < indexer.size(); ++i)
        {
            REQUIRE(indexer(i) == expected_results.at(i));
        }

        for (const auto i : indexer)
        {
            REQUIRE(indexer(i) == expected_results.at(i));
        }
    }

    SECTION("Support common functions")
    {
        PyIndexer indexer(10, 1, 5, 2);
        REQUIRE(indexer.size() == 2);

        // copy operator
        auto indexer_copy = indexer;
        REQUIRE(indexer_copy == indexer);

        // move operator
        auto indexer_move = std::move(indexer_copy);
        REQUIRE(indexer_move == indexer);

        // copy constructor
        auto indexer_copy2(indexer);
        REQUIRE(indexer_copy2 == indexer);

        // check inequality
        indexer.set_slice_indexing(2, 5, 2);
        REQUIRE(indexer.size() == 2);
        REQUIRE(indexer_copy2 != indexer);
        REQUIRE(indexer_move != indexer);

        // check that printing to stream does not crash
        std::stringstream ss;
        indexer.print(ss);

        // test internal to/from binary functions
        auto buffer              = indexer.to_binary();
        auto indexer_from_binary = PyIndexer::from_binary(buffer);
        REQUIRE(indexer_from_binary == indexer);

        // test internal to/from stream functions
        std::stringstream ss2;
        indexer.to_stream(ss2);
        auto indexer_from_stream = PyIndexer::from_stream(ss2);
        REQUIRE(indexer_from_stream == indexer);
    }

    SECTION("Reproduce precomputed results (extra cases)")
    {
        PyIndexer indexer(1,0,1,1);

        REQUIRE(indexer(0) == 0);
        REQUIRE(indexer(-1) == 0);

        REQUIRE(indexer.size() == 1);

        REQUIRE_THROWS_AS(indexer(1), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-2), std::out_of_range);
    }

    SECTION("Reproduce precomputed results (standard)")
    {
        PyIndexer indexer(100);

        REQUIRE(indexer(0) == 0);
        REQUIRE(indexer(1) == 1);
        REQUIRE(indexer(11) == 11);
        REQUIRE(indexer(99) == 99);

        REQUIRE(indexer(-100) == 0);
        REQUIRE(indexer(-99) == 1);
        REQUIRE(indexer(-89) == 11);
        REQUIRE(indexer(-1) == 99);

        REQUIRE(indexer.size() == 100);

        REQUIRE_THROWS_AS(indexer(100), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-101), std::out_of_range);
    }

    SECTION("Reproduce precomputed results (slice, positive single step)")
    {
        PyIndexer indexer(100, 10, 90, 1);

        REQUIRE(indexer(0) == 10);
        REQUIRE(indexer(1) == 11);
        REQUIRE(indexer(11) == 21);
        REQUIRE(indexer(79) == 89);

        REQUIRE(indexer(-1) == 89);
        REQUIRE(indexer(-10) == 80);
        REQUIRE(indexer(-79) == 11);
        REQUIRE(indexer(-80) == 10);

        REQUIRE(indexer.size() == 80);

        REQUIRE_THROWS_AS(indexer(80), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-81), std::out_of_range);
    }

    SECTION("Reproduce precomputed results (slice, positive multi step)")
    {
        PyIndexer indexer(100, 10, 90, 3);

        CHECK(indexer(0) == 10);
        CHECK(indexer(1) == 13);
        CHECK(indexer(11) == 43);
        CHECK(indexer(26) == 88);

        CHECK(indexer(-1) == 89);
        CHECK(indexer(-10) == 62);
        CHECK(indexer(-26) == 14);
        CHECK(indexer(-27) == 11);

        REQUIRE(indexer.size() == 27);

        REQUIRE_THROWS_AS(indexer(27), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-28), std::out_of_range);
    }

    SECTION("Reproduce precomputed results (slice, negative single step)")
    {
        PyIndexer indexer(100, 10, 90, -1);

        REQUIRE(indexer(0) == 89);
        REQUIRE(indexer(1) == 88);
        REQUIRE(indexer(11) == 78);
        REQUIRE(indexer(79) == 10);

        REQUIRE(indexer(-1) == 10);
        REQUIRE(indexer(-10) == 19);
        REQUIRE(indexer(-79) == 88);
        REQUIRE(indexer(-80) == 89);

        REQUIRE(indexer.size() == 80);

        REQUIRE_THROWS_AS(indexer(80), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-81), std::out_of_range);
    }

    SECTION("Reproduce precomputed results (slice, negative multi step)")
    {
        PyIndexer indexer(100, 10, 90, -3);

        CHECK(indexer(0) == 89);
        CHECK(indexer(1) == 86);
        CHECK(indexer(11) == 56);
        CHECK(indexer(26) == 11);

        CHECK(indexer(-1) == 10);
        CHECK(indexer(-10) == 37);
        CHECK(indexer(-26) == 85);
        CHECK(indexer(-27) == 88);

        REQUIRE(indexer.size() == 27);

        REQUIRE_THROWS_AS(indexer(27), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-28), std::out_of_range);
    }
}
