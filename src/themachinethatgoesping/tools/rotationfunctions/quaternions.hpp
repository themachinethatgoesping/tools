// SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief Convenience functions to create Eigen quaternions from yaw/pitch/roll values.
 * Rotations are applied in this order: 1) yaw (Z), 2) pitch (Y), 3) roll (X).
 *
 * Authors: Peter Urban, Sven Schorge
 */

#pragma once

/* generated doc strings */
#include ".docstrings/quaternions.doc.hpp"

#include <concepts>
#include <array>
#include <vector>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <xtensor/containers/xadapt.hpp>
#include <xtensor/containers/xtensor.hpp>

#include "helper.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace rotationfunctions {

// Workaround alias: nanobind doc generation is fragile with Eigen::Quaternion in signatures.
template<std::floating_point t_float>
using EigenQuaternion = Eigen::Quaternion<t_float>;

/**
 * @brief Create an Eigen quaternion by rotating yaw (Z), pitch (Y) and roll (X).
 *
 * @tparam t_float floating point type
 * @param ypr array containing yaw, pitch, roll
 * @param input_in_degrees if true, inputs are degrees; otherwise radians
 * @return EigenQuaternion<t_float>
 */
template<std::floating_point t_float>
EigenQuaternion<t_float> quaternion_from_ypr(std::array<t_float, 3> ypr,
                                             bool                   input_in_degrees = true);

/**
 * @brief Create an Eigen quaternion by rotating roll (X), pitch (Y) and yaw (Z).
 *
 * @tparam t_float floating point type
 * @param rpy array containing roll, pitch, yaw
 * @param input_in_degrees if true, inputs are degrees; otherwise radians
 * @return EigenQuaternion<t_float>
 */
template<std::floating_point t_float>
EigenQuaternion<t_float> quaternion_from_rpy(std::array<t_float, 3> rpy,
                                             bool                   input_in_degrees = true);

/**
 * @brief Create an Eigen quaternion by rotating yaw (Z), pitch (Y) and roll (X).
 *
 * @tparam t_float floating point type
 * @param yaw rotation around Z [deg or rad]
 * @param pitch rotation around Y [deg or rad]
 * @param roll rotation around X [deg or rad]
 * @param input_in_degrees if true, inputs are degrees; otherwise radians
 * @return EigenQuaternion<t_float>
 */
template<std::floating_point t_float>
EigenQuaternion<t_float> quaternion_from_ypr(t_float yaw,
                                             t_float pitch,
                                             t_float roll,
                                             bool    input_in_degrees = true);

/**
 * @brief Create an Eigen quaternion by rotating roll (X), pitch (Y) and yaw (Z).
 *
 * @tparam t_float floating point type
 * @param roll rotation around X [deg or rad]
 * @param pitch rotation around Y [deg or rad]
 * @param yaw rotation around Z [deg or rad]
 * @param input_in_degrees if true, inputs are degrees; otherwise radians
 * @return EigenQuaternion<t_float>
 */
template<std::floating_point t_float>
EigenQuaternion<t_float> quaternion_from_rpy(t_float roll,
                                             t_float pitch,
                                             t_float yaw,
                                             bool    input_in_degrees = true);

/**
 * @brief Convert quaternion to yaw, pitch, roll.
 *
 * Pitch is constrained to [-90°, 90°) to avoid ambiguities and gimbal lock notes apply.
 *
 * @tparam t_float floating point type
 * @param q quaternion
 * @param output_to_degrees if true, outputs are degrees; otherwise radians
 * @return {yaw, pitch, roll}
 */
template<std::floating_point t_float>
std::array<t_float, 3> ypr_from_quaternion(EigenQuaternion<t_float> q,
                                           bool                     output_to_degrees = true);

/**
 * @brief Convert quaternion to roll, pitch, yaw.
 *
 * Pitch is constrained to [-90°, 90°) to avoid ambiguities and gimbal lock notes apply.
 *
 * @tparam t_float floating point type
 * @param q quaternion
 * @param output_to_degrees if true, outputs are degrees; otherwise radians
 * @return {roll, pitch, yaw}
 */
template<std::floating_point t_float>
std::array<t_float, 3> rpy_from_quaternion(EigenQuaternion<t_float> q,
                                           bool                     output_to_degrees = true);

