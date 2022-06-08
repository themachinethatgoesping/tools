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

/**
 * @brief Interpolator class to find nearest neighbors in vector data
 * 
 */
class NearestInterpolator : public I_Interpolator<double>
{
public:
  /**
   * @brief Construct a new Nearest Interpolator object from a vector of pairs
   * usage: interpolated_y_value = interpolator.interpolate(x_value)
   * 
   * @param XY vector of x,y pairs. X must be unique and sorted (unless sortX is set).
   * @param sortX Setting this true will sort XY by X (deactiave for performance reasons)
   * @param checkX Check if the inputdata is valid (deactiave for performance reasons)
   * @param extrapolation_mode extrapolation mode (nearest or fail)
   */
  NearestInterpolator(const std::vector<std::pair<double, double>>& XY,
                      bool sortX = false,
                      bool checkX = true,
                      t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
    : I_Interpolator<double>(XY, sortX, checkX, extrapolation_mode)
  {}
  /**
   * @brief Construct a new Nearest Interpolator object from a vector of pairs
   * usage: interpolated_y_value = interpolator.interpolate(x_value)
   * 
   * @param X X vector; must be unique and sorted (unless sortX is set). same size as Y!
   * @param Y Y vector; must be unique and sorted (unless sortX is set). same size as X!
   * @param sortX Setting this true will sort XY by X (deactiave for performance reasons)
   * @param checkX Check if the inputdata is valid (deactiave for performance reasons)
   * @param extrapolation_mode extrapolation mode (nearest or fail)
   */
  NearestInterpolator(const std::vector<double>& X,
                      const std::vector<double>& Y,
                      bool sortX = false,
                      bool checkX = true,
                      t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
    : I_Interpolator<double>(X, Y, sortX, checkX, extrapolation_mode)
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
   **/
  static double nearest(double target,
                        double y1,
                        double y2)
  {
    if (target < 0.5)
      return y1;
    
    return y2;
  }

  double interpolate_pair(double targetX,
                     const double& y1,
                     const double& y2) const final
  {
    return nearest(targetX, y1, y2);
  }

};

} // namespace interpolation
} // namespace tools
} // namespace themachinethatgoesping
