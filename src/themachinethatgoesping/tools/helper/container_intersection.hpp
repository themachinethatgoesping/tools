// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief Functions for finding intersections/shared ranges between multiple sorted containers
 * @authors Peter Urban
 */

#pragma once

/* generated doc strings */
#include ".docstrings/container_intersection.doc.hpp"

#include <algorithm>
#include <cmath>
#include <concepts>
#include <limits>
#include <stdexcept>
#include <tuple>
#include <vector>

#include <xtensor/containers/xtensor.hpp>

namespace themachinethatgoesping {
namespace tools {
namespace helper {

/**
 * @brief Structure representing a continuous range/section
 */
template<typename T>
struct Range
{
    T min; ///< Minimum value of the range (inclusive)
    T max; ///< Maximum value of the range (inclusive)

    Range(T min_val, T max_val)
        : min(min_val)
        , max(max_val)
    {
    }

    /**
     * @brief Check if a value is within this range
     */
    bool contains(T value) const { return value >= min && value <= max; }

    /**
     * @brief Check if this range overlaps with another
     */
    bool overlaps(const Range& other) const { return min <= other.max && max >= other.min; }

    /**
     * @brief Get the intersection of this range with another
     * @return The overlapping range, or an empty range if no overlap
     */
    Range intersection(const Range& other) const
    {
        return Range(std::max(min, other.min), std::min(max, other.max));
    }

