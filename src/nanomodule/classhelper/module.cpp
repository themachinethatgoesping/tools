// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <nanobind/stl/string.h>

#include <sstream>
#include <tuple>
#include <vector>

#include "../../themachinethatgoesping/tools/classhelper/objectprinter.hpp"

#include "module.hpp"

namespace nb = nanobind;
using namespace themachinethatgoesping::tools::classhelper;

#include <nanobind/nanobind.h>

// -- submodule declarations --
void init_c_objectprinter(nanobind::module_& m); // init_c_objectprinter.cpp

// -- create submodule --
void init_m_classhelper(nanobind::module_& m)
{
    // module description
    auto m_classhelper = m.def_submodule(
        "classhelper",
        "Classes that help adding common functionality to themachinethatgoesping classes");

    // submodules
    init_c_objectprinter(m_classhelper);
}
