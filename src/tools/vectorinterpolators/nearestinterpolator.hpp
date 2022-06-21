// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean
// Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief Nearest neighbor vector interpolator class. 
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
 * @brief Interpolator class to find nearest neighbors within vector data
 * 
 */
class NearestInterpolator : public I_PairInterpolator<double>
{
public:
  NearestInterpolator()
    : I_PairInterpolator<double>({ 0, 1 }, { 0, 1 })
  {}

  /**
   * @brief Construct a new Nearest Interpolator object from a vector of pairs
   * usage: interpolated_y_value = interpolator.interpolate(x_value)
   * 
   * @param XY vector of x,y pairs. X must be unique and sorted in ascending order.
   * @param extrapolation_mode extrapolation mode (nearest or fail)
   */
  NearestInterpolator(const std::vector<std::pair<double, double>>& XY,
                      t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
    : I_PairInterpolator<double>(XY, extrapolation_mode)
  {}
  /**
   * @brief Construct a new Nearest Interpolator object from a vector of pairs
   * usage: interpolated_y_value = interpolator.interpolate(x_value)
   * 
   * @param X X vector; must be unique and sorted in ascending order. same size as Y!
   * @param Y Y vector; must be unique and sorted in ascending order. same size as X!
   * @param extrapolation_mode extrapolation mode (nearest or fail)
   */
  NearestInterpolator(const std::vector<double>& X,
                      const std::vector<double>& Y,
                      t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
    : I_PairInterpolator<double>(X, Y, extrapolation_mode)
  {}
  ~NearestInterpolator() = default;

  /**
   * @brief Nearest: Nearest neighbor interpolation between two values
   * @param target: the x position of the target point
   * @param p1    : An array of size 2 containing the x and y position of the
   *first  point (x,y)
   * @param p2    : An array of size 2 containing the x and y position of the
   *second point (x,y)
   * @return p1[1],p2[1]
   */
  double interpolate_pair(double target_x,
                     const double& y1,
                     const double& y2) const final
  {
    if (target_x < 0.5)
      return y1;
    
    return y2;
  }

};

} // namespace interpolation
} // namespace tools
} // namespace themachinethatgoesping
