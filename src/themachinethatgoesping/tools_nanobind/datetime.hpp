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

#include <fmt/core.h>
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/string_view.h>
#include <nanobind/stl/chrono.h>
#include <themachinethatgoesping/tools/timeconv.hpp>

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
inline nanobind::object unixtime_to_datetime(double timestamp, double timezone_offset_hours = 0.)
{
    nanobind::module_ datetimeModule = nanobind::module_::import_("datetime");
    nanobind::object datetimeClass  = datetimeModule.attr("datetime");
    nanobind::object timezoneClass  = datetimeModule.attr("timezone");
    nanobind::object timedeltaClass = datetimeModule.attr("timedelta");

    nanobind::object timezoneObject = timezoneClass(timedeltaClass(nanobind::arg("hours") = timezone_offset_hours));
    nanobind::object datetimeObject = datetimeClass.attr("fromtimestamp")(timestamp, timezoneObject);

    return datetimeObject;
}

/**
 * @brief Converts a Python datetime object to a Unix timestamp.
 *
 * @param datetimeObject The Python datetime object to convert.
 * @return The Unix timestamp representing the given datetime.
 */
inline double datetime_to_unixtime(const nanobind::handle& datetimeObject)
{
    return nanobind::cast<double>(datetimeObject.attr("timestamp")());
}

/**
 * @brief Converts a date string to a Python datetime object using the specified format.
 *
 */
inline nanobind::object datestring_to_datetime(
    std::string_view datestring,
    const std::string& format = "%z__%d-%m-%Y__%H:%M:%S",
    double timezone_offset_hours = 0.)
{
    return unixtime_to_datetime(timeconv::datestring_to_unixtime(datestring, format), timezone_offset_hours);
}

/**
 * @brief Converts a Python datetime object to a formatted date string.
 *
 * @param datetimeObject The Python datetime object to convert.
 * @param fractionalSecondsDigits Number of fractional seconds digits to include.
 * @param format The format string to use for conversion.
 * @return The formatted date string.
 */
inline std::string datetime_to_datestring(
    const nanobind::handle& datetimeObject,
    unsigned int fractionalSecondsDigits = 0,
    const std::string& format = "%z__%d-%m-%Y__%H:%M:%S")
{
    // Convert the datetime object to unixtime first, then use timeconv to format it
    double unixtime = datetime_to_unixtime(datetimeObject);
    return timeconv::unixtime_to_datestring(unixtime, fractionalSecondsDigits, format);
}

} // namespace nanobind_helper
} // namespace tools
} // namespace themachinethatgoesping