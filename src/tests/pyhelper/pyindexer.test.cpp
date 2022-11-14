// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <xtensor/xtensor.hpp>

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
        PyIndexer           indexer(10, 1, 6, 2);
        std::vector<size_t> expected_results = { 1, 3, 5 };

        REQUIRE(indexer.size() == expected_results.size());
        for (size_t enumerator = 0; enumerator < indexer.size(); ++enumerator)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(indexer(enumerator) == expected_results.at(enumerator));
        }

        size_t enumerator = 0;
        for (const auto i : indexer)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(i == expected_results.at(enumerator));
            ++enumerator;
        }

        indexer.reset(10, 5, 0, -2);
        REQUIRE(indexer.size() == expected_results.size());

        enumerator = expected_results.size() - 1;
        for (const auto i : indexer)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(i == expected_results.at(enumerator));
            --enumerator;
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
        INFO(indexer.info_string());
        REQUIRE(indexer(0) == 2);
        REQUIRE(indexer(1) == 4);
        REQUIRE_THROWS_AS(indexer(2), std::out_of_range);
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
        {
            // not well defined yet
            // PyIndexer indexer(1, 1 , 0, -1);

            // INFO(indexer.info_string());

            // REQUIRE(indexer(0) == 0);
            // REQUIRE(indexer(-1) == 0);

            // REQUIRE(indexer.size() == 1);

            // REQUIRE_THROWS_AS(indexer(1), std::out_of_range);
            // REQUIRE_THROWS_AS(indexer(-2), std::out_of_range);
        }

        {
            // (_pings: 162315, pyindexer: 2000, start 36500, end 1, step 38500, I 125816, i 162315)
            PyIndexer indexer(162315, 36500, 38500, 1);
            auto      expected_results_step1 = xt::arange(36500, 38500, 1);
            REQUIRE(indexer.size() == expected_results_step1.size());

            size_t enumerator = 0;
            for (const auto i : indexer)
            {
                INFO(fmt::format("enumerator: {}", enumerator));
                INFO(fmt::format("--- indexer ---\n{}", indexer.info_string()));

                REQUIRE(i == size_t(expected_results_step1.at(enumerator)));
                ++enumerator;
            }

            indexer.reset(162315, 36500, 38500, 3);
            auto expected_results_step3 = xt::arange(36500, 38500, 3);
            REQUIRE(indexer.size() == expected_results_step3.size());

            enumerator = 0;
            for (const auto i : indexer)
            {
                INFO(fmt::format("enumerator: {}", enumerator));
                INFO(fmt::format("--- indexer ---\n{}", indexer.info_string()));

                REQUIRE(i == size_t(expected_results_step3.at(enumerator)));
                ++enumerator;
            }
        }
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
        INFO(indexer.info_string());

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
        auto      expected_results = xt::arange(10, 90, 3);
        REQUIRE(indexer.size() == expected_results.size());

        for (size_t enumerator = 0; enumerator < indexer.size(); ++enumerator)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(indexer(enumerator) == size_t(expected_results.at(enumerator)));
        }

        CHECK(indexer(-1) == indexer(26));
        CHECK(indexer(-10) == indexer(17));
        CHECK(indexer(-26) == indexer(1));
        CHECK(indexer(-27) == indexer(0));

        REQUIRE(indexer.size() == 27);

        REQUIRE_THROWS_AS(indexer(27), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-28), std::out_of_range);
    }

    SECTION("Reproduce precomputed results (slice, negative single step)")
    {
        PyIndexer indexer(100, 90, 10, -1);

        auto expected_results = xt::arange(90, 10, -1);

        REQUIRE(indexer.size() == expected_results.size());

        for (size_t enumerator = 0; enumerator < indexer.size(); ++enumerator)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(indexer(enumerator) == size_t(expected_results.at(enumerator)));
        }

        CHECK(indexer(-1) == 11);
        CHECK(indexer(-10) == 20);
        CHECK(indexer(-79) == 89);
        CHECK(indexer(-80) == 90);

        REQUIRE(indexer.size() == 80);

        REQUIRE_THROWS_AS(indexer(80), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-81), std::out_of_range);
    }

    SECTION("Reproduce precomputed results (slice, negative multi step)")
    {
        PyIndexer indexer(100, 90, 10, -3);

        CHECK(indexer(0) == 90);
        CHECK(indexer(1) == 87);
        CHECK(indexer(11) == 57);
        CHECK(indexer(26) == 12);

        CHECK(indexer(-1) == 12);
        CHECK(indexer(-10) == 39);
        CHECK(indexer(-26) == 87);
        CHECK(indexer(-27) == 90);

        REQUIRE(indexer.size() == 27);

        REQUIRE_THROWS_AS(indexer(27), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-28), std::out_of_range);
    }
}
