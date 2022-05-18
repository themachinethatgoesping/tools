// SPDX-FileCopyrightText: 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <chrono>

#include "../../src/tools/timeconv.h"

//using namespace testing;
using namespace std;
using namespace themachinethatgoesping::tools;

namespace themachinethatgoesping_tools_tests
{

TEST_CASE("UnixTime_to_TimePoint: should be reversible","[timeconv]")
{
    auto now = chrono::system_clock::now();

    auto unixTime = timeconv::timepoint_to_unixtime(now);
    auto then     = timeconv::unixtime_to_timepoint(unixTime);
    REQUIRE(chrono::duration_cast<chrono::microseconds>(now - then).count() == 0);

}

TEST_CASE("UnixTime_to_TimePoint: should not loose microseconds during the conversation","[timeconv]")
{

    auto now = chrono::system_clock::now();

    auto unixTime = timeconv::timepoint_to_unixtime(now);
    auto then     = timeconv::unixtime_to_timepoint(unixTime) - chrono::microseconds(1234567);

    REQUIRE(chrono::duration_cast<chrono::microseconds>(now - then).count() == 1234567);


    unixTime = timeconv::timepoint_to_unixtime(now)       - (1234567.0 / 1000000.0);
    then     = timeconv::unixtime_to_timepoint(unixTime);

    REQUIRE(chrono::duration_cast<chrono::microseconds>(now - then).count() == 1234567);
}

TEST_CASE("unixtime_to_datestring: should be reversible","[timeconv]")
{
    auto now = chrono::system_clock::now();

    auto unixTime   = timeconv::timepoint_to_unixtime(now);
    auto datestring = timeconv::unixtime_to_datestring(unixTime,18);

    REQUIRE(timeconv::datestring_to_unixtime(datestring) == Approx(unixTime));

}

TEST_CASE("datestring_to_unixtime: should be reversible","[timeconv]")
{
    auto now = chrono::system_clock::now();

    auto unixTime   = timeconv::timepoint_to_unixtime(now);
    auto datestring = timeconv::unixtime_to_datestring(unixTime,3);
    unixTime        = timeconv::datestring_to_unixtime(datestring);

    REQUIRE(timeconv::unixtime_to_datestring(unixTime,3) == datestring);
}


TEST_CASE("datestring_to_unixtime: should convert zone to UTC by default","[timeconv]")
{
    auto datestring1  = "+0500__05-06-2017__08:09:12";
    auto datestring2  = "-0500__05-06-2017__08:09:12";

    auto unixTime1        = timeconv::datestring_to_unixtime(datestring1);
    auto unixTime2        = timeconv::datestring_to_unixtime(datestring2);

    REQUIRE("+0000__05-06-2017__03:09:12" == timeconv::unixtime_to_datestring(unixTime1,0));
    REQUIRE("+0000__05-06-2017__13:09:12" == timeconv::unixtime_to_datestring(unixTime2,0));

}


TEST_CASE("unixtime_to_datestring: should round fractional seconds correctly","[timeconv]")
{
    auto datestring     = "+0000__05-06-2017__08:09:12.123456";
    auto datestring2    = "+0000__05-06-2017__08:09:12.1234567";
    auto unixTime       = timeconv::datestring_to_unixtime(datestring);
    auto unixTime2      = timeconv::datestring_to_unixtime(datestring2,
                                                           "%z__%d-%m-%Y__%H:%M:%11S");

    CHECK("+0000__05-06-2017__08:09:12"        == timeconv::unixtime_to_datestring(unixTime,0));
    CHECK("+0000__05-06-2017__08:09:12.1"      == timeconv::unixtime_to_datestring(unixTime,1));
    CHECK("+0000__05-06-2017__08:09:12.12"     == timeconv::unixtime_to_datestring(unixTime,2));
    CHECK("+0000__05-06-2017__08:09:12.123"    == timeconv::unixtime_to_datestring(unixTime,3));
    CHECK("+0000__05-06-2017__08:09:12.1235"   == timeconv::unixtime_to_datestring(unixTime,4));
    CHECK("+0000__05-06-2017__08:09:12.12346"  == timeconv::unixtime_to_datestring(unixTime,5));
    CHECK("+0000__05-06-2017__08:09:12.123456" == timeconv::unixtime_to_datestring(unixTime,6));
    CHECK("+0000__05-06-2017__08:09:12.123456" == timeconv::unixtime_to_datestring(unixTime,7));

    CHECK("+0000__05-06-2017__08:09:12.123457" == timeconv::unixtime_to_datestring(unixTime2,6));

}


TEST_CASE("datestring_to_unixtime: should read fractional second digits correctly", "[timeconv]")
{
    auto datestring     = "+0000__05-06-2017__08:09:12.123456";
    auto unixTime1      = timeconv::datestring_to_unixtime(datestring, "%z__%d-%m-%Y__%H:%M:%3S");
    auto unixTime2      = timeconv::datestring_to_unixtime(datestring, "%z__%d-%m-%Y__%H:%M:%4S");
    auto unixTime3      = timeconv::datestring_to_unixtime(datestring, "%z__%d-%m-%Y__%H:%M:%5S");
    auto unixTime4      = timeconv::datestring_to_unixtime(datestring, "%z__%d-%m-%Y__%H:%M:%6S");
    auto unixTime5      = timeconv::datestring_to_unixtime(datestring, "%z__%d-%m-%Y__%H:%M:%7S");
    auto unixTime6      = timeconv::datestring_to_unixtime(datestring, "%z__%d-%m-%Y__%H:%M:%8S");
    auto unixTime7      = timeconv::datestring_to_unixtime(datestring, "%z__%d-%m-%Y__%H:%M:%9S");
    auto unixTime8      = timeconv::datestring_to_unixtime(datestring, "%z__%d-%m-%Y__%H:%M:%10S");
    auto unixTime9      = timeconv::datestring_to_unixtime(datestring, "%z__%d-%m-%Y__%H:%M:%11S");

    CHECK("+0000__05-06-2017__08:09:12.000000" == timeconv::unixtime_to_datestring(unixTime1,6));
    CHECK("+0000__05-06-2017__08:09:12.100000" == timeconv::unixtime_to_datestring(unixTime2,6));
    CHECK("+0000__05-06-2017__08:09:12.120000" == timeconv::unixtime_to_datestring(unixTime3,6));
    CHECK("+0000__05-06-2017__08:09:12.123000" == timeconv::unixtime_to_datestring(unixTime4,6));
    CHECK("+0000__05-06-2017__08:09:12.123400" == timeconv::unixtime_to_datestring(unixTime5,6));
    CHECK("+0000__05-06-2017__08:09:12.123450" == timeconv::unixtime_to_datestring(unixTime6,6));
    CHECK("+0000__05-06-2017__08:09:12.123456" == timeconv::unixtime_to_datestring(unixTime7,6));
    CHECK("+0000__05-06-2017__08:09:12.123456" == timeconv::unixtime_to_datestring(unixTime8,6));
    CHECK("+0000__05-06-2017__08:09:12.123456" == timeconv::unixtime_to_datestring(unixTime9,6));

}


TEST_CASE("datestring_to_unixtime: should use UTC0 as default","[timeconv]")
{
    auto datestring = "05-06-2017__08:09:12";
    auto unixTime   = timeconv::datestring_to_unixtime(datestring, "%d-%m-%Y__%H:%M:%S");


    REQUIRE("+0000__05-06-2017__08:09:12" == timeconv::unixtime_to_datestring(unixTime));

}

}
