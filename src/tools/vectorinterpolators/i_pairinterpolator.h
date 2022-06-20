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

#include "i_interpolator.h"

namespace themachinethatgoesping {
namespace tools {
namespace vectorinterpolators {


/**
 * @brief Interface class for interpolator classes
 * This template clas implements base functions interpolators that interpolate between two values (pairs).
 * This interface implements the search for the x position within this vector (closest 2 x/y
 * value pair) and computes an x interpolation value (target_x) Then it call the
 * Interpolate functions of the implementation classes that use this interface
 * to interpolate between these pairs.
 *
 * @tparam YType: type of the y values (typically double, but will be a vector
 * for the slerp interpolator class)
 */
template<typename YType>
class I_PairInterpolator : public I_Interpolator<YType>
{
protected:

  struct _t_x_pair
  {
    size_t
      _xmin_index; ///< index of the smaller x value (in the internal vector)
    size_t
      _xmax_index;   ///< index of the larger x value (in the internal vector)
    double _xmin;    ///< smaller xvalue
    double _xmax;    ///< larger xvalue
    double _xfactor; ///< 1/(xmax-xmin)

    _t_x_pair(size_t xmin_index, size_t xmax_index, double xmin, double xmax)
      : _xmin_index(xmin_index)
      , _xmax_index(xmax_index)
      , _xmin(xmin)
      , _xmax(xmax)
      , _xfactor(1 / (_xmax - _xmin))
    {}

    /**
     * @brief compute the interpolation factor between xmin and xmax
     *
     * @param target_x x value for which we want to know the interpolation factor
     * @return interpolation factor
     */
    double calc_target_x(double target_x) { return (target_x - _xmin) * _xfactor; }

  } _last_x_pair; ///< last pair (for faster consequtive searches)

  /**
   * @brief extrapolation mode type.
   *
   */

