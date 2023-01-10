# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.tools import timeconv

import time
import pytest


# define class for grouping (test sections)
class Test_tools_timeconv:
    # define actual tests (must start with "test_"
    # test case 1
    def test_unixtime_to_datestring_should_be_reversible(self):
        unixtime = time.time()

        assert timeconv.datestring_to_unixtime(
            timeconv.unixtime_to_datestring(unixtime)
        ) == pytest.approx(unixtime)

    # test case 2-0
    def test_datestring_to_unixtime_should_convert_specified_unixtime_to_specified_datestring(
        self,
    ):
        unixtime = 1234567890.123456
        datestring = "+0000__13-02-2009__23:31:30.123456"

        assert timeconv.datestring_to_unixtime(datestring) == pytest.approx(unixtime)
        assert (
            timeconv.unixtime_to_datestring(unixtime, fractionalSecondsDigits=6)
            == datestring
        )

    # test case 2-1
    def test_datestring_to_unixtime_should_be_reversible(self):
        unixtime = time.time()
        datestring = timeconv.unixtime_to_datestring(
            unixtime, fractionalSecondsDigits=3
        )

        assert (
            timeconv.unixtime_to_datestring(
                timeconv.datestring_to_unixtime(datestring), fractionalSecondsDigits=3
            )
            == datestring
        )

    # test case 3
    def test_datestring_to_unixtime_should_convert_zone_to_UTC_by_default(self):
        datestring1 = "+0500__05-06-2017__08:09:12"
        datestring2 = "-0500__05-06-2017__08:09:12"

        unixtime1 = timeconv.datestring_to_unixtime(datestring1)
        unixtime2 = timeconv.datestring_to_unixtime(datestring2)

        assert "+0000__05-06-2017__03:09:12" == timeconv.unixtime_to_datestring(
            unixtime1, 0
        )
        assert "+0000__05-06-2017__13:09:12" == timeconv.unixtime_to_datestring(
            unixtime2, 0
        )

    # test case 4
    def test_unixtime_to_datestring_should_round_fractional_seconds_correctly(self):
        datestring = "+0000__05-06-2017__08:09:12.123456"
        datestring2 = "+0000__05-06-2017__08:09:12.1234567"
        unixtime = timeconv.datestring_to_unixtime(datestring)
        unixtime2 = timeconv.datestring_to_unixtime(
            datestring2, "%z__%d-%m-%Y__%H:%M:%11S"
        )

        assert "+0000__05-06-2017__08:09:12" == timeconv.unixtime_to_datestring(
            unixtime, 0
        )
        assert "+0000__05-06-2017__08:09:12.1" == timeconv.unixtime_to_datestring(
            unixtime, 1
        )
        assert "+0000__05-06-2017__08:09:12.12" == timeconv.unixtime_to_datestring(
            unixtime, 2
        )
        assert "+0000__05-06-2017__08:09:12.123" == timeconv.unixtime_to_datestring(
            unixtime, 3
        )
        assert "+0000__05-06-2017__08:09:12.1235" == timeconv.unixtime_to_datestring(
            unixtime, 4
        )
        assert "+0000__05-06-2017__08:09:12.12346" == timeconv.unixtime_to_datestring(
            unixtime, 5
        )
        assert "+0000__05-06-2017__08:09:12.123456" == timeconv.unixtime_to_datestring(
            unixtime, 6
        )
        assert "+0000__05-06-2017__08:09:12.123456" == timeconv.unixtime_to_datestring(
            unixtime, 7
        )

        assert "+0000__05-06-2017__08:09:12.123457" == timeconv.unixtime_to_datestring(
            unixtime2, 6
        )

    # test case 5
    def test_datestring_to_unixtime_should_read_fractional_second_digits_correctly(
        self,
    ):
        datestring = "+0000__05-06-2017__08:09:12.123456"
        unixtime1 = timeconv.datestring_to_unixtime(
            datestring, "%z__%d-%m-%Y__%H:%M:%3S"
        )
        unixtime2 = timeconv.datestring_to_unixtime(
            datestring, "%z__%d-%m-%Y__%H:%M:%4S"
        )
        unixtime3 = timeconv.datestring_to_unixtime(
            datestring, "%z__%d-%m-%Y__%H:%M:%5S"
        )
        unixtime4 = timeconv.datestring_to_unixtime(
            datestring, "%z__%d-%m-%Y__%H:%M:%6S"
        )
        unixtime5 = timeconv.datestring_to_unixtime(
            datestring, "%z__%d-%m-%Y__%H:%M:%7S"
        )
        unixtime6 = timeconv.datestring_to_unixtime(
            datestring, "%z__%d-%m-%Y__%H:%M:%8S"
        )
        unixtime7 = timeconv.datestring_to_unixtime(
            datestring, "%z__%d-%m-%Y__%H:%M:%9S"
        )
        unixtime8 = timeconv.datestring_to_unixtime(
            datestring, "%z__%d-%m-%Y__%H:%M:%10S"
        )
        unixtime9 = timeconv.datestring_to_unixtime(
            datestring, "%z__%d-%m-%Y__%H:%M:%11S"
        )

        assert "+0000__05-06-2017__08:09:12.000000" == timeconv.unixtime_to_datestring(
            unixtime1, 6
        )
        assert "+0000__05-06-2017__08:09:12.100000" == timeconv.unixtime_to_datestring(
            unixtime2, 6
        )
        assert "+0000__05-06-2017__08:09:12.120000" == timeconv.unixtime_to_datestring(
            unixtime3, 6
        )
        assert "+0000__05-06-2017__08:09:12.123000" == timeconv.unixtime_to_datestring(
            unixtime4, 6
        )
        assert "+0000__05-06-2017__08:09:12.123400" == timeconv.unixtime_to_datestring(
            unixtime5, 6
        )
        assert "+0000__05-06-2017__08:09:12.123450" == timeconv.unixtime_to_datestring(
            unixtime6, 6
        )
        assert "+0000__05-06-2017__08:09:12.123456" == timeconv.unixtime_to_datestring(
            unixtime7, 6
        )
        assert "+0000__05-06-2017__08:09:12.123456" == timeconv.unixtime_to_datestring(
            unixtime8, 6
        )
        assert "+0000__05-06-2017__08:09:12.123456" == timeconv.unixtime_to_datestring(
            unixtime9, 6
        )

    def test_year_month_day_to_unixtime_should_convert_specified_ymd_to_specified_unixtime(
        self,
    ):
        datestring = "+0000__13-02-2009__23:31:30.123456" # to check that the ymd result is equivalent to this datestring
        unixtime = 1234567890.123456

        y = 2009
        m = 2
        d = 13
        us = 123456 + 1000000 * (30 + 31*60 + 23*3600)

        assert timeconv.datestring_to_unixtime(datestring) == pytest.approx(unixtime)
        assert timeconv.year_month_day_to_unixtime(y, m, d, us) == pytest.approx(unixtime)
