// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#include "m_timeconv.hpp"

// -- c++ library headers
#include "../themachinethatgoesping/tools/timeconv.hpp"

// -- include nanobind headers
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/string_view.h>

#include "../themachinethatgoesping/tools_nanobind/datetime.hpp"

namespace nb          = nanobind;
namespace pingtools   = themachinethatgoesping::tools;
namespace pypingtools = pingtools::nanobind_helper;

void init_m_timeconv(nb::module_& m)
{
    auto m_timeconv =
        m.def_submodule("timeconv", "Convenient functions for converting time strings.");

    m_timeconv.def("datestring_to_unixtime",
                   &pingtools::timeconv::datestring_to_unixtime,
                   DOC(themachinethatgoesping, tools, timeconv, datestring_to_unixtime),
                   nb::arg("datestring"),
                   nb::arg("format") = "%z__%d-%m-%Y__%H:%M:%S");

    m_timeconv.def("year_month_day_to_unixtime",
                   &pingtools::timeconv::year_month_day_to_unixtime,
                   DOC(themachinethatgoesping, tools, timeconv, year_month_day_to_unixtime),
                   nb::arg("year"),
                   nb::arg("month"),
                   nb::arg("day"),
                   nb::arg("micro_seconds") = 0);

    m_timeconv.def("unixtime_to_datestring",
                   &pingtools::timeconv::unixtime_to_datestring,
                   DOC(themachinethatgoesping, tools, timeconv, unixtime_to_datestring),
                   nb::arg("unixtime"),
                   nb::arg("fractionalSecondsDigits") = 0,
                   nb::arg("format")                  = "%z__%d-%m-%Y__%H:%M:%S");

    m_timeconv.def("unixtime_to_datetime",
                   &pypingtools::unixtime_to_datetime,
                   DOC(themachinethatgoesping, tools, nanobind_helper, unixtime_to_datetime),
                   nb::arg("unixtime"),
                   nb::arg("timezone_offset_hours") = 0.);

    m_timeconv.def("datetime_to_unixtime",
                   &pypingtools::datetime_to_unixtime,
                   DOC(themachinethatgoesping, tools, nanobind_helper, datetime_to_unixtime),
                   nb::arg("datetime"));

    m_timeconv.def("datestring_to_datetime",
                   &pypingtools::datestring_to_datetime,
                   DOC(themachinethatgoesping, tools, nanobind_helper, datestring_to_datetime),
                   nb::arg("unixtime"),
                   nb::arg("format")                = "%z__%d-%m-%Y__%H:%M:%S",
                   nb::arg("timezone_offset_hours") = 0.);

    m_timeconv.def("datetime_to_datestring",
                   &pypingtools::datetime_to_datestring,
                   DOC(themachinethatgoesping, tools, nanobind_helper, datetime_to_datestring),
                   nb::arg("datetime"),
                   nb::arg("fractionalSecondsDigits") = 0,
                   nb::arg("format") = "%z__%d-%m-%Y__%H:%M:%S");
}
