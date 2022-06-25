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
        .def(py::init<const std::vector<double>&, const std::vector<double>&, t_extr_mode>(),
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_PairInterpolator,
                 I_PairInterpolator),
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
             &LinearInterpolator::set_data_XY,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, set_data_XY),
             py::arg("X"),
             py::arg("Y"))
        .def(
            "get_data_X",
            &LinearInterpolator::get_data_X,
            DOC(themachinethatgoesping, tools, vectorinterpolators, I_PairInterpolator, get_data_X))
        .def(
            "get_data_Y",
            &LinearInterpolator::get_data_Y,
            DOC(themachinethatgoesping, tools, vectorinterpolators, I_PairInterpolator, get_data_Y))
        .def("append",
             &LinearInterpolator::append,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, append),
             py::arg("x"),
             py::arg("y"))
        .def("extend",
             &LinearInterpolator::extend,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, extend),
             py::arg("X"),
             py::arg("Y"))
        // default class functions
        __PYCLASS_DEFAULT_COPY__(LinearInterpolator)
        // end LinearInterpolator
        ;
}
