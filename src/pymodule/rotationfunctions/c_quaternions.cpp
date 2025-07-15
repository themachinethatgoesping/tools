// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
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

    m.def(
        "rotateYPR",
        [](t_float yaw1,
           t_float pitch1,
           t_float roll1,
           t_float yaw2,
           t_float pitch2,
           t_float roll2,
           bool    input_in_degrees = true) {
            auto q1 = quaternion_from_ypr(yaw1, pitch1, roll1, input_in_degrees);
            auto q2 = quaternion_from_ypr(yaw2, pitch2, roll2, input_in_degrees);

            auto q3 = q1 * q2;
            return ypr_from_quaternion(q3, input_in_degrees);
        },
        "Rotate yaw pitch roll angles by other yaw pitch and roll angles",
        py::arg("yaw1"),
        py::arg("pitch1"),
        py::arg("roll1"),
        py::arg("yaw2"),
        py::arg("pitch2"),
        py::arg("roll2"),
        py::arg("input_in_degrees") = true);

    m.def(
        "rotateYPR",
        [](const std::vector<t_float>& yaw1,
           const std::vector<t_float>& pitch1,
           const std::vector<t_float>& roll1,
           t_float                     yaw2,
           t_float                     pitch2,
           t_float                     roll2,
           bool                        input_in_degrees = true) {
            auto Q1 = quaternion_from_ypr(yaw1, pitch1, roll1, input_in_degrees);
            auto q2 = quaternion_from_ypr(yaw2, pitch2, roll2, input_in_degrees);

            std::vector<Eigen::Quaternion<t_float>> Q3;
            Q3.reserve(Q1.size());

            for (unsigned int i = 0; i < Q1.size(); ++i)
            {
                Q3.push_back(Q1[i] * q2);
            }
            return ypr_from_quaternion(Q3, input_in_degrees);
        },
        "Rotate yaw pitch roll angles by other yaw pitch and roll angles",
        py::arg("yaw1"),
        py::arg("pitch1"),
        py::arg("roll1"),
        py::arg("yaw2"),
        py::arg("pitch2"),
        py::arg("roll2"),
        py::arg("input_in_degrees") = true);
}

void init_quaternions(pybind11::module& m)
{
    init_quaternion_types<float>(m);
    init_quaternion_types<double>(m);
}