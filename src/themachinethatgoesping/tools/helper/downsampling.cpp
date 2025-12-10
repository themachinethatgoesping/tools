// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "downsampling.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace helper {

template<typename T>
DownsamplingResult compute_downsampling_indices(const T& timestamps,
                                                double   downsample_interval_sec,
                                                double   max_gap_sec)
{
    DownsamplingResult result;

    const size_t n = timestamps.size();
    if (n == 0)
    {
        return result;
    }

    // Set default max_gap if not specified
    if (max_gap_sec <= 0)
    {
        max_gap_sec = (downsample_interval_sec > 0) ? 2.0 * downsample_interval_sec : 10.0;
    }

    // Reserve estimated capacity
    if (downsample_interval_sec > 0 && n > 1)
    {
        // Use data() for xtensor compatibility, or direct access for vector
        double t_min, t_max;
        if constexpr (requires { timestamps.data(); })
        {
            t_min = timestamps.data()[0];
            t_max = timestamps.data()[n - 1];
        }
        else
        {
            t_min = timestamps[0];
            t_max = timestamps[n - 1];
        }
        size_t estimated_samples =
            static_cast<size_t>((t_max - t_min) / downsample_interval_sec) + 1;
        result.indices.reserve(std::min(estimated_samples, n));
    }
    else
    {
        result.indices.reserve(n);
    }

    // Helper lambda to access element (works with both vector and xtensor)
    auto get_value = [&timestamps](size_t i) -> double {
        if constexpr (requires { timestamps.data(); })
        {
            return static_cast<double>(timestamps.data()[i]);
        }
        else
        {
            return static_cast<double>(timestamps[i]);
        }
    };

    // If no downsampling, return all indices (but still check for gaps if needed)
    if (downsample_interval_sec <= 0)
    {
        for (size_t i = 0; i < n; ++i)
        {
            result.indices.push_back(i);
        }
        return result;
    }

    // Start with the first timestamp
    result.indices.push_back(0);
    double last_selected_time = get_value(0);

    for (size_t i = 1; i < n; ++i)
    {
        double current_time = get_value(i);
        double prev_time    = get_value(i - 1);

        // Check for gap between consecutive original timestamps
        double gap = current_time - prev_time;
        if (gap > max_gap_sec)
        {
            // Gap detected - restart sampling from this timestamp
            result.indices.push_back(i);
            last_selected_time = current_time;
            continue;
        }

        // Check if enough time has passed since last selected timestamp
        if (current_time - last_selected_time >= downsample_interval_sec)
        {
            result.indices.push_back(i);
            last_selected_time = current_time;
        }
    }

    return result;
}

// Explicit instantiations
template DownsamplingResult compute_downsampling_indices(const std::vector<float>& timestamps,
                                                          double downsample_interval_sec,
                                                          double max_gap_sec);

template DownsamplingResult compute_downsampling_indices(const std::vector<double>& timestamps,
                                                          double downsample_interval_sec,
                                                          double max_gap_sec);

template DownsamplingResult compute_downsampling_indices(const xt::xtensor<float, 1>& timestamps,
                                                          double downsample_interval_sec,
                                                          double max_gap_sec);

template DownsamplingResult compute_downsampling_indices(const xt::xtensor<double, 1>& timestamps,
                                                          double downsample_interval_sec,
                                                          double max_gap_sec);

} // namespace helper
} // namespace tools
} // namespace themachinethatgoesping
