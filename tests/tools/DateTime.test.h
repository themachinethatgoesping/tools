// SPDX-FileCopyrightText: 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <gtest/gtest.h>


#include <chrono>

#include "themachinethatgoesping/tools/DateTime.h"

using namespace testing;
using namespace std;
using namespace themachinethatgoesping;

namespace themachinethatgoespingToolsTests
{

TEST(UnixTime_to_TimePoint__Should,beReversible)
{
    auto now = chrono::system_clock::now();

    auto unixTime = DateTime::TimePoint_to_UnixTime(now);
    auto then     = DateTime::UnixTime_to_TimePoint(unixTime);
    ASSERT_EQ(0,chrono::duration_cast<chrono::microseconds>(now - then).count());

}

TEST(UnixTime_to_TimePoint__Should,notLooseMicrosecondsDuringTheConversation)
{

    auto now = chrono::system_clock::now();

    auto unixTime = DateTime::TimePoint_to_UnixTime(now);
    auto then     = DateTime::UnixTime_to_TimePoint(unixTime) - chrono::microseconds(1234567);

    ASSERT_EQ(1234567,chrono::duration_cast<chrono::microseconds>(now - then).count());


    unixTime = DateTime::TimePoint_to_UnixTime(now)       - (1234567.0 / 1000000.0);
    then     = DateTime::UnixTime_to_TimePoint(unixTime);

    ASSERT_EQ(1234567,chrono::duration_cast<chrono::microseconds>(now - then).count());
}

TEST(UnixTime_to_DateString__Should,beReversible)
{
    auto now = chrono::system_clock::now();

    auto unixTime   = DateTime::TimePoint_to_UnixTime(now);
    auto datestring = DateTime::UnixTime_to_DateString(unixTime,18);

    ASSERT_DOUBLE_EQ(unixTime, DateTime::DateString_to_UnixTime(datestring));

}

TEST(DateString_to_UnixTime__Should,beReversible)
{
    auto now = chrono::system_clock::now();

    auto unixTime   = DateTime::TimePoint_to_UnixTime(now);
    auto datestring = DateTime::UnixTime_to_DateString(unixTime,3);
    unixTime        = DateTime::DateString_to_UnixTime(datestring);

    ASSERT_EQ(datestring, DateTime::UnixTime_to_DateString(unixTime,3));

}


TEST(DateString_to_UnixTime__Should,convertZoneToUTCByDefault)
{
    auto datestring1  = "+0500__05-06-2017__08:09:12";
    auto datestring2  = "-0500__05-06-2017__08:09:12";

    auto unixTime1        = DateTime::DateString_to_UnixTime(datestring1);
    auto unixTime2        = DateTime::DateString_to_UnixTime(datestring2);

    ASSERT_EQ("+0000__05-06-2017__03:09:12",        DateTime::UnixTime_to_DateString(unixTime1,0));
    ASSERT_EQ("+0000__05-06-2017__13:09:12",        DateTime::UnixTime_to_DateString(unixTime2,0));

}


TEST(UnixTime_to_DateString__Should,roundFractionalSecondsCorrectly)
{
    auto datestring     = "+0000__05-06-2017__08:09:12.123456";
    auto datestring2    = "+0000__05-06-2017__08:09:12.1234567";
    auto unixTime       = DateTime::DateString_to_UnixTime(datestring);
    auto unixTime2      = DateTime::DateString_to_UnixTime(datestring2,
                                                           "%z__%d-%m-%Y__%H:%M:%11S");

    ASSERT_EQ("+0000__05-06-2017__08:09:12",        DateTime::UnixTime_to_DateString(unixTime,0));
    ASSERT_EQ("+0000__05-06-2017__08:09:12.1",      DateTime::UnixTime_to_DateString(unixTime,1));
    ASSERT_EQ("+0000__05-06-2017__08:09:12.12",     DateTime::UnixTime_to_DateString(unixTime,2));
    ASSERT_EQ("+0000__05-06-2017__08:09:12.123",    DateTime::UnixTime_to_DateString(unixTime,3));
    ASSERT_EQ("+0000__05-06-2017__08:09:12.1235",   DateTime::UnixTime_to_DateString(unixTime,4));
    ASSERT_EQ("+0000__05-06-2017__08:09:12.12346",  DateTime::UnixTime_to_DateString(unixTime,5));
    ASSERT_EQ("+0000__05-06-2017__08:09:12.123456", DateTime::UnixTime_to_DateString(unixTime,6));
    ASSERT_EQ("+0000__05-06-2017__08:09:12.123456", DateTime::UnixTime_to_DateString(unixTime,7));

    ASSERT_EQ("+0000__05-06-2017__08:09:12.123457", DateTime::UnixTime_to_DateString(unixTime2,6));

}


TEST(DateString_to_UnixTime__Should,readFractionalSecondDigitsCorrectly)
{
    auto datestring     = "+0000__05-06-2017__08:09:12.123456";
    auto unixTime1      = DateTime::DateString_to_UnixTime(datestring, "%z__%d-%m-%Y__%H:%M:%3S");
    auto unixTime2      = DateTime::DateString_to_UnixTime(datestring, "%z__%d-%m-%Y__%H:%M:%4S");
    auto unixTime3      = DateTime::DateString_to_UnixTime(datestring, "%z__%d-%m-%Y__%H:%M:%5S");
    auto unixTime4      = DateTime::DateString_to_UnixTime(datestring, "%z__%d-%m-%Y__%H:%M:%6S");
    auto unixTime5      = DateTime::DateString_to_UnixTime(datestring, "%z__%d-%m-%Y__%H:%M:%7S");
    auto unixTime6      = DateTime::DateString_to_UnixTime(datestring, "%z__%d-%m-%Y__%H:%M:%8S");
    auto unixTime7      = DateTime::DateString_to_UnixTime(datestring, "%z__%d-%m-%Y__%H:%M:%9S");
    auto unixTime8      = DateTime::DateString_to_UnixTime(datestring, "%z__%d-%m-%Y__%H:%M:%10S");
    auto unixTime9      = DateTime::DateString_to_UnixTime(datestring, "%z__%d-%m-%Y__%H:%M:%11S");

    ASSERT_EQ("+0000__05-06-2017__08:09:12.000000", DateTime::UnixTime_to_DateString(unixTime1,6));
    ASSERT_EQ("+0000__05-06-2017__08:09:12.100000", DateTime::UnixTime_to_DateString(unixTime2,6));
    ASSERT_EQ("+0000__05-06-2017__08:09:12.120000", DateTime::UnixTime_to_DateString(unixTime3,6));
    ASSERT_EQ("+0000__05-06-2017__08:09:12.123000", DateTime::UnixTime_to_DateString(unixTime4,6));
    ASSERT_EQ("+0000__05-06-2017__08:09:12.123400", DateTime::UnixTime_to_DateString(unixTime5,6));
    ASSERT_EQ("+0000__05-06-2017__08:09:12.123450", DateTime::UnixTime_to_DateString(unixTime6,6));
    ASSERT_EQ("+0000__05-06-2017__08:09:12.123456", DateTime::UnixTime_to_DateString(unixTime7,6));
    ASSERT_EQ("+0000__05-06-2017__08:09:12.123456", DateTime::UnixTime_to_DateString(unixTime8,6));
    ASSERT_EQ("+0000__05-06-2017__08:09:12.123456", DateTime::UnixTime_to_DateString(unixTime9,6));

}


TEST(DateString_to_UnixTime__Should,useUTC0asDefault)
{
    auto datestring     = "05-06-2017__08:09:12";
    auto unixTime      = DateTime::DateString_to_UnixTime(datestring, "%d-%m-%Y__%H:%M:%S");


    ASSERT_EQ("+0000__05-06-2017__08:09:12", DateTime::UnixTime_to_DateString(unixTime));

}

}
