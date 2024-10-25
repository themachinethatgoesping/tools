// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <sstream>
#include <tuple>
#include <vector>

#include <themachinethatgoesping/tools/rotationfunctions/quaternions.hpp>
#include <themachinethatgoesping/tools_pybind/classhelper.hpp>

#include "module.hpp"

#define DOC_Quaternions(ARG) DOC(themachinethatgoesping, tools, rotationfunctions, ARG)

namespace py = pybind11;
using namespace themachinethatgoesping::tools::rotationfunctions;

template<std::floating_point t_float>
void init_quaternion_types(pybind11::module& m)
{
    m.def("quaternion_from_ypr",
          py::overload_cast<std::array<t_float, 3>, bool>(&quaternion_from_ypr<t_float>),
          DOC_Quaternions(quaternion_from_ypr),
          py::arg("ypr"),
          py::arg("input_in_degrees") = true);

    m.def("quaternion_from_rpy",
          py::overload_cast<std::array<t_float, 3>, bool>(&quaternion_from_rpy<t_float>),
          DOC_Quaternions(quaternion_from_rpy),
          py::arg("rpy"),
          py::arg("input_in_degrees") = true);

    m.def("quaternion_from_ypr",
          py::overload_cast<t_float, t_float, t_float, bool>(&quaternion_from_ypr<t_float>),
          DOC_Quaternions(quaternion_from_ypr),
          py::arg("yaw"),
          py::arg("pitch"),
          py::arg("roll"),
          py::arg("input_in_degrees") = true);

    m.def("quaternion_from_rpy",
          py::overload_cast<t_float, t_float, t_float, bool>(&quaternion_from_rpy<t_float>),
          DOC_Quaternions(quaternion_from_rpy),
          py::arg("roll"),
          py::arg("pitch"),
          py::arg("yaw"),
          py::arg("input_in_degrees") = true);

    m.def("ypr_from_quaternion",
          py::overload_cast<Eigen::Quaternion<t_float>, bool>(&ypr_from_quaternion<t_float>),
          DOC_Quaternions(ypr_from_quaternion),
          py::arg("q"),
          py::arg("output_to_degrees") = true);

    m.def("rpy_from_quaternion",
          py::overload_cast<Eigen::Quaternion<t_float>, bool>(&rpy_from_quaternion<t_float>),
          DOC_Quaternions(rpy_from_quaternion),
          py::arg("q"),
          py::arg("output_to_degrees") = true);

    m.def("quaternion_from_ypr",
          py::overload_cast<const std::vector<std::array<t_float, 3>>&, bool>(
              &quaternion_from_ypr<t_float>),
          DOC_Quaternions(quaternion_from_ypr),
          py::arg("YPR"),
          py::arg("input_in_degrees") = true);

    m.def("quaternion_from_rpy",
          py::overload_cast<const std::vector<std::array<t_float, 3>>&, bool>(
              &quaternion_from_rpy<t_float>),
          DOC_Quaternions(quaternion_from_rpy),
          py::arg("RPY"),
          py::arg("input_in_degrees") = true);

    m.def("quaternion_from_ypr",
          py::overload_cast<const std::vector<t_float>&,
                            const std::vector<t_float>&,
                            const std::vector<t_float>&,
                            bool>(&quaternion_from_ypr<t_float>),
          DOC_Quaternions(quaternion_from_ypr),
          py::arg("yaw"),
          py::arg("pitch"),
          py::arg("roll"),
          py::arg("input_in_degrees") = true);

    m.def("quaternion_from_rpy",
          py::overload_cast<const std::vector<t_float>&,
                            const std::vector<t_float>&,
                            const std::vector<t_float>&,
                            bool>(&quaternion_from_rpy<t_float>),
          DOC_Quaternions(quaternion_from_rpy),
          py::arg("roll"),
          py::arg("pitch"),
          py::arg("yaw"),
          py::arg("input_in_degrees") = true);

    m.def("ypr_from_quaternion",
          py::overload_cast<const std::vector<Eigen::Quaternion<t_float>>&, bool>(
              &ypr_from_quaternion<t_float>),
          DOC_Quaternions(ypr_from_quaternion),
          py::arg("Q"),
          py::arg("output_to_degrees") = true);

    m.def("rpy_from_quaternion",
          py::overload_cast<const std::vector<Eigen::Quaternion<t_float>>&, bool>(
              &rpy_from_quaternion<t_float>),
          DOC_Quaternions(rpy_from_quaternion),
          py::arg("Q"),
          py::arg("output_to_degrees") = true);

    // m.def("get_quaternion_from_vector",
    //         py::overload_cast<const std::vector<t_float>&, const std::vector<t_float>&, const
    //         std::vector<t_float>&, bool>(&get_quaternion_from_vector<t_float>),
    //         DOC_Quaternions(
    //         get_quaternion_from_vector), py::arg("yaw"), py::arg("pitch"), py::arg("roll"),
    //         py::arg("input_in_degrees") = true);

    // m.def("get_quaternion_from_vector",
    //         py::overload_cast<const std::vector<std::array<t_float, 3>>&,
    //         bool>(&get_quaternion_from_vector<t_float>), DOC(themachinethatgoesping, tools,
    //         rotationfunctions, quaternions, get_quaternion_from_vector), py::arg("YPR"),
    //         py::arg("input_in_degrees") = true);

    m.def("rotateXYZ",
          py::overload_cast<Eigen::Quaternion<t_float>, t_float, t_float, t_float>(
              &rotateXYZ<t_float>),
          DOC_Quaternions(rotateXYZ),
          py::arg("q"),
          py::arg("x"),
          py::arg("y"),
          py::arg("z"));

    m.def("rotateXYZ",
          py::overload_cast<Eigen::Quaternion<t_float>, Eigen::Quaternion<t_float>>(
              &rotateXYZ<t_float>),
          DOC_Quaternions(rotateXYZ),
          py::arg("q"),
          py::arg("v"));
}

void init_quaternions(pybind11::module& m)
{
    init_quaternion_types<float>(m);
    init_quaternion_types<double>(m);
}