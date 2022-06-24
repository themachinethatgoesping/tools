// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/stl.h>

#include <sstream>
#include <tuple>
#include <vector>

#include "../../tools/pybind11/classhelpers.hpp"
#include "../../tools/vectorinterpolators/linearinterpolator.hpp"
#include "../docstrings.hpp"
#include "module.hpp"

namespace py = pybind11;
using namespace themachinethatgoesping::tools::vectorinterpolators;



void init_subm_linearinterpolator(pybind11::module& m)
{

    py::class_<LinearInterpolator>(
        m,
        "LinearInterpolator",
        DOC(themachinethatgoesping, tools, vectorinterpolators, LinearInterpolator))
        .def(py::init<const std::vector<std::pair<double, double>>&, t_extr_mode>(),
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_PairInterpolator,
                 I_PairInterpolator),
             py::arg("XY"),
             py::arg("extrapolation_mode") = t_extr_mode::extrapolate)
        .def(py::init<const std::vector<double>&, const std::vector<double>&, t_extr_mode>(),
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_PairInterpolator,
                 I_PairInterpolator_2),
             py::arg("X")                  = std::vector<double>({ 0, 1 }),
             py::arg("Y")                  = std::vector<double>({ 0, 1 }),
             py::arg("extrapolation_mode") = t_extr_mode::extrapolate)
        .def("__call__",
             py::overload_cast<double>(&LinearInterpolator::operator()),
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, operator_call),
             py::arg("target_x"))
        .def("__call__",
             py::overload_cast<const std::vector<double>&>(&LinearInterpolator::operator()),
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 operator_call_2),
             py::arg("targets_x"))
        .def("set_extrapolation_mode",
             &LinearInterpolator::set_extrapolation_mode,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 set_extrapolation_mode),
             py::arg("extrapolation_mode"))
        .def("get_extrapolation_mode",
             &LinearInterpolator::get_extrapolation_mode,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 get_extrapolation_mode))
        .def("set_data_XY",
             py::overload_cast<const std::vector<std::pair<double, double>>&>(
                 &LinearInterpolator::set_data_XY),
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, set_data_XY),
             py::arg("XY"))
        .def("set_data_XY",
             py::overload_cast<const std::vector<double>&, const std::vector<double>&>(
                 &LinearInterpolator::set_data_XY),
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, set_data_XY_2),
             py::arg("X"),
             py::arg("Y"))
        .def("append",
             py::overload_cast<double, double>(&LinearInterpolator::append),
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, append),
             py::arg("x"),
             py::arg("y"))
        .def("append",
             py::overload_cast<std::pair<double, double>>(&LinearInterpolator::append),
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, append_2),
             py::arg("xy"))
        .def("extend",
             py::overload_cast<const std::vector<double>&, const std::vector<double>&>(
                 &LinearInterpolator::extend),
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, extend),
             py::arg("X"),
             py::arg("Y"))
        .def("extend",
             py::overload_cast<const std::vector<std::pair<double, double>>&>(
                 &LinearInterpolator::extend),
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, extend_2),
             py::arg("XY"))
        // default class functions
        __PYCLASS_DEFAULT_COPY__(LinearInterpolator)
        // end LinearInterpolator
        ;
}