    /**
     * @brief Check if range is valid (min <= max)
     */
    bool is_valid() const { return min <= max; }
};

/**
 * @brief Extract continuous sections from a sorted container, splitting at gaps
 *
 * This function analyzes a sorted container and identifies continuous sections
 * where consecutive values are no more than max_gap apart.
 *
 * @tparam T Container type (must support .size() and element access, contain floating point values)
 * @param data Container of values, must be sorted in ascending order
 * @param max_gap Maximum allowed gap between consecutive values before starting a new section.
 *                If <= 0 or NaN, treats the entire container as one section.
 * @return std::vector<Range<value_type>> Vector of ranges representing continuous sections
 *
 * @note The data must be sorted in ascending order. Behavior is undefined for unsorted input.
 */
template<typename T>
std::vector<Range<typename T::value_type>> get_sections(
    const T& data,
    double   max_gap = std::numeric_limits<double>::quiet_NaN());

/**
 * @brief Find the intersection of sections from multiple containers
 *
 * This function takes multiple sorted containers and finds the ranges where
 * all containers have data. It respects gaps in each container - if any container
 * has a gap larger than max_gap, the intersection is split at that point.
 *
 * @tparam T Container type (must support .size() and element access, contain floating point values)
 * @param containers Vector of containers, each must be sorted in ascending order
 * @param max_gap Maximum allowed gap between consecutive values in any container.
 *                If <= 0 or NaN, defaults to checking only container boundaries.
 * @return std::vector<Range<value_type>> Vector of ranges where all containers have overlapping data
 *
 * @note All containers must be sorted in ascending order. Behavior is undefined for unsorted input.
 */
template<typename T>
std::vector<Range<typename T::value_type>> get_shared_sections(
    const std::vector<T>& containers,
    double                max_gap = std::numeric_limits<double>::quiet_NaN());

/**
 * @brief Cut containers to their shared/intersecting ranges
 *
 * This function takes multiple sorted containers and returns new containers
 * containing only the values that fall within ranges shared by all input containers.
 * Gaps in any container (values more than max_gap apart) cause the shared range
 * to be split.
 *
 * @tparam T Container type (must support .size() and element access, contain floating point values)
 * @param containers Vector of containers, each must be sorted in ascending order
 * @param max_gap Maximum allowed gap between consecutive values in any container.
 *                If <= 0 or NaN, defaults to only considering container boundaries.
 * @return std::vector<xt::xtensor<value_type, 1>> Vector of containers cut to shared ranges
 *
 * @note All containers must be sorted in ascending order. Behavior is undefined for unsorted input.
 * @note The returned containers maintain the original order but only include values
 *       that fall within the shared ranges.
 */
template<typename T>
std::vector<xt::xtensor<typename T::value_type, 1>> cut_to_shared_sections(
    const std::vector<T>& containers,
    double                max_gap = std::numeric_limits<double>::quiet_NaN());

/**
 * @brief Get indices of values that fall within the shared sections
 *
 * This function takes multiple sorted containers and returns indices into each
 * container for values that fall within ranges shared by all input containers.
 *
 * @tparam T Container type (must support .size() and element access, contain floating point values)
 * @param containers Vector of containers, each must be sorted in ascending order
 * @param max_gap Maximum allowed gap between consecutive values in any container.
 *                If <= 0 or NaN, defaults to only considering container boundaries.
 * @return std::vector<xt::xtensor<size_t, 1>> Vector of index arrays, one per input container
 *
 * @note All containers must be sorted in ascending order. Behavior is undefined for unsorted input.
 */
template<typename T>
std::vector<xt::xtensor<size_t, 1>> get_shared_section_indices(
    const std::vector<T>& containers,
    double                max_gap = std::numeric_limits<double>::quiet_NaN());

/**
 * @brief Get values that fall within the shared sections (flattened)
 *
 * This function takes multiple sorted containers and returns a single container
 * containing all unique values from any container that fall within shared sections.
 * This is useful when you need a common set of values for interpolation or alignment.
 *
 * @tparam T Container type (must support .size() and element access, contain floating point values)
 * @param containers Vector of containers, each must be sorted in ascending order
 * @param max_gap Maximum allowed gap between consecutive values in any container.
 *                If <= 0 or NaN, defaults to only considering container boundaries.
 * @return xt::xtensor<value_type, 1> Sorted unique values from all containers within shared sections
 *
 * @note All containers must be sorted in ascending order. Behavior is undefined for unsorted input.
 */
template<typename T>
xt::xtensor<typename T::value_type, 1> get_shared_section_values(
    const std::vector<T>& containers,
    double                max_gap = std::numeric_limits<double>::quiet_NaN());

// Explicit instantiation declarations for common types
extern template std::vector<Range<float>> get_sections(
    const std::vector<float>& data,
    double                    max_gap);

extern template std::vector<Range<double>> get_sections(
    const std::vector<double>& data,
    double                     max_gap);

extern template std::vector<Range<float>> get_sections(
    const xt::xtensor<float, 1>& data,
    double                       max_gap);

extern template std::vector<Range<double>> get_sections(
    const xt::xtensor<double, 1>& data,
    double                        max_gap);

extern template std::vector<Range<float>> get_shared_sections(
    const std::vector<std::vector<float>>& containers,
    double                                 max_gap);

extern template std::vector<Range<double>> get_shared_sections(
    const std::vector<std::vector<double>>& containers,
    double                                  max_gap);

extern template std::vector<Range<float>> get_shared_sections(
    const std::vector<xt::xtensor<float, 1>>& containers,
    double                                    max_gap);

extern template std::vector<Range<double>> get_shared_sections(
    const std::vector<xt::xtensor<double, 1>>& containers,
    double                                     max_gap);

extern template std::vector<xt::xtensor<float, 1>> cut_to_shared_sections(
    const std::vector<std::vector<float>>& containers,
    double                                 max_gap);

extern template std::vector<xt::xtensor<double, 1>> cut_to_shared_sections(
    const std::vector<std::vector<double>>& containers,
    double                                  max_gap);

extern template std::vector<xt::xtensor<float, 1>> cut_to_shared_sections(
    const std::vector<xt::xtensor<float, 1>>& containers,
    double                                    max_gap);

extern template std::vector<xt::xtensor<double, 1>> cut_to_shared_sections(
    const std::vector<xt::xtensor<double, 1>>& containers,
    double                                     max_gap);

extern template std::vector<xt::xtensor<size_t, 1>> get_shared_section_indices(
    const std::vector<std::vector<float>>& containers,
    double                                 max_gap);

extern template std::vector<xt::xtensor<size_t, 1>> get_shared_section_indices(
    const std::vector<std::vector<double>>& containers,
    double                                  max_gap);

extern template std::vector<xt::xtensor<size_t, 1>> get_shared_section_indices(
    const std::vector<xt::xtensor<float, 1>>& containers,
    double                                    max_gap);

extern template std::vector<xt::xtensor<size_t, 1>> get_shared_section_indices(
    const std::vector<xt::xtensor<double, 1>>& containers,
    double                                     max_gap);

extern template xt::xtensor<float, 1> get_shared_section_values(
    const std::vector<std::vector<float>>& containers,
    double                                 max_gap);

extern template xt::xtensor<double, 1> get_shared_section_values(
    const std::vector<std::vector<double>>& containers,
    double                                  max_gap);

extern template xt::xtensor<float, 1> get_shared_section_values(
    const std::vector<xt::xtensor<float, 1>>& containers,
    double                                    max_gap);

extern template xt::xtensor<double, 1> get_shared_section_values(
    const std::vector<xt::xtensor<double, 1>>& containers,
    double                                     max_gap);

} // namespace helper
} // namespace tools
} // namespace themachinethatgoesping
