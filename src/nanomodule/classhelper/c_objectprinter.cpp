// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#include <nanobind/stl/string.h>
#include <nanobind/stl/string_view.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/optional.h>

#include <sstream>
#include <tuple>
#include <vector>

#include "../../themachinethatgoesping/tools/classhelper/objectprinter.hpp"
#include "../../themachinethatgoesping/tools_nanobind/classhelper.hpp"

#include "module.hpp"

namespace nb = nanobind;
using namespace themachinethatgoesping::tools::classhelper;

void init_c_objectprinter(nanobind::module_& m)
{

    nb::class_<ObjectPrinter>(
        m, "ObjectPrinter", DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter))
        .def(nb::init<std::string_view, unsigned int, bool>(),
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, ObjectPrinter),
             nb::arg("name"),
             nb::arg("float_precission"),
             nb::arg("superscript_exponents"))
        .def("class_name",
             &ObjectPrinter::class_name,
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, class_name))
        .def("create_str",
             &ObjectPrinter::create_str,
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, create_str))
        .def("register_value",
             nb::overload_cast<std::string_view, double, std::string_view, int>(
                 &ObjectPrinter::register_value<double>),
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_value),
             nb::arg("name"),
             nb::arg("value"),
             nb::arg("value_info") = "",
             nb::arg("pos")        = -1)
        .def("register_value",
             nb::overload_cast<std::string_view, int, std::string_view, int>(
                 &ObjectPrinter::register_value<int>),
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_value),
             nb::arg("name"),
             nb::arg("value"),
             nb::arg("value_info") = "",
             nb::arg("pos")        = -1)
        .def("register_value",
             nb::overload_cast<std::string_view, std::string, std::string_view, int>(
                 &ObjectPrinter::register_value<std::string>),
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_value),
             nb::arg("name"),
             nb::arg("value"),
             nb::arg("value_info") = "",
             nb::arg("pos")        = -1)
        .def(
            "register_optional_value",
            nb::overload_cast<std::string_view,
                              std::optional<double>,
                              std::string_view,
                              std::string_view,
                              int>(&ObjectPrinter::register_optional_value<double>),
            DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_optional_value),
            nb::arg("name"),
            nb::arg("value"),
            nb::arg("value_info")     = "",
            nb::arg("optional_value") = "Not set",
            nb::arg("pos")            = -1)
        .def(
            "register_optional_value",
            nb::overload_cast<std::string_view,
                              std::optional<int>,
                              std::string_view,
                              std::string_view,
                              int>(&ObjectPrinter::register_optional_value<int>),
            DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_optional_value),
            nb::arg("name"),
            nb::arg("value"),
            nb::arg("value_info")     = "",
            nb::arg("optional_value") = "Not set",
            nb::arg("pos")            = -1)
        .def(
            "register_optional_value",
            nb::overload_cast<std::string_view,
                              std::optional<std::string>,
                              std::string_view,
                              std::string_view,
                              int>(&ObjectPrinter::register_optional_value<std::string>),
            DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_optional_value),
            nb::arg("name"),
            nb::arg("value"),
            nb::arg("value_info")     = "",
            nb::arg("optional_value") = "Not set",
            nb::arg("pos")            = -1)
        .def("register_value_bytes",
             &ObjectPrinter::register_value_bytes,
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_value_bytes),
             nb::arg("name"),
             nb::arg("value"),
             nb::arg("pos") = -1)
        .def("register_container",
             nb::overload_cast<std::string_view,
                               const std::vector<double>&,
                               std::string_view,
                               int>(&ObjectPrinter::register_container<std::vector<double>>),
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_container),
             nb::arg("name"),
             nb::arg("value"),
             nb::arg("value_info") = "",
             nb::arg("pos")        = -1)
        .def("register_container",
             nb::overload_cast<std::string_view, const std::vector<int>&, std::string_view, int>(
                 &ObjectPrinter::register_container<std::vector<int>>),
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_container),
             nb::arg("name"),
             nb::arg("value"),
             nb::arg("value_info") = "",
             nb::arg("pos")        = -1)
        .def("register_container",
             nb::overload_cast<std::string_view,
                               const std::vector<std::string>&,
                               std::string_view,
                               int>(&ObjectPrinter::register_container<std::vector<std::string>>),
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_container),
             nb::arg("name"),
             nb::arg("value"),
             nb::arg("value_info") = "",
             nb::arg("pos")        = -1)
        .def("register_string",
             &ObjectPrinter::register_string,
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_string),
             nb::arg("name"),
             nb::arg("value"),
             nb::arg("value_info")           = "",
             nb::arg("pos")                  = -1,
             nb::arg("max_visible_elements") = 0)
        .def("register_string_with_delimiters",
             &ObjectPrinter::register_string_with_delimiters,
             DOC(themachinethatgoesping,
                 tools,
                 classhelper,
                 ObjectPrinter,
                 register_string_with_delimiters),
             nb::arg("name"),
             nb::arg("value"),
             nb::arg("value_info")           = "",
             nb::arg("delimiter_left")       = "\"",
             nb::arg("delimiter_right")      = "\"",
             nb::arg("pos")                  = -1,
             nb::arg("max_visible_elements") = 0)
        .def("register_section",
             &ObjectPrinter::register_section,
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_section),
             nb::arg("name"),
             nb::arg("underliner") = '-',
             nb::arg("pos")        = -1)

        // default copy functions
        __PYCLASS_DEFAULT_COPY__(ObjectPrinter)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(ObjectPrinter)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(ObjectPrinter)
        // end LinearInterpolator
        ;
}
