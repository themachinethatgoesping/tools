// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
// Research Kiel
// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief some convenience functions to create eigen quaternions from yaw pitch
 * roll values using eigen rotations Note: Rotations are created in the
 * following order: 1. yaw, 2. pitch, 3. roll
 *
 * @authors Peter Urban, Sven Schorge
 */

#pragma once

/* generated doc strings */
#include ".docstrings/helper.doc.hpp"

#include <Eigen/Eigen>
#include <Eigen/Geometry>
#include <array>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <numbers>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace themachinethatgoesping {
namespace tools {
namespace rotationfunctions {

/**
 * @brief Shift angles into specified angular range: yaw [0,_2PI], pitch [-p/2°, p/2°], roll [-pi,
 * pi]
 *
 * @tparam floattype double or float
 * @param ypr Matrix with yaw, pitch and roll value in rad
 * @return std::array<floattype, 3> (Matrix with yaw, pitch and roll value in rad)
 */
template<typename floattype>
std::array<floattype, 3> normalize_angles_rad(std::array<floattype, 3> ypr)
{
    /* pitch is constrained to -90° -> 90°
     * otherwise there is two possibilities to reach every point.
     * because: rotate(yaw,pitch,roll) == rotate(yaw+pi,pi-pitch,roll+pi)
     * Also note: pitch = 90 degrees leads to a gimbal lock situation
     */
    static const floattype _2PI   = 2. * std::numbers::pi;
    static const floattype PI     = std::numbers::pi;
    static const floattype PI_2   = .5 * std::numbers::pi;
    static const floattype PI_3_2 = std::numbers::pi * 1.5; // * 3. / 2.;

    while (ypr[1] > PI_3_2)
    {
        ypr[1] -= _2PI;
    }
    while (ypr[1] < -PI_2)
    {
        ypr[1] += _2PI;
    }
    while (ypr[1] > PI_2)
    {
        ypr[0] -= PI;
        ypr[1] = PI - ypr[1];
        ypr[2] -= PI;
    }

    // roll is defined within -180° -> +179.0000 or +- pi
    while (ypr[2] < PI)
        ypr[2] += _2PI;
    while (ypr[2] >= PI)
        ypr[2] -= _2PI;

    // yaw is defined within 0 - 359.9999 ° or 0 - _2PI
    while (ypr[0] < 0)
        ypr[0] += _2PI;
    while (ypr[0] >= _2PI)
        ypr[0] -= _2PI;

    return ypr;
}

extern template std::array<float, 3>  normalize_angles_rad<float>(std::array<float, 3>);
extern template std::array<double, 3> normalize_angles_rad<double>(std::array<double, 3>);

/**
 * @brief Shift angles into specified angular range: yaw [0°,359.99°], pitch [-90°, 90°], roll
 * [-180¶, 179.99°]
 *
 * @tparam floattype double or float
 * @param ypr Matrix with yaw, pitch and roll value in °
 * @return std::array<floattype, 3> (Matrix with yaw, pitch and roll value in °)
 */
template<typename floattype>
std::array<floattype, 3> normalize_angles_degrees(std::array<floattype, 3> ypr)
{
    //
    static const floattype _0   = 0.;
    static const floattype _90  = 90.;
    static const floattype _180 = 180.;
    static const floattype _270 = 270.;
    static const floattype _360 = 360.;

    /* pitch is constrained to -90° -> 90°
     * otherwise there is two possibilities to reach every point.
     * because: rotate(yaw,pitch,roll) == rotate(yaw+pi,pi-pitch,roll+pi)
     * Also note: pitch = 90 degrees leads to a gimbal lock situation
     */
    while (ypr[1] > _270)
    {
        ypr[1] -= _360;
    }
    while (ypr[1] < -_90)
    {
        ypr[1] += _360;
    }
    while (ypr[1] > _90)
    {
        ypr[0] -= _180;
        ypr[1] = _180 - ypr[1];
        ypr[2] -= _180;
    }

    // roll is defined within -180° -> +179.999 or +- pi
    while (ypr[2] < _180)
        ypr[2] += _360;
    while (ypr[2] >= _180)
        ypr[2] -= _360;

    // yaw is defined within 0 - 359.9999 ° or 0 - _2PI
    while (ypr[0] < _0)
        ypr[0] += _360;
    while (ypr[0] >= _360)
        ypr[0] -= _360;

    return ypr;
}

extern template std::array<float, 3>  normalize_angles_degrees<float>(std::array<float, 3>);
extern template std::array<double, 3> normalize_angles_degrees<double>(std::array<double, 3>);

/**
 * @brief compute heading from northing and easting
 * north 0°/360°, east 90°, south 180°, west 270
 *
 * @param northing northing in m
 * @param easting easting in m
 * @param radians return as rad, otherwise as degrees
 * @return heading in rad or degrees
 */
template<typename floattype>
inline floattype compute_heading(floattype northing, floattype easting, bool radians = false)
{
    static const floattype _2PI    = 2. * std::numbers::pi;
    static const floattype _180_PI = 180. / std::numbers::pi;

    floattype heading = atan2(easting, northing);
    if (heading < 0)
        heading += _2PI;

    if (!radians)
        heading *= _180_PI;

    return heading;
}

extern template float  compute_heading<float>(float northing, float easting, bool radians);
extern template double compute_heading<double>(double northing, double easting, bool radians);

} // namespace rotationfunctions
} // namespace tools
} // namespace themachinethatgoesping
