// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief some macros to easily implement common enum capabilities for for pybind classes
 *
 * @authors Peter Urban
 */

#pragma once

/* generated doc strings */
#include ".docstrings/datetime.doc.hpp"

// Only need pybind11 type declarations for object/handle
#include <pybind11/pytypes.h>

namespace themachinethatgoesping {
namespace tools {
namespace pybind_helper {

/**
 * @brief Converts a Unix timestamp to a Python datetime object.
 *
 * @param timestamp The Unix timestamp to convert.
 * @param timezone_offset_hours The timezone offset in hours (default: 0).
 * @return The Python datetime object representing the given timestamp.
 */
__attribute__((visibility("default")))
pybind11::object unixtime_to_datetime(double timestamp, double timezone_offset_hours = 0.);

/**
 * @brief Converts a Python datetime object to a Unix timestamp.
 *
 * @param datetimeObject The Python datetime object to convert.
 * @return The Unix timestamp representing the given datetime.
 */
__attribute__((visibility("default")))
double datetime_to_unixtime(const pybind11::handle& datetimeObject);

} // namespace pybind_helper
} // namespace tools
} // namespace themachinethatgoesping