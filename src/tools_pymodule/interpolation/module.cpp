// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/stl.h>

#include <sstream>
#include <tuple>
#include <vector>

#include "../../tools/interpolation/linearinterpolator.h"
#include "../docstrings.h"
#include "module.h"

namespace py = pybind11;
using namespace themachinethatgoesping::tools::interpolation;

#include <pybind11/pybind11.h>

// -- submodule declerations --
void init_subm_nearestinterpolator(pybind11::module& m);  // subm_nearestinterpolator.cpp
void init_subm_linearinterpolator(pybind11::module& m);  // subm_linearinterpolator.cpp


// -- create submodule --
void init_m_interpolation(pybind11::module& m)
{
  //module description
  auto m_interpolation = m.def_submodule(
    "interpolation",
    "Classes for getting interpolated values from within vectors");

  //small classes
  pybind11::enum_<t_extr_mode>(
    m_interpolation,
    "t_extr_mode",
    DOC(themachinethatgoesping, tools, interpolation, t_extr_mode))
    .value("extrapolate", t_extr_mode::extrapolate)
    .value("nearest", t_extr_mode::nearest)
    .value("fail", t_extr_mode::fail)
    .export_values();

  //interpolator classes
  init_subm_nearestinterpolator(m_interpolation);
  init_subm_linearinterpolator(m_interpolation);
}
