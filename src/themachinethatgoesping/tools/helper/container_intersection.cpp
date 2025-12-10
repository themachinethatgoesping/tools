// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief Implementation of container intersection functions
 * @authors Peter Urban
 */

#include "container_intersection.hpp"

#include <algorithm>
#include <cmath>
#include <set>
#include <vector>

namespace themachinethatgoesping {
namespace tools {
namespace helper {

namespace {
/**
 * @brief Helper to check if max_gap is valid (positive and finite)
 */
inline bool is_valid_gap(double max_gap)
{
    return std::isfinite(max_gap) && max_gap > 0;
}

/**
 * @brief Helper to intersect two vectors of ranges
 */
template<typename T>
std::vector<Range<T>> intersect_ranges(const std::vector<Range<T>>& ranges1,
                                       const std::vector<Range<T>>& ranges2)
{
    std::vector<Range<T>> result;

    for (const auto& r1 : ranges1)
    {
        for (const auto& r2 : ranges2)
        {
            if (r1.overlaps(r2))
            {
                auto intersection = r1.intersection(r2);
                if (intersection.is_valid())
                {
                    result.push_back(intersection);
                }
            }
        }
    }

    return result;
}
} // anonymous namespace

template<typename T>
std::vector<Range<typename T::value_type>> get_sections(const T& data, double max_gap)
{
    using value_type = typename T::value_type;
    std::vector<Range<value_type>> sections;

    if (data.size() == 0)
    {
        return sections;
    }

    if (data.size() == 1)
    {
        sections.emplace_back(data[0], data[0]);
        return sections;
    }

    // If max_gap is not valid, treat entire container as one section
    if (!is_valid_gap(max_gap))
    {
        sections.emplace_back(static_cast<value_type>(data[0]),
                              static_cast<value_type>(data[data.size() - 1]));
        return sections;
    }

    // Find sections by detecting gaps
    value_type section_start = static_cast<value_type>(data[0]);
    value_type prev_value    = section_start;

    for (size_t i = 1; i < data.size(); ++i)
    {
        value_type current_value = static_cast<value_type>(data[i]);
        double     gap           = static_cast<double>(current_value - prev_value);

        if (gap > max_gap)
        {
            // End current section and start new one
            sections.emplace_back(section_start, prev_value);
            section_start = current_value;
        }

        prev_value = current_value;
    }

    // Add the last section
    sections.emplace_back(section_start, prev_value);

    return sections;
}

template<typename T>
std::vector<Range<typename T::value_type>> get_shared_sections(const std::vector<T>& containers,
                                                               double                max_gap)
{
    using value_type = typename T::value_type;

    if (containers.empty())
    {
        return {};
    }

    if (containers.size() == 1)
    {
        return get_sections(containers[0], max_gap);
    }

    // Get sections for each container
    std::vector<std::vector<Range<value_type>>> all_sections;
    all_sections.reserve(containers.size());

    for (const auto& container : containers)
    {
        all_sections.push_back(get_sections(container, max_gap));
    }

    // Intersect all sections progressively
    std::vector<Range<value_type>> result = all_sections[0];

    for (size_t i = 1; i < all_sections.size(); ++i)
    {
        result = intersect_ranges(result, all_sections[i]);

        // Early exit if no shared sections remain
        if (result.empty())
        {
            break;
        }
    }

    return result;
}

template<typename T>
std::vector<xt::xtensor<typename T::value_type, 1>> cut_to_shared_sections(
    const std::vector<T>& containers,
    double                max_gap)
{
    using value_type = typename T::value_type;

    std::vector<xt::xtensor<value_type, 1>> result;
    result.reserve(containers.size());

    if (containers.empty())
    {
        return result;
    }

    // Get the shared sections
    auto shared_sections = get_shared_sections(containers, max_gap);

    if (shared_sections.empty())
    {
        // Return empty containers
        for (size_t i = 0; i < containers.size(); ++i)
        {
            result.push_back(xt::xtensor<value_type, 1>::from_shape({ 0 }));
        }
        return result;
    }

    // For each container, extract values that fall within shared sections
    for (const auto& container : containers)
    {
        std::vector<value_type> values;
        values.reserve(container.size());

        for (size_t i = 0; i < container.size(); ++i)
        {
            value_type val = static_cast<value_type>(container[i]);

            // Check if this value falls within any shared section
            for (const auto& section : shared_sections)
            {
                if (section.contains(val))
                {
                    values.push_back(val);
                    break;
                }
            }
        }

        // Convert to xtensor
        xt::xtensor<value_type, 1> tensor = xt::empty<value_type>({ values.size() });
        for (size_t i = 0; i < values.size(); ++i)
        {
            tensor(i) = values[i];
        }
        result.push_back(std::move(tensor));
    }

    return result;
}

template<typename T>
std::vector<xt::xtensor<size_t, 1>> get_shared_section_indices(const std::vector<T>& containers,
                                                               double                max_gap)
{
    using value_type = typename T::value_type;

    std::vector<xt::xtensor<size_t, 1>> result;
    result.reserve(containers.size());

    if (containers.empty())
    {
        return result;
    }

    // Get the shared sections
    auto shared_sections = get_shared_sections(containers, max_gap);

    if (shared_sections.empty())
    {
        // Return empty index arrays
        for (size_t i = 0; i < containers.size(); ++i)
        {
            result.push_back(xt::xtensor<size_t, 1>::from_shape({ 0 }));
        }
        return result;
    }

    // For each container, find indices of values that fall within shared sections
    for (const auto& container : containers)
    {
        std::vector<size_t> indices;
        indices.reserve(container.size());

        for (size_t i = 0; i < container.size(); ++i)
        {
            value_type val = static_cast<value_type>(container[i]);

            // Check if this value falls within any shared section
            for (const auto& section : shared_sections)
            {
                if (section.contains(val))
                {
                    indices.push_back(i);
                    break;
                }
            }
        }

        // Convert to xtensor
        xt::xtensor<size_t, 1> tensor = xt::empty<size_t>({ indices.size() });
        for (size_t i = 0; i < indices.size(); ++i)
        {
            tensor(i) = indices[i];
        }
        result.push_back(std::move(tensor));
    }

    return result;
}

template<typename T>
xt::xtensor<typename T::value_type, 1> get_shared_section_values(const std::vector<T>& containers,
                                                                 double                max_gap)
{
    using value_type = typename T::value_type;

    if (containers.empty())
    {
        return xt::xtensor<value_type, 1>::from_shape({ 0 });
    }

    // Get the shared sections
    auto shared_sections = get_shared_sections(containers, max_gap);

    if (shared_sections.empty())
    {
        return xt::xtensor<value_type, 1>::from_shape({ 0 });
    }

    // Collect all unique values from all containers that fall within shared sections
    std::set<value_type> unique_values;

    for (const auto& container : containers)
    {
        for (size_t i = 0; i < container.size(); ++i)
        {
            value_type val = static_cast<value_type>(container[i]);

            // Check if this value falls within any shared section
            for (const auto& section : shared_sections)
            {
                if (section.contains(val))
                {
                    unique_values.insert(val);
                    break;
                }
            }
        }
    }

    // Convert to xtensor (std::set is already sorted)
    xt::xtensor<value_type, 1> result = xt::empty<value_type>({ unique_values.size() });
    size_t                     idx    = 0;
    for (const auto& val : unique_values)
    {
        result(idx++) = val;
    }

    return result;
}

// Explicit instantiations for get_sections
template std::vector<Range<float>> get_sections(const std::vector<float>& data, double max_gap);

template std::vector<Range<double>> get_sections(const std::vector<double>& data, double max_gap);

template std::vector<Range<float>> get_sections(const xt::xtensor<float, 1>& data, double max_gap);

template std::vector<Range<double>> get_sections(const xt::xtensor<double, 1>& data, double max_gap);

// Explicit instantiations for get_shared_sections
template std::vector<Range<float>> get_shared_sections(
    const std::vector<std::vector<float>>& containers,
    double                                 max_gap);

template std::vector<Range<double>> get_shared_sections(
    const std::vector<std::vector<double>>& containers,
    double                                  max_gap);

template std::vector<Range<float>> get_shared_sections(
    const std::vector<xt::xtensor<float, 1>>& containers,
    double                                    max_gap);

template std::vector<Range<double>> get_shared_sections(
    const std::vector<xt::xtensor<double, 1>>& containers,
    double                                     max_gap);

// Explicit instantiations for cut_to_shared_sections
template std::vector<xt::xtensor<float, 1>> cut_to_shared_sections(
    const std::vector<std::vector<float>>& containers,
    double                                 max_gap);

template std::vector<xt::xtensor<double, 1>> cut_to_shared_sections(
    const std::vector<std::vector<double>>& containers,
    double                                  max_gap);

template std::vector<xt::xtensor<float, 1>> cut_to_shared_sections(
    const std::vector<xt::xtensor<float, 1>>& containers,
    double                                    max_gap);

template std::vector<xt::xtensor<double, 1>> cut_to_shared_sections(
    const std::vector<xt::xtensor<double, 1>>& containers,
    double                                     max_gap);

// Explicit instantiations for get_shared_section_indices
template std::vector<xt::xtensor<size_t, 1>> get_shared_section_indices(
    const std::vector<std::vector<float>>& containers,
    double                                 max_gap);

template std::vector<xt::xtensor<size_t, 1>> get_shared_section_indices(
    const std::vector<std::vector<double>>& containers,
    double                                  max_gap);

template std::vector<xt::xtensor<size_t, 1>> get_shared_section_indices(
    const std::vector<xt::xtensor<float, 1>>& containers,
    double                                    max_gap);

template std::vector<xt::xtensor<size_t, 1>> get_shared_section_indices(
    const std::vector<xt::xtensor<double, 1>>& containers,
    double                                     max_gap);

// Explicit instantiations for get_shared_section_values
template xt::xtensor<float, 1> get_shared_section_values(
    const std::vector<std::vector<float>>& containers,
    double                                 max_gap);

template xt::xtensor<double, 1> get_shared_section_values(
    const std::vector<std::vector<double>>& containers,
    double                                  max_gap);

template xt::xtensor<float, 1> get_shared_section_values(
    const std::vector<xt::xtensor<float, 1>>& containers,
    double                                    max_gap);

template xt::xtensor<double, 1> get_shared_section_values(
    const std::vector<xt::xtensor<double, 1>>& containers,
    double                                     max_gap);

} // namespace helper
} // namespace tools
} // namespace themachinethatgoesping
