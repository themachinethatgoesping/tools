// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean
// Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <algorithm>
#include <array>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

namespace themachinethatgoesping {
namespace tools {
namespace vectorinterpolators {


/**
 * @brief extrapolation mode type.
 * 
 */
enum class t_extr_mode
{
  extrapolate = 0, ///< interpolate using the closest value pair in the internal x vector
  fail = 1, ///< throw out_of_range exception if given x value exceeds boundaries of internal vector
  nearest = 2, ///< return nearest value in the vector.
};

static const std::array<t_extr_mode,3> t_extr_mode_all = {
  t_extr_mode::extrapolate,
  t_extr_mode::fail,
  t_extr_mode::nearest
};

/**
 * @brief Interface class for interpolator classes
 * Create an interpolator object by provding vectors for x and y (same size). X
 * must be sorted and no duplicates are allowed. then call class.Interpolate(new
 * x value) to get a corresponding y value at this x position. 
 *
 * @tparam YType: type of the y values (typically double, but will be a vector
 * for the slerp interpolator class)
 */
template<typename YType>
class I_Interpolator
{
protected:
  /**
   * @brief extrapolation mode type.
   * 
   */
  t_extr_mode _extr_mode;


public:
  /**
   * @brief Construct a new Interpolator object from two vectors
   * usage: interpolated_y_value = interpolator.interpolate(x_value)
   * 
   * @param extrapolation_mode extrapolation mode (nearest or fail)
   */
  I_Interpolator(t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
      : _extr_mode(extrapolation_mode)
  {
  }
  virtual ~I_Interpolator() = default;


  /**
   * @brief change the input data to these X and Y vectors
   *
   * @param X: x vector (must be same size, must be sorted in ascending order)
   * @param Y: y vector (must be same size)
   */
  virtual void set_data_XY(const std::vector<double>& X, const std::vector<YType>& Y) = 0;

  /**
   * @brief change the input data to this vector of XY pairs
   *
   * @param XY: input data vector given as vector<pair<X,Y>>
   */
  virtual void set_data_XY(const std::vector<std::pair<double, YType>>& XY) = 0;



  // -----------------------
  // getter setter functions
  // -----------------------
  /**
   * @brief Set the extrapolation mode
   * 
   * @param extrapolation_mode :py:class:`t_extr_mode <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>` object (enumerator) that describes the extrapolation mode
   */
  void set_extrapolation_mode(const t_extr_mode extrapolation_mode)
  {
    _extr_mode = extrapolation_mode;
  }

  /**
   * @brief Get the currently set extrapolation mode
   * 
   * @return :py:class:`t_extr_mode <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>` object (enumerator) that describes the extrapolation mode
   */
  t_extr_mode get_extrapolation_mode() const
  {
    return _extr_mode;
  }

  //-------------------------
  // interpolation functions
  //-------------------------
  
  /**
   * @brief get the interolated y value for given x target
   * 
   * @param target_x find the corresponding y value for this x value
   * @return corresponding y value 
   */
  virtual YType interpolate(double target_x) = 0;

  
  /**
   * @brief get nearest y values for given x targets (vectorized call)
   * 
   * @param targets_x vector of x values. For each of these values find the corrspondig y value 
   * @return corresponding y value 
   */
  std::vector<YType> interpolate(const std::vector<double>& targetsX)
  {
    std::vector<YType> y_values;
    y_values.reserve(targetsX.size());
    for(const auto target_x : targetsX){
      y_values.push_back(interpolate(target_x));
    }

    return y_values;
  }

  /**
   * @brief append an x- and the corresponding y value to the interpolator data.
   * 
   * @param x value, must be > than all existing x values
   * @param y corresponding y value
   */
  virtual void append(double x, double y) = 0;

  /**
   * @brief append a x and y value pair to the interpolator data
   * 
   * @param xy x and y value pair. x must be > than all existing x values
   */
  virtual void append(std::pair<double , double> xy) = 0;

  /**
   * @brief append x and y value lists to the interplator data
   * 
   * @param X list of x values. Must be sorted in ascending order. All x values must be larger than the largest x value in the interpolator data.
   * @param Y list of corresponding Y values. Must be same size as X
   */
  virtual void extend(const std::vector<double>& X, const std::vector<double>& Y) = 0;

  
  /**
   * @brief append a list of x and y value pairs to the interplator data
   * 
   * @param XY list of x,y value pairs. X Must be sorted in ascending order. All x values must be larger than the largest x value in the interpolator data.
   */
  virtual void extend(const std::vector<std::pair<double, double>>& XY) = 0;


protected:  
  /**
   * @brief check if input data is valid (e.g. sorted, no duplicated x values)
   *
   */
  static void _check_XY(const std::vector<std::pair<double,YType>>& XY)
  {
    if (XY.size() < 2)
      throw(
        std::invalid_argument("ERROR[Interpolation::_check_XY]: list size is < 2!"));

    for (size_t i = 0; i < XY.size() - 1; ++i) {
      if (std::get<0>(XY[i]) == std::get<0>(XY[i + 1]))
        throw(
          std::invalid_argument("ERROR[Interpolation::_check_XY]: double x values!"));

      if (std::get<0>(XY[i]) > std::get<0>(XY[i + 1]))
        throw(std::invalid_argument("ERROR[Interpolation::_check_XY]: List is not "
                                 "sorted in asscending order!"));
    }
  }

  /**
   * @brief check if input data is valid (e.g. sorted, no duplicated x values)
   *
   */
  static void _check_XY(const std::vector<double>& X, const std::vector<YType>& Y)
  {
    if (X.size() < 2)
      throw(
        std::runtime_error("ERROR[Interpolation::_check_XY]: list size is < 2!"));
    if (X.size() != Y.size())
      throw(
        std::runtime_error("ERROR[Interpolation::_check_XY]: list X and Y list sizes do not match!"));

    for (size_t i = 0; i < X.size() - 1; ++i) {
      if (X[i] == X[i + 1])
        throw(
          std::runtime_error("ERROR[Interpolation::_check_XY]: double x values!"));

      if (X[i] > X[i + 1])
        throw(std::runtime_error("ERROR[Interpolation::_check_XY]: List is not "
                                 "sorted in asscending order!"));
    }
  }

};

} // namespace interpolation
} // namespace tools
} // namespace themachinethatgoesping
