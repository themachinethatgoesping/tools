// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
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

void
init_subm_linearinterpolator(pybind11::module& m)
{

  py::class_<LinearInterpolator>(
    m,
    "LinearInterpolator",
    DOC(themachinethatgoesping, tools, interpolation, LinearInterpolator))
    .def(py::init<const std::vector<std::pair<double, double>>&,
                  bool,
                  bool,
                  t_extr_mode>(),
         DOC(themachinethatgoesping,
             tools,
             interpolation,
             LinearInterpolator,
             LinearInterpolator),
         py::arg("XY"),
         py::arg("sortX") = false,
         py::arg("checkX") = true,
         py::arg("extrapolation_mode") = t_extr_mode::extrapolate)
    .def(py::init<const std::vector<double>&,
                  const std::vector<double>&,
                  bool,
                  bool,
                  t_extr_mode>(),
         DOC(themachinethatgoesping,
             tools,
             interpolation,
             LinearInterpolator,
             LinearInterpolator_2),
         py::arg("X") = std::vector<double>({ 0, 1 }),
         py::arg("Y") = std::vector<double>({ 0, 1 }),
         py::arg("sortX") = false,
         py::arg("checkX") = true,
         py::arg("extrapolation_mode") = t_extr_mode::extrapolate)
    .def("interpolate",
         py::overload_cast<double>(&LinearInterpolator::interpolate),
         DOC(themachinethatgoesping,
             tools,
             interpolation,
             I_Interpolator,
             interpolate),
         py::arg("target_x"))
    .def("interpolate",
         py::overload_cast<const std::vector<double>&>(
           &LinearInterpolator::interpolate),
         DOC(themachinethatgoesping,
             tools,
             interpolation,
             I_Interpolator,
             interpolate_2),
         py::arg("targets_x"))
    .def(
      "sortX",
      &LinearInterpolator::sortX,
      DOC(themachinethatgoesping, tools, interpolation, I_Interpolator, sortX))
    .def(
      "checkX",
      &LinearInterpolator::checkX,
      DOC(themachinethatgoesping, tools, interpolation, I_Interpolator, checkX))
    .def("set_data_XY",
         py::overload_cast<const std::vector<std::pair<double, double>>&,
                           bool,
                           bool>(&LinearInterpolator::set_data_XY),
         DOC(themachinethatgoesping,
             tools,
             interpolation,
             I_Interpolator,
             set_data_XY),
         py::arg("XY"),
         py::arg("sortX") = false,
         py::arg("checkX") = false)
    .def("set_data_XY",
         py::overload_cast<const std::vector<double>&,
                           const std::vector<double>&,
                           bool,
                           bool>(&LinearInterpolator::set_data_XY),
         DOC(themachinethatgoesping,
             tools,
             interpolation,
             I_Interpolator,
             set_data_XY_2),
         py::arg("X"),
         py::arg("Y"),
         py::arg("sortX") = false,
         py::arg("checkX") = false)
    .def("get_data_X",
         &LinearInterpolator::get_data_X,
         DOC(themachinethatgoesping,
             tools,
             interpolation,
             I_Interpolator,
             get_data_X))
    .def("get_data_Y",
         &LinearInterpolator::get_data_X,
         DOC(themachinethatgoesping,
             tools,
             interpolation,
             I_Interpolator,
             get_data_Y))
    .def("get_data_XY",
         &LinearInterpolator::get_data_XY,
         DOC(themachinethatgoesping,
             tools,
             interpolation,
             I_Interpolator,
             get_data_XY))
    .def("set_extrapolation_mode",
         &LinearInterpolator::set_extrapolation_mode,
         DOC(themachinethatgoesping,
             tools,
             interpolation,
             I_Interpolator,
             set_extrapolation_mode),
         py::arg("extrapolation_mode"))
    .def("get_extrapolation_mode",
         &LinearInterpolator::get_extrapolation_mode,
         DOC(themachinethatgoesping,
             tools,
             interpolation,
             I_Interpolator,
             get_extrapolation_mode));
}
