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

#include <themachinethatgoesping/tools_nanobind/pytensor_nanobind.hpp>

namespace nb          = nanobind;
namespace pingtools   = themachinethatgoesping::tools;

void init_m_downsampling(nb::module_& m)
{
    auto m_helper = m.def_submodule("helper");

    // Bind the DownsamplingResult structure
    nb::class_<pingtools::helper::DownsamplingResult>(
        m_helper,
        "DownsamplingResult",
        "Result structure for downsampling operations containing indices to keep")
        .def(nb::init<>())
        .def_rw("indices",
                &pingtools::helper::DownsamplingResult::indices,
                "Indices into the original timestamps that should be kept")
        .def("empty",
             &pingtools::helper::DownsamplingResult::empty,
             "Check if the result is empty")
        .def("size",
             &pingtools::helper::DownsamplingResult::size,
             "Get the number of selected indices")
        .def("__len__",
             &pingtools::helper::DownsamplingResult::size,
             "Get the number of selected indices")
        .def("__bool__",
             [](const pingtools::helper::DownsamplingResult& self) { return !self.empty(); },
             "Check if the result is non-empty");

    // Bind compute_downsampling_indices for pytensor<double, 1>
    m_helper.def(
        "compute_downsampling_indices",
        [](const xt::nanobind::pytensor<double, 1>& timestamps,
           double                                   downsample_interval_sec,
           double                                   max_gap_sec) {
            // Adapt the pytensor to work with our template function
            xt::xtensor<double, 1> ts_copy = timestamps;
            return pingtools::helper::compute_downsampling_indices(
                ts_copy, downsample_interval_sec, max_gap_sec);
        },
        DOC(themachinethatgoesping, tools, helper, compute_downsampling_indices),
        nb::arg("timestamps"),
        nb::arg("downsample_interval_sec") = 1.0,
        nb::arg("max_gap_sec")             = -1.0);

    // Bind compute_downsampling_indices for pytensor<float, 1>
    m_helper.def(
        "compute_downsampling_indices",
        [](const xt::nanobind::pytensor<float, 1>& timestamps,
           double                                  downsample_interval_sec,
           double                                  max_gap_sec) {
            // Adapt the pytensor to work with our template function
            xt::xtensor<float, 1> ts_copy = timestamps;
            return pingtools::helper::compute_downsampling_indices(
                ts_copy, downsample_interval_sec, max_gap_sec);
        },
        DOC(themachinethatgoesping, tools, helper, compute_downsampling_indices),
        nb::arg("timestamps"),
        nb::arg("downsample_interval_sec") = 1.0,
        nb::arg("max_gap_sec")             = -1.0);
}
