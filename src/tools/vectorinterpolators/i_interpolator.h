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
  fail = 1,   ///< return nearest value in the vector.
  nearest = 2 ///< throw out_of_range exception if given x value exceeds
              ///< boundaries of internal vector
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
 * x value) to get a corresponding y value at this x position. This interface
 * implements the search for the x position within this vector (closest 2 x/y
 * value pair) and computes an x interpolation value (target_data_X) Then it call the
 * Interpolate functions of the implementation classes that use this interface
 * to interpolate between these pairs.
 *
 * @tparam YType: type of the y values (typically double, but will be a vector
 * for the slerp interpolator class)
 */
template<typename YType>
class I_Interpolator
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
     * @param target_data_X x value for which we want to know the interpolation factor
     * @return interpolation factor
     */
    double calc_target_data_X(double target_data_X) { return (target_data_X - _xmin) * _xfactor; }

  } _last_x_pair; ///< last pair (for faster consequtive searches)

  /**
   * @brief extrapolation mode type.
   *
   */
  t_extr_mode _extr_mode;

  std::vector<std::pair<double, YType>> _XY; ///< main data vector containing pairs of corresponding x and y datapoitns

public:
  /**
   * @brief Construct a new i interpolator object from a vector of x,y pairs
   *
   * @param XY: input data vector given as vector<pair<X,Y>>
   * @param sortX: sort the input data vector after interpolator construction
   * (necessary if the vector was not sorted before)
   * @param checkX: check if the inptur data vector is valid
   */
  I_Interpolator(const std::vector<std::pair<double, YType>>& XY,
                 bool sortX = false,
                 bool checkX = true,
                 t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
    : _last_x_pair(0, 1, 0, 1),
      _extr_mode(extrapolation_mode)
  {
    set_data_XY(XY, sortX, checkX);
  }
  /**
   * @brief Construct a new i interpolator object from two (x and y) data
   * vectors (of same size)
   *
   * @param X: x vector (must be same size)
   * @param Y: y vector (must be same size)
   * @param sortX: sort the input data vector after interpolator construction
   * (necessary if the vector was not sorted before)
   * @param checkX: check if the inptur data vector is valid
   */
  I_Interpolator(const std::vector<double>& X,
                 const std::vector<YType>& Y,
                 bool sortX = false,
                 bool checkX = true,
                 t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
    : _last_x_pair(0, 1, 0, 1),
      _extr_mode(extrapolation_mode)
  {
    set_data_XY(X, Y, sortX, checkX);
  }

  virtual ~I_Interpolator() = default;

  /**
   * @brief sort internal vectors by X.
   * This is necessary if the input data was not sorted by X so far!
   * TODO: provide function to deal with x value duplicates
   */
  void sortX()
  {
    std::sort(
      _XY.begin(),
      _XY.end(),
      [](const std::pair<double, YType>& x, const std::pair<double, YType>& y) {
        // only sort by the first element
        return x.first < y.first;
      });
  }

  /**
   * @brief check if input data is valid (e.g. sorted, no duplicated x values)
   *
   */
  void checkX() const
  {
    if (_XY.size() < 2)
      throw(
        std::runtime_error("ERROR[Interpolation::checkX]: list size is < 2!"));

    for (size_t i = 0; i < _XY.size() - 1; ++i) {
      if (std::get<0>(_XY[i]) == std::get<0>(_XY[i + 1]))
        throw(
          std::runtime_error("ERROR[Interpolation::checkX]: double x values!"));

      if (std::get<0>(_XY[i]) > std::get<0>(_XY[i + 1]))
        throw(std::runtime_error("ERROR[Interpolation::checkX]: List is not "
                                 "sorted in asscending order!"));
    }
  }

  /**
   * @brief change the input data to this vector of XY pairs
   *
   * @param XY: input data vector given as vector<pair<X,Y>>
   * @param sortX: sort the input data vector after interpolator construction
   * (necessary if the vector was not sorted before)
   * @param checkX: check if the inptur data vector is valid
   */
  virtual void set_data_XY(const std::vector<std::pair<double, YType>>& XY,
                      bool sortx = false,
                      bool checkx = true)
  {
    if (XY.size() < 2)
      throw(
        std::runtime_error("ERROR[Interpolation::set_data_XY]: list size is < 2!"));

    // set list
    _XY = XY;

    // make sure the vector is sorted, except the caller guarantues that it is
    // already sorted
    if (sortx)
      sortX();
    if (checkx)
      checkX();

    _last_x_pair = _t_x_pair(0, 1, std::get<0>(_XY[0]), std::get<0>(_XY[1]));
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
  virtual void set_data_XY(const std::vector<double>& X,
                      const std::vector<YType>& Y,
                      bool sortx = false,
                      bool checkx = true)
  {
    if (X.size() != Y.size())
      throw(std::runtime_error(
        "ERROR[Interpolation::set_data_XY]: list sizes do not match"));

    std::vector<std::pair<double, YType>> XY;
    XY.reserve(X.size());

    for (unsigned int i = 0; i < X.size(); ++i) {
      XY.push_back(std::make_pair(X[i], Y[i]));
    }

    set_data_XY(XY, sortx, checkx);
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
    _extr_mode = extrapolation_mode;
  }

  t_extr_mode get_extrapolation_mode() const
  {
    return _extr_mode;
  }

  //-------------------------
  // interpolation functions
  //-------------------------

  
  /**
   * @brief get neares y values for given x target
   * 
   * @param targets_x vector of x values. For each of these values find the corrspondig y value 
   * @return corresponding y value 
   */
  virtual YType interpolate(double target_data_X)
  {
    /* find correct xpair */

    // if target value is smaller than the min value of the last, decrement
    // backwards
    if (target_data_X > std::get<0>(_XY[_last_x_pair._xmax_index])) {
      size_t i = _last_x_pair._xmax_index;
      while (true) {
        ++i;

        // if i is smaler than the index
        if (size_t last = _XY.size() - 1; i > last) {
          // set the new last pair (will be used for interpolation)
          switch (_extr_mode) {
            case t_extr_mode::fail: {
              std::string msg;
              msg += "ERROR[INTERPOLATE]: x value [" + std::to_string(target_data_X) +
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
        if (target_data_X <= std::get<0>(_XY[i])) {
          // set the new last pair (will be used for interpolation)
          _last_x_pair =
            _t_x_pair(i - 1, i, std::get<0>(_XY[i - 1]), std::get<0>(_XY[i]));
          break;
        }
      }
    }

    // if target value is smaller than the min value of the last, decrement
    // backwards
    else if (target_data_X < std::get<0>(_XY[_last_x_pair._xmin_index])) {
      long int i = static_cast<long int>(_last_x_pair._xmin_index);
      while (true) {
        --i;

        // if i is smaler than the index
        if (i < 0) {

          // set the new last pair (will be used for interpolation)
          switch (_extr_mode) {
            case t_extr_mode::fail: {
              std::string msg;
              msg += "ERROR[INTERPOLATE]: x value [" + std::to_string(target_data_X) +
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
        if (target_data_X >= std::get<0>(_XY[i])) {
          _last_x_pair =
            _t_x_pair(i, i + 1, std::get<0>(_XY[i]), std::get<0>(_XY[i + 1]));
          break;
        }
      }
    }

    else // target_data_X <= _XY[_lastXPair._xmax_index] && target_data_X >=
         // _XY[_lastXPair._xmin_index]
    {
    }

    /* interpolate useing the (new) last XPair (call function from derived class) */
    return interpolate_pair(_last_x_pair.calc_target_data_X(target_data_X),
                       std::get<1>(_XY[_last_x_pair._xmin_index]),
                       std::get<1>(_XY[_last_x_pair._xmax_index]));
  }

  
  /**
   * @brief get nearest y values for given x targets (vectorized call)
   * 
   * @param targets_x vector of x values. For each of these values find the corrspondig y value 
   * @return corresponding y value 
   */
  virtual std::vector<YType> interpolate(const std::vector<double>& targetsX)
  {
    std::vector<YType> y_values;
    y_values.reserve(targetsX.size());
    for(const auto target_data_X : targetsX){
      y_values.push_back(interpolate(target_data_X));
    }

    return y_values;
  }

  //--------------------------------
  // virtual (interface) functions
  //--------------------------------

  /**
   * @brief Interface for implementing an interpolation between two y values
   * using a given interpolation factor
   *
   * @param target_data_X interpolation factor. 0 means return smaller y value, 1
   * means return larger y value
   * @param y1 smaller y value
   * @param y1 larger y value
   * @return interpolated y value
   */
  virtual YType interpolate_pair(double target_data_X,
                            const YType& y1,
                            const YType& y2) const = 0;

};

} // namespace interpolation
} // namespace tools
} // namespace themachinethatgoesping