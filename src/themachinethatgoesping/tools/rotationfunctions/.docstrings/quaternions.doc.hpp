//sourcehash: d012b4b73a636ad74569ccd512d9c285079ebdbcbfe0760b99417299bde41abb

/*
  This file contains docstrings for use in the Python bindings.
  Do not edit! They were automatically extracted by pybind11_mkdoc.

  This is a modified version which allows for more than 8 arguments and includes def-guard
 */

#pragma once

#ifndef __DOCSTRINGS_HPP__

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

#endif // NEW_DOC_HEADER_HPP
#if defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif


static const char *__doc_themachinethatgoesping_tools_rotationfunctions_get_quaternion_from_vector =
R"doc(---- untested ////

get_quaternion_from_vector: creates a Quaternion that holds the passed
parameters x,y,z as a Vector

Parameter ``x:``:
    x as double or float

Parameter ``y:``:
    y as double or float

Parameter ``z:``:
    z as double or float

Parameter ``w:``:
    w as double or float with the default value 0.0

Returns:
    returns the Quaternion that holds a vector)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_get_quaternion_from_vector_2 =
R"doc(get_quaternion_from_vector: creates a Quaternion that holds the passed
parameters x,y,z as a Vector

Parameter ``xyz:``:
    x, y, z as Array<t_float, 3>

Parameter ``w:``:
    w as double or float with the default value 0.0

Returns:
    returns the Quaternion that holds a vector)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_get_quaternion_wxyz = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_rpy =
R"doc(create an eigen quaternion by rotating roll (x axis), pitch (y axis)
and yaw (z axis)

Template parameter ``t_float``:
    $Parameter ``rpy``:

array that contains roll, pitch and yaw value

Parameter ``input_in_degrees``:
    if true, roll, pitch and roll input values are in ° otherwise rad

Returns:
    EigenQuaternion<t_float>)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_rpy_2 =
R"doc(create an eigen quaternion by rotating roll (x axis), pitch (y axis)
and yaw (z axis)

Template parameter ``t_float``:
    floating point value

Parameter ``roll``:
    rotation around x axis [° or rad]

Parameter ``pitch``:
    rotation around y axis [° or rad]

Parameter ``yaw``:
    rotation around z axis [° or rad]

Parameter ``input_in_degrees``:
    if true, roll, pitch and roll input values are in ° otherwise rad

Returns:
    EigenQuaternion<t_float>)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_rpy_3 =
R"doc(create eigen quaternions by rotating roll (x axis), pitch (y axis) and
yaw (z axis) values (vectorized call)

Template parameter ``t_float``:
    floating point value

Parameter ``RPY``:
    vector of roll, pitch and yaw rotation values [° or rad]

Parameter ``input_in_degrees``:
    if true, roll, pitch and yaw input values are in ° otherwise rad

Returns:
    std::vector<EigenQuaternion<t_float>>)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_rpy_4 =
R"doc(create eigen quaternions by rotating roll (x axis), pitch (y axis) and
yaw (z axis) values (vectorized call)

Template parameter ``t_float``:
    $Template parameter ``t_float``:

floating point value

Parameter ``roll``:
    of rotation values the x axis [° or rad]

Parameter ``pitch``:
    vector of rotation values the y axis [° or rad]

Parameter ``yaw``:
    vector of rotation values around the z axis [° or rad]

Parameter ``input_in_degrees``:
    if true, roll, pitch and yaw input values are in ° otherwise rad

Returns:
    std::vector<EigenQuaternion<t_float>>)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_ypr =
R"doc(create an eigen quaternion by rotating yaw (z axis), pitch (y axis)
and roll (x axis)

Template parameter ``t_float``:
    $Parameter ``ypr``:

array that contains yaw, pitch and roll value

Parameter ``input_in_degrees``:
    if true, yaw, pitch and roll input values are in ° otherwise rad

Returns:
    EigenQuaternion<t_float>)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_ypr_2 =
