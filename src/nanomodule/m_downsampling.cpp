// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "m_downsampling.hpp"

// -- c++ library headers
#include <themachinethatgoesping/tools/helper/downsampling.hpp>

// -- include nanobind headers
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

#include <xtensor-python/nanobind/pytensor.hpp>

namespace nb        = nanobind;
namespace pingtools = themachinethatgoesping::tools;

void init_m_downsampling(nb::module_& m)
{
    auto m_helper = m.def_submodule("helper");

    // Bind get_index_downsampling for pytensor<double, 1>
    m_helper.def(
        "get_index_downsampling",
        [](const xt::nanobind::pytensor<double, 1>& data,
           double                                   downsample_interval,
           double                                   max_gap) {
            // Adapt the pytensor to work with our template function
            xt::xtensor<double, 1> data_copy = data;
            return pingtools::helper::get_index_downsampling(
                data_copy, downsample_interval, max_gap);
        },
        DOC(themachinethatgoesping, tools, helper, get_index_downsampling),
        nb::arg("data"),
        nb::arg("downsample_interval"),
        nb::arg("max_gap") = std::numeric_limits<double>::quiet_NaN());

    // Bind get_index_downsampling for pytensor<float, 1>
    m_helper.def(
        "get_index_downsampling",
        [](const xt::nanobind::pytensor<float, 1>& data,
           double                                  downsample_interval,
           double                                  max_gap) {
            // Adapt the pytensor to work with our template function
            xt::xtensor<float, 1> data_copy = data;
            return pingtools::helper::get_index_downsampling(
                data_copy, downsample_interval, max_gap);
        },
        DOC(themachinethatgoesping, tools, helper, get_index_downsampling),
        nb::arg("data"),
        nb::arg("downsample_interval"),
        nb::arg("max_gap") = std::numeric_limits<double>::quiet_NaN());

    // Bind get_value_downsampling for pytensor<double, 1>
    m_helper.def(
        "get_value_downsampling",
        [](const xt::nanobind::pytensor<double, 1>& data,
           double                                   downsample_interval,
           double                                   max_gap) {
            // Adapt the pytensor to work with our template function
            xt::xtensor<double, 1> data_copy = data;
            return pingtools::helper::get_value_downsampling(
                data_copy, downsample_interval, max_gap);
        },
        DOC(themachinethatgoesping, tools, helper, get_value_downsampling),
        nb::arg("data"),
        nb::arg("downsample_interval"),
        nb::arg("max_gap") = std::numeric_limits<double>::quiet_NaN());

    // Bind get_value_downsampling for pytensor<float, 1>
    m_helper.def(
        "get_value_downsampling",
        [](const xt::nanobind::pytensor<float, 1>& data,
           double                                  downsample_interval,
           double                                  max_gap) {
            // Adapt the pytensor to work with our template function
            xt::xtensor<float, 1> data_copy = data;
            return pingtools::helper::get_value_downsampling(
                data_copy, downsample_interval, max_gap);
        },
        DOC(themachinethatgoesping, tools, helper, get_value_downsampling),
        nb::arg("data"),
        nb::arg("downsample_interval"),
        nb::arg("max_gap")             = std::numeric_limits<double>::quiet_NaN());
}
