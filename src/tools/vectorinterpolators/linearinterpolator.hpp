// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean
// Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief Linear vector interpolator class.
 *
 * @authors Peter Urban
 *
 */

#pragma once

#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "i_pairinterpolator.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace vectorinterpolators {

/**
 * @brief Find linear interpolated values within vector data
 *
 */
class LinearInterpolator : public I_PairInterpolator<double>
{

  public:
    // LinearInterpolator()
    //     : I_PairInterpolator<double>({ 0, 1 }, { 0, 1 })
    // {
    // }

    LinearInterpolator(const std::vector<double>& X,
                       const std::vector<double>& Y,
                       t_extr_mode                extrapolation_mode = t_extr_mode::extrapolate)
        : I_PairInterpolator<double>(X, Y, extrapolation_mode)
    {
    }

    /**
     * @brief Interpolate: Interpolate interpolation between two values
     * @param target_x: the target point [0.0 - 1.0]
     * @param y1     : first y value (target_x = 0)
     * @param y2     : second value (target_x = 01)
     * inbetween)
     * @return Interpolated value for target position
     */
    double interpolate_pair(double target_x, double y1, double y2) const final
    {
        return (double)(target_x * (y2) + (double(1.0) - target_x) * (y1));
    }
};

} // namespace interpolation
} // namespace tools
} // namespace themachinethatgoesping
