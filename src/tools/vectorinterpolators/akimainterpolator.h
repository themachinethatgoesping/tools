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
  boost::math::interpolators::makima _akima_spline({0,1},{0,1});

public:
  AkimaInterpolator()
    : I_Interpolator<double>({ 0, 1 }, { 0, 1 })
  {
  }

  /**
   * @brief Construct a new Akima Spline Interpolator object from a vector of
   * pairs This class uses the modified akima interpolation of boost c++
   * https://www.boost.org/doc/libs/1_79_0/libs/math/doc/html/math_toolkit/makima.html
   * usage: interpolated_y_value = interpolator.interpolate(x_value)
   *
   * @param XY vector of x,y pairs. X must be unique and sorted (unless sortX is
   * set).
   * @param sortX Setting this true will sort XY by X (deactiave for performance
   * reasons)
   * @param checkX Check if the inputdata is valid (deactiave for performance
   * reasons)
   * @param extrapolation_mode extrapolation mode (nearest or fail)
   */
  AkimaInterpolator(const std::vector<std::pair<double, double>>& XY,
                    bool sortX = false,
                    bool checkX = true,
                    t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
    : I_Interpolator<double>(XY, sortX, checkX, extrapolation_mode)
  {
  }
  /**
   * @brief Construct a new Akima Spline Interpolator object from a vector of
   * pairs This class uses the modified akima interpolation of boost c++
   * https://www.boost.org/doc/libs/1_79_0/libs/math/doc/html/math_toolkit/makima.html
   * usage: interpolated_y_value = interpolator.interpolate(x_value)
   *
   * @param X X vector; must be unique and sorted (unless sortX is set). same
   * size as Y!
   * @param Y Y vector; must be unique and sorted (unless sortX is set). same
   * size as X!
   * @param sortX Setting this true will sort XY by X (deactiave for performance
   * reasons)
   * @param checkX Check if the inputdata is valid (deactiave for performance
   * reasons)
   * @param extrapolation_mode extrapolation mode (nearest or fail)
   */
  AkimaInterpolator(const std::vector<double>& X,
                    const std::vector<double>& Y,
                    bool sortX = false,
                    bool checkX = true,
                    t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
    : I_Interpolator<double>(X, Y, sortX, checkX, extrapolation_mode)
  {
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
    return _akima_spline(target_);
  }

  /**
   * @brief change the input data to these X and Y vectors
   *
   * @param X: x vector (must be same size)
   * @param Y: y vector (must be same size)
   * @param sortX: sort the input data vector after interpolator construction
   * (necessary if the vector was not sorted before)
   * @param checkX: check if the inptur data vector is valid
   */
  void set_data_XY(const std::vector<double>& X,
                      const std::vector<YType>& Y,
                      bool sortx = false,
                      bool checkx = true) virtual
  {
    //these variables are not used for the akima interpolator class
    (void) sortX;
    (void) checkx;

    // check if vectors are same size
    if (X.size() != Y.size())
      throw(std::runtime_error(
        "ERROR[Interpolation::set_data_XY]: list sizes do not match"));        

    _akima_spline = boost::math::interpolators::makima(X, Y);
  }

  /**
   * @brief change the input data to this vector of XY pairs
   *
   * @param XY: input data vector given as vector<pair<X,Y>>
   * @param sortX: sort the input data vector after interpolator construction
   * (necessary if the vector was not sorted before)
   * @param checkX: check if the inptur data vector is valid
   */
  void set_data_XY(const std::vector<std::pair<double, YType>>& XY,
                           bool sortx = false,
                           bool checkx = true) final
  {
    std::vector<double> X,Y;
    X.reserve(XY.size());
    Y.reserve(XY.size());
    for (const auto& xy : XY){
      X.push_back(xy.first);
      X.push_back(xy.second);
    }  
    _akima_inter

    set_data_XY(X,Y,sortx,checkx);
  }

  

  /**
   * @brief Function for the i_interpolator interface. Is NOT implemented for the akima interpolator class!
   */
  double interpolate_pair(double target_x,
                          const double& y1,
                          const double& y2) const final
  {
    throw std::runtime_error("This function is not implemented for the AkimaInterpolator class");    
  }
};

} // namespace interpolation
} // namespace tools
} // namespace themachinethatgoesping
