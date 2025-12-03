# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.tools import timeconv

from datetime import datetime, timezone

# import time
# import pytest

# This tests the python extensions in tools (timeconv_ext)

# define class for grouping (test sections)


class Test_tools_timeconv_ext:
    # define actual tests (must start with "test_"
    # test case 1
    def test_datetime_to_datestring_should_be_reversible(self):
        dt = datetime.now(timezone.utc)

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
        dt1 = timeconv.datestring_to_datetime(datestring)

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


    # test case 5
    def test_datestring_to_datetime_should_read_fractional_second_digits_correctly(
        self,
    ):
        datestring = "+0000__05-06-2017__08:09:12.123456"
        dt1 = timeconv.datestring_to_datetime(datestring, "%z__%d-%m-%Y__%H:%M:%S")
\
        assert "+0000__05-06-2017__08:09:12.123456" == timeconv.datetime_to_datestring(
            dt1, 6
        )
