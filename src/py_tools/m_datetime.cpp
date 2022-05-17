// SPDX-FileCopyrightText: 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "m_datetime.h"

// -- c++ library headers
#include "../tools/datetime.h"

// -- include system headers
#include <sstream>


namespace py = pybind11;
namespace pingtools = themachinethatgoesping::tools;

void init_m_datetime(py::module& m)
{
    auto m_time = m.def_submodule("datetime","Convinient functions for converting time strings.");

    {
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
        m_time.def("DateString_to_UnixTime",&pingtools::datetime::DateString_to_UnixTime,
                   doc.str().c_str(),
                   py::arg("unixtime"),
                   py::arg("format") = "%z__%d-%m-%Y__%H:%M:%S"
                                     );
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
        m_time.def("UnixTime_to_DateString",&pingtools::datetime::UnixTime_to_DateString,
                   doc.str().c_str(),
                   py::arg("unixtime"),
                   py::arg("fractionalSecondsDigits") = 0,
                   py::arg("format") = "%z__%d-%m-%Y__%H:%M:%S"//,
                   //py::arg("zone") = 0
                                       );
    }




}
