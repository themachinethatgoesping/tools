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
namespace interpolation {

class LinearInterpolator : public I_Interpolator<double>
{

public:
  LinearInterpolator()
    : I_Interpolator<double>({ 0, 1 }, { 0, 1 }, false, false)
  {}

  LinearInterpolator(const std::vector<std::pair<double, double>>& XY,
                     bool sortX = false,
                     bool checkX = false)
    : I_Interpolator<double>(XY, sortX, checkX)
  {}
  LinearInterpolator(const std::vector<double>& X,
                     const std::vector<double>& Y,
                     bool sortX = false,
                     bool checkX = false)
    : I_Interpolator<double>(X, Y, sortX, checkX)
  {}

  /**
   * @brief Interpolate: Interpolate interpolation between two values
   * @param target: the target point [0.0 - 1.0]
   * @param v     : An array of size 2 containing 2 values (to interpolate
   * inbetween)
   * @return Interpolated value for target position
   */

  static inline double linear(double targetX, double y1, double y2)
  {
    return (double)(targetX * (y2) + (double(1.0) - targetX) * (y1));
  }


  double interpolate_pair(double targetX,
                     const double& y1,
                     const double& y2) const final
  {
    return linear(targetX, y1, y2);
  }

  double interpolate(double targetX)
  {
      return I_Interpolator::interpolate(targetX);
  }
  
  std::vector<double> interpolate(const std::vector<double>& targetsX) final
  {
    return I_Interpolator::interpolate(targetsX);
  }
};

} // namespace interpolation
} // namespace tools
} // namespace themachinethatgoesping
