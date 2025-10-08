// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>
#include <nanobind/stl/array.h>

#include <sstream>
#include <tuple>
#include <vector>

#include <themachinethatgoesping/tools/vectorinterpolators/slerpinterpolator.hpp>
#include <themachinethatgoesping/tools_nanobind/classhelper.hpp>

#include "module.hpp"
#include <themachinethatgoesping/tools_nanobind/enumhelper.hpp>

namespace nb = nanobind;
using namespace themachinethatgoesping::tools::vectorinterpolators;

template<std::floating_point XType, std::floating_point YType>
void init_slerpinterpolator(nanobind::module_& m, const std::string& name)
{
    using t_SlerpInterpolator = SlerpInterpolator<XType, YType>;

    nb::class_<t_SlerpInterpolator>(
        m, name.c_str(), DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator))
        .def(nb::init<const std::vector<XType>&,
                      const std::vector<YType>&,
                      const std::vector<YType>&,
                      const std::vector<YType>&,
                      bool,
                      t_extr_mode>(),
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 SlerpInterpolator,
                 SlerpInterpolator_3),
             nb::arg("X")                  = std::vector<XType>({}),
             nb::arg("Yaw")                = std::vector<YType>({}),
             nb::arg("Pitch")              = std::vector<YType>({}),
             nb::arg("Roll")               = std::vector<YType>({}),
             nb::arg("input_in_degrees")   = true,
             nb::arg("extrapolation_mode") = t_extr_mode::extrapolate)
        .def("empty",
             &t_SlerpInterpolator::empty,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_PairInterpolator, empty))
        .def("__call__",
             nb::overload_cast<XType, bool>(&t_SlerpInterpolator::ypr, nb::const_),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, ypr),
             nb::arg("target_x"),
             nb::arg("output_in_degrees") = true)
        .def("__call__",
             nb::overload_cast<const std::vector<XType>&, bool>(&t_SlerpInterpolator::ypr,
                                                                nb::const_),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, ypr_2),
             nb::arg("targets_x"),
             nb::arg("output_in_degrees") = true)
        .def("ypr",
             nb::overload_cast<XType, bool>(&t_SlerpInterpolator::ypr, nb::const_),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, ypr),
             nb::arg("target_x"),
             nb::arg("output_in_degrees") = true)
        .def("ypr",
             nb::overload_cast<const std::vector<XType>&, bool>(&t_SlerpInterpolator::ypr,
                                                                nb::const_),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, ypr_2),
             nb::arg("targets_x"),
             nb::arg("output_in_degrees") = true)
        .def("set_extrapolation_mode",
             &t_SlerpInterpolator::set_extrapolation_mode,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 set_extrapolation_mode),
             nb::arg("extrapolation_mode"))
        .def("get_extrapolation_mode",
             &t_SlerpInterpolator::get_extrapolation_mode,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 get_extrapolation_mode))
        .def("set_data_XYPR",
             nb::overload_cast<const std::vector<XType>&,
                               const std::vector<YType>&,
                               const std::vector<YType>&,
                               const std::vector<YType>&,
                               bool>(&t_SlerpInterpolator::set_data_XYPR),
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 SlerpInterpolator,
                 set_data_XYPR),
             nb::arg("X"),
             nb::arg("Yaw"),
             nb::arg("Pitch"),
             nb::arg("Roll"),
             nb::arg("input_in_degrees") = true)
        .def("set_data_XYPR",
             nb::overload_cast<const std::vector<XType>&,
                               const std::vector<std::array<YType, 3>>&,
                               bool>(&t_SlerpInterpolator::set_data_XYPR),
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 SlerpInterpolator,
                 set_data_XYPR_2),
             nb::arg("X"),
             nb::arg("YPR"),
             nb::arg("input_in_degrees") = true)
        .def(
            "get_data_X",
            &t_SlerpInterpolator::get_data_X,
            DOC(themachinethatgoesping, tools, vectorinterpolators, I_PairInterpolator, get_data_X))
        .def("get_data_YPR",
             &t_SlerpInterpolator::get_data_YPR,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 SlerpInterpolator,
                 get_data_YPR),
             nb::arg("output_in_degrees") = true)
        .def("append",
             nb::overload_cast<XType, YType, YType, YType, bool>(&t_SlerpInterpolator::append),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, append),
             nb::arg("x"),
             nb::arg("yaw"),
             nb::arg("pitch"),
             nb::arg("roll"),
             nb::arg("input_in_degrees") = true)
        .def("append",
             nb::overload_cast<XType, std::array<YType, 3>, bool>(&t_SlerpInterpolator::append),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, append_2),
             nb::arg("x"),
             nb::arg("ypr"),
             nb::arg("input_in_degrees") = true)
        .def("extend",
             nb::overload_cast<const std::vector<XType>&,
                               const std::vector<YType>&,
                               const std::vector<YType>&,
                               const std::vector<YType>&,
                               bool>(&t_SlerpInterpolator::extend),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, extend),
             nb::arg("X"),
             nb::arg("Yaw"),
             nb::arg("Pitch"),
             nb::arg("Roll"),
             nb::arg("input_in_degrees") = true)
        .def("extend",
             nb::overload_cast<const std::vector<XType>&,
                               const std::vector<std::array<YType, 3>>&,
                               bool>(&t_SlerpInterpolator::extend),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, extend_2),
             nb::arg("X"),
             nb::arg("YPR"),
             nb::arg("input_in_degrees") = true)
        .def("insert",
             nb::overload_cast<const std::vector<XType>&,
                               const std::vector<YType>&,
                               const std::vector<YType>&,
                               const std::vector<YType>&,
                               bool,
                               bool>(&t_SlerpInterpolator::insert),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, insert),
             nb::arg("X"),
             nb::arg("Yaw"),
             nb::arg("Pitch"),
             nb::arg("Roll"),
             nb::arg("input_in_degrees") = true,
             nb::arg("bool")             = false)
        .def("insert",
             nb::overload_cast<const std::vector<XType>&,
                               const std::vector<std::array<YType, 3>>&,
                               bool,
                               bool>(&t_SlerpInterpolator::insert),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, insert_2),
             nb::arg("X"),
             nb::arg("YPR"),
             nb::arg("input_in_degrees") = true,
             nb::arg("bool")             = false)
        .def(
            "__eq__",
            &t_SlerpInterpolator::operator==,
            DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, operator_eq),
            nb::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(t_SlerpInterpolator)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(t_SlerpInterpolator)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(t_SlerpInterpolator)
        // end t_SlerpInterpolator
        ;
}

void init_c_slerpinterpolator(nanobind::module_& m)
{
    init_slerpinterpolator<double, double>(m, "SlerpInterpolator");
    init_slerpinterpolator<float, float>(m, "SlerpInterpolatorF");
    init_slerpinterpolator<float, double>(m, "SlerpInterpolatorFD");
    init_slerpinterpolator<double, float>(m, "SlerpInterpolatorDF");
}