// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/stl.h>

#include <sstream>
#include <tuple>
#include <vector>

#include "../../tools/vectorinterpolators/nearestinterpolator.hpp"
#include "../docstrings.hpp"
#include "module.hpp"

namespace py = pybind11;
using namespace themachinethatgoesping::tools::vectorinterpolators;

void
init_subm_nearestinterpolator(pybind11::module& m)
{

  py::class_<NearestInterpolator>(
    m,
    "NearestInterpolator",
    DOC(
      themachinethatgoesping, tools, vectorinterpolators, NearestInterpolator))
    .def(py::init<const std::vector<std::pair<double, double>>&, t_extr_mode>(),
         DOC(themachinethatgoesping,
             tools,
             vectorinterpolators,
             I_PairInterpolator,
             I_PairInterpolator),
         py::arg("XY"),
         py::arg("extrapolation_mode") = t_extr_mode::extrapolate)
    .def(py::init<const std::vector<double>&,
                  const std::vector<double>&,
                  t_extr_mode>(),
         DOC(themachinethatgoesping,
             tools,
             vectorinterpolators,
             I_PairInterpolator,
             I_PairInterpolator_2),
         py::arg("X") = std::vector<double>({ 0, 1 }),
         py::arg("Y") = std::vector<double>({ 0, 1 }),
         py::arg("extrapolation_mode") = t_extr_mode::extrapolate)
    .def("interpolate",
         py::overload_cast<double>(&NearestInterpolator::interpolate),
         DOC(themachinethatgoesping,
             tools,
             vectorinterpolators,
             I_Interpolator,
             interpolate),
         py::arg("target_x"))
    .def("interpolate",
         py::overload_cast<const std::vector<double>&>(
           &NearestInterpolator::interpolate),
         DOC(themachinethatgoesping,
             tools,
             vectorinterpolators,
             I_Interpolator,
             interpolate_2),
         py::arg("targets_x"))
    .def("set_extrapolation_mode",
         &NearestInterpolator::set_extrapolation_mode,
         DOC(themachinethatgoesping,
             tools,
             vectorinterpolators,
             I_Interpolator,
             set_extrapolation_mode),
         py::arg("extrapolation_mode"))
    .def("get_extrapolation_mode",
         &NearestInterpolator::get_extrapolation_mode,
         DOC(themachinethatgoesping,
             tools,
             vectorinterpolators,
             I_Interpolator,
             get_extrapolation_mode))
    .def("set_data_XY",
         py::overload_cast<const std::vector<std::pair<double, double>>&>(
           &NearestInterpolator::set_data_XY),
         DOC(themachinethatgoesping,
             tools,
             vectorinterpolators,
             I_Interpolator,
             set_data_XY),
         py::arg("XY"))
    .def(
      "set_data_XY",
      py::overload_cast<const std::vector<double>&, const std::vector<double>&>(
        &NearestInterpolator::set_data_XY),
      DOC(themachinethatgoesping,
          tools,
          vectorinterpolators,
          I_Interpolator,
          set_data_XY_2),
      py::arg("X"),
      py::arg("Y"))
    .def(
      "append",
      py::overload_cast<double, double>(
        &NearestInterpolator::append),
      DOC(themachinethatgoesping,
          tools,
          vectorinterpolators,
          I_Interpolator,
          append),
      py::arg("X"),
      py::arg("Y"))
    .def(
      "append",
      py::overload_cast<std::pair<double,double>>(
        &NearestInterpolator::append),
      DOC(themachinethatgoesping,
          tools,
          vectorinterpolators,
          I_Interpolator,
          append_2),
      py::arg("XY"))
    .def(
      "extend",
      py::overload_cast<const std::vector<double>&, const std::vector<double>&>(
        &NearestInterpolator::extend),
      DOC(themachinethatgoesping,
          tools,
          vectorinterpolators,
          I_Interpolator,
          extend),
      py::arg("X"),
      py::arg("Y"))
    .def(
      "extend",
      py::overload_cast<const std::vector<std::pair<double,double>>&>(
        &NearestInterpolator::extend),
      DOC(themachinethatgoesping,
          tools,
          vectorinterpolators,
          I_Interpolator,
          extend_2),
      py::arg("XY"));
}
