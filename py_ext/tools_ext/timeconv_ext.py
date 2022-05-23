# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

import time
from datetime import datetime

#import c++ module
from themachinethatgoesping.tools.timeconv import *



def datetime_to_datestring(dt : datetime, fractionalSecondsDigits: int = 0, format : str = '%z__%d-%m-%Y__%H:%M:%S') -> str:
    return unixtime_to_datestring(dt.timestamp(),
                                  fractionalSecondsDigits = fractionalSecondsDigits,
                                  format = format)

def datestring_to_datetime(datestring : str, format : str = '%z__%d-%m-%Y__%H:%M:%S') -> str:
    return datetime.fromtimestamp(datestring_to_unixtime(datestring,
                                                            format = format))
