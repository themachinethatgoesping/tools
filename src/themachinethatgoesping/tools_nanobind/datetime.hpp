// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief some macros to easily implement common datetime capabilities for nanobind classes
 *
 * @authors Peter Urban
 */

#pragma once

/* generated doc strings */
#include ".docstrings/datetime.doc.hpp"

// Only need nanobind type declarations for object/handle
#include <nanobind/nanobind.h>

namespace themachinethatgoesping {
namespace tools {
namespace nanobind_helper {

/**
 * @brief Converts a Unix timestamp to a Python datetime object.
 *
 * @param timestamp The Unix timestamp to convert.
 * @param timezone_offset_hours The timezone offset in hours (default: 0).
 * @return The Python datetime object representing the given timestamp.
 */
__attribute__((visibility("default"))) nanobind::object unixtime_to_datetime(
    double timestamp,
    double timezone_offset_hours = 0.);

/**
 * @brief Converts a Python datetime object to a Unix timestamp.
 *
 * @param datetimeObject The Python datetime object to convert.
 * @return The Unix timestamp representing the given datetime.
 */
__attribute__((visibility("default"))) double datetime_to_unixtime(
    const nanobind::handle& datetimeObject);

/**
 * @brief Converts a date string to a Python datetime object using the specified format.
 *
 */
__attribute__((visibility("default"))) nanobind::object datestring_to_datetime(
    std::string_view datestring,
    const std::string& format                = "%z__%d-%m-%Y__%H:%M:%S",
    double           timezone_offset_hours = 0.);

/**
 * @brief Converts a Python datetime object to a formatted date string.
 *
 * @param datetimeObject The Python datetime object to convert.
 * @param fractionalSecondsDigits Number of fractional seconds digits to include.
 * @param format The format string to use for conversion.
 * @return The formatted date string.
 */
__attribute__((visibility("default"))) std::string datetime_to_datestring(
    const nanobind::handle& datetimeObject,
    unsigned int fractionalSecondsDigits = 0,
    const std::string& format = "%z__%d-%m-%Y__%H:%M:%S");

} // namespace nanobind_helper
} // namespace tools
} // namespace themachinethatgoesping