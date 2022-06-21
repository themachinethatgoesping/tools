// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz
// Centre for Ocean Research Kiel SPDX-FileCopyrightText: 2022 Peter Urban,
// Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief some convinience functions to create eigen quaternions from yaw pitch
 * roll values using eigen rotations Note: Rotations are created in the
 * following order: 1. yaw, 2. pitch, 3. roll
 *
 * @authors Peter Urban, Sven Schorge
 */

#pragma once

//#define _USE_MATH_DEFINES // for C++ // windows // this is not necessary
#include <cmath>

#include <Eigen/Eigen>
#include <Eigen/Geometry>
#include <array>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace themachinethatgoesping {
namespace tools {
namespace rotationfunctions {

/**
 * @brief Shift angles into specified angular range: yaw [0,2pi], pitch [-p/2°, p/2°], roll [-pi,
 * pi]
 *
 * @tparam floattype double or gloat
 * @param ypr Matrix with yaw, pitch and roll value in rad
 * @return std::array<floattype, 3> (Matrix with yaw, pitch and roll value in rad)
 */
template<typename floattype>
std::array<floattype, 3> normalize_angles_rad(std::array<floattype, 3> ypr)
{
    /* pitch is constrained to -90° -> 90°
     * otherwise there is two possibilites to reach every point.
     * because: rotate(yaw,pitch,roll) == rotate(yaw+pi,pi-pitch,roll+pi)
     * Also note: pitch = 90 degrees leads to a gimbal lock situation
     */
    static const floattype M_2PI    = 2. * M_PI;
    static const floattype M_PI_3_2 = M_PI_2 * 3.;

    while (ypr[1] > M_PI_3_2)
    {
        ypr[1] -= M_2PI;
    }
    while (ypr[1] < -M_PI_2)
    {
        ypr[1] += 2 * M_PI;
    }
    while (ypr[1] > M_PI_2)
    {
        ypr[0] -= M_PI;
        ypr[1] = M_PI - ypr[1];
        ypr[2] -= M_PI;
    }

    // roll is defined within -180° -> +179.0000 or +- pi
    while (ypr[2] < M_PI)
        ypr[2] += M_2PI;
    while (ypr[2] >= M_PI)
        ypr[2] -= M_2PI;

    // yaw is defined within 0 - 359.9999 ° or 0 - 2pi
    while (ypr[0] < 0)
        ypr[0] += M_2PI;
    while (ypr[0] >= M_2PI)
        ypr[0] -= M_2PI;

    return ypr;
}

/**
 * @brief Shift angles into specified angular range: yaw [0°,359.99°], pitch [-90°, 90°], roll
 * [-180¶, 179.99°]
 *
 * @tparam floattype double or gloat
 * @param ypr Matrix with yaw, pitch and roll value in °
 * @return std::array<floattype, 3> (Matrix with yaw, pitch and roll value in °)
 */
template<typename floattype>
std::array<floattype, 3> normalize_angles_degrees(std::array<floattype, 3> ypr)
{
    //

    /* pitch is constrained to -90° -> 90°
     * otherwise there is two possibilites to reach every point.
     * because: rotate(yaw,pitch,roll) == rotate(yaw+pi,pi-pitch,roll+pi)
     * Also note: pitch = 90 degrees leads to a gimbal lock situation
     */
    while (ypr[1] > 270.)
    {
        ypr[1] -= 360.;
    }
    while (ypr[1] < -90.)
    {
        ypr[1] += 360.;
    }
    while (ypr[1] > 90.)
    {
        ypr[0] -= 180.;
        ypr[1] = 180. - ypr[1];
        ypr[2] -= 180.;
    }

    // roll is defined within -180° -> +179.999 or +- pi
    while (ypr[2] < 180.)
        ypr[2] += 360.;
    while (ypr[2] >= 180.)
        ypr[2] -= 360.;

    // yaw is defined within 0 - 359.9999 ° or 0 - 2pi
    while (ypr[0] < 0)
        ypr[0] += 360.;
    while (ypr[0] >= 360.)
        ypr[0] -= 360.;

    return ypr;
}

/**
 * @brief create an eigen quaternion by rotating yaw (z axis), pitch (y axis) and roll (x axis)
 *
 * @tparam floattype
 * @param ypr array that contains yaw, pitch and roll value
 * @param input_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
 * @return Eigen::Quaternion<floattype>
 */
template<typename floattype>
Eigen::Quaternion<floattype> quaternion_from_ypr(std::array<floattype, 3> ypr,
                                                 bool                     input_in_degrees = true)
{
    static const floattype _quaternion_from_ypr_to_rad = M_PI / 180.;

    // convert to rad
    if (input_in_degrees)
    {
        ypr[0] *= _quaternion_from_ypr_to_rad;
        ypr[1] *= _quaternion_from_ypr_to_rad;
        ypr[2] *= _quaternion_from_ypr_to_rad;
    }

    // creaste quaternion by rotating arround axes first, yaw, then pitch, then roll
    Eigen::Quaternion<floattype> q =
        Eigen::AngleAxis<floattype>(ypr[0], Eigen::Matrix<floattype, 1, 3>::UnitZ()) *
        Eigen::AngleAxis<floattype>(ypr[1], Eigen::Matrix<floattype, 1, 3>::UnitY()) *
        Eigen::AngleAxis<floattype>(ypr[2], Eigen::Matrix<floattype, 1, 3>::UnitX());

    // normalize quaterion
    q.normalize();

    return q;
}

/**
 * @brief create an eigen quaternion by rotating yaw (z axis), pitch (y axis) and roll (x axis)
 *
 * @tparam floattype floating point value
 * @param yaw rotation arround z axis [° or rad]
 * @param pitch rotation arround y axis [° or rad]
 * @param roll rotation arround x axis [° or rad]
 * @param input_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
 * @return Eigen::Quaternion<floattype>
 */
template<typename floattype>
Eigen::Quaternion<floattype> quaternion_from_ypr(floattype yaw,
                                                 floattype pitch,
                                                 floattype roll,
                                                 bool      input_in_degrees = true)
{
    std::array<floattype, 3> ypr = { yaw, pitch, roll };

    return quaternion_from_ypr(std::move(ypr), input_in_degrees);
}

template<typename floattype>
std::array<floattype, 3> ypr_from_quaternion(Eigen::Quaternion<floattype> q,
                                             bool                         output_to_degrees = true)
{
    q.normalize();

    auto                     Me  = q.toRotationMatrix().eulerAngles(2, 1, 0);
    std::array<floattype, 3> ypr = { Me[0], Me[1], Me[2] };

    /* pitch is constrained to -90° -> 89.9999°
     * otherwise there is two possibilites to reach every point.
     * because: rotate(yaw,pitch,roll) == rotate(yaw+pi,pi-pitch,roll+pi)
     * Also note: pitch = 90 degrees leads to a gimbal lock situation
     */
    ypr = normalize_angles_rad(ypr);

    static const floattype _ypr_from_quaternion_to_degrees = 180 / M_PI;
    if (output_to_degrees)
    {
        ypr[0] *= _ypr_from_quaternion_to_degrees;
        ypr[1] *= _ypr_from_quaternion_to_degrees;
        ypr[2] *= _ypr_from_quaternion_to_degrees;
    }

    return ypr;
}

// --- vectorized calls ---

template<typename floattype>
std::vector<Eigen::Quaternion<floattype>> quaternion_from_ypr(
    const std::vector<std::array<floattype, 3>>& YPR)
{
    std::vector<Eigen::Quaternion<floattype>> Q;
    Q.reserve(YPR.size());
    for (const auto ypr : YPR)
    {
        Q.push_back(quaternion_from_ypr(ypr));
    }

    return Q;
}

template<typename floattype>
std::vector<Eigen::Quaternion<floattype>> quaternion_from_ypr(const std::vector<floattype>& yaw,
                                                              const std::vector<floattype>& pitch,
                                                              const std::vector<floattype>& roll)
{
    if (yaw.size() != pitch.size() || yaw.size() != roll.size())
    {
        throw std::invalid_argument("ERROR[quaternion_from_ypr]: input vectors must have the same size!");
    }

    std::vector<Eigen::Quaternion<floattype>> Q;
    Q.reserve(yaw.size());
    for (unsigned int i = 0; i < yaw.size(); ++i)
    {
        Q.push_back(quaternion_from_ypr(yaw[i], pitch[i], roll[i]));
    }

    return Q;

}

template<typename floattype>
std::vector<std::array<floattype, 3>> ypr_from_quaternion(const std::vector<Eigen::Quaternion<floattype>>& Q)
{
    std::vector<std::array<floattype, 3>> YPR;
    YPR.reserve(Q.size());
    for (const auto& q : Q)
    {
        YPR.push_back(ypr_from_quaternion(q));
    }

    return YPR;
}

// /**
//  * @brief getQuaterniondfromVector: creates a Quaternion that holds the passed
//  * parameters x,y,z as a Vector
//  * @param x: x as double or float
//  * @param y: y as double or float
//  * @param z: z as double or float
//  * @param w: w as double or float with the default value 0.0
//  * @return returns the Quaternion that holds a vector
//  */
// template<typename floattype>
// Eigen::Quaternion<floattype> getQuaterniondfromVector(const floattype x,
//                                                       const floattype y,
//                                                       const floattype z,
//                                                       const floattype w = 0.0)
// {
//     Eigen::Vector3d              vec_to_rotate(x, y, z);
//     Eigen::Quaternion<floattype> vec_to_rotate_as_quat;
//     vec_to_rotate_as_quat.w()   = w;
//     vec_to_rotate_as_quat.vec() = vec_to_rotate;
//     return vec_to_rotate_as_quat;
// }

// /**
//  * @brief getQuaterniondfromVector: creates a Quaternion that holds the passed
//  * parameters x,y,z as a Vector
//  * @param xyz: x, y, z as Array<floattype, 3>
//  * @param w: w as double or float with the default value 0.0
//  * @return returns the Quaternion that holds a vector
//  */
// template<typename floattype>
// Eigen::Quaternion<floattype> getQuaterniondfromVector(const std::array<floattype, 3>& xyz,
//                                                       const floattype                 w = 0.0)
// {
//     return getQuaterniondfromVector(xyz[0], xyz[1], xyz[2], w);
// }

// template<typename floattype>
// std::vector<floattype> get_quaternion_wxyz(const Eigen::Quaternion<floattype>& q)
// {
//     return { q.w(), q.x(), q.y(), q.z() };
// }

} // namespace rotationfunctions
} // namespace tools
} // namespace themachinethatgoesping
