// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/stl.h>

#include <sstream>
#include <tuple>
#include <vector>

#include "../../themachinethatgoesping/tools/classhelper/objectprinter.hpp"
#include "../../themachinethatgoesping/tools_pybind/classhelper.hpp"

#include "module.hpp"

namespace py = pybind11;
using namespace themachinethatgoesping::tools::classhelper;

void init_c_objectprinter(pybind11::module& m)
{

    py::class_<ObjectPrinter>(
        m, "ObjectPrinter", DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter))
        .def(py::init<const std::string&, unsigned int, bool>(),
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, ObjectPrinter),
             py::arg("name"),
             py::arg("float_precission"),
             py::arg("superscript_exponents"))
        .def("class_name",
             &ObjectPrinter::class_name,
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, class_name))
        .def("create_str",
             &ObjectPrinter::create_str,
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, create_str))
        .def("register_value",
             py::overload_cast<const std::string&, double, std::string_view, int>(
                 &ObjectPrinter::register_value<double>),
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_value),
             py::arg("name"),
             py::arg("value"),
             py::arg("value_info") = "",
             py::arg("pos")        = -1)
        .def("register_value",
             py::overload_cast<const std::string&, int, std::string_view, int>(
                 &ObjectPrinter::register_value<int>),
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_value),
             py::arg("name"),
             py::arg("value"),
             py::arg("value_info") = "",
             py::arg("pos")        = -1)
        .def("register_value",
             py::overload_cast<const std::string&, std::string, std::string_view, int>(
                 &ObjectPrinter::register_value<std::string>),
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_value),
             py::arg("name"),
             py::arg("value"),
             py::arg("value_info") = "",
             py::arg("pos")        = -1)
        .def(
            "register_optional_value",
            py::overload_cast<const std::string&, std::optional<double>, std::string_view, int>(
                &ObjectPrinter::register_optional_value<double>),
            DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_optional_value),
            py::arg("name"),
            py::arg("value"),
            py::arg("value_info") = "",
            py::arg("pos")        = -1)
        .def(
            "register_optional_value",
            py::overload_cast<const std::string&, std::optional<int>, std::string_view, int>(
                &ObjectPrinter::register_optional_value<int>),
            DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_optional_value),
            py::arg("name"),
            py::arg("value"),
            py::arg("value_info") = "",
            py::arg("pos")        = -1)
        .def(
            "register_optional_value",
            py::overload_cast<const std::string&,
                              std::optional<std::string>,
                              std::string_view,
                              int>(&ObjectPrinter::register_optional_value<std::string>),
            DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_optional_value),
            py::arg("name"),
            py::arg("value"),
            py::arg("value_info") = "",
            py::arg("pos")        = -1)
        .def("register_value_bytes",
             &ObjectPrinter::register_value_bytes,
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_value_bytes),
             py::arg("name"),
             py::arg("value"),
             py::arg("pos") = -1)
        .def("register_container",
             py::overload_cast<const std::string&,
                               const std::vector<double>&,
                               std::string_view,
                               int>(&ObjectPrinter::register_container<std::vector<double>>),
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_container),
             py::arg("name"),
             py::arg("value"),
             py::arg("value_info") = "",
             py::arg("pos")        = -1)
        .def("register_container",
             py::overload_cast<const std::string&, const std::vector<int>&, std::string_view, int>(
                 &ObjectPrinter::register_container<std::vector<int>>),
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_container),
             py::arg("name"),
             py::arg("value"),
             py::arg("value_info") = "",
             py::arg("pos")        = -1)
        .def("register_container",
             py::overload_cast<const std::string&,
                               const std::vector<std::string>&,
                               std::string_view,
                               int>(&ObjectPrinter::register_container<std::vector<std::string>>),
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_container),
             py::arg("name"),
             py::arg("value"),
             py::arg("value_info") = "",
             py::arg("pos")        = -1)
        .def("register_section",
             &ObjectPrinter::register_section,
             DOC(themachinethatgoesping, tools, classhelper, ObjectPrinter, register_section),
             py::arg("name"),
             py::arg("underliner") = '-',
             py::arg("pos")        = -1)

        // default copy functions
        __PYCLASS_DEFAULT_COPY__(ObjectPrinter)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(ObjectPrinter)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(ObjectPrinter)
        // end LinearInterpolator
        ;
}
