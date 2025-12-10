// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief Functions for time-based downsampling of timestamp containers
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
 * @brief Result structure for downsampling operations
 *
 * Contains the indices of timestamps that should be kept after downsampling,
 * respecting both the downsample interval and maximum gap constraints.
 */
struct DownsamplingResult
{
    std::vector<size_t> indices; ///< Indices into the original timestamps that should be kept

    /**
     * @brief Check if the result is empty
     * @return true if no indices were selected
     */
    bool empty() const { return indices.empty(); }

    /**
     * @brief Get the number of selected indices
     * @return Number of indices
     */
    size_t size() const { return indices.size(); }
};

/**
 * @brief Compute indices for downsampling a sorted timestamp container
 *
 * This function takes a container of sorted timestamps and returns indices of timestamps
 * that should be kept when downsampling at a specified interval. It also detects gaps
 * in the data and does not bridge them (i.e., does not return indices that would require
 * interpolating across a gap larger than max_gap_sec).
 *
 * The function selects the first timestamp, then selects subsequent timestamps that are
 * at least downsample_interval_sec apart from the last selected timestamp. When a gap
 * larger than max_gap_sec is encountered, the sampling restarts from the first timestamp
 * after the gap.
 *
 * @tparam T Container type (must support .size(), .begin(), .end() and contain floating point values)
 * @param timestamps Container of timestamps in seconds, must be sorted in ascending order
 * @param downsample_interval_sec Time interval between samples in seconds.
 *                                Use 0 or negative to disable downsampling (return all indices)
 * @param max_gap_sec Maximum allowed gap in the original data before considering it a data gap.
 *                    When a gap larger than this is encountered, sampling restarts after the gap.
 *                    If <= 0, defaults to 2x downsample_interval_sec (or 10 seconds if no downsampling)
 * @return DownsamplingResult containing indices of timestamps to keep
 *
 * @throws std::invalid_argument if timestamps container is empty
 *
 * @note The timestamps must be sorted in ascending order. Behavior is undefined for unsorted input.
 */
template<typename T>
DownsamplingResult compute_downsampling_indices(const T& timestamps,
                                                double   downsample_interval_sec,
                                                double   max_gap_sec);

// Explicit instantiation declarations for common types
extern template DownsamplingResult compute_downsampling_indices(const std::vector<float>& timestamps,
                                                                 double downsample_interval_sec,
                                                                 double max_gap_sec);

extern template DownsamplingResult compute_downsampling_indices(const std::vector<double>& timestamps,
                                                                 double downsample_interval_sec,
                                                                 double max_gap_sec);

extern template DownsamplingResult compute_downsampling_indices(const xt::xtensor<float, 1>& timestamps,
                                                                 double downsample_interval_sec,
                                                                 double max_gap_sec);

extern template DownsamplingResult compute_downsampling_indices(const xt::xtensor<double, 1>& timestamps,
                                                                 double downsample_interval_sec,
                                                                 double max_gap_sec);

} // namespace helper
} // namespace tools
} // namespace themachinethatgoesping
