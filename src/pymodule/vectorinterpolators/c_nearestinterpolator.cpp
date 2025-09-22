// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <sstream>
#include <tuple>
#include <vector>

#include <themachinethatgoesping/tools/vectorinterpolators/nearestinterpolator.hpp>
#include <themachinethatgoesping/tools_pybind/classhelper.hpp>

#include "module.hpp"

namespace py = pybind11;
using namespace themachinethatgoesping::tools::vectorinterpolators;

template<std::floating_point XType, typename YType>
void init_nearestinterpolator(pybind11::module& m, const std::string& name)
{
    using t_NearestInterpolator = NearestInterpolator<XType, YType>;

    py::classh<t_NearestInterpolator>(
        m,
        name.c_str(),
        DOC(themachinethatgoesping, tools, vectorinterpolators, NearestInterpolator))
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
             py::overload_cast<XType>(&t_NearestInterpolator::operator(), py::const_),
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, operator_call),
             py::arg("target_x"))
        .def("get_y",
             py::overload_cast<XType>(&t_NearestInterpolator::get_y, py::const_),
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_PairInterpolator, get_y),
             py::arg("target_x"))
        .def("__call__",
             py::overload_cast<const std::vector<XType>&>(&t_NearestInterpolator::operator(),
                                                          py::const_),
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 operator_call_2),
             py::arg("targets_x"))
        .def("empty",
             &t_NearestInterpolator::empty,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_PairInterpolator, empty))
        .def("set_extrapolation_mode",
             &t_NearestInterpolator::set_extrapolation_mode,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 set_extrapolation_mode),
             py::arg("extrapolation_mode"))
        .def("get_extrapolation_mode",
             &t_NearestInterpolator::get_extrapolation_mode,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 get_extrapolation_mode))
        .def("set_data_XY",
             &t_NearestInterpolator::set_data_XY,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, set_data_XY),
             py::arg("X"),
             py::arg("Y"))
        .def("get_data_X",
             &t_NearestInterpolator::get_data_X,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, get_data_X))
        .def("get_data_Y",
             &t_NearestInterpolator::get_data_Y,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, get_data_Y))
        .def("append",
             &t_NearestInterpolator::append,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, append),
             py::arg("x"),
             py::arg("y"))
        .def("extend",
             &t_NearestInterpolator::extend,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, extend),
             py::arg("X"),
             py::arg("Y"))
        .def("insert",
             &t_NearestInterpolator::insert,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, insert),
             py::arg("X"),
             py::arg("Y"),
             py::arg("bool") = false)
        .def("__eq__",
             &t_NearestInterpolator::operator==,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 NearestInterpolator,
                 operator_eq),
             py::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(t_NearestInterpolator)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(t_NearestInterpolator)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(t_NearestInterpolator)
        // end t_NearestInterpolator
        ;
}

void init_c_nearestinterpolator(pybind11::module& m)
{
    init_nearestinterpolator<double, double>(m, "NearestInterpolator");
    init_nearestinterpolator<float, float>(m, "NearestInterpolatorF");
    init_nearestinterpolator<double, float>(m, "NearestInterpolatorDF");
    init_nearestinterpolator<float, double>(m, "NearestInterpolatorFD");
    init_nearestinterpolator<double, int64_t>(m, "NearestInterpolatorDI");
    init_nearestinterpolator<float, int64_t>(m, "NearestInterpolatorFI");
    init_nearestinterpolator<double, py::object>(m, "NearestInterpolatorDO");
    init_nearestinterpolator<float, py::object>(m, "NearestInterpolatorFO");
}