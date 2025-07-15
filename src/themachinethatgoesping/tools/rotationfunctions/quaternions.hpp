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
#include ".docstrings/quaternions.doc.hpp"

// #define _USE_MATH_DEFINES // for C++ // windows // this is not necessary
#include <cmath>

#include <Eigen/Core>
#include <Eigen/Eigen>
#include <Eigen/Geometry>
#include <array>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "helper.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace rotationfunctions {

// this is a workaround
// pybind11_mkdoc to failed on functions with Eigen::Quaternion as argument
template<std::floating_point t_float>
using EigenQuaternion = Eigen::Quaternion<t_float>;

/**
 * @brief create an eigen quaternion by rotating yaw (z axis), pitch (y axis) and roll (x axis)
 *
 * @tparam t_float
 * @param ypr array that contains yaw, pitch and roll value
 * @param input_in_degrees if true, yaw, pitch and roll input values are in ° otherwise rad
 * @return EigenQuaternion<t_float>
 */
template<std::floating_point t_float>
EigenQuaternion<t_float> quaternion_from_ypr(std::array<t_float, 3> ypr,
                                             bool                   input_in_degrees = true)
{
    static const t_float _quaternion_from_ypr_to_rad = M_PI / 180.;

    // check if values are valid
    if (!std::isfinite(ypr[0]) || !std::isfinite(ypr[1]) || !std::isfinite(ypr[2]))
    {
        throw std::invalid_argument(
            "ERROR[quaternion_from_ypr]: NAN or INFINITY yaw, pitch or roll value!");
    }

    // convert to rad
    if (input_in_degrees)
    {
        ypr[0] *= _quaternion_from_ypr_to_rad;
        ypr[1] *= _quaternion_from_ypr_to_rad;
        ypr[2] *= _quaternion_from_ypr_to_rad;
    }

    // create quaternion by rotating around axes first, yaw, then pitch, then roll
    EigenQuaternion<t_float> q =
        Eigen::AngleAxis<t_float>(ypr[0], Eigen::Matrix<t_float, 1, 3>::UnitZ()) *
        Eigen::AngleAxis<t_float>(ypr[1], Eigen::Matrix<t_float, 1, 3>::UnitY()) *
        Eigen::AngleAxis<t_float>(ypr[2], Eigen::Matrix<t_float, 1, 3>::UnitX());

    // normalize quaternion
    q.normalize();

    return q;
}

/**
 * @brief create an eigen quaternion by rotating roll (x axis), pitch (y axis) and yaw (z axis)
 *
 * @tparam t_float
 * @param rpy array that contains roll, pitch and yaw value
 * @param input_in_degrees if true, roll, pitch and roll input values are in ° otherwise rad
 * @return EigenQuaternion<t_float>
 */
template<std::floating_point t_float>
EigenQuaternion<t_float> quaternion_from_rpy(std::array<t_float, 3> rpy,
                                             bool                   input_in_degrees = true)
{
    static const t_float _quaternion_from_rpy_to_rad = M_PI / 180.;

    // check if values are valid
    if (!std::isfinite(rpy[0]) || !std::isfinite(rpy[1]) || !std::isfinite(rpy[2]))
    {
        throw std::invalid_argument(
            "ERROR[quaternion_from_rpy]: NAN or INFINITY yaw, pitch or roll value!");
    }

    // convert to rad
    if (input_in_degrees)
    {
        rpy[0] *= _quaternion_from_rpy_to_rad;
        rpy[1] *= _quaternion_from_rpy_to_rad;
        rpy[2] *= _quaternion_from_rpy_to_rad;
    }

    // create quaternion by rotating around axes first, yaw, then pitch, then roll
    EigenQuaternion<t_float> q =
        Eigen::AngleAxis<t_float>(rpy[0], Eigen::Matrix<t_float, 1, 3>::UnitX()) *
        Eigen::AngleAxis<t_float>(rpy[1], Eigen::Matrix<t_float, 1, 3>::UnitY()) *
        Eigen::AngleAxis<t_float>(rpy[2], Eigen::Matrix<t_float, 1, 3>::UnitZ());

    // normalize quaternion
    q.normalize();

    return q;
}

/**
 * @brief create an eigen quaternion by rotating yaw (z axis), pitch (y axis) and roll (x axis)
 *
 * @tparam t_float floating point value
 * @param yaw rotation around z axis [° or rad]
 * @param pitch rotation around y axis [° or rad]
 * @param roll rotation around x axis [° or rad]
 * @param input_in_degrees if true, yaw, pitch and roll input values are in ° otherwise rad
 * @return EigenQuaternion<t_float>
 */
