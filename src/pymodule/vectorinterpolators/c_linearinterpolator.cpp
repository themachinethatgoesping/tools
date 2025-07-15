// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <sstream>
#include <tuple>
#include <vector>

#include <themachinethatgoesping/tools/vectorinterpolators/linearinterpolator.hpp>
#include <themachinethatgoesping/tools_pybind/classhelper.hpp>

#include "module.hpp"

namespace py = pybind11;
using namespace themachinethatgoesping::tools::vectorinterpolators;

template<std::floating_point XType, typename YType>
void init_linearinterpolator(pybind11::module& m, const std::string& name)
{
    using t_LinearInterpolator = LinearInterpolator<XType, YType>;

    py::class_<t_LinearInterpolator>(
        m,
        name.c_str(),
        DOC(themachinethatgoesping, tools, vectorinterpolators, LinearInterpolator))
        .def(py::init<const std::vector<XType>&, const std::vector<YType>&, t_extr_mode>(),
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_PairInterpolator,
                 I_PairInterpolator),
             py::arg("X")                  = std::vector<XType>({}),
             py::arg("Y")                  = std::vector<YType>({}),
             py::arg("extrapolation_mode") = t_extr_mode::extrapolate)
        .def("__call__",
             py::overload_cast<XType>(&t_LinearInterpolator::operator(), py::const_),
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, operator_call),
             py::arg("target_x"))
        .def("get_y",
             py::overload_cast<XType>(&t_LinearInterpolator::get_y, py::const_),
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_PairInterpolator, get_y),
             py::arg("target_x"))
        .def("__call__",
             py::overload_cast<const std::vector<XType>&>(&t_LinearInterpolator::operator(), py::const_),
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 operator_call_2),
             py::arg("targets_x"))
        .def("empty",
             &t_LinearInterpolator::empty,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_PairInterpolator, empty))
        .def("set_extrapolation_mode",
             &t_LinearInterpolator::set_extrapolation_mode,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 set_extrapolation_mode),
             py::arg("extrapolation_mode"))
        .def("get_extrapolation_mode",
             &t_LinearInterpolator::get_extrapolation_mode,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 get_extrapolation_mode))
        .def("set_data_XY",
             &t_LinearInterpolator::set_data_XY,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, set_data_XY),
             py::arg("X"),
             py::arg("Y"))
        .def("get_data_X",
             &t_LinearInterpolator::get_data_X,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, get_data_X))
        .def("get_data_Y",
             &t_LinearInterpolator::get_data_Y,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, get_data_Y))
        .def("append",
             &t_LinearInterpolator::append,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, append),
             py::arg("x"),
             py::arg("y"))
        .def("extend",
             &t_LinearInterpolator::extend,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, extend),
             py::arg("X"),
             py::arg("Y"))
        .def("insert",
             &t_LinearInterpolator::insert,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, insert),
             py::arg("X"),
             py::arg("Y"),
             py::arg("bool") = false)
        .def("__eq__",
             &t_LinearInterpolator::operator==,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 LinearInterpolator,
                 operator_eq),
             py::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(t_LinearInterpolator)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(t_LinearInterpolator)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(t_LinearInterpolator)
        // end t_LinearInterpolator
        ;
}

void init_c_linearinterpolator(pybind11::module& m)
{
     init_linearinterpolator<double, double>(m, "LinearInterpolator");
     init_linearinterpolator<float, float>(m, "LinearInterpolatorF");
     init_linearinterpolator<double, float>(m, "LinearInterpolatorDF");
     init_linearinterpolator<float, double>(m, "LinearInterpolatorFD");
}