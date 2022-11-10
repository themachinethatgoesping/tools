// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/stl.h>

#include <sstream>
#include <tuple>
#include <vector>

#include "../../themachinethatgoesping/tools/classhelper/objectprinter.hpp"
#include "../docstrings.hpp"
#include "module.hpp"

namespace py = pybind11;
using namespace themachinethatgoesping::tools::classhelper;

#include <pybind11/pybind11.h>

// -- submodule declarations --
void init_c_objectprinter(pybind11::module& m); // init_c_objectprinter.cpp

// -- create submodule --
void init_m_classhelper(pybind11::module& m)
{
    // module description
    auto m_classhelper = m.def_submodule(
        "classhelper",
        "Classes that help adding common functionality to themachinethatgoesping classes");

    // submodules
    init_c_objectprinter(m_classhelper);
}
