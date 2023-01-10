// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

// -- module header
#include "m_helper.hpp"
#include "docstrings.hpp" //automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include "../themachinethatgoesping/tools/helper.hpp"

// -- include system headers
#include <sstream>

// -- include pybind11 headers
#include <pybind11/chrono.h>
#include <pybind11/stl.h>

namespace py = pybind11;
using namespace themachinethatgoesping::tools::helper;

void init_m_helper(py::module& m)
{
    auto m_helper = m.def_submodule("helper", "Small helper functions");

    m_helper.def("int_as_string_4b",
                 &int_as_string<int32_t>,
                 "Interprete an integer to a 4 byte string",
                 py::arg("value"));
    m_helper.def("int_as_string_8b",
                 &int_as_string<int64_t>,
                 "Interprete an integer to a 8 byte string",
                 py::arg("value"));
    m_helper.def("string_as_int_4b",
                 &string_as_int<int32_t>,
                 "Interprete a 4 byte string to an integer",
                 py::arg("value"));
    m_helper.def("string_as_int_8b",
                 &string_as_int<int64_t>,
                 "Interprete a 8 byte string to an integer",
                 py::arg("value"));
}
