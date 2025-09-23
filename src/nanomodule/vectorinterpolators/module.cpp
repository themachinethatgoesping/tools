// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

#include <sstream>
#include <tuple>
#include <vector>

#include <themachinethatgoesping/tools/vectorinterpolators/i_interpolator.hpp>

#include "module.hpp"

namespace nb = nanobind;
using namespace themachinethatgoesping::tools::vectorinterpolators;
using namespace themachinethatgoesping;

#include <nanobind/nanobind.h>
#include <themachinethatgoesping/tools_nanobind/enumhelper.hpp>

// Make the enum opaque so we can bind it as a class instead of using the built-in enum type caster
NB_MAKE_OPAQUE(themachinethatgoesping::tools::vectorinterpolators::t_extr_mode);

// -- submodule declarations --
void init_c_nearestinterpolator(nanobind::module_& m);  // c_nearestinterpolator.cpp
void init_c_linearinterpolator(nanobind::module_& m);   // c_linearinterpolator.cpp
void init_c_akimainterpolator(nanobind::module_& m);    // c_linearinterpolator.cpp
void init_c_slerpinterpolator(nanobind::module_& m);    // c_linearinterpolator.cpp
void init_c_bivectorinterpolator(nanobind::module_& m); // c_bivectorinterpolator.cpp

// -- create submodule --
void init_m_vectorinterpolators(nanobind::module_& m)
{
    // module description
    auto m_vectorinterpolators = m.def_submodule(
        "vectorinterpolators", "Classes for getting interpolated values from within vectors");

    // small classes
    auto pyenum_extr_mode =
        nanobind::enum_<t_extr_mode>(
            m_vectorinterpolators,
            "t_extr_mode",
            DOC(themachinethatgoesping, tools, vectorinterpolators, t_extr_mode))
            .value("extrapolate", t_extr_mode::extrapolate)
            .value("nearest", t_extr_mode::nearest)
            .value("fail", t_extr_mode::fail)
            .export_values()
        // end
        ;
    tools::nanobind_helper::add_string_to_enum_conversion<t_extr_mode>(pyenum_extr_mode);
    // tools::nanobind_helper::make_enum_string_class<t_extr_mode>(
    //     m_vectorinterpolators, "t_extr_mode");

    // interpolator classes
    init_c_nearestinterpolator(m_vectorinterpolators);
    init_c_linearinterpolator(m_vectorinterpolators);
    init_c_akimainterpolator(m_vectorinterpolators);
    init_c_slerpinterpolator(m_vectorinterpolators);
    init_c_bivectorinterpolator(m_vectorinterpolators);
}
