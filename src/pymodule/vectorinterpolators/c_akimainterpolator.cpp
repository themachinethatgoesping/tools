// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/stl.h>

#include <sstream>
#include <tuple>
#include <vector>

#include "../../themachinethatgoesping/tools/vectorinterpolators/akimainterpolator.hpp"
#include "../../themachinethatgoesping/tools_pybind/classhelper.hpp"
#include "../docstrings.hpp"
#include "module.hpp"

namespace py = pybind11;
using namespace themachinethatgoesping::tools::vectorinterpolators;

void init_c_akimainterpolator(pybind11::module& m)
{

    py::class_<AkimaInterpolator>(
        m,
        "AkimaInterpolator",
        DOC(themachinethatgoesping, tools, vectorinterpolators, AkimaInterpolator))
        .def(py::init<const std::vector<double>&, const std::vector<double>&, t_extr_mode>(),
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_PairInterpolator,
                 I_PairInterpolator),
             py::arg("X")                  = std::vector<double>({}),
             py::arg("Y")                  = std::vector<double>({}),
             py::arg("extrapolation_mode") = t_extr_mode::extrapolate)
        .def("__call__",
             py::overload_cast<double>(&AkimaInterpolator::operator()),
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, operator_call),
             py::arg("target_x"))
        .def("__call__",
             py::overload_cast<const std::vector<double>&>(&AkimaInterpolator::operator()),
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 operator_call_2),
             py::arg("targets_x"))
        .def("empty",
             &AkimaInterpolator::empty,
             DOC(themachinethatgoesping, tools, vectorinterpolators, AkimaInterpolator, empty))
        .def("set_extrapolation_mode",
             &AkimaInterpolator::set_extrapolation_mode,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 set_extrapolation_mode),
             py::arg("extrapolation_mode"))
        .def("get_extrapolation_mode",
             &AkimaInterpolator::get_extrapolation_mode,
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_Interpolator,
                 get_extrapolation_mode))
        .def("set_data_XY",
             &AkimaInterpolator::set_data_XY,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, set_data_XY),
             py::arg("X"),
             py::arg("Y"))
        .def("get_data_X",
             &AkimaInterpolator::get_data_X,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, get_data_X))
        .def("get_data_Y",
             &AkimaInterpolator::get_data_Y,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, get_data_Y))
        .def("append",
             &AkimaInterpolator::append,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, append),
             py::arg("x"),
             py::arg("y"))
        .def("extend",
             &AkimaInterpolator::extend,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, extend),
             py::arg("X"),
             py::arg("Y"))
        .def("insert",
             &AkimaInterpolator::insert,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, insert),
             py::arg("X"),
             py::arg("Y"),
             py::arg("bool") = false)
        .def(
            "__eq__",
            &AkimaInterpolator::operator==,
            DOC(themachinethatgoesping, tools, vectorinterpolators, AkimaInterpolator, operator_eq),
            py::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(AkimaInterpolator)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(AkimaInterpolator)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(AkimaInterpolator)
        // end AkimaInterpolator
        ;
}
