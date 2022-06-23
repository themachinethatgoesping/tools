// SPDX-FileCopyrightText: 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

// this header only works if libeigen was found
//#ifdef USE_LIBEIGEN

#include <Eigen/Eigen>
#include <Eigen/Geometry>
#include <array>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "../rotationfunctions/quaternions.hpp"
#include "i_pairinterpolator.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace vectorinterpolators {

using t_quaternion = Eigen::Quaternion<double>;

/**
 * @brief Class that implements a slerp interpolation for vectors.
 * Data is internaly represented in quaternions using libeigen.
 * Interfaces to represent the data in yaw, pitch, roll angles are provided.
 *
 */
class SlerpInterpolator : public I_PairInterpolator<t_quaternion>
{

  public:
    /**
     * @brief Constructor to make default initialization possible (neccessary?)
     */
    SlerpInterpolator()
        : I_PairInterpolator<t_quaternion>({
              {0,  rotationfunctions::quaternion_from_ypr<double>(0,   -180, -89.99)},
              { 1, rotationfunctions::quaternion_from_ypr<double>(360, 180,  89.99) }
    })
    {
    }

    SlerpInterpolator(const std::vector<std::pair<double, t_quaternion>>& XY,
                      t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
        : I_PairInterpolator<t_quaternion>(XY, extrapolation_mode)
    {
    }
    SlerpInterpolator(const std::vector<double>&       X,
                      const std::vector<t_quaternion>& Y,
                      t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
        : I_PairInterpolator<t_quaternion>(X, Y, extrapolation_mode)
    {
    }

    /**
     * @brief Construct a new Slerp Interpolator object using vectors of x, yaw, pitch and roll
     *
     * @param X vector; must be unique and sorted in ascending order
     * @param yaw vector with yaw data (rotation arround z axis). Must be same size as X!
     * @param pitch vector with pitch data (rotation arround y axis). Must be same size as X!
     * @param roll vector with roll data (rotation arround x axis). Must be same size as X!
     * @param input_in_degrees if true (default) yaw,pitch and roll are in °, otherwise [rad]
     * @param extrapolation_mode :py:class:`t_extr_mode
     * <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>` object that describes the
     * extrapolation mode
     */
    SlerpInterpolator(const std::vector<double>& X,
                      const std::vector<double>& Yaw,
                      const std::vector<double>& Pitch,
                      const std::vector<double>& Roll,
                      bool                       input_in_degrees   = true,
                      t_extr_mode                extrapolation_mode = t_extr_mode::extrapolate)
        : I_PairInterpolator<t_quaternion>(
              X,
              rotationfunctions::quaternion_from_ypr(Yaw, Pitch, Roll, input_in_degrees),
              extrapolation_mode)
    {
    }

    /**
     * @brief Construct a new Slerp Interpolator object using vectors of x, yaw, pitch and roll
     *
     * @param X vector; must be unique and sorted in ascending order
     * @param YPR vector with yaw, pitch and roll data points. Must be same size as X!
     * @param input_in_degrees if true (default) yaw,pitch and roll are in °, otherwise [rad]
     * @param extrapolation_mode :py:class:`t_extr_mode
     * <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>` object that describes the
     * extrapolation mode
     */
    SlerpInterpolator(const std::vector<double>&                X,
                      const std::vector<std::array<double, 3>>& YPR,
                      bool                                      input_in_degrees = true,
                      t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
        : I_PairInterpolator<t_quaternion>(
              X,
              rotationfunctions::quaternion_from_ypr(YPR, input_in_degrees),
              extrapolation_mode)
    {
    }

    /**
     * @brief get the interolated yaw, pitch and roll values for given x target
     *
     * @param target_x find the corresponding y value for this x value
     * @param output_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
     * @return corresponding y value
     */
    std::array<double, 3> interpolate_ypr(double target_x, bool output_in_degrees = true)
    {
        return rotationfunctions::ypr_from_quaternion(
            I_PairInterpolator<t_quaternion>::interpolate(target_x), output_in_degrees);
    }

    /**
     * @brief get the interolated yaw, pitch and roll values for given x target (vectorized call)
     *
     * @param targets_x vector of x values. For each of these values find the corrspondig yaw, pitch
     * and roll value
     * @param output_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
     * @return corresponding y value
     */
    std::vector<std::array<double, 3>> interpolate_ypr(const std::vector<double>& targets_x,
                                                       bool output_in_degrees = true)
    {
        std::vector<std::array<double, 3>> y_values;
        y_values.reserve(targets_x.size());
        for (const auto target_x : targets_x)
        {
            y_values.push_back(interpolate_ypr(target_x, output_in_degrees));
        }

        return y_values;
    }

    // ------------------
    // set data functions
    // ------------------
    /**
     * @brief change the input data to thes X, yaw, pitch, roll vectors (will be converted to
     * queternion)
     *
     * @param X vector; must be unique and sorted in ascending order
     * @param yaw vector with yaw data (rotation arround z axis). Must be same size as X!
     * @param pitch vector with pitch data (rotation arround y axis). Must be same size as X!
     * @param roll vector with roll data (rotation arround x axis). Must be same size as X!
     * @param input_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
     */
    void set_data_XY(const std::vector<double>& X,
                     const std::vector<double>& Yaw,
                     const std::vector<double>& Pitch,
                     const std::vector<double>& Roll,
                     bool                       input_in_degrees = true)
    {
        I_PairInterpolator<t_quaternion>::set_data_XY(
            X, rotationfunctions::quaternion_from_ypr(Yaw, Pitch, Roll, input_in_degrees));
    }

    /**
     * @brief change the input data to thes X, yaw, pitch, roll vectors (will be converted to
     * queternion)
     *
     * @param X vector; must be unique and sorted in ascending order
     * @param yaw vector with yaw data (rotation arround z axis). Must be same size as X!
     * @param pitch vector with pitch data (rotation arround y axis). Must be same size as X!
     * @param roll vector with roll data (rotation arround x axis). Must be same size as X!
     * @param input_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
     */
    void set_data_XY(const std::vector<double>&                X,
                     const std::vector<std::array<double, 3>>& YPR,
                     bool                                      input_in_degrees = true)
    {
        I_PairInterpolator<t_quaternion>::set_data_XY(
            X, rotationfunctions::quaternion_from_ypr(YPR, input_in_degrees));
    }

    // -----------------------
    // append/extend functions
    // -----------------------
    
    /**
     * @brief append an x, yaw, pitch, roll data point
     *
     * @param X must be larger than all internal data points
     * @param yaw rotation arround z axis
     * @param pitch rotation arround y axis
     * @param roll rotation arround x axis
     * @param input_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
     */
    void append(double x, double yaw, double pitch, double roll, bool input_in_degrees = true)
    {
        I_PairInterpolator<t_quaternion>::append(
            x, rotationfunctions::quaternion_from_ypr(yaw, pitch, roll, input_in_degrees));
    }

    /**
     * @brief append an x, yaw, pitch, roll data point
     *
     * @param X must be larger than all internal data points
     * @param ypr array with one yaw, pitch and roll data point
     * @param input_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
     */
    void append(double x, std::array<double, 3> ypr, bool input_in_degrees = true)
    {
        I_PairInterpolator<t_quaternion>::append(
            x, rotationfunctions::quaternion_from_ypr(ypr, input_in_degrees));
    }

    /**
     * @brief append data with lists of x, yaw, pitch, roll data (vectorized call)
     *
     * @param X vector; must be unique and sorted in ascending order
     * @param yaw vector with yaw data (rotation arround z axis). Must be same size as X!
     * @param pitch vector with pitch data (rotation arround y axis). Must be same size as X!
     * @param roll vector with roll data (rotation arround x axis). Must be same size as X!
     * @param input_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
     */
    void extend(const std::vector<double>& x,
                const std::vector<double>& yaw,
                const std::vector<double>& pitch,
                const std::vector<double>& roll,
                bool                       input_in_degrees = true)
    {
        I_PairInterpolator<t_quaternion>::extend(
            x, rotationfunctions::quaternion_from_ypr(yaw, pitch, roll, input_in_degrees));
    }

    
    /**
     * @brief append data with list of x, yaw, pitch, roll data (vectorized call)
     *
     * @param X vector; must be unique and sorted in ascending order
     * @param ypr vector with yaw, pitch and roll data points. Must be same size as X!
     * @param input_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
     */
    void extend(const std::vector<double>&                x,
                const std::vector<std::array<double, 3>>& ypr,
                bool                                      input_in_degrees = true)
    {
        I_PairInterpolator<t_quaternion>::extend(
            x, rotationfunctions::quaternion_from_ypr(ypr, input_in_degrees));
    }

    /**
     * @brief Interpolate: Slerp interpolation between two values
     * @param target_x: the target point [0.0 - 1.0]
     * @param y1     : first quaternion (target_x = 0)
     * @param y2     : second quaternion (target_x = 01)
     * inbetween)
     * @return Interpolated value for target position
     */
    t_quaternion interpolate_pair(double              target_x,
                                  const t_quaternion& y1,
                                  const t_quaternion& y2) const final
    {
        return y1.slerp(target_x, y2);
    }
};

} // namespace vectorinterpolators
} // namespace tools
} // namespace themachinethatgoesping

//#endif