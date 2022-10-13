// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <chrono>

#include "../themachinethatgoesping/tools/helper/defaultsharedpointermap.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::tools::helper;

#define TESTTAG "[helper]"

TEST_CASE("defaultsharedpointermap: test default values", TESTTAG)
{
    auto map_vec = DefaultSharedPointerMap<std::string, std::vector<int>>();

    map_vec.get("test1")->push_back(1);
    map_vec.get("test1")->push_back(5);
    map_vec.get("test2")->push_back(2);

    REQUIRE(map_vec.get("test1")->size() == 2);
    REQUIRE(map_vec.get("test1")->at(0) == 1);
    REQUIRE(map_vec.get("test1")->at(1) == 5);

    REQUIRE(map_vec.get("test2")->size() == 1);
    REQUIRE(map_vec.get("test2")->at(0) == 2);

    REQUIRE(map_vec.get_const("test3")->size() == 0);
    REQUIRE(map_vec.get("test3")->size() == 0);
    
}

