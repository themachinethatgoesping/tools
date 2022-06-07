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

class NearestInterpolator : public I_Interpolator<double>
{
  bool _average_halves = false;

public:
  NearestInterpolator(const std::vector<std::pair<double, double>>& XY,
                      bool sortX = false,
                      bool checkX = false,
                      bool average_halves = false)
    : I_Interpolator<double>(XY, sortX, checkX)
    , _average_halves(average_halves)
  {}
  NearestInterpolator(const std::vector<double>& X,
                      const std::vector<double>& Y,
                      bool sortX = false,
                      bool checkX = false,
                      bool average_halves = false)
    : I_Interpolator<double>(X, Y, sortX, checkX)
    , _average_halves(average_halves)
  {}
  ~NearestInterpolator() = default;

  void set_average_halves(bool average_halves = true) { _average_halves = average_halves; }
  bool get_average_halves() { return _average_halves; }

  /**
   * @brief Nearest: Nearest neighbor interpolation between two values
   * @param target: the x position of the target point
   * @param p1    : An array of size 2 containing the x and y position of the
   *first  point (x,y)
   * @param p2    : An array of size 2 containing the x and y position of the
   *second point (x,y)
   * @param average_halves: if true, the average_halves of both will be used when target is
   *0.5, if False v[1] is used
   * @return p1[1],p2[1] or average_halves of the 2
   **/
  static double nearest(double target,
                        double y1,
                        double y2,
                        bool average_halves = false)
  {
    if (target < 0.5)
      return y1;
    if (target > 0.5)
      return y2;

    if (average_halves)
      return (y1 + y2) / 2;
    else
      return y1;
  }

  double interpolate(double targetX,
                     const double& y1,
                     const double& y2) const final
  {
    return nearest(targetX, y1, y2, _average_halves);
  }

  double interpolate(double targetX) final
  {
    return I_Interpolator::interpolate(targetX);
  }
};

} // namespace interpolation
} // namespace tools
} // namespace themachinethatgoesping
