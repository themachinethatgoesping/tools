//sourcehash: 09ccde5c20c7a876f75815a6ae1338ac24e3b995a4e3d0274820ecc5ae271fb9

/*
  This file contains docstrings for use in the Python bindings.
  Do not edit! They were automatically extracted by pybind11_mkdoc.

  This is a modified version which allows for more than 8 arguments and includes def-guard
 */

#pragma once

#ifndef __DOCSTRINGS_HPP__
#define __DOCSTRINGS_HPP__

#define MKD_EXPAND(x)                                      x
#define MKD_COUNT(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, COUNT, ...)  COUNT
#define MKD_VA_SIZE(...)                                   MKD_EXPAND(MKD_COUNT(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define MKD_CAT1(a, b)                                     a ## b
#define MKD_CAT2(a, b)                                     MKD_CAT1(a, b)
#define MKD_DOC1(n1)                                       mkd_doc_##n1
#define MKD_DOC2(n1, n2)                                   mkd_doc_##n1##_##n2
#define MKD_DOC3(n1, n2, n3)                               mkd_doc_##n1##_##n2##_##n3
#define MKD_DOC4(n1, n2, n3, n4)                           mkd_doc_##n1##_##n2##_##n3##_##n4
#define MKD_DOC5(n1, n2, n3, n4, n5)                       mkd_doc_##n1##_##n2##_##n3##_##n4##_##n5
#define MKD_DOC6(n1, n2, n3, n4, n5, n6)                   mkd_doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6
#define MKD_DOC7(n1, n2, n3, n4, n5, n6, n7)               mkd_doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7
#define MKD_DOC8(n1, n2, n3, n4, n5, n6, n7, n8)           mkd_doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7##_##n8
#define MKD_DOC9(n1, n2, n3, n4, n5, n6, n7, n8, n9)       mkd_doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7##_##n8##_##n9
#define MKD_DOC10(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10) mkd_doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7##_##n8##_##n9##_##n10
#define DOC(...)                                           MKD_EXPAND(MKD_EXPAND(MKD_CAT2(MKD_DOC, MKD_VA_SIZE(__VA_ARGS__)))(__VA_ARGS__))

#if defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif

#endif // __DOCSTRINGS_HPP__
#if defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif


static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_adapt_xtensor_to_eigen =
R"doc(Const (read-only) overload of adapt_xtensor_to_eigen.

Args:
    xyz: row-major [n, 3] xtensor

Template Args:
    t_float: floating point type

Returns:
    read-only Eigen::Map sharing storage with ``xyz``)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_get_quaternion_from_vector =
R"doc(Create a quaternion that stores a 3D vector (x, y, z) in its imaginary
part and w.

Args:
    x: X component
    y: Y component
    z: Z component
    w: W component (default 0)

Template Args:
    t_float: floating point type

Returns:
    quaternion [w, x, y, z])doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_get_quaternion_from_vector_2 =
R"doc(Create a quaternion that stores a 3D vector (x, y, z) in its imaginary
part and w.

Args:
    xyz: array {x, y, z}
    w: W component (default 0)

Template Args:
    t_float: floating point type

Returns:
    quaternion [w, x, y, z])doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_get_quaternion_wxyz =
R"doc(Extract [w, x, y, z] as a std::vector from a quaternion.

Template Args:
    t_float: floating point type)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_rpy =
R"doc(Create an Eigen quaternion by rotating roll (X), pitch (Y) and yaw
(Z).

Args:
    rpy: array containing roll, pitch, yaw
    input_in_degrees: if true, inputs are degrees; otherwise radians

Template Args:
    t_float: floating point type

Returns:
    EigenQuaternion<t_float>)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_rpy_2 =
R"doc(Create an Eigen quaternion by rotating roll (X), pitch (Y) and yaw
(Z).

Args:
    roll: rotation around X [deg or rad]
    pitch: rotation around Y [deg or rad]
    yaw: rotation around Z [deg or rad]
    input_in_degrees: if true, inputs are degrees; otherwise radians

Template Args:
    t_float: floating point type

Returns:
    EigenQuaternion<t_float>)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_rpy_3 =
