// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/stl.h>

#include <sstream>
#include <tuple>
#include <vector>

#include "../../tools/classhelpers/objectprinter.hpp"
#include "../docstrings.hpp"
#include "module.hpp"

namespace py = pybind11;
using namespace themachinethatgoesping::tools::classhelpers;

#include <pybind11/pybind11.h>

// -- submodule declerations --
void init_subm_objectprinter(pybind11::module& m); // init_subm_objectprinter.cpp

// -- create submodule --
void init_m_classhelpers(pybind11::module& m)
{
    // module description
    auto m_classhelpers = m.def_submodule(
        "classhelpers", "Classes that help adding common functionality to themachinethatgoesping classes");

    // submodules
    init_subm_objectprinter(m_classhelpers);
}