template<std::floating_point t_float>
EigenQuaternion<t_float> quaternion_from_ypr(t_float yaw,
                                             t_float pitch,
                                             t_float roll,
                                             bool    input_in_degrees = true)
{
    std::array<t_float, 3> ypr = { yaw, pitch, roll };

    return quaternion_from_ypr(std::move(ypr), input_in_degrees);
}

/**
 * @brief create an eigen quaternion by rotating roll (x axis), pitch (y axis) and yaw (z axis)
 *
 * @tparam t_float floating point value
 * @param roll rotation around x axis [° or rad]
 * @param pitch rotation around y axis [° or rad]
 * @param yaw rotation around z axis [° or rad]
 * @param input_in_degrees if true, roll, pitch and roll input values are in ° otherwise rad
 * @return EigenQuaternion<t_float>
 */
template<std::floating_point t_float>
EigenQuaternion<t_float> quaternion_from_rpy(t_float roll,
                                             t_float pitch,
                                             t_float yaw,
                                             bool    input_in_degrees = true)
{
    std::array<t_float, 3> rpy = { roll, pitch, yaw };

    return quaternion_from_rpy(std::move(rpy), input_in_degrees);
}

/**
 * @brief Convert quaternion to yaw, pitch and roll
 *
 * @tparam t_float
 * @param q quaternion
 * @param output_to_degrees  if true, yaw, pitch and roll input values are in ° otherwise rad
 * @return std::array<t_float, 3> yaw, pitch and roll
 */
template<std::floating_point t_float>
std::array<t_float, 3> ypr_from_quaternion(EigenQuaternion<t_float> q,
                                           bool                     output_to_degrees = true)
{
    q.normalize();

    auto                   Me  = q.toRotationMatrix().eulerAngles(2, 1, 0);
    std::array<t_float, 3> ypr = { Me[0], Me[1], Me[2] };

    /* pitch is constrained to -90° -> 89.9999°
     * otherwise there is two possibilities to reach every point.
     * because: rotate(yaw,pitch,roll) == rotate(yaw+pi,pi-pitch,roll+pi)
     * Also note: pitch = 90 degrees leads to a gimbal lock situation
     */
    ypr = normalize_angles_rad(ypr);

    static const t_float _ypr_from_quaternion_to_degrees = 180 / M_PI;
    if (output_to_degrees)
    {
        ypr[0] *= _ypr_from_quaternion_to_degrees;
        ypr[1] *= _ypr_from_quaternion_to_degrees;
        ypr[2] *= _ypr_from_quaternion_to_degrees;
    }

    return ypr;
}

/**
 * @brief Convert quaternion to roll, pitch and yaw
 *
 * @tparam t_float
 * @param q quaternion
 * @param output_to_degrees  if true, roll, pitch and yaw input values are in ° otherwise rad
 * @return std::array<t_float, 3> roll, pitch and yaw
 */
template<std::floating_point t_float>
std::array<t_float, 3> rpy_from_quaternion(EigenQuaternion<t_float> q,
                                           bool                     output_to_degrees = true)
{
    q.normalize();

    auto                   Me  = q.toRotationMatrix().eulerAngles(0, 1, 2);
    std::array<t_float, 3> rpy = { Me[0], Me[1], Me[2] };

    /* pitch is constrained to -90° -> 89.9999°
     * otherwise there is two possibilities to reach every point.
     * because: rotate(yaw,pitch,roll) == rotate(yaw+pi,pi-pitch,roll+pi)
     * Also note: pitch = 90 degrees leads to a gimbal lock situation
     */
    rpy = normalize_angles_rad(rpy);

    static const t_float _rpy_from_quaternion_to_degrees = 180 / M_PI;
    if (output_to_degrees)
    {
        rpy[0] *= _rpy_from_quaternion_to_degrees;
        rpy[1] *= _rpy_from_quaternion_to_degrees;
        rpy[2] *= _rpy_from_quaternion_to_degrees;
    }

    return rpy;
}
// --- vectorized calls ---

/**
 * @brief create eigen quaternions by rotating yaw (z axis), pitch (y axis) and roll (x axis)
 values
 * (vectorized call)
 *
 * @tparam t_float floating point value
 * @param YPR vector of yaw, pitch and roll rotation values [° or rad]
 * @param input_in_degrees if true, yaw, pitch and roll input values are in ° otherwise rad
 * @return std::vector<EigenQuaternion<t_float>>
 */
