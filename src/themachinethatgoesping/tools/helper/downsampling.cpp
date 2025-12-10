// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "downsampling.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace helper {

namespace {
// Helper to check if downsampling should be disabled
inline bool is_downsampling_disabled(double downsample_interval)
{
    return downsample_interval <= 0 || !std::isfinite(downsample_interval);
}

// Helper to get effective max_gap
inline double get_effective_max_gap(double max_gap, double downsample_interval)
{
    if (max_gap <= 0 || !std::isfinite(max_gap))
    {
        return is_downsampling_disabled(downsample_interval) ? 10.0 : 2.0 * downsample_interval;
    }
    return max_gap;
}

// Helper lambda to access element (works with both vector and xtensor)
template<typename T>
inline double get_value(const T& data, size_t i)
{
    if constexpr (requires { data.data(); })
    {
        return static_cast<double>(data.data()[i]);
    }
    else
    {
        return static_cast<double>(data[i]);
    }
}
} // anonymous namespace

template<typename T>
xt::xtensor<size_t, 1> get_index_downsampling(const T& data,
                                              double   downsample_interval,
                                              double   max_gap)
{
    const size_t n = data.size();
    if (n == 0)
    {
        return xt::xtensor<size_t, 1>::from_shape({ 0 });
    }

    max_gap = get_effective_max_gap(max_gap, downsample_interval);

    // If downsampling disabled, return all indices
    if (is_downsampling_disabled(downsample_interval))
    {
        xt::xtensor<size_t, 1> result = xt::xtensor<size_t, 1>::from_shape({ n });
        for (size_t i = 0; i < n; ++i)
        {
            result[i] = i;
        }
        return result;
    }

    // Estimate capacity and collect indices in a vector first
    double t_min = get_value(data, 0);
    double t_max = get_value(data, n - 1);
    size_t estimated_samples = static_cast<size_t>((t_max - t_min) / downsample_interval) + 1;
    
    std::vector<size_t> indices;
    indices.reserve(std::min(estimated_samples, n));

    // Start with the first value
    indices.push_back(0);
    double last_selected_value = t_min;

    for (size_t i = 1; i < n; ++i)
    {
        double current_value = get_value(data, i);
        double prev_value    = get_value(data, i - 1);

        // Check for gap between consecutive original values
        double gap = current_value - prev_value;
        if (gap > max_gap)
        {
            // Gap detected - restart sampling from this value
            indices.push_back(i);
            last_selected_value = current_value;
            continue;
        }

        // Check if enough distance since last selected value
        if (current_value - last_selected_value >= downsample_interval)
        {
            indices.push_back(i);
            last_selected_value = current_value;
        }
    }

    // Convert to xtensor
    xt::xtensor<size_t, 1> result = xt::xtensor<size_t, 1>::from_shape({ indices.size() });
    std::copy(indices.begin(), indices.end(), result.begin());
    return result;
}

template<typename T>
std::vector<double> get_value_downsampling(const T& data,
                                           double   downsample_interval,
                                           double   max_gap)
{
    const size_t n = data.size();
    if (n == 0)
    {
        return {};
    }

    max_gap = get_effective_max_gap(max_gap, downsample_interval);

    // If downsampling disabled, return copy of all values
    if (is_downsampling_disabled(downsample_interval))
    {
        std::vector<double> result;
        result.reserve(n);
        for (size_t i = 0; i < n; ++i)
        {
            result.push_back(get_value(data, i));
        }
        return result;
    }

    double t_min = get_value(data, 0);
    double t_max = get_value(data, n - 1);
    
    // Estimate capacity
    size_t estimated_samples = static_cast<size_t>((t_max - t_min) / downsample_interval) + 1;
    
    std::vector<double> result;
    result.reserve(estimated_samples);

    // Track position in original data for gap detection
    size_t data_idx = 0;
    double current_sample = t_min;
    
    // Start with the first value
    result.push_back(current_sample);
    current_sample += downsample_interval;

    while (current_sample <= t_max && data_idx < n - 1)
    {
        // Find the interval in original data that contains current_sample
        while (data_idx < n - 1 && get_value(data, data_idx + 1) < current_sample)
        {
            ++data_idx;
        }

        // Check for gap: if we're between two original values with a gap > max_gap
        if (data_idx < n - 1)
        {
            double gap = get_value(data, data_idx + 1) - get_value(data, data_idx);
            if (gap > max_gap)
            {
                // Gap detected - skip to first value after gap and restart
                ++data_idx;
                current_sample = get_value(data, data_idx);
                result.push_back(current_sample);
                current_sample += downsample_interval;
                continue;
            }
        }

        // No gap, add the sample point
        if (current_sample <= t_max)
        {
            result.push_back(current_sample);
        }
        current_sample += downsample_interval;
    }

    return result;
}

// Explicit instantiations for get_index_downsampling
template xt::xtensor<size_t, 1> get_index_downsampling(const std::vector<float>& data,
                                                       double downsample_interval,
                                                       double max_gap);

template xt::xtensor<size_t, 1> get_index_downsampling(const std::vector<double>& data,
                                                       double downsample_interval,
                                                       double max_gap);

template xt::xtensor<size_t, 1> get_index_downsampling(const xt::xtensor<float, 1>& data,
                                                       double downsample_interval,
                                                       double max_gap);

template xt::xtensor<size_t, 1> get_index_downsampling(const xt::xtensor<double, 1>& data,
                                                       double downsample_interval,
                                                       double max_gap);

// Explicit instantiations for get_value_downsampling
template std::vector<double> get_value_downsampling(const std::vector<float>& data,
                                                    double downsample_interval,
                                                    double max_gap);

template std::vector<double> get_value_downsampling(const std::vector<double>& data,
                                                    double downsample_interval,
                                                    double max_gap);

template std::vector<double> get_value_downsampling(const xt::xtensor<float, 1>& data,
                                                    double downsample_interval,
                                                    double max_gap);

template std::vector<double> get_value_downsampling(const xt::xtensor<double, 1>& data,
                                                    double downsample_interval,
                                                    double max_gap);

} // namespace helper
} // namespace tools
} // namespace themachinethatgoesping
