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
#include <themachinethatgoesping/tools/vectorinterpolators/bivectorinterpolator.hpp>
#include <themachinethatgoesping/tools/vectorinterpolators/linearinterpolator.hpp>
#include <themachinethatgoesping/tools/vectorinterpolators/nearestinterpolator.hpp>
#include <themachinethatgoesping/tools/vectorinterpolators/slerpinterpolator.hpp>
#include <themachinethatgoesping/tools_nanobind/classhelper.hpp>

#include "module.hpp"
#include <themachinethatgoesping/tools_nanobind/enumhelper.hpp>
#include <themachinethatgoesping/tools_nanobind/pytensor_nanobind.hpp>

#define DOC_BiVectorInterpolator(ARG)                                                              \
    DOC(themachinethatgoesping, tools, vectorinterpolators, BiVectorInterpolator, ARG)

namespace nb = nanobind;
using namespace themachinethatgoesping::tools::vectorinterpolators;

template<typename t_interpolator>
void init_BiVectorInterpolator(nanobind::module_& m, const std::string& name)
{
    using t_BiVectorInterpolator = BiVectorInterpolator<t_interpolator>;

    nb::class_<t_BiVectorInterpolator>(
        m,
        name.c_str(),
        DOC(themachinethatgoesping, tools, vectorinterpolators, BiVectorInterpolator))
        .def(nb::init<o_extr_mode>(),
             DOC_BiVectorInterpolator(BiVectorInterpolator),
             nb::arg("extrapolation_mode") = t_extr_mode::extrapolate)
        .def("clear", &t_BiVectorInterpolator::clear, DOC_BiVectorInterpolator(clear))
        .def("size", &t_BiVectorInterpolator::size, DOC_BiVectorInterpolator(size))
        .def("get_row_coordinates",
             &t_BiVectorInterpolator::get_row_coordinates,
             DOC_BiVectorInterpolator(get_row_coordinates))
        .def("get_col_interpolators",
             &t_BiVectorInterpolator::get_col_interpolators,
             DOC_BiVectorInterpolator(get_col_interpolators))
        // interpolation function
        .def("__call__",
             &t_BiVectorInterpolator::operator(),
             DOC_BiVectorInterpolator(operator_call),
             nb::arg("row_coordinates"),
             nb::arg("column_coordinates"),
             nb::arg("mp_cores") = 1)
        .def("empty", &t_BiVectorInterpolator::empty, DOC_BiVectorInterpolator(empty))
        .def("set_extrapolation_mode",
             &t_BiVectorInterpolator::set_extrapolation_mode,
             DOC_BiVectorInterpolator(set_extrapolation_mode),
             nb::arg("extrapolation_mode"))
        .def("get_extrapolation_mode",
             &t_BiVectorInterpolator::get_extrapolation_mode,
             DOC_BiVectorInterpolator(get_extrapolation_mode))
        .def("append_row",
             &t_BiVectorInterpolator::append_row,
             DOC_BiVectorInterpolator(append_row),
             nb::arg("row_coordinate"),
             nb::arg("column_coordinates"),
             nb::arg("values"))
        .def("insert_row",
             &t_BiVectorInterpolator::insert_row,
             DOC_BiVectorInterpolator(insert_row),
             nb::arg("row_coordinate"),
             nb::arg("column_coordinates"),
             nb::arg("values"))
        .def("__eq__",
             &t_BiVectorInterpolator::operator==,
             DOC_BiVectorInterpolator(operator_eq),
             nb::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(t_BiVectorInterpolator)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(t_BiVectorInterpolator)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(t_BiVectorInterpolator)
        // end t_BiVectorInterpolator
        ;
}

void init_c_bivectorinterpolator(nanobind::module_& m)
{
    auto m_biv = m.def_submodule("bivectorinterpolators", "2D interpolators");

    init_BiVectorInterpolator<LinearInterpolator<double, double>>(m_biv, "BiLinearInterpolator");
    init_BiVectorInterpolator<LinearInterpolator<float, float>>(m_biv, "BiLinearInterpolatorF");
    init_BiVectorInterpolator<LinearInterpolator<double, float>>(m_biv, "BiLinearInterpolatorDF");
    init_BiVectorInterpolator<LinearInterpolator<float, double>>(m_biv, "BiLinearInterpolatorFD");

    init_BiVectorInterpolator<AkimaInterpolator<double>>(m_biv, "BiAkimaInterpolator");
    init_BiVectorInterpolator<AkimaInterpolator<float>>(m_biv, "BiAkimaInterpolatorF");

    init_BiVectorInterpolator<NearestInterpolator<double, double>>(m_biv, "BiNearestInterpolator");
    init_BiVectorInterpolator<NearestInterpolator<float, float>>(m_biv, "BiNearestInterpolatorF");
    init_BiVectorInterpolator<NearestInterpolator<double, float>>(m_biv, "BiNearestInterpolatorDF");
    init_BiVectorInterpolator<NearestInterpolator<float, double>>(m_biv, "BiNearestInterpolatorFD");
    init_BiVectorInterpolator<NearestInterpolator<double, int64_t>>(m_biv,
                                                                    "BiNearestInterpolatorDI");
    init_BiVectorInterpolator<NearestInterpolator<float, int64_t>>(m_biv,
                                                                   "BiNearestInterpolatorFI");
    // init_BiVectorInterpolator<NearestInterpolator<double, py::object>>(m_biv,
    //                                                                    "BiNearestInterpolatorDO");
    // init_BiVectorInterpolator<NearestInterpolator<float, py::object>>(m_biv,
    //                                                                   "BiNearestInterpolatorFO");
}