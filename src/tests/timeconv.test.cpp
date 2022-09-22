// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <chrono>

#include "../themachinethatgoesping/tools/timeconv.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::tools;

#define TESTTAG "[timeconv]"

TEST_CASE("unixtime_to_timepoint: should be reversible", TESTTAG)
{
    auto now = chrono::system_clock::now();

    auto unixtime = timeconv::timepoint_to_unixtime(now);
    auto then     = timeconv::unixtime_to_timepoint(unixtime);
    REQUIRE(chrono::duration_cast<chrono::microseconds>(now - then).count() == 0);
}

TEST_CASE("unixtime_to_timepoint: should not loose microseconds during the conversation", TESTTAG)
{

    auto now = chrono::system_clock::now();

    auto unixtime = timeconv::timepoint_to_unixtime(now);
    auto then     = timeconv::unixtime_to_timepoint(unixtime) - chrono::microseconds(1234567);

    REQUIRE(chrono::duration_cast<chrono::microseconds>(now - then).count() == 1234567);

    unixtime = timeconv::timepoint_to_unixtime(now) - (1234567.0 / 1000000.0);
    then     = timeconv::unixtime_to_timepoint(unixtime);

    REQUIRE(chrono::duration_cast<chrono::microseconds>(now - then).count() == 1234567);
}

TEST_CASE("unixtime_to_datestring: should convert a specified timepoint to specified string",
          TESTTAG)
{
    auto unixtime   = 1234567890.123456;
    auto datestring = "+0000__13-02-2009__23:31:30.123456";

    REQUIRE(timeconv::datestring_to_unixtime(datestring) == Approx(unixtime));
    REQUIRE(timeconv::unixtime_to_datestring(unixtime, 6) == datestring);
}

TEST_CASE("unixtime_to_datestring: should be reversible", TESTTAG)
{
    auto now = chrono::system_clock::now();

    auto unixtime   = timeconv::timepoint_to_unixtime(now);
    auto datestring = timeconv::unixtime_to_datestring(unixtime, 18);

    REQUIRE(timeconv::datestring_to_unixtime(datestring) == Approx(unixtime));
}

TEST_CASE("datestring_to_unixtime: should be reversible", TESTTAG)
{
    auto now = chrono::system_clock::now();

    auto unixtime   = timeconv::timepoint_to_unixtime(now);
    auto datestring = timeconv::unixtime_to_datestring(unixtime, 3);
    unixtime        = timeconv::datestring_to_unixtime(datestring);

    REQUIRE(timeconv::unixtime_to_datestring(unixtime, 3) == datestring);
}

TEST_CASE("datestring_to_unixtime: should convert zone to UTC by default", TESTTAG)
{
    auto datestring1 = "+0500__05-06-2017__08:09:12";
    auto datestring2 = "-0500__05-06-2017__08:09:12";

    auto unixtime1 = timeconv::datestring_to_unixtime(datestring1);
    auto unixtime2 = timeconv::datestring_to_unixtime(datestring2);

    REQUIRE("+0000__05-06-2017__03:09:12" == timeconv::unixtime_to_datestring(unixtime1, 0));
    REQUIRE("+0000__05-06-2017__13:09:12" == timeconv::unixtime_to_datestring(unixtime2, 0));
}

TEST_CASE("unixtime_to_datestring: should round fractional seconds correctly", TESTTAG)
{
    auto datestring  = "+0000__05-06-2017__08:09:12.123456";
    auto datestring2 = "+0000__05-06-2017__08:09:12.1234567";
    auto unixtime    = timeconv::datestring_to_unixtime(datestring);
    auto unixtime2   = timeconv::datestring_to_unixtime(datestring2, "%z__%d-%m-%Y__%H:%M:%11S");

    CHECK("+0000__05-06-2017__08:09:12" == timeconv::unixtime_to_datestring(unixtime, 0));
    CHECK("+0000__05-06-2017__08:09:12.1" == timeconv::unixtime_to_datestring(unixtime, 1));
    CHECK("+0000__05-06-2017__08:09:12.12" == timeconv::unixtime_to_datestring(unixtime, 2));
    CHECK("+0000__05-06-2017__08:09:12.123" == timeconv::unixtime_to_datestring(unixtime, 3));
    CHECK("+0000__05-06-2017__08:09:12.1235" == timeconv::unixtime_to_datestring(unixtime, 4));
    CHECK("+0000__05-06-2017__08:09:12.12346" == timeconv::unixtime_to_datestring(unixtime, 5));
    CHECK("+0000__05-06-2017__08:09:12.123456" == timeconv::unixtime_to_datestring(unixtime, 6));
    CHECK("+0000__05-06-2017__08:09:12.123456" == timeconv::unixtime_to_datestring(unixtime, 7));

    CHECK("+0000__05-06-2017__08:09:12.123457" == timeconv::unixtime_to_datestring(unixtime2, 6));
}

