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
    .def("copy", [](const T_CLASS& self) { return T_CLASS(self); })                                \
        .def("__copy__", [](const T_CLASS& self) { return T_CLASS(self); })                        
        // TODO: deepcopy example does not work
        // https://pybind11.readthedocs.io/en/stable/advanced/classes.html?highlight=deepcopy#deepcopy-support
        // .def(                                                                                      
        //     "__deepcopy__",                                                                        
        //     [](const T_CLASS& self, py::dict) { return T_CLASS(self); },                           
        //     "memo"_a);