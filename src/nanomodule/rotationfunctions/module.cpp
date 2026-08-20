// SPDX-FileCopyrightText: 2022 - 2026 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <nanobind/nanobind.h>

#include "module.hpp"

namespace nb = nanobind;

// -- submodule declarations --
void init_c_rotation(nanobind::module_& m); // c_rotation.cpp

// -- create submodule --
void init_m_rotationfunctions(nb::module_& m)
{
    auto m_rotationfunctions = m.def_submodule(
        "rotationfunctions",
        "Rotation class (Rotation = float, RotationD = double) built on Eigen quaternions, "
        "with yaw/pitch/roll construction and (vectorized) vector rotation");

    init_c_rotation(m_rotationfunctions);
}
