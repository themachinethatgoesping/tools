// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/stl.h>

#include <sstream>
#include <tuple>
#include <vector>

#include "../../tools/vectorinterpolators/nearestinterpolator.h"
#include "../docstrings.h"
#include "module.h"

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
    .def(py::init<const std::vector<std::pair<double, double>>&,
                  bool,
                  bool,
                  t_extr_mode>(),
         DOC(themachinethatgoesping,
             tools,
             vectorinterpolators,
             I_Interpolator,
             I_Interpolator),
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
             vectorinterpolators,
             I_Interpolator,
             I_Interpolator),
         py::arg("X") = std::vector<double>({ 0, 1 }),
         py::arg("Y") = std::vector<double>({ 0, 1 }),
         py::arg("sortX") = false,
         py::arg("checkX") = true,
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
    .def("checkX",
         &NearestInterpolator::checkX,
         DOC(themachinethatgoesping,
             tools,
             vectorinterpolators,
             I_Interpolator,
             checkX))
    .def("sortX",
         &NearestInterpolator::sortX,
         DOC(themachinethatgoesping,
             tools,
             vectorinterpolators,
             I_Interpolator,
             sortX))
    .def("set_data_XY",
         py::overload_cast<const std::vector<std::pair<double, double>>&,
                           bool,
                           bool>(&NearestInterpolator::set_data_XY),
         DOC(themachinethatgoesping,
             tools,
             vectorinterpolators,
             I_Interpolator,
             set_data_XY),
         py::arg("XY"),
         py::arg("sortX") = false,
         py::arg("checkX") = true)
    .def("set_data_XY",
         py::overload_cast<const std::vector<double>&,
                           const std::vector<double>&,
                           bool,
                           bool>(&NearestInterpolator::set_data_XY),
         DOC(themachinethatgoesping,
             tools,
             vectorinterpolators,
             I_Interpolator,
             set_data_XY_2),
         py::arg("X"),
         py::arg("Y"),
         py::arg("sortX") = false,
         py::arg("checkX") = true)
    .def("get_data_X",
         &NearestInterpolator::get_data_X,
         DOC(themachinethatgoesping,
             tools,
             vectorinterpolators,
             I_Interpolator,
             get_data_X))
    .def("get_data_Y",
         &NearestInterpolator::get_data_X,
         DOC(themachinethatgoesping,
             tools,
             vectorinterpolators,
             I_Interpolator,
             get_data_Y))
    .def("get_data_XY",
         &NearestInterpolator::get_data_XY,
         DOC(themachinethatgoesping,
             tools,
             vectorinterpolators,
             I_Interpolator,
             get_data_XY));
}
