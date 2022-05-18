// SPDX-FileCopyrightText: 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "m_timeconv.h"

// -- c++ library headers
#include "../tools/timeconv.h"

// -- include system headers
#include <sstream>

// -- include pybind11 headers
#include <pybind11/chrono.h>
#include <pybind11/stl.h>

namespace py = pybind11;
namespace pingtools = themachinethatgoesping::tools;

void init_m_timeconv(py::module &m)
{
    auto m_time = m.def_submodule("timeconv", "Convinient functions for converting time strings.");

    {
        m_time.def("UnixTime_to_TimePoint", &pingtools::timeconv::UnixTime_to_TimePoint,
                   // doc.str().c_str(),
                   py::arg("unixtime"));
        m_time.def("TimePoint_to_UnixTime", &pingtools::timeconv::TimePoint_to_UnixTime,
                   // doc.str().c_str(),
                   py::arg("TimePoint"));
        // std::chrono::system_clock::time_point UnixTime_to_TimePoint(double UnixTime);
        // double TimePoint_to_UnixTime(std::chrono::system_clock::time_point TimePoint);

        std::stringstream doc;
        doc << "Convert a date string to a unix time"
            << "\n\n\t unixtime: Seconds since 1-Jan-1970 0:00:00 as double"
            << "\n\t format: Format string for output"
            << "\n\n\t -- date_string format --"
            << "\n\t-%z: zone (in hhmm (as hours/minuts east of utc); z may only be at the beginning of the string!"
            << "\n\t\tif no z is given the string will be interpreted as utc 0"
            << "\n\t-%d: day as   int dd"
            << "\n\t-%m: month as int mm"
            << "\n\t-%b: month as string Bbb"
            << "\n\t-%Y: year is  int YYYY"
            << "\n\t-%H: hours as int HH"
            << "\n\t-%M: Minutes as int mm"
            << "\n\t-%S: Seconds as int SS"
            << std::endl;
        m_time.def("DateString_to_UnixTime", &pingtools::timeconv::DateString_to_UnixTime,
                   doc.str().c_str(),
                   py::arg("unixtime"),
                   py::arg("format") = "%z__%d-%m-%Y__%H:%M:%S");
    }

    {
        std::stringstream doc;
        doc << "Convert a unix time to a date string"
            << "\n\n\t unixtime: Seconds since 1-Jan-1970 0:00:00 as double"
            << "\n\t fractionalSecondsDigits: Amount of digits to display fractional seconds parts"
            << "\n\t format: Format string for output"
            << "\n\n\t -- date_string format --"
            << "\n\t-%z: zone (in hhmm (as hours/minuts east of utc); z may only be at the beginning of the string!"
            << "\n\t\tif no z is given the string will be interpreted as utc 0"
            << "\n\t-%d: day as   int dd"
            << "\n\t-%m: month as int mm"
            << "\n\t-%b: month as string Bbb"
            << "\n\t-%Y: year is  int YYYY"
            << "\n\t-%H: hours as int HH"
            << "\n\t-%M: Minutes as int mm"
            << "\n\t-%S: Seconds as int SS"
            << std::endl;
        m_time.def("UnixTime_to_DateString", &pingtools::timeconv::UnixTime_to_DateString,
                   doc.str().c_str(),
                   py::arg("unixtime"),
                   py::arg("fractionalSecondsDigits") = 0,
                   py::arg("format") = "%z__%d-%m-%Y__%H:%M:%S" //,
                                                                // py::arg("zone") = 0
        );
    }
}
