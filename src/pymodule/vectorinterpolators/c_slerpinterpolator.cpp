// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/stl.h>

#include <sstream>
#include <tuple>
#include <vector>

#include "../../themachinethatgoesping/tools/vectorinterpolators/slerpinterpolator.hpp"
#include "../../themachinethatgoesping/tools_pybind/classhelper.hpp"

#include "module.hpp"

namespace py = pybind11;
using namespace themachinethatgoesping::tools::vectorinterpolators;

template<std::floating_point XType, std::floating_point YType>
void init_slerpinterpolator(pybind11::module& m, const std::string& name)
{
    using t_SlerpInterpolator = SlerpInterpolator<XType, YType>;

    py::class_<t_SlerpInterpolator>(
        m, name.c_str(), DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator))
        .def(py::init<const std::vector<XType>&,
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
             py::arg("X")                  = std::vector<XType>({}),
             py::arg("Yaw")                = std::vector<YType>({}),
             py::arg("Pitch")              = std::vector<YType>({}),
             py::arg("Roll")               = std::vector<YType>({}),
             py::arg("input_in_degrees")   = true,
             py::arg("extrapolation_mode") = t_extr_mode::extrapolate)
        .def("empty",
             &t_SlerpInterpolator::empty,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_PairInterpolator, empty))
        .def("__call__",
             py::overload_cast<XType, bool>(&t_SlerpInterpolator::ypr),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, ypr),
             py::arg("target_x"),
             py::arg("output_in_degrees") = true)
        .def("__call__",
             py::overload_cast<const std::vector<XType>&, bool>(&t_SlerpInterpolator::ypr),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, ypr_2),
             py::arg("targets_x"),
             py::arg("output_in_degrees") = true)
        .def("set_extrapolation_mode",
             &t_SlerpInterpolator::set_extrapolation_mode,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 set_extrapolation_mode),
             py::arg("extrapolation_mode"))
        .def("get_extrapolation_mode",
             &t_SlerpInterpolator::get_extrapolation_mode,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 get_extrapolation_mode))
        .def("set_data_XYPR",
             py::overload_cast<const std::vector<XType>&,
                               const std::vector<YType>&,
                               const std::vector<YType>&,
                               const std::vector<YType>&,
                               bool>(&t_SlerpInterpolator::set_data_XYPR),
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
             py::overload_cast<const std::vector<XType>&,
                               const std::vector<std::array<YType, 3>>&,
                               bool>(&t_SlerpInterpolator::set_data_XYPR),
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
            &t_SlerpInterpolator::get_data_X,
            DOC(themachinethatgoesping, tools, vectorinterpolators, I_PairInterpolator, get_data_X))
        .def("get_data_YPR",
             &t_SlerpInterpolator::get_data_YPR,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 SlerpInterpolator,
                 get_data_YPR),
             py::arg("output_in_degrees") = true)
        .def("append",
             py::overload_cast<XType, YType, YType, YType, bool>(&t_SlerpInterpolator::append),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, append),
             py::arg("x"),
             py::arg("yaw"),
             py::arg("pitch"),
             py::arg("roll"),
             py::arg("input_in_degrees") = true)
        .def("append",
             py::overload_cast<XType, std::array<YType, 3>, bool>(&t_SlerpInterpolator::append),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, append_2),
             py::arg("x"),
             py::arg("ypr"),
             py::arg("input_in_degrees") = true)
        .def("extend",
             py::overload_cast<const std::vector<XType>&,
                               const std::vector<YType>&,
                               const std::vector<YType>&,
                               const std::vector<YType>&,
                               bool>(&t_SlerpInterpolator::extend),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, extend),
             py::arg("X"),
             py::arg("Yaw"),
             py::arg("Pitch"),
             py::arg("Roll"),
             py::arg("input_in_degrees") = true)
        .def("extend",
             py::overload_cast<const std::vector<XType>&,
                               const std::vector<std::array<YType, 3>>&,
                               bool>(&t_SlerpInterpolator::extend),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, extend_2),
             py::arg("X"),
             py::arg("YPR"),
             py::arg("input_in_degrees") = true)
        .def("insert",
             py::overload_cast<const std::vector<XType>&,
                               const std::vector<YType>&,
                               const std::vector<YType>&,
                               const std::vector<YType>&,
                               bool,
                               bool>(&t_SlerpInterpolator::insert),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, insert),
             py::arg("X"),
             py::arg("Yaw"),
             py::arg("Pitch"),
             py::arg("Roll"),
             py::arg("input_in_degrees") = true,
             py::arg("bool")             = false)
        .def("insert",
             py::overload_cast<const std::vector<XType>&,
                               const std::vector<std::array<YType, 3>>&,
                               bool,
                               bool>(&t_SlerpInterpolator::insert),
             DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, insert_2),
             py::arg("X"),
             py::arg("YPR"),
             py::arg("input_in_degrees") = true,
             py::arg("bool")             = false)
        .def(
            "__eq__",
            &t_SlerpInterpolator::operator==,
            DOC(themachinethatgoesping, tools, vectorinterpolators, SlerpInterpolator, operator_eq),
            py::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(t_SlerpInterpolator)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(t_SlerpInterpolator)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(t_SlerpInterpolator)
        // end t_SlerpInterpolator
        ;
}

void init_c_slerpinterpolator(pybind11::module& m)
{
    init_slerpinterpolator<double, double>(m, "SlerpInterpolator");
    init_slerpinterpolator<float, float>(m, "SlerpInterpolatorF");
    init_slerpinterpolator<float, double>(m, "SlerpInterpolatorFD");
    init_slerpinterpolator<double, float>(m, "SlerpInterpolatorDF");
}