TEST_CASE("datestring_to_unixtime: should read fractional second digits correctly", TESTTAG)
{
    auto datestring = "+0000__05-06-2017__08:09:12.123456";
    auto unixtime1  = timeconv::datestring_to_unixtime(datestring, "%z__%d-%m-%Y__%H:%M:%3S");
    auto unixtime2  = timeconv::datestring_to_unixtime(datestring, "%z__%d-%m-%Y__%H:%M:%4S");
    auto unixtime3  = timeconv::datestring_to_unixtime(datestring, "%z__%d-%m-%Y__%H:%M:%5S");
    auto unixtime4  = timeconv::datestring_to_unixtime(datestring, "%z__%d-%m-%Y__%H:%M:%6S");
    auto unixtime5  = timeconv::datestring_to_unixtime(datestring, "%z__%d-%m-%Y__%H:%M:%7S");
    auto unixtime6  = timeconv::datestring_to_unixtime(datestring, "%z__%d-%m-%Y__%H:%M:%8S");
    auto unixtime7  = timeconv::datestring_to_unixtime(datestring, "%z__%d-%m-%Y__%H:%M:%9S");
    auto unixtime8  = timeconv::datestring_to_unixtime(datestring, "%z__%d-%m-%Y__%H:%M:%10S");
    auto unixtime9  = timeconv::datestring_to_unixtime(datestring, "%z__%d-%m-%Y__%H:%M:%11S");

    CHECK("+0000__05-06-2017__08:09:12.000000" == timeconv::unixtime_to_datestring(unixtime1, 6));
    CHECK("+0000__05-06-2017__08:09:12.100000" == timeconv::unixtime_to_datestring(unixtime2, 6));
    CHECK("+0000__05-06-2017__08:09:12.120000" == timeconv::unixtime_to_datestring(unixtime3, 6));
    CHECK("+0000__05-06-2017__08:09:12.123000" == timeconv::unixtime_to_datestring(unixtime4, 6));
    CHECK("+0000__05-06-2017__08:09:12.123400" == timeconv::unixtime_to_datestring(unixtime5, 6));
    CHECK("+0000__05-06-2017__08:09:12.123450" == timeconv::unixtime_to_datestring(unixtime6, 6));
    CHECK("+0000__05-06-2017__08:09:12.123456" == timeconv::unixtime_to_datestring(unixtime7, 6));
    CHECK("+0000__05-06-2017__08:09:12.123456" == timeconv::unixtime_to_datestring(unixtime8, 6));
    CHECK("+0000__05-06-2017__08:09:12.123456" == timeconv::unixtime_to_datestring(unixtime9, 6));
}

TEST_CASE("datestring_to_unixtime: should use UTC0 as default", TESTTAG)
{
    auto datestring = "05-06-2017__08:09:12";
    auto unixtime   = timeconv::datestring_to_unixtime(datestring, "%d-%m-%Y__%H:%M:%S");

    REQUIRE("+0000__05-06-2017__08:09:12" == timeconv::unixtime_to_datestring(unixtime));
}

TEST_CASE("windows_filetime_conversion", TESTTAG)
{
    SECTION("conversion should be reproduce precomputed values")
    {
        double unixtime = 123456789.123456789;
        auto   high_low = timeconv::unixtime_to_windows_filetime(unixtime);

        REQUIRE(high_low.first == 27399348);
        REQUIRE(high_low.second == 299511560);

        REQUIRE(timeconv::windows_filetime_to_unixtime(high_low.first, high_low.second) ==
                Approx(unixtime));
    }
}
