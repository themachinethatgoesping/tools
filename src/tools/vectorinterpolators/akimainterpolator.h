// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean
// Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <array>
#include <boost/math/interpolators/makima.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "i_interpolator.h"

namespace themachinethatgoesping {
namespace tools {
namespace vectorinterpolators {

/**
 * @brief Interpolator class to find nearest neighbors within vector data
 *
 */
class AkimaInterpolator : public I_Interpolator<double>
{
private:
  std::unique_ptr<boost::math::interpolators::makima<std::vector<double>>> _akima_spline;

public:
  AkimaInterpolator()
    : I_Interpolator<double>()
  {
    set_data_XY({ 0, 1 }, { 0, 1 });
  }

  /**
   * @brief Construct a new Akima Spline Interpolator object from a vector of
   * pairs This class uses the modified akima interpolation of boost c++
   * https://www.boost.org/doc/libs/1_79_0/libs/math/doc/html/math_toolkit/makima.html
   * usage: interpolated_y_value = interpolator.interpolate(x_value)
   *
   * @param XY vector of x,y pairs. X must be unique and sorted in ascending order
   * @param extrapolation_mode extrapolation mode (nearest or fail)
   */
  AkimaInterpolator(const std::vector<std::pair<double, double>>& XY,
                    t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
    : I_Interpolator<double>(extrapolation_mode)
  {
    set_data_XY(XY);
  }
  /**
   * @brief Construct a new Akima Spline Interpolator object from a vector of
   * pairs This class uses the modified akima interpolation of boost c++
   * https://www.boost.org/doc/libs/1_79_0/libs/math/doc/html/math_toolkit/makima.html
   * usage: interpolated_y_value = interpolator.interpolate(x_value)
   *
   * @param X X vector; must be unique and sorted in ascending order. same
   * size as Y!
   * @param Y Y vector; must be unique and sorted in ascending order. same
   * size as X!
   * @param extrapolation_mode extrapolation mode (nearest or fail)
   */
  AkimaInterpolator(const std::vector<double>& X,
                    const std::vector<double>& Y,
                    t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
    : I_Interpolator<double>(extrapolation_mode)
  {
    set_data_XY(X,Y);
  }
  ~AkimaInterpolator() = default;

  /**
   * @brief get the interolated y value for given x target
   *
   * @param target_x find the corresponding y value for this x value
   * @return corresponding y value
   */
  double interpolate(double target_x) final
  {
    return _akima_spline->operator()(target_x);
  }


  /**
   * @brief change the input data to these X and Y vectors
   *
   * @param X: x vector (must be same size)
   * @param Y: y vector (must be same size)
   */
  void set_data_XY(const std::vector<double>& X,
                   const std::vector<double>& Y) final
  {
    // check if vectors are same size
    if (X.size() != Y.size())
      throw(std::runtime_error(
        "ERROR[Interpolation::set_data_XY]: list sizes do not match"));

    auto x = X;
    auto y = Y;

    _akima_spline = std::make_unique<boost::math::interpolators::makima<std::vector<double>>>(std::move(x),std::move(y));
  }

  /**
   * @brief change the input data to this vector of XY pairs
   *
   * @param XY: input data vector given as vector<pair<X,Y>>
   */
  void set_data_XY(const std::vector<std::pair<double, double>>& XY) final
  {
    std::vector<double> X, Y;
    X.reserve(XY.size());
    Y.reserve(XY.size());
    for (const auto& xy : XY) {
      X.push_back(xy.first);
      X.push_back(xy.second);
    }

    set_data_XY(X, Y);
  }

  
  /**
   * @brief get nearest y values for given x targets (vectorized call)
   * 
   * @param targets_x vector of x values. For each of these values find the corrspondig y value 
   * @return corresponding y value 
   */
  std::vector<double> interpolate(const std::vector<double>& targetsX)
  {
    return I_Interpolator<double>::interpolate(targetsX);
  }

};

} // namespace interpolation
} // namespace tools
} // namespace themachinethatgoesping
