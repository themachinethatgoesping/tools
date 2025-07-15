// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0




#include "m_timeconv.hpp"
// automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/tools/timeconv.hpp"

// -- include system headers
#include <sstream>

// -- include pybind11 headers
#include <pybind11/chrono.h>
#include <pybind11/stl.h>

#include "../themachinethatgoesping/tools_pybind/datetime.hpp"

namespace py        = pybind11;
namespace pingtools = themachinethatgoesping::tools;
namespace pypingtools = pingtools::pybind_helper;

void init_m_timeconv(py::module& m)
{
    auto m_timeconv =
        m.def_submodule("timeconv", "Convenient functions for converting time strings.");

    // this does not yet work the way I want it
    // maybe when c++20 chrono is finally avaliable to all compilers (utc_time instead of system
    // time) m_timeconv.def("UnixTime_to_TimePoint",
    // &pingtools::timeconv::UnixTime_to_TimePoint,
    //            // doc.str().c_str(),
    //            py::arg("unixtime"));
    // m_timeconv.def("timepoint_to_unixtime", &pingtools::timeconv::timepoint_to_unixtime,
    //            // doc.str().c_str(),
    //            py::arg("TimePoint"));

    m_timeconv.def("datestring_to_unixtime",
                   &pingtools::timeconv::datestring_to_unixtime,
                   DOC(themachinethatgoesping, tools, timeconv, datestring_to_unixtime),
                   py::arg("unixtime"),
                   py::arg("format") = "%z__%d-%m-%Y__%H:%M:%S");

    m_timeconv.def("year_month_day_to_unixtime",
                   &pingtools::timeconv::year_month_day_to_unixtime,
                   DOC(themachinethatgoesping, tools, timeconv, year_month_day_to_unixtime),
                   py::arg("year"),
                   py::arg("month"),
                   py::arg("day"),
                   py::arg("micro_seconds") = 0);

    m_timeconv.def("unixtime_to_datestring",
                   &pingtools::timeconv::unixtime_to_datestring,
                   DOC(themachinethatgoesping, tools, timeconv, unixtime_to_datestring),
                   py::arg("unixtime"),
                   py::arg("fractionalSecondsDigits") = 0,
                   py::arg("format")                  = "%z__%d-%m-%Y__%H:%M:%S");

    m_timeconv.def("unixtime_to_datetime",
                   &pypingtools::unixtime_to_datetime,
                   DOC(themachinethatgoesping, tools, pybind_helper, unixtime_to_datetime),
                   py::arg("unixtime"),
                   py::arg("timezone_offset_hours") = 0.);

    m_timeconv.def("datetime_to_unixtime",
                   &pypingtools::datetime_to_unixtime,
                   DOC(themachinethatgoesping, tools, pybind_helper, datetime_to_unixtime),
                   py::arg("datetime"));
}
