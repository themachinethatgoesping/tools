// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Drew Dormann (stackoverflow)
//
// SPDX-License-Identifier: CC-BY-SA-4.0

#pragma once

/**
 * @brief small helper functions, often copied from stackoverflow, therefore CC-BY-SA-4.0
 * see also: https://stackoverflow.com/help/licensing
 * see also: https://creativecommons.org/licenses/by-sa/4.0/
 *
 */

namespace themachinethatgoesping {
namespace tools {
namespace helpers {

/**
 * @brief compare to floats using a relative difference factor
 * src: Drew Dormann
 * https://stackoverflow.com/questions/67842444/modern-practice-to-compare-double-float-for-equality-in-modern-c
 *
 * @tparam t_float floating point type
 * @param f1 float/double 1
 * @param f2 float/double 1
 * @param relative_difference_factor relative factor by which the 2 numbers must be comparable
 * (default 0.01%)
 * @return true/false
 */
template<typename t_float>
bool approx(t_float f1,
            t_float f2,
            t_float relative_difference_factor = 0.0001 // 0.01%
)
{
    const auto greater_magnitude = std::max(std::abs(f1), std::abs(f2));

    return (std::abs(f1 - f2) < relative_difference_factor * greater_magnitude);
}

} // namespace helpers
} // namespace tools
} // namespace themachinethatgoesping