# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

"""
This module extends the tools.timeconv with some functions implemented in pure python

"""

import time
from datetime import datetime

# import c++ module
from themachinethatgoesping.tools.timeconv import *


def datetime_to_datestring(dt: datetime, fractionalSecondsDigits: int = 0,
                           format: str = '%z__%d-%m-%Y__%H:%M:%S') -> str:
    """ 
    Converting between date strings and python datetime objects
    date_string format:
        z: zone (in hhmm (as hours/minuts east of utc)  
            z may only be at the beginning of the string!
            If no z is given the string will be interpreted as utc 0
            d: day as   int dd
            m: month as int mm
            b: month as string bb
            Y: year is  int YYYY
            H: hours as int HH
            M: Minutes as int mm
            S: Seconds as int SS

    :param dt: 
        datetime to be converted
    :param fractionalSecondsDigits: 
        How many digits to use for the split seconds.
            Minimum is 0 (second resolution)
            Maximum is 6 (microsecond resolutiuon)
    :param format: 
        Format string to convert Date string. Default Format:
        "%z__%d-%m-%Y__%H:%M:%S" see:
        https://m.cplusplus.com/reference/ctime/strftime/
    :return: 
        DateString that fits to the specified format
    """

    return unixtime_to_datestring(dt.timestamp(),
                                  fractionalSecondsDigits=fractionalSecondsDigits,
                                  format=format)


def datestring_to_datetime(datestring: str,
                           format: str = '%z__%d-%m-%Y__%H:%M:%S') -> datetime:
    """
    Converting between date strings and python datetime objects
    date_string format:
        z: zone (in hhmm (as hours/minuts east of utc)  
            z may only be at the beginning of the string!
            If no z is given the string will be interpreted as utc 0
            d: day as   int dd
            m: month as int mm
            b: month as string bb
            Y: year is  int YYYY
            H: hours as int HH
            M: Minutes as int mm
            S: Seconds as int SS

    :param datestring: 
        DateString to be converted. Must fit format string.
    :param format:
        Format string to convert Date string. Default Format:
        "%z__%d-%m-%Y__%H:%M:%S" see
        https://m.cplusplus.com/reference/ctime/strftime/
    :return: 
        python datetime object
    """
    return datetime.fromtimestamp(datestring_to_unixtime(datestring,
                                                         format=format))
