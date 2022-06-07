// SPDX-FileCopyrightText: 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @file timeconv.h
 * @brief Converting chrono time points / unix timestamps (double) and date time
 * strings to each other
 * @authors Peter Urban
 * @copyright 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
 * @copyright 2022 Ghent University
 *
 */

#pragma once

/* std includes */
#include <chrono>
#include <string>

namespace themachinethatgoesping {

namespace tools {

namespace timeconv {

//------------------------------------- time conversions
//------------------------------------------
/**
 * @brief unixtime_to_timepoint
 *        IMPORTANT: return value will only have microseconds precision!
 * @param UnixTime: Unix time stamp (seconds since 01.01.1970) as double
 * @return chrono::system_clock::time_point
 */
std::chrono::system_clock::time_point unixtime_to_timepoint(double UnixTime);

/**
 * @brief timepoint_to_unixtime
 *        IMPORTANT: Conversion does only have microseconds precision!
 * @param TimePoint: chrono::system_clock::time_point
 * @return Unix time stamp (seconds since 01.01.1970) as double
 */
double timepoint_to_unixtime(std::chrono::system_clock::time_point TimePoint);

//------------------------------------- time conversions
//------------------------------------------
/**
 * @brief Converting between date strings and UnixTime stampes (ref 1970)
 *
 * @param  DateString: DateString to be converted. Must fit format string.
 * @param  format: Format string to convert Date string.
 *      Default Format: "%z__%d-%m-%Y__%H:%M:%S"
 *      see https://m.cplusplus.com/reference/ctime/strftime/ *
        https://themachinethatgoesping.readthedocs.io/en/latest/modules/tools/timeconv.html#format-string
 * @return UnixTime as double (seconds since 01.01.1970)
 */
double datestring_to_unixtime(
    const std::string& DateString,
    const std::string& format = std::string("%z__%d-%m-%Y__%H:%M:%S"));

/**
 * @brief Converting between date strings and UnixTime stampes (ref 1970)
 *
 * @param UnixTime: seconds since 01.01.1970 as double
 * @param fractionalSecondsDigits: How many digits to use for the split seconds.
 *          Minimum is 0 (second resolution)
 *          Maximum is 6 (microsecond resolutiuon)
 * @param format: Format string to convert Date string.
 *      Default Format: "%z__%d-%m-%Y__%H:%M:%S"
 *      see: https://m.cplusplus.com/reference/ctime/strftime/ *
        https://themachinethatgoesping.readthedocs.io/en/latest/modules/tools/timeconv.html#format-string
 * @return DateString that fits to the specified format
 */
std::string unixtime_to_datestring(
    double UnixTime, unsigned int fractionalSecondsDigits = 0,
    const std::string& format = std::string("%z__%d-%m-%Y__%H:%M:%S"));

}  // namespace timeconv

}  // namespace tools

}  // namespace themachinethatgoesping
