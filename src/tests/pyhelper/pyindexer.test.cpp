// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <xtensor/containers/xtensor.hpp>

#include "../../themachinethatgoesping/tools/pyhelper/pyindexer.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::tools::pyhelper;

#define TESTTAG "[pyhelper]"

void test_reversed(const PyIndexer& indexer)
{
    INFO("--- test_reversed ---");
    INFO("original indexer");
    INFO(indexer.info_string());
    auto reversed = indexer.reversed();
    INFO("reversed indexer");
    INFO(reversed.info_string());

    for (int64_t i = 0; i < int64_t(indexer.size()); ++i)
    {
        INFO("i: " << i);
        REQUIRE(indexer(i) == reversed(-i - 1));
    }
}

TEST_CASE("pyhelper:PyIndexer", TESTTAG)
{
    SECTION("Support basic loop iteration")
    {
        PyIndexer indexer(10, 1, 6, 2);
        test_reversed(indexer);
        std::vector<size_t> expected_results = { 1, 3, 5 };

        REQUIRE(indexer.size() == expected_results.size());
        for (int64_t enumerator = 0; enumerator < int64_t(indexer.size()); ++enumerator)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(indexer(enumerator) == expected_results.at(enumerator));
        }

        int64_t enumerator = 0;
        for (const auto i : indexer)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(i == expected_results.at(enumerator));
            ++enumerator;
        }

        indexer.reset(10, 5, 0, -2);
        REQUIRE(indexer.size() == expected_results.size());

        enumerator = int64_t(expected_results.size() - 1);
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
            // (_pings: 162315, pyindexer: 2000, start 36500, stop 1, step 38500, I 125816, i
            // 162315)
            PyIndexer indexer(162315, 36500, 38500, 1);
            test_reversed(indexer);
            REQUIRE(indexer == PyIndexer(162315, PyIndexer::Slice(36500, 38500, 1)));
            auto expected_results_step1 = xt::arange(36500, 38500, 1);
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
            REQUIRE(indexer == PyIndexer(162315, PyIndexer::Slice(36500, 38500, 3)));
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
        test_reversed(indexer);

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
        test_reversed(indexer);
        INFO(indexer.info_string());

        REQUIRE(indexer == PyIndexer(100, PyIndexer::Slice(10, 90, 1)));

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
        test_reversed(indexer);
        auto expected_results = xt::arange(10, 90, 3);
        REQUIRE(indexer.size() == expected_results.size());

        for (int64_t enumerator = 0; enumerator < int64_t(indexer.size()); ++enumerator)
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
        test_reversed(indexer);

        auto expected_results = xt::arange(90, 10, -1);

        REQUIRE(indexer.size() == expected_results.size());

        for (int64_t enumerator = 0; enumerator < int64_t(indexer.size()); ++enumerator)
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
        test_reversed(indexer);

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

    SECTION("Reproduce precomputed results (slice, negative start, negative multi step)")
    {
        PyIndexer indexer(100, -1, 0, -3);
        test_reversed(indexer);
        auto expected_results = xt::arange(99, 0, -3);
        REQUIRE(indexer.size() == expected_results.size());

        for (int64_t enumerator = 0; enumerator < int64_t(indexer.size()); ++enumerator)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(indexer(enumerator) == size_t(expected_results.at(enumerator)));
        }

        // INFO(indexer.info_string());
        CHECK(indexer(-1) == 3);
        CHECK(indexer(-10) == 30);
        CHECK(indexer(-26) == 78);
        CHECK(indexer(-27) == 81);
        CHECK(indexer(-32) == 96);
        CHECK(indexer(-33) == 99);

        REQUIRE(indexer.size() == 33);

        REQUIRE_THROWS_AS(indexer(33), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-34), std::out_of_range);
    }

    SECTION("Reproduce precomputed results (slice, negative stop, positive multi step)")
    {
        PyIndexer indexer(100, 0, -1, 3);
        test_reversed(indexer);
        auto expected_results = xt::arange(0, 99, 3);
        REQUIRE(indexer.size() == expected_results.size());

        for (int64_t enumerator = 0; enumerator < int64_t(indexer.size()); ++enumerator)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(indexer(enumerator) == size_t(expected_results.at(enumerator)));
        }

        // INFO(indexer.info_string());
        CHECK(indexer(-1) == 96);
        CHECK(indexer(-10) == 69);
        CHECK(indexer(-26) == 21);
        CHECK(indexer(-27) == 18);
        CHECK(indexer(-32) == 3);
        CHECK(indexer(-33) == 0);

        REQUIRE(indexer.size() == 33);

        REQUIRE_THROWS_AS(indexer(33), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-34), std::out_of_range);
    }

    SECTION(
        "Reproduce precomputed results (slice, negative start, negative stop, positive multi step)")
    {
        PyIndexer indexer(100, -80, -10, 3);
        test_reversed(indexer);
        auto expected_results = xt::arange(20, 90, 3);
        REQUIRE(indexer.size() == expected_results.size());

        for (int64_t enumerator = 0; enumerator < int64_t(indexer.size()); ++enumerator)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(indexer(enumerator) == size_t(expected_results.at(enumerator)));
        }

        // INFO(indexer.info_string());
        CHECK(indexer(-1) == 89);
        CHECK(indexer(-10) == 62);
        CHECK(indexer(-23) == 23);
        CHECK(indexer(-24) == 20);

        REQUIRE(indexer.size() == 24);

        REQUIRE_THROWS_AS(indexer(24), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-25), std::out_of_range);
    }

    SECTION(
        "Reproduce precomputed results (slice, negative start, negative stop, negative multi step)")
    {
        PyIndexer indexer(100, -30, -70, -7);
        test_reversed(indexer);
        auto expected_results = xt::arange(70, 30, -7);
        REQUIRE(indexer.size() == expected_results.size());

        for (int64_t enumerator = 0; enumerator < int64_t(indexer.size()); ++enumerator)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(indexer(enumerator) == size_t(expected_results.at(enumerator)));
        }

        // INFO(indexer.info_string());
        CHECK(indexer(-1) == 35);
        CHECK(indexer(-2) == 42);
        CHECK(indexer(-3) == 49);
        CHECK(indexer(-4) == 56);
        CHECK(indexer(-5) == 63);
        CHECK(indexer(-6) == 70);

        REQUIRE(indexer.size() == 6);

        REQUIRE_THROWS_AS(indexer(6), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-7), std::out_of_range);
    }

    SECTION("Reproduce precomputed results (slice, none start, positive stop, positive multi step)")
    {
        PyIndexer indexer(100, std::numeric_limits<int64_t>::max(), 70, 7);
        test_reversed(indexer);
        auto expected_results = xt::arange(0, 70, 7);
        REQUIRE(indexer.size() == expected_results.size());

        for (int64_t enumerator = 0; enumerator < int64_t(indexer.size()); ++enumerator)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(indexer(enumerator) == size_t(expected_results.at(enumerator)));
        }

        // INFO(indexer.info_string());
        CHECK(indexer(-1) == 63);
        CHECK(indexer(-2) == 56);
        CHECK(indexer(-9) == 7);
        CHECK(indexer(-10) == 0);

        REQUIRE(indexer.size() == 10);

        REQUIRE_THROWS_AS(indexer(10), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-11), std::out_of_range);
    }

    SECTION("Reproduce precomputed results (slice, none start, positive stop, negative multi step)")
    {
        PyIndexer indexer(100, std::numeric_limits<int64_t>::max(), 70, -7);
        test_reversed(indexer);
        auto expected_results = xt::arange(99, 70, -7);
        REQUIRE(indexer.size() == expected_results.size());

        for (int64_t enumerator = 0; enumerator < int64_t(indexer.size()); ++enumerator)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(indexer(enumerator) == size_t(expected_results.at(enumerator)));
        }

        // INFO(indexer.info_string());
        CHECK(indexer(-1) == 71);
        CHECK(indexer(-2) == 78);
        CHECK(indexer(-4) == 92);
        CHECK(indexer(-5) == 99);

        REQUIRE(indexer.size() == 5);

        REQUIRE_THROWS_AS(indexer(5), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-6), std::out_of_range);
    }

    SECTION("Reproduce precomputed results (slice, none start, negative stop, positive multi step)")
    {
        PyIndexer indexer(100, std::numeric_limits<int64_t>::max(), -70, 7);
        test_reversed(indexer);
        auto expected_results = xt::arange(0, 30, 7);
        REQUIRE(indexer.size() == expected_results.size());

        for (int64_t enumerator = 0; enumerator < int64_t(indexer.size()); ++enumerator)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(indexer(enumerator) == size_t(expected_results.at(enumerator)));
        }

        // INFO(indexer.info_string());
        CHECK(indexer(-1) == 28);
        CHECK(indexer(-2) == 21);
        CHECK(indexer(-4) == 7);
        CHECK(indexer(-5) == 0);

        REQUIRE(indexer.size() == 5);

        REQUIRE_THROWS_AS(indexer(5), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-6), std::out_of_range);
    }

    SECTION("Reproduce precomputed results (slice, none start, negative stop, negative multi step)")
    {
        PyIndexer indexer(100, std::numeric_limits<int64_t>::max(), -70, -7);
        test_reversed(indexer);
        auto expected_results = xt::arange(99, 30, -7);
        REQUIRE(indexer.size() == expected_results.size());

        for (int64_t enumerator = 0; enumerator < int64_t(indexer.size()); ++enumerator)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(indexer(enumerator) == size_t(expected_results.at(enumerator)));
        }

        // INFO(indexer.info_string());
        CHECK(indexer(-1) == 36);
        CHECK(indexer(-2) == 43);
        CHECK(indexer(-9) == 92);
        CHECK(indexer(-10) == 99);

        REQUIRE(indexer.size() == 10);

        REQUIRE_THROWS_AS(indexer(10), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-11), std::out_of_range);
    }

    SECTION("Reproduce precomputed results (slice, none start, none stop, positive multi step)")
    {
        PyIndexer indexer(
            100, std::numeric_limits<int64_t>::max(), std::numeric_limits<int64_t>::max(), 5);
        test_reversed(indexer);
        auto expected_results = xt::arange(0, 99, 5);
        REQUIRE(indexer.size() == expected_results.size());

        for (int64_t enumerator = 0; enumerator < int64_t(indexer.size()); ++enumerator)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(indexer(enumerator) == size_t(expected_results.at(enumerator)));
        }

        // INFO(indexer.info_string());
        CHECK(indexer(-1) == 95);
        CHECK(indexer(-2) == 90);
        CHECK(indexer(-19) == 5);
        CHECK(indexer(-20) == 0);

        REQUIRE(indexer.size() == 20);

        REQUIRE_THROWS_AS(indexer(20), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-21), std::out_of_range);
    }

    SECTION("Reproduce precomputed results (slice, none start, none stop, negative single step)")
    {
        PyIndexer indexer(
            100, std::numeric_limits<int64_t>::max(), std::numeric_limits<int64_t>::max(), -1);
        test_reversed(indexer);
        // xt::arange(99, 0, -1) does not capture the very last index (0)
        auto expected_results = xt::arange(99, 0, -1);
        REQUIRE(indexer.size() == expected_results.size() + 1);

        for (int64_t enumerator = 0; enumerator < int64_t(indexer.size() - 1); ++enumerator)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(int64_t(indexer(enumerator)) == expected_results.at(enumerator));
        }
        CHECK(indexer(99) == 0);

        // INFO(indexer.info_string());
        CHECK(indexer(-1) == 0);
        CHECK(indexer(-2) == 1);
        CHECK(indexer(-99) == 98);
        CHECK(indexer(-100) == 99);

        REQUIRE(indexer.size() == 100);

        REQUIRE_THROWS_AS(indexer(100), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-101), std::out_of_range);
    }

    SECTION("Reproduce precomputed results (slice, none start, none stop, negative multi step)")
    {
        PyIndexer indexer(
            100, std::numeric_limits<int64_t>::max(), std::numeric_limits<int64_t>::max(), -11);
        test_reversed(indexer);
        // xt::arange(99, 0, -11) does not capture the very last index (0)
        auto expected_results = xt::arange(99, 0, -11);
        REQUIRE(indexer.size() == expected_results.size() + 1);

        for (int64_t enumerator = 0; enumerator < int64_t(indexer.size() - 1); ++enumerator)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(int64_t(indexer(enumerator)) == expected_results.at(enumerator));
        }
        CHECK(indexer(9) == 0);

        // INFO(indexer.info_string());
        CHECK(indexer(-1) == 0);
        CHECK(indexer(-2) == 11);
        CHECK(indexer(-9) == 88);
        CHECK(indexer(-10) == 99);

        REQUIRE(indexer.size() == 10);

        REQUIRE_THROWS_AS(indexer(10), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-11), std::out_of_range);
    }

    SECTION("Reproduce precomputed results (slice, positive start, none stop, positive multi step)")
    {
        PyIndexer indexer(100, 30, std::numeric_limits<int64_t>::max(), 11);
        test_reversed(indexer);
        auto expected_results = xt::arange(30, 100, 11);
        REQUIRE(indexer.size() == expected_results.size());

        for (int64_t enumerator = 0; enumerator < int64_t(indexer.size()); ++enumerator)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(indexer(enumerator) == size_t(expected_results.at(enumerator)));
        }

        // INFO(indexer.info_string());
        CHECK(indexer(-1) == 96);
        CHECK(indexer(-2) == 85);
        CHECK(indexer(-6) == 41);
        CHECK(indexer(-7) == 30);

        REQUIRE(indexer.size() == 7);

        REQUIRE_THROWS_AS(indexer(7), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-8), std::out_of_range);
    }

    SECTION("Reproduce precomputed results (slice, positive start, none stop, negative multi step)")
    {
        PyIndexer indexer(100, 30, std::numeric_limits<int64_t>::max(), -13);
        test_reversed(indexer);
        auto expected_results = xt::arange(30, 0, -13);
        REQUIRE(indexer.size() == expected_results.size());

        for (int64_t enumerator = 0; enumerator < int64_t(indexer.size()); ++enumerator)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(indexer(enumerator) == size_t(expected_results.at(enumerator)));
        }
        CHECK(indexer(0) == 30);

        // INFO(indexer.info_string());
        CHECK(indexer(-1) == 4);
        CHECK(indexer(-2) == 17);
        CHECK(indexer(-3) == 30);

        REQUIRE(indexer.size() == 3);

        REQUIRE_THROWS_AS(indexer(3), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-4), std::out_of_range);
    }

    SECTION(
        "Reproduce precomputed results (slice, positive start, none stop, negative single step)")
    {
        PyIndexer indexer(100, 30, std::numeric_limits<int64_t>::max(), -1);
        test_reversed(indexer);
        auto expected_results = xt::arange(30, 0, -1);
        REQUIRE(indexer.size() == expected_results.size() + 1);

        for (int64_t enumerator = 0; enumerator < int64_t(indexer.size() - 1); ++enumerator)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(int64_t(indexer(enumerator)) == expected_results.at(enumerator));
        }
        CHECK(indexer(0) == 30);

        // INFO(indexer.info_string());
        CHECK(indexer(-1) == 0);
        CHECK(indexer(-2) == 1);
        CHECK(indexer(-30) == 29);
        CHECK(indexer(-31) == 30);

        REQUIRE(indexer.size() == 31);

        REQUIRE_THROWS_AS(indexer(31), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-32), std::out_of_range);
    }

    SECTION("Reproduce precomputed results (slice, negative start, none stop, positive multi step)")
    {
        PyIndexer indexer(100, -30, std::numeric_limits<int64_t>::max(), 4);
        test_reversed(indexer);
        auto expected_results = xt::arange(70, 100, 4);
        REQUIRE(indexer.size() == expected_results.size());

        for (int64_t enumerator = 0; enumerator < int64_t(indexer.size()); ++enumerator)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(indexer(enumerator) == size_t(expected_results.at(enumerator)));
        }
        CHECK(indexer(0) == 70);

        // INFO(indexer.info_string());
        CHECK(indexer(-1) == 98);
        CHECK(indexer(-2) == 94);
        CHECK(indexer(-7) == 74);
        CHECK(indexer(-8) == 70);

        REQUIRE(indexer.size() == 8);

        REQUIRE_THROWS_AS(indexer(8), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-9), std::out_of_range);
    }

    SECTION("Reproduce precomputed results (slice, negative start, none stop, negative multi step)")
    {
        PyIndexer indexer(100, -30, std::numeric_limits<int64_t>::max(), -4);
        test_reversed(indexer);
        auto expected_results = xt::arange(70, 0, -4);
        REQUIRE(indexer.size() == expected_results.size());

        for (int64_t enumerator = 0; enumerator < int64_t(indexer.size()); ++enumerator)
        {
            INFO(fmt::format("enumerator: {}", enumerator));
            INFO(indexer.info_string());
            REQUIRE(indexer(enumerator) == size_t(expected_results.at(enumerator)));
        }
        CHECK(indexer(0) == 70);

        // INFO(indexer.info_string());
        CHECK(indexer(-1) == 2);
        CHECK(indexer(-2) == 6);
        CHECK(indexer(-17) == 66);
        CHECK(indexer(-18) == 70);

        REQUIRE(indexer.size() == 18);

        REQUIRE_THROWS_AS(indexer(18), std::out_of_range);
        REQUIRE_THROWS_AS(indexer(-19), std::out_of_range);
    }

    SECTION("Compare initialization using default and PyIndexer::Slice")
    {
        REQUIRE(PyIndexer(100, 0, 100, 1) == PyIndexer(100, PyIndexer::Slice(0, 100, 1)));

        REQUIRE(PyIndexer(100, PyIndexer::None, -10, -1) ==
                PyIndexer(100, PyIndexer::Slice(PyIndexer::None, -10, -1)));
    }
}

TEST_CASE("pyhelper:PyIndexer::Slice should", TESTTAG)
{
    SECTION("Support common functions")
    {
        PyIndexer::Slice slice(1, 5, 2);

        // copy operator
        auto slice_copy = slice;
        REQUIRE(slice_copy == slice);

        // move operator
        auto slice_move = std::move(slice_copy);
        REQUIRE(slice_move == slice);

        // copy constructor
        auto slice_copy2(slice);
        REQUIRE(slice_copy2 == slice);

        // check inequality
        slice = PyIndexer::Slice(2, 5, 2);
        INFO(slice.info_string());
        REQUIRE(slice_copy2 != slice);
        REQUIRE(slice_move != slice);

        // check that printing to stream does not crash
        std::stringstream ss;
        slice.print(ss);

        // test internal to/from binary functions
        auto buffer            = slice.to_binary();
        auto slice_from_binary = PyIndexer::Slice::from_binary(buffer);
        REQUIRE(slice_from_binary == slice);

        // test internal to/from stream functions
        std::stringstream ss2;
        slice.to_stream(ss2);
        auto slice_from_stream = PyIndexer::Slice::from_stream(ss2);
        REQUIRE(slice_from_stream == slice);
    }
}