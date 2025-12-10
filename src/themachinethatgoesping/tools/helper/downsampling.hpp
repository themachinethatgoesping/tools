// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief Functions for downsampling data containers
 * @authors Peter Urban
 */

#pragma once

/* generated doc strings */
#include ".docstrings/downsampling.doc.hpp"

#include <algorithm>
#include <cmath>
#include <concepts>
#include <stdexcept>
#include <vector>

#include <xtensor/containers/xadapt.hpp>
#include <xtensor/containers/xtensor.hpp>

namespace themachinethatgoesping {
namespace tools {
namespace helper {

/**
 * @brief Compute indices for downsampling a sorted data container
 *
 * This function takes a container of sorted values and returns indices of values
 * that should be kept when downsampling at a specified interval. It also detects gaps
 * in the data and does not bridge them (i.e., does not return indices that would require
 * interpolating across a gap larger than max_gap).
 *
 * The function selects the first value, then selects subsequent values that are
 * at least downsample_interval apart from the last selected value. When a gap
 * larger than max_gap is encountered, the sampling restarts from the first value
 * after the gap.
 *
 * @tparam T Container type (must support .size() and element access, contain floating point values)
 * @param data Container of values, must be sorted in ascending order
 * @param downsample_interval Interval between samples.
 *                            Use 0, negative, or NaN to disable downsampling (return all indices)
 * @param max_gap Maximum allowed gap in the original data before considering it a data gap.
 *                When a gap larger than this is encountered, sampling restarts after the gap.
 *                If <= 0 or NaN, defaults to 2x downsample_interval (or 10 if no downsampling)
 * @return xt::xtensor<size_t, 1> containing indices of values to keep
 *
 * @note The data must be sorted in ascending order. Behavior is undefined for unsorted input.
 */
template<typename T>
xt::xtensor<size_t, 1> get_index_downsampling(const T& data,
                                              double   downsample_interval,
                                              double   max_gap);

/**
 * @brief Downsample a sorted data container and return the downsampled values
 *
 * This function takes a container of sorted values and returns a new container with
 * values at exact intervals starting from the first value. It also detects gaps
 * in the data and restarts sampling after gaps.
 *
 * Unlike get_index_downsampling which returns indices into the original data,
 * this function generates exact sample points at regular intervals.
 *
 * @tparam T Container type (must support .size() and element access, contain floating point values)
 * @param data Container of values, must be sorted in ascending order
 * @param downsample_interval Interval between samples.
 *                            Use 0, negative, or NaN to disable downsampling (return copy of data)
 * @param max_gap Maximum allowed gap in the original data before considering it a data gap.
 *                When a gap larger than this is encountered, sampling restarts after the gap.
 *                If <= 0 or NaN, defaults to 2x downsample_interval (or 10 if no downsampling)
 * @return std::vector<double> containing the downsampled values at exact intervals
 *
 * @note The data must be sorted in ascending order. Behavior is undefined for unsorted input.
 */
template<typename T>
std::vector<double> get_value_downsampling(const T& data,
                                           double   downsample_interval,
                                           double   max_gap);

// Explicit instantiation declarations for common types
extern template xt::xtensor<size_t, 1> get_index_downsampling(const std::vector<float>& data,
                                                              double downsample_interval,
                                                              double max_gap);

extern template xt::xtensor<size_t, 1> get_index_downsampling(const std::vector<double>& data,
                                                              double downsample_interval,
                                                              double max_gap);

extern template xt::xtensor<size_t, 1> get_index_downsampling(const xt::xtensor<float, 1>& data,
                                                              double downsample_interval,
                                                              double max_gap);

extern template xt::xtensor<size_t, 1> get_index_downsampling(const xt::xtensor<double, 1>& data,
                                                              double downsample_interval,
                                                              double max_gap);

extern template std::vector<double> get_value_downsampling(const std::vector<float>& data,
                                                           double downsample_interval,
                                                           double max_gap);

extern template std::vector<double> get_value_downsampling(const std::vector<double>& data,
                                                           double downsample_interval,
                                                           double max_gap);

extern template std::vector<double> get_value_downsampling(const xt::xtensor<float, 1>& data,
                                                           double downsample_interval,
                                                           double max_gap);

extern template std::vector<double> get_value_downsampling(const xt::xtensor<double, 1>& data,
                                                           double downsample_interval,
                                                           double max_gap);

} // namespace helper
} // namespace tools
} // namespace themachinethatgoesping
