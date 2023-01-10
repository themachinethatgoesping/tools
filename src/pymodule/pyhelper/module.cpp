// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/stl.h>

#include <sstream>
#include <tuple>
#include <vector>

#include "../../themachinethatgoesping/tools/pyhelper/pyindexer.hpp"
#include "../docstrings.hpp"
#include "module.hpp"

namespace py = pybind11;
using namespace themachinethatgoesping::tools::pyhelper;

#include <pybind11/pybind11.h>

// -- submodule declarations --
void init_c_pyindexer(pybind11::module& m); // init_c_pyindexer.cpp

// -- create submodule --
void init_m_pyhelper(pybind11::module& m)
{
    // module description
    auto m_pyhelper =
        m.def_submodule("pyhelper", "Classes that provide python helper functionality");

    // submodules
    init_c_pyindexer(m_pyhelper);
}