template<std::floating_point t_float>
std::vector<EigenQuaternion<t_float>> quaternion_from_ypr(
    const std::vector<std::array<t_float, 3>>& YPR,
    bool                                       input_in_degrees = true)
{
    std::vector<EigenQuaternion<t_float>> Q;
    Q.reserve(YPR.size());
    for (const auto ypr : YPR)
    {
        Q.push_back(quaternion_from_ypr(ypr, input_in_degrees));
    }

    return Q;
}

/**
 * @brief create eigen quaternions by rotating roll (x axis), pitch (y axis) and yaw (z axis)
 values
 * (vectorized call)
 *
 * @tparam t_float floating point value
 * @param RPY vector of roll, pitch and yaw rotation values [° or rad]
 * @param input_in_degrees if true, roll, pitch and yaw input values are in ° otherwise rad
 * @return std::vector<EigenQuaternion<t_float>>
 */
template<std::floating_point t_float>
std::vector<EigenQuaternion<t_float>> quaternion_from_rpy(
    const std::vector<std::array<t_float, 3>>& RPY,
    bool                                       input_in_degrees = true)
{
    std::vector<EigenQuaternion<t_float>> Q;
    Q.reserve(RPY.size());
    for (const auto rpy : RPY)
    {
        Q.push_back(quaternion_from_rpy(rpy, input_in_degrees));
    }

    return Q;
}

/**
 * @brief create eigen quaternions by rotating yaw (z axis), pitch (y axis) and roll (x axis)
 values
 * (vectorized call)
 *
 * @tparam t_float
 * @tparam t_float floating point value
 * @param yaw vector of rotation values around the z axis [° or rad]
 * @param pitch vector of rotation values the y axis [° or rad]
 * @param roll of rotation values the x axis [° or rad]
 * @param input_in_degrees if true, yaw, pitch and roll input values are in ° otherwise rad
 * @return std::vector<EigenQuaternion<t_float>>
 */
template<std::floating_point t_float>
std::vector<EigenQuaternion<t_float>> quaternion_from_ypr(const std::vector<t_float>& yaw,
                                                          const std::vector<t_float>& pitch,
                                                          const std::vector<t_float>& roll,
                                                          bool input_in_degrees = true)
{
    if (yaw.size() != pitch.size() || yaw.size() != roll.size())
    {
        throw std::invalid_argument(
            "ERROR[quaternion_from_ypr]: input vectors must have the same size!");
    }

    std::vector<EigenQuaternion<t_float>> Q;
    Q.reserve(yaw.size());
    for (size_t i = 0; i < yaw.size(); ++i)
    {
        Q.push_back(quaternion_from_ypr(yaw[i], pitch[i], roll[i], input_in_degrees));
    }

    return Q;
}

/**
 * @brief create eigen quaternions by rotating roll (x axis), pitch (y axis) and yaw (z axis)
 values
 * (vectorized call)
 *
 * @tparam t_float
 * @tparam t_float floating point value
 * @param roll of rotation values the x axis [° or rad]
 * @param pitch vector of rotation values the y axis [° or rad]
 * @param yaw vector of rotation values around the z axis [° or rad]
 * @param input_in_degrees if true, roll, pitch and yaw input values are in ° otherwise rad
 * @return std::vector<EigenQuaternion<t_float>>
 */
template<std::floating_point t_float>
std::vector<EigenQuaternion<t_float>> quaternion_from_rpy(const std::vector<t_float>& roll,
                                                          const std::vector<t_float>& pitch,
                                                          const std::vector<t_float>& yaw,
                                                          bool input_in_degrees = true)
{
    if (yaw.size() != pitch.size() || yaw.size() != roll.size())
    {
        throw std::invalid_argument(
            "ERROR[quaternion_from_rpy]: input vectors must have the same size!");
    }

    std::vector<EigenQuaternion<t_float>> Q;
    Q.reserve(yaw.size());
    for (size_t i = 0; i < yaw.size(); ++i)
    {
        Q.push_back(quaternion_from_rpy(roll[i], pitch[i], yaw[i], input_in_degrees));
    }

    return Q;
}

/**
 * @brief Convert quaternions to yaw, pitch and roll values (vectorized call)
 *
 * @tparam t_float
 * @param Q vector of quaternions
 * @param output_to_degrees  if true, yaw, pitch and roll input values are in ° otherwise rad
 * @return std::vector<std::array<t_float, 3>>
 */
