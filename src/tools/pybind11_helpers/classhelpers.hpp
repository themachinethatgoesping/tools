// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief some macros to easily implement comon class capabilities for for pybind classes
 *
 * @authors Peter Urban
 */

#pragma once

/**
 * @brief return a copy using the c++ default copy constructor
 *
 */
#define __PYCLASS_DEFAULT_COPY__(T_CLASS)                                                          \
    .def(                                                                                          \
        "copy",                                                                                    \
        [](const T_CLASS& self) { return T_CLASS(self); },                                         \
        "return a copy using the c++ default copy constructor")                                    \
        .def("__copy__", [](const T_CLASS& self) { return T_CLASS(self); })

// TODO: deepcopy example does not work
// https://pybind11.readthedocs.io/en/stable/advanced/classes.html?highlight=deepcopy#deepcopy-support
// .def(
//     "__deepcopy__",
//     [](const T_CLASS& self, py::dict) { return T_CLASS(self); },
//     "memo"_a);

// --- pickle and binary support --
// this requires to_binary and from_binary functions implemented in
// bitsery_helpers/classfunctions.hpp

#define __PYCLASS_DEFAULT_BINARY__(T_CLASS)                                                        \
    __PYCLASS_DEFAULT_BINARY__1__(T_CLASS)                                                         \
    __PYCLASS_DEFAULT_BINARY__2__(T_CLASS)                                                         \
    __PYCLASS_DEFAULT_PICKLE__(T_CLASS)

#define __PYCLASS_DEFAULT_BINARY__1__(T_CLASS)                                                     \
    .def(                                                                                          \
        "to_binary", /*&T_CLASS::to_binary,  */                                                    \
        [](const T_CLASS& self, bool resize_buffer) {                                              \
            return py::bytes(self.to_binary(resize_buffer));                                       \
        },                                                                                         \
        "convert object to bytearray",                                                             \
        py::arg("resize_buffer") = true)

#define __PYCLASS_DEFAULT_BINARY__2__(T_CLASS)                                                     \
    .def_static(                                                                                   \
        "from_binary",                                                                             \
        [](const py::bytes& buffer, bool check_buffer_is_read_completely) {                        \
            return T_CLASS::from_binary(buffer, check_buffer_is_read_completely);                  \
        },                                                                                         \
        "create T_CLASS object from bytearray",                                                    \
        py::arg("buffer"),                                                                         \
        py::arg("check_buffer_is_read_completely") = true)

#define __PYCLASS_DEFAULT_PICKLE__(T_CLASS)                                                        \
    .def(py::pickle([](const T_CLASS& self) { return py::bytes(self.to_binary()); },               \
                    [](const py::bytes& b) { return T_CLASS::from_binary(b); }))

// --- print functions (need objectprinter __printer__ function) ---
#define __PYCLASS_DEFAULT_PRINTING__(T_CLASS)                                                      \
    .def("__str__", [](const T_CLASS& self) { return self.__printer__().str(); })                  \
        .def("__repr__", [](const T_CLASS& self) { return self.__printer__().str(); })              \
        .def("to_string", [](const T_CLASS& self) { return self.__printer__().str(); })            \
        .def("print", [](const T_CLASS& self) { py::print(self.__printer__().str()); })
