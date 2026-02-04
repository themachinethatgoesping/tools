// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "m_container_intersection.hpp"

// -- c++ library headers
#include <themachinethatgoesping/tools/helper/container_intersection.hpp>

// -- include nanobind headers
#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

#include <xtensor-python/nanobind/pytensor.hpp>

namespace nb        = nanobind;
namespace pingtools = themachinethatgoesping::tools;

void init_m_container_intersection(nb::module_& m)
{
    auto m_helper = m.def_submodule("helper");

    // Bind Range<double>
    nb::class_<pingtools::helper::Range<double>>(
        m_helper,
        "RangeDouble",
        R"doc(A continuous range with min and max values.

Represents a range [min, max] that can be used to check containment
and compute intersections with other ranges.

Attributes
----------
min : float
    Minimum value of the range (inclusive)
max : float
    Maximum value of the range (inclusive)
)doc")
        .def(nb::init<double, double>(),
             nb::arg("min_val"),
             nb::arg("max_val"),
             "Create a range with given min and max values")
        .def_rw("min", &pingtools::helper::Range<double>::min, "Minimum value of the range")
        .def_rw("max", &pingtools::helper::Range<double>::max, "Maximum value of the range")
        .def("contains",
             &pingtools::helper::Range<double>::contains,
             nb::arg("value"),
             "Check if a value is within this range")
        .def("overlaps",
             &pingtools::helper::Range<double>::overlaps,
             nb::arg("other"),
             "Check if this range overlaps with another")
        .def("intersection",
             &pingtools::helper::Range<double>::intersection,
             nb::arg("other"),
             "Get the intersection of this range with another")
        .def("is_valid",
             &pingtools::helper::Range<double>::is_valid,
             "Check if range is valid (min <= max)")
        .def("__repr__", [](const pingtools::helper::Range<double>& self) {
            return "RangeDouble(" + std::to_string(self.min) + ", " + std::to_string(self.max) +
                   ")";
        });

    // Bind Range<float>
    nb::class_<pingtools::helper::Range<float>>(
        m_helper,
        "RangeFloat",
        R"doc(A continuous range with min and max values (float32).

Represents a range [min, max] that can be used to check containment
and compute intersections with other ranges.

Attributes
----------
min : float
    Minimum value of the range (inclusive)
max : float
    Maximum value of the range (inclusive)
)doc")
        .def(nb::init<float, float>(),
             nb::arg("min_val"),
             nb::arg("max_val"),
             "Create a range with given min and max values")
        .def_rw("min", &pingtools::helper::Range<float>::min, "Minimum value of the range")
        .def_rw("max", &pingtools::helper::Range<float>::max, "Maximum value of the range")
        .def("contains",
             &pingtools::helper::Range<float>::contains,
             nb::arg("value"),
             "Check if a value is within this range")
        .def("overlaps",
             &pingtools::helper::Range<float>::overlaps,
             nb::arg("other"),
             "Check if this range overlaps with another")
        .def("intersection",
             &pingtools::helper::Range<float>::intersection,
             nb::arg("other"),
             "Get the intersection of this range with another")
        .def("is_valid",
             &pingtools::helper::Range<float>::is_valid,
             "Check if range is valid (min <= max)")
        .def("__repr__", [](const pingtools::helper::Range<float>& self) {
            return "RangeFloat(" + std::to_string(self.min) + ", " + std::to_string(self.max) + ")";
        });

    // Bind get_sections for pytensor<double, 1>
    m_helper.def(
        "get_sections",
        [](const xt::nanobind::pytensor<double, 1>& data, double max_gap) {
            xt::xtensor<double, 1> data_copy = data;
            return pingtools::helper::get_sections(data_copy, max_gap);
        },
        R"doc(Extract continuous sections from a sorted container based on max_gap.

A section is a range [min, max] where consecutive elements have gaps <= max_gap.

Parameters
----------
data : numpy.ndarray
    Sorted 1D array of values
max_gap : float
    Maximum allowed gap between consecutive elements within a section.
    If <= 0 or non-finite, entire container is treated as one section.

Returns
-------
list
    List of Range objects representing continuous sections
)doc",
        nb::arg("data"),
        nb::arg("max_gap") = std::numeric_limits<double>::quiet_NaN());

    // Bind get_sections for pytensor<float, 1>
    m_helper.def(
        "get_sections",
        [](const xt::nanobind::pytensor<float, 1>& data, double max_gap) {
            xt::xtensor<float, 1> data_copy = data;
            return pingtools::helper::get_sections(data_copy, max_gap);
        },
        R"doc(Extract continuous sections from a sorted container based on max_gap.

A section is a range [min, max] where consecutive elements have gaps <= max_gap.

Parameters
----------
data : numpy.ndarray
    Sorted 1D array of values (float32)
max_gap : float
    Maximum allowed gap between consecutive elements within a section.

Returns
-------
list
    List of Range objects representing continuous sections
)doc",
        nb::arg("data"),
        nb::arg("max_gap") = std::numeric_limits<double>::quiet_NaN());

    // Bind get_shared_sections for list of pytensor<double, 1>
    m_helper.def(
        "get_shared_sections",
        [](const std::vector<xt::nanobind::pytensor<double, 1>>& containers, double max_gap) {
            std::vector<xt::xtensor<double, 1>> containers_copy;
            containers_copy.reserve(containers.size());
            for (const auto& c : containers)
            {
                containers_copy.push_back(c);
            }
            return pingtools::helper::get_shared_sections(containers_copy, max_gap);
        },
        R"doc(Find shared sections across multiple sorted containers.

Each container is split into sections based on max_gap, then intersections
across all containers are computed.

Parameters
----------
containers : list of numpy.ndarray
    List of sorted 1D arrays
max_gap : float
    Maximum allowed gap between consecutive elements within a section.

Returns
-------
list
    List of Range objects representing shared sections
)doc",
        nb::arg("containers"),
        nb::arg("max_gap") = std::numeric_limits<double>::quiet_NaN());

    // Bind get_shared_sections for list of pytensor<float, 1>
    m_helper.def(
        "get_shared_sections",
        [](const std::vector<xt::nanobind::pytensor<float, 1>>& containers, double max_gap) {
            std::vector<xt::xtensor<float, 1>> containers_copy;
            containers_copy.reserve(containers.size());
            for (const auto& c : containers)
            {
                containers_copy.push_back(c);
            }
            return pingtools::helper::get_shared_sections(containers_copy, max_gap);
        },
        R"doc(Find shared sections across multiple sorted containers.

Parameters
----------
containers : list of numpy.ndarray
    List of sorted 1D arrays (float32)
max_gap : float
    Maximum allowed gap between consecutive elements within a section.

Returns
-------
list
    List of Range objects representing shared sections
)doc",
        nb::arg("containers"),
        nb::arg("max_gap") = std::numeric_limits<double>::quiet_NaN());

    // Bind cut_to_shared_sections for list of pytensor<double, 1>
    m_helper.def(
        "cut_to_shared_sections",
        [](const std::vector<xt::nanobind::pytensor<double, 1>>& containers, double max_gap) {
            std::vector<xt::xtensor<double, 1>> containers_copy;
            containers_copy.reserve(containers.size());
            for (const auto& c : containers)
            {
                containers_copy.push_back(c);
            }
            return pingtools::helper::cut_to_shared_sections(containers_copy, max_gap);
        },
        R"doc(Cut multiple containers to only include values within shared sections.

Each container is filtered to keep only values that fall within the
intersection of all containers' sections.

Parameters
----------
containers : list of numpy.ndarray
    List of sorted 1D arrays
max_gap : float
    Maximum allowed gap between consecutive elements within a section.

Returns
-------
list of numpy.ndarray
    Filtered containers containing only values within shared sections
)doc",
        nb::arg("containers"),
        nb::arg("max_gap") = std::numeric_limits<double>::quiet_NaN());

    // Bind cut_to_shared_sections for list of pytensor<float, 1>
    m_helper.def(
        "cut_to_shared_sections",
        [](const std::vector<xt::nanobind::pytensor<float, 1>>& containers, double max_gap) {
            std::vector<xt::xtensor<float, 1>> containers_copy;
            containers_copy.reserve(containers.size());
            for (const auto& c : containers)
            {
                containers_copy.push_back(c);
            }
            return pingtools::helper::cut_to_shared_sections(containers_copy, max_gap);
        },
        R"doc(Cut multiple containers to only include values within shared sections.

Parameters
----------
containers : list of numpy.ndarray
    List of sorted 1D arrays (float32)
max_gap : float
    Maximum allowed gap between consecutive elements within a section.

Returns
-------
list of numpy.ndarray
    Filtered containers containing only values within shared sections
)doc",
        nb::arg("containers"),
        nb::arg("max_gap") = std::numeric_limits<double>::quiet_NaN());

    // Bind get_shared_section_indices for list of pytensor<double, 1>
    m_helper.def(
        "get_shared_section_indices",
        [](const std::vector<xt::nanobind::pytensor<double, 1>>& containers, double max_gap) {
            std::vector<xt::xtensor<double, 1>> containers_copy;
            containers_copy.reserve(containers.size());
            for (const auto& c : containers)
            {
                containers_copy.push_back(c);
            }
            return pingtools::helper::get_shared_section_indices(containers_copy, max_gap);
        },
        R"doc(Get indices of elements within shared sections for each container.

Parameters
----------
containers : list of numpy.ndarray
    List of sorted 1D arrays
max_gap : float
    Maximum allowed gap between consecutive elements within a section.

Returns
-------
list of numpy.ndarray
    For each container, indices of elements within shared sections
)doc",
        nb::arg("containers"),
        nb::arg("max_gap") = std::numeric_limits<double>::quiet_NaN());

    // Bind get_shared_section_indices for list of pytensor<float, 1>
    m_helper.def(
        "get_shared_section_indices",
        [](const std::vector<xt::nanobind::pytensor<float, 1>>& containers, double max_gap) {
            std::vector<xt::xtensor<float, 1>> containers_copy;
            containers_copy.reserve(containers.size());
            for (const auto& c : containers)
            {
                containers_copy.push_back(c);
            }
            return pingtools::helper::get_shared_section_indices(containers_copy, max_gap);
        },
        R"doc(Get indices of elements within shared sections for each container.

Parameters
----------
containers : list of numpy.ndarray
    List of sorted 1D arrays (float32)
max_gap : float
    Maximum allowed gap between consecutive elements within a section.

Returns
-------
list of numpy.ndarray
    For each container, indices of elements within shared sections
)doc",
        nb::arg("containers"),
        nb::arg("max_gap") = std::numeric_limits<double>::quiet_NaN());

    // Bind get_shared_section_values for list of pytensor<double, 1>
    m_helper.def(
        "get_shared_section_values",
        [](const std::vector<xt::nanobind::pytensor<double, 1>>& containers, double max_gap) {
            std::vector<xt::xtensor<double, 1>> containers_copy;
            containers_copy.reserve(containers.size());
            for (const auto& c : containers)
            {
                containers_copy.push_back(c);
            }
            return pingtools::helper::get_shared_section_values(containers_copy, max_gap);
        },
        R"doc(Get unique values from all containers within shared sections.

This function collects all unique values from all containers that fall
within the shared sections, returning them as a sorted array.

Parameters
----------
containers : list of numpy.ndarray
    List of sorted 1D arrays
max_gap : float
    Maximum allowed gap between consecutive elements within a section.

Returns
-------
numpy.ndarray
    Sorted array of unique values within shared sections
)doc",
        nb::arg("containers"),
        nb::arg("max_gap") = std::numeric_limits<double>::quiet_NaN());

    // Bind get_shared_section_values for list of pytensor<float, 1>
    m_helper.def(
        "get_shared_section_values",
        [](const std::vector<xt::nanobind::pytensor<float, 1>>& containers, double max_gap) {
            std::vector<xt::xtensor<float, 1>> containers_copy;
            containers_copy.reserve(containers.size());
            for (const auto& c : containers)
            {
                containers_copy.push_back(c);
            }
            return pingtools::helper::get_shared_section_values(containers_copy, max_gap);
        },
        R"doc(Get unique values from all containers within shared sections.

Parameters
----------
containers : list of numpy.ndarray
    List of sorted 1D arrays (float32)
max_gap : float
    Maximum allowed gap between consecutive elements within a section.

Returns
-------
numpy.ndarray
    Sorted array of unique values within shared sections
)doc",
        nb::arg("containers"),
        nb::arg("max_gap") = std::numeric_limits<double>::quiet_NaN());
}
