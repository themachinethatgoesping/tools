// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <nanobind/stl/string.h>

#include <sstream>
#include <tuple>
#include <vector>

#include "../../themachinethatgoesping/tools/pyhelper/pyindexer.hpp"

#include "module.hpp"

namespace nb = nanobind;
using namespace themachinethatgoesping::tools::pyhelper;

#include <nanobind/nanobind.h>

// -- submodule declarations --
void init_c_pyindexer(nanobind::module_& m); // init_c_pyindexer.cpp

// -- create submodule --
void init_m_pyhelper(nanobind::module_& m)
{
    // module description
    auto m_pyhelper =
        m.def_submodule("pyhelper", "Classes that provide python helper functionality");

    // submodules
    init_c_pyindexer(m_pyhelper);
}