R"doc(create an eigen quaternion by rotating yaw (z axis), pitch (y axis)
and roll (x axis)

Template parameter ``t_float``:
    floating point value

Parameter ``yaw``:
    rotation around z axis [° or rad]

Parameter ``pitch``:
    rotation around y axis [° or rad]

Parameter ``roll``:
    rotation around x axis [° or rad]

Parameter ``input_in_degrees``:
    if true, yaw, pitch and roll input values are in ° otherwise rad

Returns:
    EigenQuaternion<t_float>)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_ypr_3 =
R"doc(create eigen quaternions by rotating yaw (z axis), pitch (y axis) and
roll (x axis) values (vectorized call)

Template parameter ``t_float``:
    floating point value

Parameter ``YPR``:
    vector of yaw, pitch and roll rotation values [° or rad]

Parameter ``input_in_degrees``:
    if true, yaw, pitch and roll input values are in ° otherwise rad

Returns:
    std::vector<EigenQuaternion<t_float>>)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_ypr_4 =
R"doc(create eigen quaternions by rotating yaw (z axis), pitch (y axis) and
roll (x axis) values (vectorized call)

Template parameter ``t_float``:
    $Template parameter ``t_float``:

floating point value

Parameter ``yaw``:
    vector of rotation values around the z axis [° or rad]

Parameter ``pitch``:
    vector of rotation values the y axis [° or rad]

Parameter ``roll``:
    of rotation values the x axis [° or rad]

Parameter ``input_in_degrees``:
    if true, yaw, pitch and roll input values are in ° otherwise rad

Returns:
    std::vector<EigenQuaternion<t_float>>)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_rotateXYZ =
R"doc(OVERLOADED rotateXYZ: rotates a x,y,z vector with the passed
parameters roll, pitch, yaw as a Quaternion

Parameter ``q:``:
    roll, pitch, yaw as Quaternion<t_float>

Parameter ``x:``:
    x as double

Parameter ``y:``:
    y as double

Parameter ``z:``:
    z as double

Returns:
    returns vector with rotated xyz)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_rotateXYZ_2 =
R"doc(OVERLOADED rotateXYZ: rotates a x,y,z vector as a Quaternion with the
passed parameters roll, pitch, yaw as a Quaternion

Parameter ``q:``:
    roll, pitch, yaw as Quaternion<t_float>

Parameter ``v:``:
    x, y, z as Quaternion<t_float>

Returns:
    returns vector with rotated xyz)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_rpy_from_quaternion =
R"doc(Convert quaternion to roll, pitch and yaw

Template parameter ``t_float``:
    $Parameter ``q``:

quaternion

Parameter ``output_to_degrees``:
    if true, roll, pitch and yaw input values are in ° otherwise rad

Returns:
    std::array<t_float, 3> roll, pitch and yaw)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_rpy_from_quaternion_2 =
R"doc(Convert quaternions to roll, pitch and yaw values (vectorized call)

Template parameter ``t_float``:
    $Parameter ``Q``:

vector of quaternions

Parameter ``output_to_degrees``:
    if true, roll, pitch and yaw input values are in ° otherwise rad

Returns:
    std::vector<std::array<t_float, 3>>)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_ypr_from_quaternion =
R"doc(Convert quaternion to yaw, pitch and roll

Template parameter ``t_float``:
    $Parameter ``q``:

quaternion

Parameter ``output_to_degrees``:
    if true, yaw, pitch and roll input values are in ° otherwise rad

Returns:
    std::array<t_float, 3> yaw, pitch and roll)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_ypr_from_quaternion_2 =
R"doc(Convert quaternions to yaw, pitch and roll values (vectorized call)

Template parameter ``t_float``:
    $Parameter ``Q``:

vector of quaternions

Parameter ``output_to_degrees``:
    if true, yaw, pitch and roll input values are in ° otherwise rad

Returns:
    std::vector<std::array<t_float, 3>>)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


