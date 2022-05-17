// SPDX-FileCopyrightText: 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <chrono>

#include <tools/datetime.h>

//using namespace testing;
using namespace std;
using namespace themachinethatgoesping::tools;

namespace themachinethatgoesping_tools_tests
{

TEST_CASE("UnixTime_to_TimePoint: should be reversible","[datetime]")
{
    auto now = chrono::system_clock::now();

    auto unixTime = datetime::TimePoint_to_UnixTime(now);
    auto then     = datetime::UnixTime_to_TimePoint(unixTime);
    REQUIRE(chrono::duration_cast<chrono::microseconds>(now - then).count() == 0);

}

TEST_CASE("UnixTime_to_TimePoint: should not loose microseconds during the conversation","[datetime]")
{

    auto now = chrono::system_clock::now();

    auto unixTime = datetime::TimePoint_to_UnixTime(now);
    auto then     = datetime::UnixTime_to_TimePoint(unixTime) - chrono::microseconds(1234567);

    REQUIRE(chrono::duration_cast<chrono::microseconds>(now - then).count() == 1234567);


    unixTime = datetime::TimePoint_to_UnixTime(now)       - (1234567.0 / 1000000.0);
    then     = datetime::UnixTime_to_TimePoint(unixTime);

    REQUIRE(chrono::duration_cast<chrono::microseconds>(now - then).count() == 1234567);
}

TEST_CASE("UnixTime_to_DateString: should be reversible","[datetime]")
{
    auto now = chrono::system_clock::now();

    auto unixTime   = datetime::TimePoint_to_UnixTime(now);
    auto datestring = datetime::UnixTime_to_DateString(unixTime,18);

    REQUIRE(datetime::DateString_to_UnixTime(datestring) == Approx(unixTime));

}

TEST_CASE("DateString_to_UnixTime: should be reversible","[datetime]")
{
    auto now = chrono::system_clock::now();

    auto unixTime   = datetime::TimePoint_to_UnixTime(now);
    auto datestring = datetime::UnixTime_to_DateString(unixTime,3);
    unixTime        = datetime::DateString_to_UnixTime(datestring);

    REQUIRE(datetime::UnixTime_to_DateString(unixTime,3) == datestring);
}


TEST_CASE("DateString_to_UnixTime: should convert zone to UTC by default","[datetime]")
{
    auto datestring1  = "+0500__05-06-2017__08:09:12";
    auto datestring2  = "-0500__05-06-2017__08:09:12";

    auto unixTime1        = datetime::DateString_to_UnixTime(datestring1);
    auto unixTime2        = datetime::DateString_to_UnixTime(datestring2);

    REQUIRE("+0000__05-06-2017__03:09:12" == datetime::UnixTime_to_DateString(unixTime1,0));
    REQUIRE("+0000__05-06-2017__13:09:12" == datetime::UnixTime_to_DateString(unixTime2,0));

}


TEST_CASE("UnixTime_to_DateString: should round fractional seconds correctly","[datetime]")
{
    auto datestring     = "+0000__05-06-2017__08:09:12.123456";
    auto datestring2    = "+0000__05-06-2017__08:09:12.1234567";
    auto unixTime       = datetime::DateString_to_UnixTime(datestring);
    auto unixTime2      = datetime::DateString_to_UnixTime(datestring2,
                                                           "%z__%d-%m-%Y__%H:%M:%11S");

    CHECK("+0000__05-06-2017__08:09:12"        == datetime::UnixTime_to_DateString(unixTime,0));
    CHECK("+0000__05-06-2017__08:09:12.1"      == datetime::UnixTime_to_DateString(unixTime,1));
    CHECK("+0000__05-06-2017__08:09:12.12"     == datetime::UnixTime_to_DateString(unixTime,2));
    CHECK("+0000__05-06-2017__08:09:12.123"    == datetime::UnixTime_to_DateString(unixTime,3));
    CHECK("+0000__05-06-2017__08:09:12.1235"   == datetime::UnixTime_to_DateString(unixTime,4));
    CHECK("+0000__05-06-2017__08:09:12.12346"  == datetime::UnixTime_to_DateString(unixTime,5));
    CHECK("+0000__05-06-2017__08:09:12.123456" == datetime::UnixTime_to_DateString(unixTime,6));
    CHECK("+0000__05-06-2017__08:09:12.123456" == datetime::UnixTime_to_DateString(unixTime,7));

    CHECK("+0000__05-06-2017__08:09:12.123457" == datetime::UnixTime_to_DateString(unixTime2,6));

}


TEST_CASE("DateString_to_UnixTime: should read fractional second digits correctly", "[datetime]")
{
    auto datestring     = "+0000__05-06-2017__08:09:12.123456";
    auto unixTime1      = datetime::DateString_to_UnixTime(datestring, "%z__%d-%m-%Y__%H:%M:%3S");
    auto unixTime2      = datetime::DateString_to_UnixTime(datestring, "%z__%d-%m-%Y__%H:%M:%4S");
    auto unixTime3      = datetime::DateString_to_UnixTime(datestring, "%z__%d-%m-%Y__%H:%M:%5S");
    auto unixTime4      = datetime::DateString_to_UnixTime(datestring, "%z__%d-%m-%Y__%H:%M:%6S");
    auto unixTime5      = datetime::DateString_to_UnixTime(datestring, "%z__%d-%m-%Y__%H:%M:%7S");
    auto unixTime6      = datetime::DateString_to_UnixTime(datestring, "%z__%d-%m-%Y__%H:%M:%8S");
    auto unixTime7      = datetime::DateString_to_UnixTime(datestring, "%z__%d-%m-%Y__%H:%M:%9S");
    auto unixTime8      = datetime::DateString_to_UnixTime(datestring, "%z__%d-%m-%Y__%H:%M:%10S");
    auto unixTime9      = datetime::DateString_to_UnixTime(datestring, "%z__%d-%m-%Y__%H:%M:%11S");

    CHECK("+0000__05-06-2017__08:09:12.000000" == datetime::UnixTime_to_DateString(unixTime1,6));
    CHECK("+0000__05-06-2017__08:09:12.100000" == datetime::UnixTime_to_DateString(unixTime2,6));
    CHECK("+0000__05-06-2017__08:09:12.120000" == datetime::UnixTime_to_DateString(unixTime3,6));
    CHECK("+0000__05-06-2017__08:09:12.123000" == datetime::UnixTime_to_DateString(unixTime4,6));
    CHECK("+0000__05-06-2017__08:09:12.123400" == datetime::UnixTime_to_DateString(unixTime5,6));
    CHECK("+0000__05-06-2017__08:09:12.123450" == datetime::UnixTime_to_DateString(unixTime6,6));
    CHECK("+0000__05-06-2017__08:09:12.123456" == datetime::UnixTime_to_DateString(unixTime7,6));
    CHECK("+0000__05-06-2017__08:09:12.123456" == datetime::UnixTime_to_DateString(unixTime8,6));
    CHECK("+0000__05-06-2017__08:09:12.123456" == datetime::UnixTime_to_DateString(unixTime9,6));

}


TEST_CASE("DateString_to_UnixTime: should use UTC0 as default","[datetime]")
{
    auto datestring = "05-06-2017__08:09:12";
    auto unixTime   = datetime::DateString_to_UnixTime(datestring, "%d-%m-%Y__%H:%M:%S");


    REQUIRE("+0000__05-06-2017__08:09:12" == datetime::UnixTime_to_DateString(unixTime));

}

}
