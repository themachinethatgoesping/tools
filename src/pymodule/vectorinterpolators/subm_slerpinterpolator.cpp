// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/stl.h>

#include <sstream>
#include <tuple>
#include <vector>

#include "../../themachinethatgoesping/tools/pybind11_helpers/classhelpers.hpp"
#include "../../themachinethatgoesping/tools/vectorinterpolators/slerpinterpolator.hpp"
#include "../docstrings.hpp"
#include "module.hpp"

namespace py = pybind11;
using namespace themachinethatgoesping::tools::vectorinterpolators;

void init_subm_slerpinterpolator(pybind11::module& m)
{

    py::class_<SlerpInterpolator>(
        m,
        "SlerpInterpolator",
        DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator))
        .def(py::init<const std::vector<double>&,
                      const std::vector<double>&,
                      const std::vector<double>&,
                      const std::vector<double>&,
                      bool,
                      t_extr_mode>(),
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 SlerpInterpolator,
                 SlerpInterpolator_3),
             py::arg("X")                  = std::vector<double>({}),
             py::arg("Yaw")                = std::vector<double>({}),
             py::arg("Pitch")              = std::vector<double>({}),
             py::arg("Roll")               = std::vector<double>({}),
             py::arg("input_in_degrees")   = true,
             py::arg("extrapolation_mode") = t_extr_mode::extrapolate)
        .def("__call__",
             py::overload_cast<double, bool>(&SlerpInterpolator::ypr),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, ypr),
             py::arg("target_x"),
             py::arg("output_in_degrees") = true)
        .def("__call__",
             py::overload_cast<const std::vector<double>&, bool>(&SlerpInterpolator::ypr),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, ypr_2),
             py::arg("targets_x"),
             py::arg("output_in_degrees") = true)
        .def("set_extrapolation_mode",
             &SlerpInterpolator::set_extrapolation_mode,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 set_extrapolation_mode),
             py::arg("extrapolation_mode"))
        .def("get_extrapolation_mode",
             &SlerpInterpolator::get_extrapolation_mode,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 get_extrapolation_mode))
        .def("set_data_XYPR",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<double>&,
                               const std::vector<double>&,
                               const std::vector<double>&,
                               bool>(&SlerpInterpolator::set_data_XYPR),
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 SlerpInterpolator,
                 set_data_XYPR),
             py::arg("X"),
             py::arg("Yaw"),
             py::arg("Pitch"),
             py::arg("Roll"),
             py::arg("input_in_degrees") = true)
        .def("set_data_XYPR",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<std::array<double, 3>>&,
                               bool>(&SlerpInterpolator::set_data_XYPR),
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 SlerpInterpolator,
                 set_data_XYPR_2),
             py::arg("X"),
             py::arg("YPR"),
             py::arg("input_in_degrees") = true)
        .def(
            "get_data_X",
            &SlerpInterpolator::get_data_X,
            DOC(themachinethatgoesping, tools, vectorinterpolators, I_PairInterpolator, get_data_X))
        .def("get_data_YPR",
             &SlerpInterpolator::get_data_YPR,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 SlerpInterpolator,
                 get_data_YPR),
             py::arg("output_in_degrees") = true)
        .def("append",
             py::overload_cast<double, double, double, double, bool>(&SlerpInterpolator::append),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, append),
             py::arg("x"),
             py::arg("yaw"),
             py::arg("pitch"),
             py::arg("roll"),
             py::arg("input_in_degrees") = true)
        .def("append",
             py::overload_cast<double, std::array<double, 3>, bool>(&SlerpInterpolator::append),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, append_2),
             py::arg("x"),
             py::arg("ypr"),
             py::arg("input_in_degrees") = true)
        .def("extend",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<double>&,
                               const std::vector<double>&,
                               const std::vector<double>&,
                               bool>(&SlerpInterpolator::extend),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, extend),
             py::arg("X"),
             py::arg("Yaw"),
             py::arg("Pitch"),
             py::arg("Roll"),
             py::arg("input_in_degrees") = true)
        .def("extend",
             py::overload_cast<const std::vector<double>&,
                               const std::vector<std::array<double, 3>>&,
                               bool>(&SlerpInterpolator::extend),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, extend_2),
             py::arg("X"),
             py::arg("YPR"),
             py::arg("input_in_degrees") = true)
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(SlerpInterpolator)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(SlerpInterpolator)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(SlerpInterpolator)
        // end SlerpInterpolator
        ;
}