template<std::floating_point t_float>
std::vector<std::array<t_float, 3>> ypr_from_quaternion(
    const std::vector<EigenQuaternion<t_float>>& Q,
    bool                                         output_to_degrees = true)
{
    std::vector<std::array<t_float, 3>> YPR;
    YPR.resize(Q.size());

    for (unsigned int i = 0; i < Q.size(); ++i)
    {
        YPR[i] = ypr_from_quaternion(Q[i], output_to_degrees);
    }

    return YPR;
}

/**
 * @brief Convert quaternions to roll, pitch and yaw values (vectorized call)
 *
 * @tparam t_float
 * @param Q vector of quaternions
 * @param output_to_degrees  if true, roll, pitch and yaw input values are in ° otherwise rad
 * @return std::vector<std::array<t_float, 3>>
 */
template<std::floating_point t_float>
std::vector<std::array<t_float, 3>> rpy_from_quaternion(
    const std::vector<EigenQuaternion<t_float>>& Q,
    bool                                         output_to_degrees = true)
{
    std::vector<std::array<t_float, 3>> RPY;
    RPY.resize(Q.size());

    for (unsigned int i = 0; i < Q.size(); ++i)
    {
        RPY[i] = rpy_from_quaternion(Q[i], output_to_degrees);
    }

    return RPY;
}

/// ---- untested ////
/**
 * @brief get_quaternion_from_vector: creates a Quaternion that holds the passed
 * parameters x,y,z as a Vector
 * @param x: x as double or float
 * @param y: y as double or float
 * @param z: z as double or float
 * @param w: w as double or float with the default value 0.0
 * @return returns the Quaternion that holds a vector
 */
template<std::floating_point t_float>
EigenQuaternion<t_float> get_quaternion_from_vector(t_float x,
                                                    t_float y,
                                                    t_float z,
                                                    t_float w = 0.0)
{
    Eigen::Vector3<t_float>  vec_to_rotate(x, y, z);
    EigenQuaternion<t_float> vec_to_rotate_as_quat;
    vec_to_rotate_as_quat.w()   = w;
    vec_to_rotate_as_quat.vec() = vec_to_rotate;
    return vec_to_rotate_as_quat;
}

/**
 * @brief get_quaternion_from_vector: creates a Quaternion that holds the passed
 * parameters x,y,z as a Vector
 * @param xyz: x, y, z as Array<t_float, 3>
 * @param w: w as double or float with the default value 0.0
 * @return returns the Quaternion that holds a vector
 */
template<std::floating_point t_float>
EigenQuaternion<t_float> get_quaternion_from_vector(const std::array<t_float, 3>& xyz,
                                                    const t_float                 w = 0.0)
{
    return get_quaternion_from_vector(xyz[0], xyz[1], xyz[2], w);
}

template<std::floating_point t_float>
std::vector<t_float> get_quaternion_wxyz(const EigenQuaternion<t_float>& q)
{
    return { q.w(), q.x(), q.y(), q.z() };
}

/**
 * @brief OVERLOADED rotateXYZ: rotates a x,y,z vector with the passed
 * parameters roll, pitch, yaw as a Quaternion
 * @param q: roll, pitch, yaw as Quaternion<t_float>
 * @param x: x as double
 * @param y: y as double
 * @param z: z as double
 * @return returns vector with rotated xyz
 */
template<std::floating_point t_float>
Eigen::Vector3<t_float> rotateXYZ(EigenQuaternion<t_float> q, t_float x, t_float y, t_float z)
{
    q.normalize();

    EigenQuaternion<t_float> vec_to_rotate_as_quat = get_quaternion_from_vector(x, y, z);

    EigenQuaternion<t_float> rotated_quaternion = q * vec_to_rotate_as_quat * q.inverse();

    Eigen::Vector3<t_float> rotatedV = rotated_quaternion.vec();

    return rotatedV;
}

/**
 * @brief OVERLOADED rotateXYZ: rotates a x,y,z vector as a Quaternion with the
 * passed parameters roll, pitch, yaw as a Quaternion
 * @param q: roll, pitch, yaw as Quaternion<t_float>
 * @param v: x, y, z as Quaternion<t_float>
 * @return returns vector with rotated xyz
 */
template<std::floating_point t_float>
Eigen::Vector3<t_float> rotateXYZ(EigenQuaternion<t_float> q, EigenQuaternion<t_float> v)
{
    q.normalize();

    EigenQuaternion<t_float> rotated_quaternion = q * v * q.inverse();

    Eigen::Vector3<t_float> rotatedV = rotated_quaternion.vec();

    return rotatedV;
}

} // namespace rotationfunctions
} // namespace tools
} // namespace themachinethatgoesping