/**
 * @brief Vectorized: create quaternions from yaw/pitch/roll triplets.
 *
 * @tparam t_float floating point type
 * @param YPR vector of {yaw, pitch, roll} [deg or rad]
 * @param input_in_degrees if true, inputs are degrees; otherwise radians
 */
template<std::floating_point t_float>
std::vector<EigenQuaternion<t_float>> quaternion_from_ypr(
    const std::vector<std::array<t_float, 3>>& YPR,
    bool                                       input_in_degrees = true);

/**
 * @brief Vectorized: create quaternions from roll/pitch/yaw triplets.
 *
 * @tparam t_float floating point type
 * @param RPY vector of {roll, pitch, yaw} [deg or rad]
 * @param input_in_degrees if true, inputs are degrees; otherwise radians
 */
template<std::floating_point t_float>
std::vector<EigenQuaternion<t_float>> quaternion_from_rpy(
    const std::vector<std::array<t_float, 3>>& RPY,
    bool                                       input_in_degrees = true);

/**
 * @brief Vectorized: create quaternions from separate yaw/pitch/roll vectors.
 *
 * @tparam t_float floating point type
 * @param yaw rotations around Z [deg or rad]
 * @param pitch rotations around Y [deg or rad]
 * @param roll rotations around X [deg or rad]
 * @param input_in_degrees if true, inputs are degrees; otherwise radians
 */
template<std::floating_point t_float>
std::vector<EigenQuaternion<t_float>> quaternion_from_ypr(const std::vector<t_float>& yaw,
                                                          const std::vector<t_float>& pitch,
                                                          const std::vector<t_float>& roll,
                                                          bool input_in_degrees = true);

/**
 * @brief Vectorized: create quaternions from separate roll/pitch/yaw vectors.
 *
 * @tparam t_float floating point type
 * @param roll rotations around X [deg or rad]
 * @param pitch rotations around Y [deg or rad]
 * @param yaw rotations around Z [deg or rad]
 * @param input_in_degrees if true, inputs are degrees; otherwise radians
 */
template<std::floating_point t_float>
std::vector<EigenQuaternion<t_float>> quaternion_from_rpy(const std::vector<t_float>& roll,
                                                          const std::vector<t_float>& pitch,
                                                          const std::vector<t_float>& yaw,
                                                          bool input_in_degrees = true);

/**
 * @brief Vectorized: convert quaternions to yaw/pitch/roll.
 *
 * @tparam t_float floating point type
 * @param Q vector of quaternions
 * @param output_to_degrees if true, outputs are degrees; otherwise radians
 */
template<std::floating_point t_float>
std::vector<std::array<t_float, 3>> ypr_from_quaternion(
    const std::vector<EigenQuaternion<t_float>>& Q,
    bool                                         output_to_degrees = true);

/**
 * @brief Vectorized: convert quaternions to roll/pitch/yaw.
 *
 * @tparam t_float floating point type
 * @param Q vector of quaternions
 * @param output_to_degrees if true, outputs are degrees; otherwise radians
 */
template<std::floating_point t_float>
std::vector<std::array<t_float, 3>> rpy_from_quaternion(
    const std::vector<EigenQuaternion<t_float>>& Q,
    bool                                         output_to_degrees = true);

/**
 * @brief Create a quaternion that stores a 3D vector (x, y, z) in its imaginary part and w.
 *
 * @tparam t_float floating point type
 * @param x X component
 * @param y Y component
 * @param z Z component
 * @param w W component (default 0)
 * @return quaternion [w, x, y, z]
 */
template<std::floating_point t_float>
EigenQuaternion<t_float> get_quaternion_from_vector(t_float x,
                                                    t_float y,
                                                    t_float z,
                                                    t_float w = static_cast<t_float>(0));

/**
 * @brief Create a quaternion that stores a 3D vector (x, y, z) in its imaginary part and w.
 *
 * @tparam t_float floating point type
 * @param xyz array {x, y, z}
 * @param w W component (default 0)
 * @return quaternion [w, x, y, z]
 */
template<std::floating_point t_float>
EigenQuaternion<t_float> get_quaternion_from_vector(const std::array<t_float, 3>& xyz,
                                                    t_float                         w = static_cast<t_float>(0));

