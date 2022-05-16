// SPDX-FileCopyrightText: 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "DateTime.h"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <date/date.h>
//#include <date/tz.h>

using namespace std;
namespace themachinethatgoesping {

namespace tools {

namespace datetime {


/**
 * @brief UnixTime_to_TimePoint
 *        IMPORTANT: return value will only have microseconds precision!
 * @param UnixTime: Unix time stamp (seconds since 01.01.1970) as double
 * @return chrono::system_clock::time_point
 */
chrono::system_clock::time_point UnixTime_to_TimePoint(double UnixTime)
{
    chrono::duration<double> time_since_epoch(UnixTime);
    return (chrono::system_clock::time_point(chrono::duration_cast<chrono::microseconds>(time_since_epoch)));
}

/**
 * @brief conv_timePoint_to_timeStamp
 *        IMPORTANT: Conversion does only have microseconds precision!
 * @param TimePoint: chrono::system_clock::time_point
 * @return Unix time stamp (seconds since 01.01.1970) as double
 */
double TimePoint_to_UnixTime(chrono::system_clock::time_point TimePoint)
{
    chrono::microseconds us = chrono::duration_cast<chrono::microseconds>(TimePoint.time_since_epoch());

    auto timeUSec = static_cast<unsigned long long> (us.count());
    return ((double)timeUSec)/1000000.0;
}

/**
 * @brief DateString_to_UnixTime
 * Converting between date strings and UnixTime stampes (ref 1970)
 * date_string format:
 *      z: zone (in hhmm (as hours/minuts east of utc); z may only be at the beginning of the string!
 *          if no z is given the string will be interpreted as utc 0
 *      d: day as   int dd
 *      m: month as int mm
 *      b: month as string Bbb
 *      Y: year is  int YYYY
 *      H: hours as int HH
 *      M: Minutes as int mm
 *      S: Seconds as int SS
 *
 *      Default Format: "%z__%d-%m-%Y__%H:%M:%S"
 *
 * @param  DateString: DateString to be converted. Must fit format string.
 * @param  format: Format string to convert Date string.
 * @return UnixTime as double (seconds since 01.01.1970)
 */
double DateString_to_UnixTime(const string& DateString,
                              const string& format)
{
    date::sys_time<chrono::microseconds> timePoint;

    stringstream(DateString) >> date::parse(format,timePoint);

    return TimePoint_to_UnixTime(timePoint);

}

/**
 * @brief UnixTime_to_DateString
 * Converting between date strings and UnixTime stampes (ref 1970)
 * date_string format:
 *      z: zone (in hhmm (as hours/minuts east of utc); z may only be at the beginning of the string!
 *          if no z is given the string will be interpreted as utc 0
 *      d: day as   int dd
 *      m: month as int mm
 *      b: month as string Bbb
 *      Y: year is  int YYYY
 *      H: hours as int HH
 *      M: Minutes as int mm
 *      S: Seconds as int SS
 *
 * Default format is: "%z__%d-%m-%Y__%H:%M:%S."
 *
 * @param UnixTime: seconds since 01.01.1970 as double
 * @param fractionalSecondsDigits: How many digits to use for the split seconds.
 *          Minimum is 0 (second resolution)
 *          Maximum is 6 (microsecond resolutiuon)
 * @param format: Format string to convert Date string.
 * @return DateString that fits to the specified format
 */
string UnixTime_to_DateString(double UnixTime,
                              unsigned int fractionalSecondsDigits,
                              const string& format)
{
    // microsecond precision is the max
    if(fractionalSecondsDigits > 6)
        fractionalSecondsDigits = 6;

    double digits = pow(10,fractionalSecondsDigits);

    UnixTime = std::round(UnixTime * digits);
    UnixTime /= digits;

    auto time = UnixTime_to_TimePoint(UnixTime);

    auto datestring = date::format(format,time);

    /* remove fractional seconds digits */
    if (auto pos = datestring.find_last_of('.'); pos != string::npos)
    {
        if(fractionalSecondsDigits == 0){
            datestring.replace(pos,datestring.size(),"");
        }
        else
        {
            if(pos+fractionalSecondsDigits > datestring.size())
                fractionalSecondsDigits = datestring.size()-pos;

            datestring.replace(pos+fractionalSecondsDigits +1,datestring.size(),"");
        }
    }

    return datestring;

}



} //namespace datetime

} //namespace tools

} //namespace themachinethatgoesping
