// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Drew Dormann (stackoverflow)
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <cmath>
#include <string>

namespace themachinethatgoesping {
namespace tools {
namespace helper {

/**
 * @brief compare to floats using a relative difference factor
 *
 * @tparam t_float floating point type
 * @param f1 float/double 1
 * @param f2 float/double 1
 * @param relative_difference_factor relative factor by which the 2 numbers must be comparable
 * (default 0.01%)
 * @return true/false
 */
template<typename t_float>
bool approx(t_float f1, t_float f2, t_float relative_difference_factor = 0.0001 // 0.01%
)
{
    // if both are NAN return true
    if (std ::isnan(f1))
        if (std::isnan(f2))
            return true;

    // if both are inf (and same sign) return true
    if (std::isinf(f1))
        if (std::isinf(f2))
        {
            if (f1 < 0)
            {
                if (f2 < 0)
                    return true;
            }
            else
            {
                if (f2 > 0)
                    return true;
            }
        }

    // if the difference between both is smaller than the relative difference factor (compared to
    // the larger float) return true
    return std::abs(f1 - f2) <= relative_difference_factor * std::max(std::abs(f1), std::abs(f2));
}

template<typename int_type>
inline std::string int_as_string(int_type value)
{
    std::string valueAsString;
    valueAsString.resize(sizeof(value));
    memcpy(valueAsString.data(), &value, sizeof(value));

    return valueAsString;
}

template<typename int_type>
inline int_type string_as_int(std::string_view value)
{
    int_type valueAsFourByteInt;
    memcpy(&valueAsFourByteInt, value.data(), sizeof(valueAsFourByteInt));
    return valueAsFourByteInt;
}

} // namespace helpers
} // namespace tools
} // namespace themachinethatgoesping
