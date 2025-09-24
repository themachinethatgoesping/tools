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

#include <themachinethatgoesping/tools/classhelper/option.hpp>

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::tools;

#define TESTTAG "[classhelper]"

TEST_CASE("Option should support common functions", TESTTAG)
{
    // create enum
    enum class TestEnum : uint8_t
    {
        OptionOne = 1,
        OptionTwo = 2
    };

    // create option
    classhelper::Option<TestEnum> opt("OptionTwo");

    // equal comparision
    opt != classhelper::Option<TestEnum>();
    opt == classhelper::Option<TestEnum>(opt);

    // bool operators
    REQUIRE(opt);
    REQUIRE(bool(classhelper::Option<TestEnum>())); // even the default value should be valid
    REQUIRE(opt == static_cast<uint8_t>(2)); // underlying value
    REQUIRE(opt == TestEnum::OptionTwo);
    REQUIRE(opt == "OptionTwo");

    // default value
    REQUIRE(classhelper::Option<TestEnum>() == TestEnum::OptionOne);
    REQUIRE(classhelper::Option<TestEnum, TestEnum::OptionTwo>() == TestEnum::OptionTwo);

    // string conversion
    std::stringstream ss;
    opt.print(ss);
    REQUIRE(opt.info_string().size() > 0);

    // test setting
    REQUIRE_THROWS_AS(opt.set(4), std::invalid_argument);
    REQUIRE_THROWS_AS(opt.set("OptionThree"), std::invalid_argument);
    REQUIRE_THROWS_AS(classhelper::Option<TestEnum>(0), std::invalid_argument);
    REQUIRE_THROWS_AS(classhelper::Option<TestEnum>("OptionZero"), std::invalid_argument);

    // serialization
    auto buffer  = opt.to_binary();
    auto opt2 = classhelper::Option<TestEnum>::from_binary(buffer);
    REQUIRE(opt == opt2);
    REQUIRE(opt.name() == "OptionTwo");
    REQUIRE(std::string(opt) == "OptionTwo");

    REQUIRE(opt.names().size() == 2);
    REQUIRE(opt.values().size() == 2);
    REQUIRE(opt.names().at(0) == "OptionOne");
    REQUIRE(opt.names().at(1) == "OptionTwo");
    REQUIRE(opt.values().at(0) == TestEnum::OptionOne);
    REQUIRE(opt.values().at(1) == TestEnum::OptionTwo);

    REQUIRE(classhelper::Option<TestEnum>::names().size() == 2);
    REQUIRE(classhelper::Option<TestEnum>::values().size() == 2);
    REQUIRE(classhelper::Option<TestEnum>::names().at(0) == "OptionOne");
    REQUIRE(classhelper::Option<TestEnum>::names().at(1) == "OptionTwo");
    REQUIRE(classhelper::Option<TestEnum>::values().at(0) == TestEnum::OptionOne);
    REQUIRE(classhelper::Option<TestEnum>::values().at(1) == TestEnum::OptionTwo);

    // hash
    REQUIRE(opt.binary_hash() == 14552307339992752127ULL);
    REQUIRE(opt2.binary_hash() == 14552307339992752127ULL);
}
