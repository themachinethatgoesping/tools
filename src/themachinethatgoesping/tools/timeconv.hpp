// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 Tim Weiß, GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief Converting chrono time points / unix timestamps (double) and date time
 * strings to each other. unix timestamps are always treated as UTC
 * @authors Peter Urban
 *
 */

#pragma once

/* generated doc strings */
#include ".docstrings/timeconv.doc.hpp"

#include <chrono>
#include <string>
#include <utility> // for std::pair

namespace themachinethatgoesping {

namespace tools {

namespace timeconv {

/**
 * @brief Converts a UNIX timestamp (seconds since epoch, UTC) to a std::chrono::system_clock::time_point.
 * @param unixtime UNIX timestamp as double (seconds since 1970-01-01T00:00:00Z)
 * @return Corresponding std::chrono::system_clock::time_point
 */
std::chrono::system_clock::time_point unixtime_to_timepoint(double unixtime);

/**
 * @brief Converts a std::chrono::system_clock::time_point to a UNIX timestamp (seconds since epoch, UTC).
 * @param TimePoint Time point to convert
 * @return UNIX timestamp as double (seconds since 1970-01-01T00:00:00Z)
 */
double timepoint_to_unixtime(std::chrono::system_clock::time_point TimePoint);

/**
 * @brief Converts a calendar date (year, month, day) and optional microseconds to a UNIX timestamp.
 * @param year Year (e.g. 2024)
 * @param month Month (1-12)
 * @param day Day (1-31)
 * @param micro_seconds Optional microseconds to add
 * @return UNIX timestamp as double (seconds since 1970-01-01T00:00:00Z)
 */
double year_month_day_to_unixtime(int year, int month, int day, uint64_t micro_seconds = 0);

/**
 * @brief Parses a date/time string to a UNIX timestamp using the specified format.
 * @param DateString Date/time string to parse
 * @param format Format string (default: "%z__%d-%m-%Y__%H:%M:%S")
 * @return UNIX timestamp as double (seconds since 1970-01-01T00:00:00Z)
 */
double datestring_to_unixtime(std::string_view DateString,
                              const std::string& format = "%z__%d-%m-%Y__%H:%M:%S");

/**
 * @brief Converts a UNIX timestamp to a formatted date/time string.
 * @param unixtime UNIX timestamp as double (seconds since 1970-01-01T00:00:00Z)
 * @param fractionalSecondsDigits Number of digits for fractional seconds (default: 0)
 * @param format Format string (default: "%z__%d-%m-%Y__%H:%M:%S")
 * @return Formatted date/time string
 */
std::string unixtime_to_datestring(double             unixtime,
                                   unsigned int       fractionalSecondsDigits = 0,
                                   const std::string& format = "%z__%d-%m-%Y__%H:%M:%S");

/**
 * @brief Converts Windows FILETIME (high/low 32-bit values) to UNIX timestamp.
 * @param highDateTime High 32 bits of FILETIME
 * @param lowDateTime Low 32 bits of FILETIME
 * @return UNIX timestamp as double (seconds since 1970-01-01T00:00:00Z)
 */
double windows_filetime_to_unixtime(uint32_t highDateTime, uint32_t lowDateTime);

/**
 * @brief Converts a UNIX timestamp to Windows FILETIME (high/low 32-bit values).
 * @param unixtime UNIX timestamp as double (seconds since 1970-01-01T00:00:00Z)
 * @return Pair of high and low 32-bit FILETIME values
 */
std::pair<uint32_t, uint32_t> unixtime_to_windows_filetime(double unixtime);

} // namespace timeconv

} // namespace tools

} // namespace themachinethatgoesping
