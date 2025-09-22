// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief some macros to easily implement common class capabilities for nanobind classes
 *
 * @authors Peter Urban
 */

#pragma once

/* generated doc strings */
#include ".docstrings/classhelper.doc.hpp"

#include <nanobind/nanobind.h>

namespace nb = nanobind;

/**
 * @brief return a copy using the c++ default copy constructor
 *
 */
#define __PYCLASS_DEFAULT_COPY__(T_CLASS)                                                          \
    .def(                                                                                          \
        "copy",                                                                                    \
        [](const T_CLASS& self) { return T_CLASS(self); },                                         \
        "return a copy using the c++ default copy constructor")                                    \
        .def("__copy__", [](const T_CLASS& self) { return T_CLASS(self); })                        \
        .def("__deepcopy__", [](const T_CLASS& self, nb::dict) { return T_CLASS(self); })

// --- pickle and binary support --
// this requires to_binary and from_binary functions to be implemented

#define __PYCLASS_DEFAULT_BINARY__(T_CLASS)                                                        \
    __PYCLASS_DEFAULT_BINARY__1__(T_CLASS)                                                         \
    __PYCLASS_DEFAULT_BINARY__2__(T_CLASS)                                                         \
    __PYCLASS_DEFAULT_PICKLE__(T_CLASS)                                                            \
    __PYCLASS_DEFAULT_HASH__(T_CLASS)

#define __PYCLASS_DEFAULT_HASH__(T_CLASS)                                                          \
    .def(                                                                                          \
        "__hash__",                                                                                \
        [](T_CLASS& self) { return self.binary_hash(); },                                          \
        "hash function implemented using binary_hash")                                             \
        .def(                                                                                      \
            "hash",                                                                                \
            [](T_CLASS& self) { return self.binary_hash(); },                                      \
            "hash function implemented using binary_hash")

#define __PYCLASS_DEFAULT_BINARY__1__(T_CLASS)                                                     \
    .def(                                                                                          \
        "to_binary", /*&T_CLASS::to_binary,  */                                                    \
        [](T_CLASS& self, bool resize_buffer) {                                                    \
            return nb::bytes(self.to_binary(resize_buffer));                                       \
        },                                                                                         \
        "convert object to bytearray",                                                             \
        nb::arg("resize_buffer") = true)

#define __PYCLASS_DEFAULT_BINARY__2__(T_CLASS)                                                     \
    .def_static(                                                                                   \
        "from_binary",                                                                             \
        [](const nb::bytes& buffer, bool check_buffer_is_read_completely) {                        \
            return T_CLASS::from_binary(buffer, check_buffer_is_read_completely);                  \
        },                                                                                         \
        "create T_CLASS object from bytearray",                                                    \
        nb::arg("buffer"),                                                                         \
        nb::arg("check_buffer_is_read_completely") = true)

#define __PYCLASS_DEFAULT_PICKLE__(T_CLASS)                                                        \
    .def(nb::pickle([](T_CLASS& self) { return nb::bytes(self.to_binary()); },                     \
                    [](const nb::bytes& b) { return T_CLASS::from_binary(b); }))

// --- print functions (need objectprinter __printer__ function) ---
#define __PYCLASS_DEFAULT_PRINTING__(T_CLASS)                                                      \
    .def(                                                                                          \
        "__str__",                                                                                 \
        [](T_CLASS& self) { return self.__printer__(3, true).create_str(); },                            \
        "Return object information as string")                                                     \
        .def(                                                                                      \
            "__repr__",                                                                            \
            [](T_CLASS& self) { return self.__printer__(3, true).class_name(); },                        \
            "Return object information as string")                                                 \
        .def(                                                                                      \
            "info_string",                                                                         \
            [](T_CLASS& self, unsigned int float_precision, bool superscript_exponents) {          \
                return self.__printer__(float_precision, superscript_exponents).create_str();      \
            },                                                                                     \
            "Return object information as string",                                                 \
            nb::arg("float_precision")       = 3,                                                  \
            nb::arg("superscript_exponents") = true)                                               \
        .def(                                                                                      \
            "print",                                                                               \
            [](T_CLASS& self, unsigned int float_precision, bool superscript_exponents) {          \
                nb::print(self.__printer__(float_precision, superscript_exponents).create_str());  \
            },                                                                                     \
            "Print object information",                                                            \
            nb::arg("float_precision")       = 3,                                                  \
            nb::arg("superscript_exponents") = true)

