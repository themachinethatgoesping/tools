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

#include <themachinethatgoesping/tools/vectorinterpolators/akimainterpolator.hpp>
#include <themachinethatgoesping/tools_nanobind/classhelper.hpp>
#include <themachinethatgoesping/tools_nanobind/pytensor_nanobind.hpp>

#include "module.hpp"
#include <themachinethatgoesping/tools_nanobind/enumhelper.hpp>

namespace nb = nanobind;
using namespace themachinethatgoesping::tools::vectorinterpolators;

template<std::floating_point XYType>
void init_akimainterpolator(nanobind::module_& m, const std::string& name)
{
    using t_AkimaInterpolator = AkimaInterpolator<XYType>;

    nb::class_<t_AkimaInterpolator>(
        m, name.c_str(), DOC(themachinethatgoesping, tools, vectorinterpolators, AkimaInterpolator))
        .def(nb::init<const std::vector<XYType>&, const std::vector<XYType>&, o_extr_mode>(),
             DOC(themachinethatgoesping,
                 tools,
                 vectorinterpolators,
                 I_PairInterpolator,
                 I_PairInterpolator),
             nb::arg("X")                  = std::vector<XYType>({}),
             nb::arg("Y")                  = std::vector<XYType>({}),
             nb::arg("extrapolation_mode") = t_extr_mode::extrapolate)
        .def(
            "__call__",
            [](const t_AkimaInterpolator& self, XYType target_x) { return self(target_x); },
            DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, operator_call),
            nb::arg("target_x"))
        .def(
            "get_y",
            [](const t_AkimaInterpolator& self, XYType target_x) { return self.get_y(target_x); },
            DOC(themachinethatgoesping, tools, vectorinterpolators, AkimaInterpolator, get_y),
            nb::arg("target_x"))
        .def(
            "__call__",
            [](const t_AkimaInterpolator&               self,
               const xt::nanobind::pytensor<XYType, 1>& targets_x,
               int mp_cores) { return self.operator()(targets_x, mp_cores); },
            DOC(themachinethatgoesping,
                tools,
                vectorinterpolators,
                I_Interpolator,
                operator_call_2),
            nb::arg("targets_x"),
            nb::arg("mp_cores") = 1)
        .def("get_sampled_X",
             &t_AkimaInterpolator::get_sampled_X,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, get_sampled_X),
             nb::arg("downsample_interval"),
             nb::arg("max_gap") = std::numeric_limits<double>::quiet_NaN())
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
             nb::arg("extrapolation_mode"))
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
             nb::arg("X"),
             nb::arg("Y"))
        .def("get_data_X",
             &t_AkimaInterpolator::get_data_X,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, get_data_X))
        .def("get_data_Y",
             &t_AkimaInterpolator::get_data_Y,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, get_data_Y))
        .def("append",
             &t_AkimaInterpolator::append,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, append),
             nb::arg("x"),
             nb::arg("y"))
        .def("extend",
             &t_AkimaInterpolator::extend,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, extend),
             nb::arg("X"),
             nb::arg("Y"))
        .def("insert",
             &t_AkimaInterpolator::insert,
             DOC(themachinethatgoesping, tools, vectorinterpolators, I_Interpolator, insert),
             nb::arg("X"),
             nb::arg("Y"),
             nb::arg("bool") = false)
        .def(
            "__eq__",
            &t_AkimaInterpolator::operator==,
            DOC(themachinethatgoesping, tools, vectorinterpolators, AkimaInterpolator, operator_eq),
            nb::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(t_AkimaInterpolator)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(t_AkimaInterpolator)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(t_AkimaInterpolator)
        // end t_AkimaInterpolator
        ;
}

void init_c_akimainterpolator(nanobind::module_& m)
{
    init_akimainterpolator<double>(m, "AkimaInterpolator");
    init_akimainterpolator<float>(m, "AkimaInterpolatorF");
}