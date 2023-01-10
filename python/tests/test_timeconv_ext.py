# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.tools_ext import timeconv

from datetime import datetime

# import time
# import pytest

# This tests the python extensions in tools_ext (timeconv_ext)

# define class for grouping (test sections)


class Test_tools_timeconv_ext:
    # define actual tests (must start with "test_"
    # test case 1
    def test_datetime_to_datestring_should_be_reversible(self):
        dt = datetime.now()

        assert (
            timeconv.datestring_to_datetime(
                timeconv.datetime_to_datestring(dt, fractionalSecondsDigits=6)
            )
            == dt
        )

    # test case 2
    def test_datestring_to_datetime_should_be_reversible(self):
        dt = datetime.now()
        datestring = timeconv.datetime_to_datestring(dt, fractionalSecondsDigits=3)

        assert (
            timeconv.datetime_to_datestring(
                timeconv.datestring_to_datetime(datestring), fractionalSecondsDigits=3
            )
            == datestring
        )

    # test case 3
    def test_datestring_to_datetime_should_convert_zone_to_UTC_by_default(self):
        datestring1 = "+0500__05-06-2017__08:09:12"
        datestring2 = "-0500__05-06-2017__08:09:12"

        dt1 = timeconv.datestring_to_datetime(datestring1)
        dt2 = timeconv.datestring_to_datetime(datestring2)

        assert "+0000__05-06-2017__03:09:12" == timeconv.datetime_to_datestring(dt1, 0)
        assert "+0000__05-06-2017__13:09:12" == timeconv.datetime_to_datestring(dt2, 0)

    # test case 4
    def test_datetime_to_datestring_should_round_fractional_seconds_correctly(self):
        datestring = "+0000__05-06-2017__08:09:12.123456"
        datestring2 = "+0000__05-06-2017__08:09:12.1234567"
        dt1 = timeconv.datestring_to_datetime(datestring)
        dt2 = timeconv.datestring_to_datetime(
            datestring2, format="%z__%d-%m-%Y__%H:%M:%11S"
        )

        assert "+0000__05-06-2017__08:09:12" == timeconv.datetime_to_datestring(dt1, 0)
        assert "+0000__05-06-2017__08:09:12.1" == timeconv.datetime_to_datestring(
            dt1, 1
        )
        assert "+0000__05-06-2017__08:09:12.12" == timeconv.datetime_to_datestring(
            dt1, 2
        )
        assert "+0000__05-06-2017__08:09:12.123" == timeconv.datetime_to_datestring(
            dt1, 3
        )
        assert "+0000__05-06-2017__08:09:12.1235" == timeconv.datetime_to_datestring(
            dt1, 4
        )
        assert "+0000__05-06-2017__08:09:12.12346" == timeconv.datetime_to_datestring(
            dt1, 5
        )
        assert "+0000__05-06-2017__08:09:12.123456" == timeconv.datetime_to_datestring(
            dt1, 6
        )
        assert "+0000__05-06-2017__08:09:12.123456" == timeconv.datetime_to_datestring(
            dt1, 7
        )

        assert "+0000__05-06-2017__08:09:12.123457" == timeconv.datetime_to_datestring(
            dt2, 6
        )

    # test case 5
    def test_datestring_to_datetime_should_read_fractional_second_digits_correctly(
        self,
    ):
        datestring = "+0000__05-06-2017__08:09:12.123456"
        dt1 = timeconv.datestring_to_datetime(datestring, "%z__%d-%m-%Y__%H:%M:%3S")
        dt2 = timeconv.datestring_to_datetime(datestring, "%z__%d-%m-%Y__%H:%M:%4S")
        dt3 = timeconv.datestring_to_datetime(datestring, "%z__%d-%m-%Y__%H:%M:%5S")
        dt4 = timeconv.datestring_to_datetime(datestring, "%z__%d-%m-%Y__%H:%M:%6S")
        dt5 = timeconv.datestring_to_datetime(datestring, "%z__%d-%m-%Y__%H:%M:%7S")
        dt6 = timeconv.datestring_to_datetime(datestring, "%z__%d-%m-%Y__%H:%M:%8S")
        dt7 = timeconv.datestring_to_datetime(datestring, "%z__%d-%m-%Y__%H:%M:%9S")
        dt8 = timeconv.datestring_to_datetime(datestring, "%z__%d-%m-%Y__%H:%M:%10S")
        dt9 = timeconv.datestring_to_datetime(datestring, "%z__%d-%m-%Y__%H:%M:%11S")

        assert "+0000__05-06-2017__08:09:12.000000" == timeconv.datetime_to_datestring(
            dt1, 6
        )
        assert "+0000__05-06-2017__08:09:12.100000" == timeconv.datetime_to_datestring(
            dt2, 6
        )
        assert "+0000__05-06-2017__08:09:12.120000" == timeconv.datetime_to_datestring(
            dt3, 6
        )
        assert "+0000__05-06-2017__08:09:12.123000" == timeconv.datetime_to_datestring(
            dt4, 6
        )
        assert "+0000__05-06-2017__08:09:12.123400" == timeconv.datetime_to_datestring(
            dt5, 6
        )
        assert "+0000__05-06-2017__08:09:12.123450" == timeconv.datetime_to_datestring(
            dt6, 6
        )
        assert "+0000__05-06-2017__08:09:12.123456" == timeconv.datetime_to_datestring(
            dt7, 6
        )
        assert "+0000__05-06-2017__08:09:12.123456" == timeconv.datetime_to_datestring(
            dt8, 6
        )
        assert "+0000__05-06-2017__08:09:12.123456" == timeconv.datetime_to_datestring(
            dt9, 6
        )
