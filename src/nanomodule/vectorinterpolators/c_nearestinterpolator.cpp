// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

#include <sstream>
#include <tuple>
#include <vector>
#include <type_traits>

#include <themachinethatgoesping/tools/vectorinterpolators/nearestinterpolator.hpp>
#include <themachinethatgoesping/tools_nanobind/classhelper.hpp>

#include "module.hpp"

namespace nb = nanobind;
using namespace themachinethatgoesping::tools::vectorinterpolators;

template<std::floating_point XType, typename YType>
void init_nearestinterpolator(nanobind::module_& m, const std::string& name)
{
    using t_NearestInterpolator = NearestInterpolator<XType, YType>;

    nb::class_<t_NearestInterpolator>(
        m, name.c_str(),
        DOC(themachinethatgoesping, tools, vectorinterpolators, NearestInterpolator))
        .def(nb::init<const std::vector<XType>&, const std::vector<YType>&, t_extr_mode>(),
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_PairInterpolator,
                 I_PairInterpolator),
             nb::arg("X")                  = std::vector<XType>({}),
             nb::arg("Y")                  = std::vector<YType>({}),
             nb::arg("extrapolation_mode") = t_extr_mode::extrapolate)
        .def("__call__",
             nb::overload_cast<XType>(&t_NearestInterpolator::operator(), nb::const_),
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, operator_call),
             nb::arg("target_x"))
        .def("get_y",
             nb::overload_cast<XType>(&t_NearestInterpolator::get_y, nb::const_),
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_PairInterpolator, get_y),
             nb::arg("target_x"))
        .def("__call__",
             nb::overload_cast<const std::vector<XType>&>(&t_NearestInterpolator::operator(),
                                                          nb::const_),
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 operator_call_2),
             nb::arg("targets_x"))
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
             nb::arg("extrapolation_mode"))
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
             nb::arg("X"),
             nb::arg("Y"))
        .def("get_data_X",
             &t_NearestInterpolator::get_data_X,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, get_data_X))
        .def("get_data_Y",
             &t_NearestInterpolator::get_data_Y,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, get_data_Y))
        .def("append",
             &t_NearestInterpolator::append,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, append),
             nb::arg("x"),
             nb::arg("y"))
        .def("extend",
             &t_NearestInterpolator::extend,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, extend),
             nb::arg("X"),
             nb::arg("Y"))
        .def("insert",
             &t_NearestInterpolator::insert,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, insert),
             nb::arg("X"),
             nb::arg("Y"),
             nb::arg("bool") = false)
        .def("__eq__",
             &t_NearestInterpolator::operator==,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 NearestInterpolator,
                 operator_eq),
             nb::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(t_NearestInterpolator)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(t_NearestInterpolator)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(t_NearestInterpolator)
        // end t_NearestInterpolator
        ;
}

void init_c_nearestinterpolator(nanobind::module_& m)
{
    init_nearestinterpolator<double, double>(m, "NearestInterpolator");
    init_nearestinterpolator<float, float>(m, "NearestInterpolatorF");
    init_nearestinterpolator<double, float>(m, "NearestInterpolatorDF");
    init_nearestinterpolator<float, double>(m, "NearestInterpolatorFD");
    init_nearestinterpolator<double, int64_t>(m, "NearestInterpolatorDI");
    init_nearestinterpolator<float, int64_t>(m, "NearestInterpolatorFI");
    // init_nearestinterpolator<double, nb::object>(m, "NearestInterpolatorDO");
    // init_nearestinterpolator<float, nb::object>(m, "NearestInterpolatorFO");
}