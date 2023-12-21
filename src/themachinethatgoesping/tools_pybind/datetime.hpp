
// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
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

#include <fmt/core.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/embed.h>

#include <themachinethatgoesping/tools/timeconv.hpp>

namespace themachinethatgoesping {
namespace tools {
namespace pybind_helper {

pybind11::object unixtime_to_datetime(double timestamp, double timezone_offset_hours = 0.)
{
    namespace py = pybind11;

    py::module datetimeModule = py::module::import("datetime");
    py::object datetimeClass  = datetimeModule.attr("datetime");
    py::object timezoneClass  = datetimeModule.attr("timezone");
    py::object timedeltaClass = datetimeModule.attr("timedelta");

    py::object timezoneObject = timezoneClass(timedeltaClass(0, 0, 0, 0, 0, timezone_offset_hours));
    py::object datetimeObject = datetimeClass.attr("fromtimestamp")(timestamp, timezoneObject);

    return datetimeObject;
}

double datetime_to_unixtime(const pybind11::handle& datetimeObject)
{
    return pybind11::cast<double>(datetimeObject.attr("timestamp")());
}

}
}
}