// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <sstream>
#include <tuple>
#include <vector>

#include <themachinethatgoesping/tools/vectorinterpolators/akimainterpolator.hpp>
#include <themachinethatgoesping/tools_pybind/classhelper.hpp>

#include "module.hpp"

namespace py = pybind11;
using namespace themachinethatgoesping::tools::vectorinterpolators;

template<std::floating_point XYType>
void init_akimainterpolator(pybind11::module& m, const std::string& name)
{
    using t_AkimaInterpolator = AkimaInterpolator<XYType>;

    py::class_<t_AkimaInterpolator>(
        m, name.c_str(), DOC(themachinethatgoesping, tools, vectorinterpolators, AkimaInterpolator))
        .def(py::init<const std::vector<XYType>&, const std::vector<XYType>&, t_extr_mode>(),
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_PairInterpolator,
                 I_PairInterpolator),
             py::arg("X")                  = std::vector<XYType>({}),
             py::arg("Y")                  = std::vector<XYType>({}),
             py::arg("extrapolation_mode") = t_extr_mode::extrapolate)
        .def("__call__",
             py::overload_cast<XYType>(&t_AkimaInterpolator::operator(), py::const_),
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, operator_call),
             py::arg("target_x"))
        .def("get_y",
             py::overload_cast<XYType>(&t_AkimaInterpolator::get_y, py::const_),
             DOC(themachinethatgoesping, tools, vectorinterpolators, AkimaInterpolator, get_y),
             py::arg("target_x"))
        .def("__call__",
             py::overload_cast<const std::vector<XYType>&>(&t_AkimaInterpolator::operator(),
                                                           py::const_),
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 operator_call_2),
             py::arg("targets_x"))
        .def("empty",
             &t_AkimaInterpolator::empty,
             DOC(themachinethatgoesping, tools, vectorinterpolators, AkimaInterpolator, empty))
        .def("set_extrapolation_mode",
             &t_AkimaInterpolator::set_extrapolation_mode,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 set_extrapolation_mode),
             py::arg("extrapolation_mode"))
        .def("get_extrapolation_mode",
             &t_AkimaInterpolator::get_extrapolation_mode,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 get_extrapolation_mode))
        .def("set_data_XY",
             &t_AkimaInterpolator::set_data_XY,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, set_data_XY),
             py::arg("X"),
             py::arg("Y"))
        .def("get_data_X",
             &t_AkimaInterpolator::get_data_X,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, get_data_X))
        .def("get_data_Y",
             &t_AkimaInterpolator::get_data_Y,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, get_data_Y))
        .def("append",
             &t_AkimaInterpolator::append,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, append),
             py::arg("x"),
             py::arg("y"))
        .def("extend",
             &t_AkimaInterpolator::extend,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, extend),
             py::arg("X"),
             py::arg("Y"))
        .def("insert",
             &t_AkimaInterpolator::insert,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, insert),
             py::arg("X"),
             py::arg("Y"),
             py::arg("bool") = false)
        .def(
            "__eq__",
            &t_AkimaInterpolator::operator==,
            DOC(themachinethatgoesping, tools, vectorinterpolators, AkimaInterpolator, operator_eq),
            py::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(t_AkimaInterpolator)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(t_AkimaInterpolator)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(t_AkimaInterpolator)
        // end t_AkimaInterpolator
        ;
}

void init_c_akimainterpolator(pybind11::module& m)
{
    init_akimainterpolator<double>(m, "AkimaInterpolator");
    init_akimainterpolator<float>(m, "AkimaInterpolatorF");
}