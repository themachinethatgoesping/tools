// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/stl.h>

#include <sstream>
#include <tuple>
#include <vector>

#include "../../tools/pybind11_helpers/classhelpers.hpp"
#include "../../tools/classhelpers/objectprinter.hpp"
#include "../docstrings.hpp"
#include "module.hpp"

namespace py = pybind11;
using namespace themachinethatgoesping::tools::classhelpers;

void init_subm_objectprinter(pybind11::module& m)
{

    py::class_<ObjectPrinter>(
        m,
        "ObjectPrinter",
        DOC(themachinethatgoesping, tools, classhelpers, ObjectPrinter))
        .def(py::init<const std::string&>(),
             DOC(themachinethatgoesping,
                 tools,
                 classhelpers,
                 ObjectPrinter,
                 ObjectPrinter),
             py::arg("name"))
        .def("create_str",
             &ObjectPrinter::create_str,
             DOC(themachinethatgoesping,
                 tools,
                 classhelpers,
                 ObjectPrinter,
                 create_str))
        .def("register_value",
             py::overload_cast<const std::string&, double, std::string>(&ObjectPrinter::register_value<double>),
             DOC(themachinethatgoesping,
                 tools,
                 classhelpers,
                 ObjectPrinter,
                 register_value),
             py::arg("name"),
             py::arg("value"),
             py::arg("value_info") = "")
        .def("register_value",
             py::overload_cast<const std::string&, int, std::string>(&ObjectPrinter::register_value<int>),
             DOC(themachinethatgoesping,
                 tools,
                 classhelpers,
                 ObjectPrinter,
                 register_value),
             py::arg("name"),
             py::arg("value"),
             py::arg("value_info") = "")
        .def("register_value",
             py::overload_cast<const std::string&, std::string, std::string>(&ObjectPrinter::register_value<std::string>),
             DOC(themachinethatgoesping,
                 tools,
                 classhelpers,
                 ObjectPrinter,
                 register_value),
             py::arg("name"),
             py::arg("value"),
             py::arg("value_info") = "")
        .def("register_container",
             py::overload_cast<const std::string&, const std::vector<double>&, std::string>(&ObjectPrinter::register_container<double>),
             DOC(themachinethatgoesping,
                 tools,
                 classhelpers,
                 ObjectPrinter,
                 register_container),
             py::arg("name"),
             py::arg("value"),
             py::arg("value_info") = "")
        .def("register_container",
             py::overload_cast<const std::string&, const std::vector<int>&, std::string>(&ObjectPrinter::register_container<int>),
             DOC(themachinethatgoesping,
                 tools,
                 classhelpers,
                 ObjectPrinter,
                 register_container),
             py::arg("name"),
             py::arg("value"),
             py::arg("value_info") = "")
        .def("register_container",
             py::overload_cast<const std::string&, const std::vector<std::string>&, std::string>(&ObjectPrinter::register_container<std::string>),
             DOC(themachinethatgoesping,
                 tools,
                 classhelpers,
                 ObjectPrinter,
                 register_container),
             py::arg("name"),
             py::arg("value"),
             py::arg("value_info") = "")
        .def("register_section",
             &ObjectPrinter::register_section,
             DOC(themachinethatgoesping,
                 tools,
                 classhelpers,
                 ObjectPrinter,
                 register_section),
             py::arg("name"))
        
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(ObjectPrinter)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(ObjectPrinter)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(ObjectPrinter)
        // end LinearInterpolator
        ;
}
