//sourcehash: 225af996dafbd4d5aa862ed5a78ed93884eaa8b89c53abd41a3526bc3e4b02ed

/*
  This file contains docstrings for use in the Python bindings.
  Do not edit! They were automatically extracted by pybind11_mkdoc.

  This is a modified version which allows for more than 8 arguments and includes def-guard
 */

#pragma once

#ifndef __DOCSTRINGS_TOOLS_ROTATIONFUNCTIONS_DOCSTRINGS_QUATERNIONS_DOC_HPP__

#define __EXPAND(x)                                                  x
#define __COUNT(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, COUNT, ...) COUNT
#define __VA_SIZE(...)                                               __EXPAND(__COUNT(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1))
#define __CAT1(a, b)                                                 a##b
#define __CAT2(a, b)                                                 __CAT1(a, b)
#define __DOC1(n1)                                                   __doc_##n1
#define __DOC2(n1, n2)                                               __doc_##n1##_##n2
#define __DOC3(n1, n2, n3)                                           __doc_##n1##_##n2##_##n3
#define __DOC4(n1, n2, n3, n4)                                       __doc_##n1##_##n2##_##n3##_##n4
#define __DOC5(n1, n2, n3, n4, n5)                                   __doc_##n1##_##n2##_##n3##_##n4##_##n5
#define __DOC6(n1, n2, n3, n4, n5, n6)                               __doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6
#define __DOC7(n1, n2, n3, n4, n5, n6, n7)                           __doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7
#define __DOC8(n1, n2, n3, n4, n5, n6, n7, n8)                                                     \
    __doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7##_##n8
#define __DOC9(n1, n2, n3, n4, n5, n6, n7, n8, n9)                                                 \
    __doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7##_##n8##_##n9
#define __DOC10(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10)                                           \
    __doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7##_##n8##_##n9##_##n10
#define DOC(...) __EXPAND(__EXPAND(__CAT2(__DOC, __VA_SIZE(__VA_ARGS__)))(__VA_ARGS__))

#endif // __DOCSTRINGS_TOOLS_ROTATIONFUNCTIONS_DOCSTRINGS_QUATERNIONS_DOC_HPP__
#if defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif


static const char *__doc_themachinethatgoesping_tools_rotationfunctions_get_quaternion_from_vector =
R"doc(Create a quaternion that stores a 3D vector (x, y, z) in its imaginary
part and w.

Template parameter ``t_float``:
    floating point type

Parameter ``x``:
    X component

Parameter ``y``:
    Y component

Parameter ``z``:
    Z component

Parameter ``w``:
    W component (default 0)

Returns:
    quaternion [w, x, y, z])doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_get_quaternion_from_vector_2 =
R"doc(Create a quaternion that stores a 3D vector (x, y, z) in its imaginary
part and w.

Template parameter ``t_float``:
    floating point type

Parameter ``xyz``:
    array {x, y, z}

Parameter ``w``:
    W component (default 0)

Returns:
    quaternion [w, x, y, z])doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_get_quaternion_wxyz =
R"doc(Extract [w, x, y, z] as a std::vector from a quaternion.

Template parameter ``t_float``:
    floating point type)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_rpy =
R"doc(Create an Eigen quaternion by rotating roll (X), pitch (Y) and yaw
(Z).

Template parameter ``t_float``:
    floating point type

Parameter ``rpy``:
    array containing roll, pitch, yaw

Parameter ``input_in_degrees``:
    if true, inputs are degrees; otherwise radians

Returns:
    EigenQuaternion<t_float>)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_rpy_2 =
R"doc(Create an Eigen quaternion by rotating roll (X), pitch (Y) and yaw
(Z).

Template parameter ``t_float``:
    floating point type

Parameter ``roll``:
    rotation around X [deg or rad]

Parameter ``pitch``:
    rotation around Y [deg or rad]

Parameter ``yaw``:
    rotation around Z [deg or rad]

Parameter ``input_in_degrees``:
    if true, inputs are degrees; otherwise radians

Returns:
    EigenQuaternion<t_float>)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_rpy_3 =
R"doc(Vectorized: create quaternions from roll/pitch/yaw triplets.