/**
 * @brief Extract [w, x, y, z] as a std::vector from a quaternion.
 *
 * @tparam t_float floating point type
 */
template<std::floating_point t_float>
std::vector<t_float> get_quaternion_wxyz(const EigenQuaternion<t_float>& q);

/**
 * @brief Rotate a 3D vector (x, y, z) by quaternion q.
 *
 * @tparam t_float floating point type
 * @return rotated vector
 */
template<std::floating_point t_float>
Eigen::Matrix<t_float, 3, 1> rotateXYZ(EigenQuaternion<t_float> q, t_float x, t_float y, t_float z);

/**
 * @brief Rotate a quaternion-encoded vector v by quaternion q.
 *
 * @tparam t_float floating point type
 * @return rotated vector
 */
template<std::floating_point t_float>
Eigen::Matrix<t_float, 3, 1> rotateXYZ(EigenQuaternion<t_float> q, EigenQuaternion<t_float> v);

/**
 * @brief Vectorized: rotate a single vector by each quaternion in a batch.
 *
 * @tparam t_float floating point type
 * @param quaternions per-element rotation quaternions (length n)
 * @param x X component of the vector to rotate
 * @param y Y component of the vector to rotate
 * @param z Z component of the vector to rotate
 * @return [n, 3] tensor; row i is quaternions[i] applied to (x, y, z)
 */
template<std::floating_point t_float>
xt::xtensor<t_float, 2> rotateXYZ(const std::vector<EigenQuaternion<t_float>>& quaternions,
                                  t_float                                      x,
                                  t_float                                      y,
                                  t_float                                      z);

// ----- Eigen <-> xtensor zero-copy adapters -----

/**
 * @brief View a row-major [n, 3] xtensor as an Eigen matrix (zero copy).
 *
 * The returned Eigen::Map shares storage with @p xyz, so writes through it modify
 * the xtensor directly. Handy to run batched Eigen (quaternion) vector math and
 * write the result straight into an xtensor output buffer without extra copies.
 *
 * @tparam t_float floating point type
 * @param xyz row-major [n, 3] xtensor
 * @return Eigen::Map sharing storage with @p xyz
 */
template<std::floating_point t_float>
inline Eigen::Map<Eigen::Matrix<t_float, Eigen::Dynamic, 3, Eigen::RowMajor>> adapt_xtensor_to_eigen(
    xt::xtensor<t_float, 2>& xyz)
{
    return Eigen::Map<Eigen::Matrix<t_float, Eigen::Dynamic, 3, Eigen::RowMajor>>(
        xyz.data(), static_cast<Eigen::Index>(xyz.shape(0)), 3);
}

/**
 * @brief Const (read-only) overload of adapt_xtensor_to_eigen.
 *
 * @tparam t_float floating point type
 * @param xyz row-major [n, 3] xtensor
 * @return read-only Eigen::Map sharing storage with @p xyz
 */
template<std::floating_point t_float>
inline Eigen::Map<const Eigen::Matrix<t_float, Eigen::Dynamic, 3, Eigen::RowMajor>>
adapt_xtensor_to_eigen(const xt::xtensor<t_float, 2>& xyz)
{
    return Eigen::Map<const Eigen::Matrix<t_float, Eigen::Dynamic, 3, Eigen::RowMajor>>(
        xyz.data(), static_cast<Eigen::Index>(xyz.shape(0)), 3);
}

/**
 * @brief View a row-major Eigen [n, 3] matrix as an [n, 3] xtensor (zero copy).
 *
 * The matrix must be row-major and outlive the returned view.
 *
 * @tparam t_float floating point type
 * @param xyz row-major Eigen [n, 3] matrix
 * @return xtensor view sharing storage with @p xyz
 */
template<std::floating_point t_float>
inline auto adapt_eigen_to_xtensor(Eigen::Matrix<t_float, Eigen::Dynamic, 3, Eigen::RowMajor>& xyz)
{
    return xt::adapt(xyz.data(),
                     static_cast<size_t>(xyz.size()),
                     xt::no_ownership(),
                     std::array<size_t, 2>{ static_cast<size_t>(xyz.rows()), size_t(3) });
}

} // namespace rotationfunctions
} // namespace tools
} // namespace themachinethatgoesping
