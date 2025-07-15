// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0



#include <pybind11/stl.h>

#include <sstream>
#include <tuple>
#include <vector>

#include <themachinethatgoesping/tools/rotationfunctions/quaternions.hpp>

#include "module.hpp"

namespace py = pybind11;
using namespace themachinethatgoesping::tools::rotationfunctions;
using namespace themachinethatgoesping;

#include <pybind11/pybind11.h>

// -- submodule declarations --
void init_quaternions(pybind11::module& m); // c_init_quaternions.cpp


// -- create submodule --
void init_m_rotationfunctions(pybind11::module& m)
{
    // module description
    auto m_rotationfunctions = m.def_submodule(
        "rotationfunctions", "functions for rotating coordinates using libeigen quaternions");

    init_quaternions(m_rotationfunctions);
}