Template parameter ``t_float``:
    floating point type

Parameter ``RPY``:
    vector of {roll, pitch, yaw} [deg or rad]

Parameter ``input_in_degrees``:
    if true, inputs are degrees; otherwise radians)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_rpy_4 =
R"doc(Vectorized: create quaternions from separate roll/pitch/yaw vectors.

Template parameter ``t_float``:
    floating point type

Parameter ``roll``:
    rotations around X [deg or rad]

Parameter ``pitch``:
    rotations around Y [deg or rad]

Parameter ``yaw``:
    rotations around Z [deg or rad]

Parameter ``input_in_degrees``:
    if true, inputs are degrees; otherwise radians)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_ypr =
R"doc(Create an Eigen quaternion by rotating yaw (Z), pitch (Y) and roll
(X).

Template parameter ``t_float``:
    floating point type

Parameter ``ypr``:
    array containing yaw, pitch, roll

Parameter ``input_in_degrees``:
    if true, inputs are degrees; otherwise radians

Returns:
    EigenQuaternion<t_float>)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_ypr_2 =
R"doc(Create an Eigen quaternion by rotating yaw (Z), pitch (Y) and roll
(X).

Template parameter ``t_float``:
    floating point type

Parameter ``yaw``:
    rotation around Z [deg or rad]

Parameter ``pitch``:
    rotation around Y [deg or rad]

Parameter ``roll``:
    rotation around X [deg or rad]

Parameter ``input_in_degrees``:
    if true, inputs are degrees; otherwise radians

Returns:
    EigenQuaternion<t_float>)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_ypr_3 =
R"doc(Vectorized: create quaternions from yaw/pitch/roll triplets.

Template parameter ``t_float``:
    floating point type

Parameter ``YPR``:
    vector of {yaw, pitch, roll} [deg or rad]

Parameter ``input_in_degrees``:
    if true, inputs are degrees; otherwise radians)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_ypr_4 =
R"doc(Vectorized: create quaternions from separate yaw/pitch/roll vectors.

Template parameter ``t_float``:
    floating point type

Parameter ``yaw``:
    rotations around Z [deg or rad]

Parameter ``pitch``:
    rotations around Y [deg or rad]

Parameter ``roll``:
    rotations around X [deg or rad]

Parameter ``input_in_degrees``:
    if true, inputs are degrees; otherwise radians)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_rotateXYZ =
R"doc(Rotate a 3D vector (x, y, z) by quaternion q.

Template parameter ``t_float``:
    floating point type

Returns:
    rotated vector)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_rotateXYZ_2 =
R"doc(Rotate a quaternion-encoded vector v by quaternion q.

Template parameter ``t_float``:
    floating point type

Returns:
    rotated vector)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_rpy_from_quaternion =
R"doc(Convert quaternion to roll, pitch, yaw.

Pitch is constrained to [-90°, 90°) to avoid ambiguities and gimbal
lock notes apply.

Template parameter ``t_float``:
    floating point type

Parameter ``q``:
    quaternion

Parameter ``output_to_degrees``:
    if true, outputs are degrees; otherwise radians

Returns:
    {roll, pitch, yaw})doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_rpy_from_quaternion_2 =
R"doc(Vectorized: convert quaternions to roll/pitch/yaw.

Template parameter ``t_float``:
    floating point type

Parameter ``Q``:
    vector of quaternions

Parameter ``output_to_degrees``:
    if true, outputs are degrees; otherwise radians)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_ypr_from_quaternion =
R"doc(Convert quaternion to yaw, pitch, roll.

Pitch is constrained to [-90°, 90°) to avoid ambiguities and gimbal
lock notes apply.

Template parameter ``t_float``:
    floating point type

Parameter ``q``:
    quaternion

Parameter ``output_to_degrees``:
    if true, outputs are degrees; otherwise radians

Returns:
    {yaw, pitch, roll})doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_ypr_from_quaternion_2 =
R"doc(Vectorized: convert quaternions to yaw/pitch/roll.

Template parameter ``t_float``:
    floating point type

Parameter ``Q``:
    vector of quaternions

Parameter ``output_to_degrees``:
    if true, outputs are degrees; otherwise radians)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


