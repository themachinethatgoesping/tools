// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/stl.h>

#include <sstream>
#include <tuple>
#include <vector>

#include <themachinethatgoesping/tools_pybind/enumhelper.hpp>

#include <themachinethatgoesping/tools/vectorinterpolators/i_interpolator.hpp>

#include "module.hpp"

namespace py = pybind11;
using namespace themachinethatgoesping::tools::vectorinterpolators;
using namespace themachinethatgoesping;

#include <pybind11/pybind11.h>

// -- submodule declarations --
void init_c_nearestinterpolator(pybind11::module& m);  // c_nearestinterpolator.cpp
void init_c_linearinterpolator(pybind11::module& m);   // c_linearinterpolator.cpp
void init_c_akimainterpolator(pybind11::module& m);    // c_linearinterpolator.cpp
void init_c_slerpinterpolator(pybind11::module& m);    // c_linearinterpolator.cpp
void init_c_bivectorinterpolator(pybind11::module& m); // c_bivectorinterpolator.cpp

// -- create submodule --
void init_m_vectorinterpolators(pybind11::module& m)
{
    // module description
    auto m_vectorinterpolators = m.def_submodule(
        "vectorinterpolators", "Classes for getting interpolated values from within vectors");

    // small classes
    auto pyenum_extr_mode =
        pybind11::enum_<t_extr_mode>(
            m_vectorinterpolators,
            "t_extr_mode",
            DOC(themachinethatgoesping, tools, vectorinterpolators, t_extr_mode))
            .value("extrapolate", t_extr_mode::extrapolate)
            .value("nearest", t_extr_mode::nearest)
            .value("fail", t_extr_mode::fail)
            .export_values()
        // end
        ;
    tools::pybind_helper::add_string_to_enum_conversion<t_extr_mode>(pyenum_extr_mode);

    // interpolator classes
    init_c_nearestinterpolator(m_vectorinterpolators);
    init_c_linearinterpolator(m_vectorinterpolators);
    init_c_akimainterpolator(m_vectorinterpolators);
    init_c_slerpinterpolator(m_vectorinterpolators);
    init_c_bivectorinterpolator(m_vectorinterpolators);
}