  std::vector<std::pair<double, YType>> _XY; ///< main data vector containing pairs of corresponding x and y datapoitns

public:
  /**
   * @brief Construct a new Interpolator object from a vector of pairs
   * usage: interpolated_y_value = interpolator.interpolate(x_value)
   * 
   * @param XY vector of x,y pairs. X must be unique and sorted
   * @param extrapolation_mode :py:class:`t_extr_mode <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>` object that describes the extrapolation mode
   */
  I_PairInterpolator(const std::vector<std::pair<double, YType>>& XY,
                 t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
    : I_Interpolator<YType>(extrapolation_mode),
      _last_x_pair(0, 1, 0, 1)
  {
    set_data_XY(XY);
  }
  /**
   * @brief Construct a new Interpolator object from a vector of pairs
   * usage: interpolated_y_value = interpolator.interpolate(x_value)
   * 
   * @param X X vector; must be unique and sorted in ascending order. same size as Y!
   * @param Y Y vector; must be unique and sorted in ascending order. same size as X!
   * @param extrapolation_mode :py:class:`t_extr_mode <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>` object that describes the extrapolation mode
   */
  I_PairInterpolator(const std::vector<double>& X,
                 const std::vector<YType>& Y,
                 t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
    : I_Interpolator<YType>(extrapolation_mode),
    _last_x_pair(0, 1, 0, 1)
  {
    set_data_XY(X, Y);
  }

  virtual ~I_PairInterpolator() = default;


  /**
   * @brief change the input data to this vector of XY pairs
   *
   * @param XY: input data vector given as vector<pair<X,Y>>
   */
  void set_data_XY(const std::vector<std::pair<double, YType>>& XY) final
  {
    if (XY.size() < 2)
      throw(
        std::invalid_argument("ERROR[Interpolation::set_data_XY]: list size is < 2!"));

    // set list
    _XY = XY;

    // make sure the vector is sorted
    I_Interpolator<YType>::_check_XY(_XY);

    _last_x_pair = _t_x_pair(0, 1, std::get<0>(_XY[0]), std::get<0>(_XY[1]));
  }

  /**
   * @brief change the input data to these X and Y vectors
   *
   * @param X: x vector (must be same size, must be sorted in ascending order)
   * @param Y: y vector (must be same size)
   */
  void set_data_XY(const std::vector<double>& X, const std::vector<YType>& Y) final
  {
    if (X.size() != Y.size())
      throw(std::invalid_argument(
        "ERROR[Interpolation::set_data_XY]: list sizes do not match"));

    std::vector<std::pair<double, YType>> XY;
    XY.reserve(X.size());

    for (unsigned int i = 0; i < X.size(); ++i) {
      XY.push_back(std::make_pair(X[i], Y[i]));
    }

    set_data_XY(XY);
  }

  // -----------------------
  // append/extend functions
  // -----------------------
  void append(double x, double y) final
  {
    if (x <= std::get<0>(_XY.back()))
    {
        throw(std::invalid_argument("ERROR[Interpolation::append]: appendet x value is not larger than existing x values in the interpolator."));
    }
    
    _XY.push_back(std::make_pair(x,y));
  }

  void append(std::pair<double , double> xy) final
  {
    if (std::get<0>(xy) <= std::get<0>(_XY.back()))
    {
        throw(std::invalid_argument("ERROR[Interpolation::append]: appendet x value is not larger than existing x values in the interpolator."));
    }
    
    _XY.push_back(xy);
  }

  void extend(const std::vector<double>& X, const std::vector<double>& Y) final
  {
    if (X.size() != Y.size())
      throw(std::invalid_argument(
        "ERROR[Interpolator::extend]: list sizes do not match"));

    for (unsigned int i = 0; i < X.size(); ++i) {
      append(X[i], Y[i]);
    }
  }

  void extend(const std::vector<std::pair<double, double>>& XY) final
  {
    for (const auto& xy : XY) {
      append(xy);
    }
  }

  // -----------------------
  // getter setter functions
  // -----------------------
  /**
   * @brief return the internal data vector
   *
   * @return const std::vector<std::pair<double,YType>>&
   */
  const std::vector<std::pair<double, YType>>& get_data_XY() const { return _XY; }

  /**
   * @brief return the x component of the internal data vector
   *
   * @return std::vector<double>
   */
  std::vector<double> get_data_X() const
  {
    std::vector<double> X;
    X.reserve(_XY.size());

    for (const auto& xy : _XY)
      X.push_back(std::get<0>(xy));

    return X;
  }

  /**
   * @brief return the y component of the itnernal data vector
   *
   * @return std::vector<YType>
   */
  std::vector<YType> get_data_Y() const
  {
    std::vector<YType> Y;
    Y.reserve(_XY.size());

    for (const auto& xy : _XY)
      Y.push_back(std::get<1>(xy));

    return Y;
  }

  void set_extrapolation_mode(const t_extr_mode extrapolation_mode)
  {
    I_Interpolator<YType>::_extr_mode = extrapolation_mode;
  }

  t_extr_mode get_extrapolation_mode() const
  {
    return I_Interpolator<YType>::_extr_mode;
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
  YType interpolate(double target_x) final
  {
    /* find correct xpair */

    // if target value is smaller than the min value of the last, decrement
    // backwards
    if (target_x > std::get<0>(_XY[_last_x_pair._xmax_index])) {
      size_t i = _last_x_pair._xmax_index;
      while (true) {
        ++i;

        // if i is smaler than the index
        if (size_t last = _XY.size() - 1; i > last) {
          // set the new last pair (will be used for interpolation)
          switch (I_Interpolator<YType>::_extr_mode) {
            case t_extr_mode::fail: {
              std::string msg;
              msg += "ERROR[INTERPOLATE]: x value [" + std::to_string(target_x) +
                     "] is out of range  (too large)(" +
                     std::to_string(std::get<0>(_XY.front())) + "/" +
                     std::to_string(std::get<0>(_XY.back())) +
                     ")! (and fail on extrapolate was set)";
              throw(std::out_of_range(msg));
            }
            case t_extr_mode::nearest:
              _last_x_pair = _t_x_pair(last - 1,
                                    last,
                                    std::get<0>(_XY[last - 1]),
                                    std::get<0>(_XY[last]));
              return std::get<1>(_XY[last]);
            default:
              _last_x_pair = _t_x_pair(last - 1,
                                    last,
                                    std::get<0>(_XY[last - 1]),
                                    std::get<0>(_XY[last]));
              break;
          }
          break;
        }

        // if target value is larger or equal than the value at i
        if (target_x <= std::get<0>(_XY[i])) {
          // set the new last pair (will be used for interpolation)
          _last_x_pair =
            _t_x_pair(i - 1, i, std::get<0>(_XY[i - 1]), std::get<0>(_XY[i]));
          break;
        }
      }
    }

    // if target value is smaller than the min value of the last, decrement
    // backwards
    else if (target_x < std::get<0>(_XY[_last_x_pair._xmin_index])) {
      long int i = static_cast<long int>(_last_x_pair._xmin_index);
      while (true) {
        --i;

        // if i is smaler than the index
        if (i < 0) {

          // set the new last pair (will be used for interpolation)
          switch (I_Interpolator<YType>::_extr_mode) {
            case t_extr_mode::fail: {
              std::string msg;
              msg += "ERROR[INTERPOLATE]: x value [" + std::to_string(target_x) +
                     "] is out of range (too small)(" +
                     std::to_string(std::get<0>(_XY.front())) + "/" +
                     std::to_string(std::get<0>(_XY.back())) +
                     ")! (and fail on extrapolate was set)";
              throw(std::out_of_range(msg));
            }
            case t_extr_mode::nearest:
              _last_x_pair =
                _t_x_pair(0, 1, std::get<0>(_XY[0]), std::get<0>(_XY[1]));
              return std::get<1>(_XY[0]);
            default:
              _last_x_pair =
                _t_x_pair(0, 1, std::get<0>(_XY[0]), std::get<0>(_XY[1]));
              break;
          }
          break;
        }

        // if target value is larger or equal than the value at i
        if (target_x >= std::get<0>(_XY[i])) {
          _last_x_pair =
            _t_x_pair(i, i + 1, std::get<0>(_XY[i]), std::get<0>(_XY[i + 1]));
          break;
        }
      }
    }

    else // target_x <= _XY[_lastXPair._xmax_index] && target_x >=
         // _XY[_lastXPair._xmin_index]
    {
    }

    /* interpolate useing the (new) last XPair (call function from derived class) */
    return interpolate_pair(_last_x_pair.calc_target_x(target_x),
                       std::get<1>(_XY[_last_x_pair._xmin_index]),
                       std::get<1>(_XY[_last_x_pair._xmax_index]));
  }

  /**
   * @brief get nearest y values for given x targets (vectorized call)
   * 
   * @param targets_x vector of x values. For each of these values find the corrspondig y value 
   * @return corresponding y value 
   */
  std::vector<YType> interpolate(const std::vector<double>& targetsX)
  {
    return I_Interpolator<YType>::interpolate(targetsX);
  }

  
  //--------------------------------
  // virtual (interface) functions
  //--------------------------------

  /**
   * @brief Interface for implementing an interpolation between two y values
   * using a given interpolation factor
   *
   * @param target_x interpolation factor. 0 means return smaller y value, 1
   * means return larger y value
   * @param y1 smaller y value
   * @param y1 larger y value
   * @return interpolated y value
   */
  virtual YType interpolate_pair(double target_x,
                            const YType& y1,
                            const YType& y2) const = 0;

};

} // namespace interpolation
} // namespace tools
} // namespace themachinethatgoesping