R"doc(Vectorized: create quaternions from roll/pitch/yaw triplets.

Args:
    RPY: vector of {roll, pitch, yaw} [deg or rad]
    input_in_degrees: if true, inputs are degrees; otherwise radians

Template Args:
    t_float: floating point type)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_rpy_4 =
R"doc(Vectorized: create quaternions from separate roll/pitch/yaw vectors.

Args:
    roll: rotations around X [deg or rad]
    pitch: rotations around Y [deg or rad]
    yaw: rotations around Z [deg or rad]
    input_in_degrees: if true, inputs are degrees; otherwise radians

Template Args:
    t_float: floating point type)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_ypr =
R"doc(Create an Eigen quaternion by rotating yaw (Z), pitch (Y) and roll
(X).

Args:
    ypr: array containing yaw, pitch, roll
    input_in_degrees: if true, inputs are degrees; otherwise radians

Template Args:
    t_float: floating point type

Returns:
    EigenQuaternion<t_float>)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_ypr_2 =
R"doc(Create an Eigen quaternion by rotating yaw (Z), pitch (Y) and roll
(X).

Args:
    yaw: rotation around Z [deg or rad]
    pitch: rotation around Y [deg or rad]
    roll: rotation around X [deg or rad]
    input_in_degrees: if true, inputs are degrees; otherwise radians

Template Args:
    t_float: floating point type

Returns:
    EigenQuaternion<t_float>)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_ypr_3 =
R"doc(Vectorized: create quaternions from yaw/pitch/roll triplets.

Args:
    YPR: vector of {yaw, pitch, roll} [deg or rad]
    input_in_degrees: if true, inputs are degrees; otherwise radians

Template Args:
    t_float: floating point type)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_ypr_4 =
R"doc(Vectorized: create quaternions from separate yaw/pitch/roll vectors.

Args:
    yaw: rotations around Z [deg or rad]
    pitch: rotations around Y [deg or rad]
    roll: rotations around X [deg or rad]
    input_in_degrees: if true, inputs are degrees; otherwise radians

Template Args:
    t_float: floating point type)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_rotateXYZ =
R"doc(Rotate a 3D vector (x, y, z) by quaternion q.

Template Args:
    t_float: floating point type

Returns:
    rotated vector)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_rotateXYZ_2 =
R"doc(Rotate a quaternion-encoded vector v by quaternion q.

Template Args:
    t_float: floating point type

Returns:
    rotated vector)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_rotateXYZ_3 =
R"doc(Vectorized: rotate a single vector by each quaternion in a batch.

Args:
    quaternions: per-element rotation quaternions (length n)
    x: X component of the vector to rotate
    y: Y component of the vector to rotate
    z: Z component of the vector to rotate

Template Args:
    t_float: floating point type

Returns:
    [n, 3] tensor; row i is quaternions[i] applied to (x, y, z))doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_rpy_from_quaternion =
R"doc(Convert quaternion to roll, pitch, yaw.

Pitch is constrained to [-90°, 90°) to avoid ambiguities and gimbal
lock notes apply.

Args:
    q: quaternion
    output_to_degrees: if true, outputs are degrees; otherwise radians

Template Args:
    t_float: floating point type

Returns:
    {roll, pitch, yaw})doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_rpy_from_quaternion_2 =
R"doc(Vectorized: convert quaternions to roll/pitch/yaw.

Args:
    Q: vector of quaternions
    output_to_degrees: if true, outputs are degrees; otherwise radians

Template Args:
    t_float: floating point type)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_ypr_from_quaternion =
R"doc(Convert quaternion to yaw, pitch, roll.

Pitch is constrained to [-90°, 90°) to avoid ambiguities and gimbal
lock notes apply.

Args:
    q: quaternion
    output_to_degrees: if true, outputs are degrees; otherwise radians

Template Args:
    t_float: floating point type

Returns:
    {yaw, pitch, roll})doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_ypr_from_quaternion_2 =
R"doc(Vectorized: convert quaternions to yaw/pitch/roll.

Args:
    Q: vector of quaternions
    output_to_degrees: if true, outputs are degrees; otherwise radians

Template Args:
    t_float: floating point type)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


