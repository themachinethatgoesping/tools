// SPDX-FileCopyrightText: 2022 - 2026 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <concepts>
#include <string>

#include <nanobind/nanobind.h>
#include <nanobind/stl/array.h>
#include <nanobind/stl/string.h>

#include <xtensor-python/nanobind/pytensor.hpp>

#include <themachinethatgoesping/tools/rotationfunctions/rotation.hpp>
#include <themachinethatgoesping/tools_nanobind/classhelper.hpp>

#include "module.hpp"

namespace nb = nanobind;
using namespace themachinethatgoesping::tools::rotationfunctions;

#define DOC_Rotation(ARG) DOC(themachinethatgoesping, tools, rotationfunctions, Rotation, ARG)

template<std::floating_point t_float>
static void init_rotation(nb::module_& m, const std::string& name)
{
    using t_Rotation = Rotation<t_float>;

    nb::class_<t_Rotation>(
        m, name.c_str(), DOC(themachinethatgoesping, tools, rotationfunctions, Rotation))

        // ----- constructors -----
        .def(nb::init<>(), DOC_Rotation(Rotation))
        .def(nb::init<const std::array<t_float, 3>&, bool>(),
             DOC_Rotation(Rotation_2),
             nb::arg("ypr"),
             nb::arg("input_in_degrees") = true)
        .def(nb::init<t_float, t_float, t_float, bool>(),
             DOC_Rotation(Rotation_3),
             nb::arg("yaw"),
             nb::arg("pitch"),
             nb::arg("roll"),
             nb::arg("input_in_degrees") = true)

        // ----- named factories -----
        .def_static("from_quaternion",
                    &t_Rotation::from_quaternion,
                    DOC_Rotation(from_quaternion),
                    nb::arg("w"),
                    nb::arg("x"),
                    nb::arg("y"),
                    nb::arg("z"))
        .def_static("from_ypr",
                    nb::overload_cast<t_float, t_float, t_float, bool>(&t_Rotation::from_ypr),
                    DOC_Rotation(from_ypr),
                    nb::arg("yaw"),
                    nb::arg("pitch"),
                    nb::arg("roll"),
                    nb::arg("input_in_degrees") = true)
        .def_static("from_ypr",
                    nb::overload_cast<const std::array<t_float, 3>&, bool>(&t_Rotation::from_ypr),
                    DOC_Rotation(from_ypr_2),
                    nb::arg("ypr"),
                    nb::arg("input_in_degrees") = true)
        .def_static("from_rpy",
                    nb::overload_cast<t_float, t_float, t_float, bool>(&t_Rotation::from_rpy),
                    DOC_Rotation(from_rpy),
                    nb::arg("roll"),
                    nb::arg("pitch"),
                    nb::arg("yaw"),
                    nb::arg("input_in_degrees") = true)
        .def_static("from_rpy",
                    nb::overload_cast<const std::array<t_float, 3>&, bool>(&t_Rotation::from_rpy),
                    DOC_Rotation(from_rpy_2),
                    nb::arg("rpy"),
                    nb::arg("input_in_degrees") = true)

        // ----- extraction -----
        .def("ypr", &t_Rotation::ypr, DOC_Rotation(ypr), nb::arg("output_in_degrees") = true)
        .def("rpy", &t_Rotation::rpy, DOC_Rotation(rpy), nb::arg("output_in_degrees") = true)
        .def("wxyz", &t_Rotation::wxyz, DOC_Rotation(wxyz))

        // ----- rotate -----
        .def("rotate",
             nb::overload_cast<t_float, t_float, t_float>(&t_Rotation::rotate, nb::const_),
             DOC_Rotation(rotate),
             nb::arg("x"),
             nb::arg("y"),
             nb::arg("z"))
        .def("rotate",
             nb::overload_cast<const std::array<t_float, 3>&>(&t_Rotation::rotate, nb::const_),
             DOC_Rotation(rotate_2),
             nb::arg("xyz"))
        .def("rotate",
             nb::overload_cast<const t_Rotation&>(&t_Rotation::rotate, nb::const_),
             DOC_Rotation(rotate_3),
             nb::arg("rotation"))
        .def(
            "rotate",
            [](const t_Rotation& self, const xt::nanobind::pytensor<t_float, 2>& points) {
                xt::xtensor<t_float, 2> points_copy = points;
                return self.rotate(points_copy);
            },
            DOC_Rotation(rotate_4),
            nb::arg("points"))

        // ----- operators -----
        .def("__eq__", &t_Rotation::operator==, DOC_Rotation(operator_eq), nb::arg("other"))
        .def(
            "__mul__",
            [](const t_Rotation& self, const t_Rotation& other) { return self.rotate(other); },
            nb::arg("other"))

        // default copy/binary/printing
        __PYCLASS_DEFAULT_COPY__(t_Rotation)
        __PYCLASS_DEFAULT_BINARY__(t_Rotation)
        __PYCLASS_DEFAULT_PRINTING__(t_Rotation)
        ;
}

void init_c_rotation(nb::module_& m)
{
    init_rotation<float>(m, "Rotation");
    init_rotation<double>(m, "RotationD");
}
