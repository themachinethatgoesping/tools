// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean
// Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "i_interpolator.h"

namespace themachinethatgoesping {
namespace tools {
namespace vectorinterpolators {

/**
 * @brief Interpolator class to find linear interpolated values within vector data
 * 
 */
class LinearInterpolator : public I_Interpolator<double>
{

public:
  LinearInterpolator()
    : I_Interpolator<double>({ 0, 1 }, { 0, 1 })
  {}

  LinearInterpolator(const std::vector<std::pair<double, double>>& XY,
                     bool sortX = false,
                     bool checkX = true,
                     t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
    : I_Interpolator<double>(XY, sortX, checkX, extrapolation_mode)
  {}
  LinearInterpolator(const std::vector<double>& X,
                     const std::vector<double>& Y,
                     bool sortX = false,
                     bool checkX = true,
                     t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
    : I_Interpolator<double>(X, Y, sortX, checkX, extrapolation_mode)
  {}

  /**
   * @brief Interpolate: Interpolate interpolation between two values
   * @param target: the target point [0.0 - 1.0]
   * @param v     : An array of size 2 containing 2 values (to interpolate
   * inbetween)
   * @return Interpolated value for target position
   */
  double interpolate_pair(double target_x,
                          const double& y1,
                          const double& y2) const final
  {
    return (double)(target_x * (y2) + (double(1.0) - target_x) * (y1));
  }
};

} // namespace interpolation
} // namespace tools
} // namespace themachinethatgoesping
