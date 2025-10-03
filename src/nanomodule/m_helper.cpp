// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#include "m_helper.hpp"
// automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

// -- c++ library headers
#include <themachinethatgoesping/tools/helper/printing.hpp>
#include <themachinethatgoesping/tools/helper/stringconversion.hpp>

#include <themachinethatgoesping/tools_nanobind/pytensor_nanobind.hpp>

// -- include system headers
#include <sstream>

// -- include nanobind headers
#include <nanobind/nanobind.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/string.h>

namespace nb = nanobind;
using namespace themachinethatgoesping::tools::helper;

void init_m_helper(nb::module_& m)
{
    auto m_helper = m.def_submodule("helper", "Small helper functions");

    m_helper.def("int_as_string_4b",
                 &int_as_string<int32_t>,
                 "Interprete an integer to a 4 byte string",
                 nb::arg("value"));
    m_helper.def("int_as_string_8b",
                 &int_as_string<int64_t>,
                 "Interprete an integer to a 8 byte string",
                 nb::arg("value"));
    m_helper.def("string_as_int_4b",
                 &string_as_int<int32_t>,
                 "Interprete a 4 byte string to an integer",
                 nb::arg("value"));
    m_helper.def("string_as_int_8b",
                 &string_as_int<int64_t>,
                 "Interprete a 8 byte string to an integer",
                 nb::arg("value"));
    m_helper.def(
        "superscript", &superscript, "convert integer number to superscript", nb::arg("exponent"));

    // performance tests
    m_helper.def("pytensor_load_ref",
                 [](xt::nanobind::pytensor<double, 2>& t) { t.unchecked(0, 0) += 1.0; });
    m_helper.def("pytensor_const_load_ref", [](const xt::nanobind::pytensor<double, 2>& t) {
        auto t2 = t;
        t2.unchecked(0, 0) += 1.0;
        return t2;
    });
    m_helper.def("pytensor_load_copy", [](xt::nanobind::pytensor<double, 2> t) {
        t.unchecked(0, 0) += 1.0;
        return t;
    });

    m_helper.def("pytensor_loop_ref", [](xt::nanobind::pytensor<double, 2>& t) {
        for (auto i = 0; i < t.size(); i += 1)
            t.flat(i) += 1.0;
    });
    m_helper.def("pytensor_loop_ref2", [](xt::nanobind::pytensor<double, 2>& t) {
        for (auto i = 0; i < t.size(); i += 1)
            t.data()[i] += 1.0;
    });
    m_helper.def("pytensor_sum_ref", [](xt::nanobind::pytensor<double, 2>& t) {
        t+= xt::sum(t)();
    });
    m_helper.def("pytensor_sum_const_ref", [](const xt::nanobind::pytensor<double, 2>& t) {
        return xt::eval(t+xt::sum(t)());
    });
}
