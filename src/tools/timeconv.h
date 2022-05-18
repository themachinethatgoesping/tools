// SPDX-FileCopyrightText: 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**************************************************************************************************
 *
 * converting chrono time points / unix timestamps (double) and date time strings to each other
 *
***************************************************************************************************/

#pragma once

/* std includes */
#include <string>
#include <chrono>


namespace themachinethatgoesping {

namespace tools {

namespace timeconv {

//------------------------------------- time conversions ------------------------------------------
/* Converting between std::chrono time points and UnixTime stampes (ref 1970)
 */
std::chrono::system_clock::time_point UnixTime_to_TimePoint(double UnixTime);
double TimePoint_to_UnixTime(std::chrono::system_clock::time_point TimePoint);


//------------------------------------- time conversions ------------------------------------------
/* Converting between date strings and UnixTime stampes (ref 1970)
 * date_string format: Default: "%z__%d-%m-%Y__%H:%M:%S."
 *      z: zone (in hhmm (as hours/minuts east of utc); z may only be at the beginning of the string!
 *          if no z is given the string will be interpreted as utc 0
 *      d: day as   int dd
 *      m: month as int mm
 *      b: month as string Bbb
 *      Y: year is  int YYYY
 *      H: hours as int HH
 *      M: Minutes as int mm
 *      S: Seconds as int SS.SSSSSS
 *
 *      Default Format: "%z__%d-%m-%Y__%H:%M:%S"
 */
// date_string format: %d-%m-%Y_%H:%M:%S [where S is a double with microsecond precision)
double DateString_to_UnixTime(const std::string &DateString,
                              const std::string &format = std::string("%z__%d-%m-%Y__%H:%M:%S"));

// format: "%d-%m-%Y_%H:%M:%S" where seconds %S have microsecond precision
std::string UnixTime_to_DateString(double UnixTime,
                                   unsigned int fractionalSecondsDigits = 0,
                                   const std::string &format = std::string("%z__%d-%m-%Y__%H:%M:%S"));

} //namespace timeconv

} //namespace tools

} //namespace themachinethatgoesping
