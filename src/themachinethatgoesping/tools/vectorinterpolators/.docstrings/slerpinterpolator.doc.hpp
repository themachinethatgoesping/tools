//sourcehash: 8ada8ce9065b812dcedc02a91c3912527315ea959a8d5d7db26cb4097f40538c

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


static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator =
R"doc(Class that implements a slerp interpolation for vectors. Data is
internally represented in quaternions using lib eigen. Interfaces to
represent the data in yaw, pitch, roll angles are provided. the
__call__ equivalent to get interpolated yaw pitch roll is the ypr
function

Template parameter ``XType:``:
    type of the x values (must be floating point)

Template parameter ``YType:``:
    floating point type of the y quaternion values (must be floating
    point))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_SlerpInterpolator = R"doc(Constructor to make default initialization possible (necessary?))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_SlerpInterpolator_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_SlerpInterpolator_3 =
R"doc(Construct a new Slerp Interpolator object using vectors of x, yaw,
pitch and roll

Parameter ``X``:
    vector; must be unique and sorted in ascending order

Parameter ``yaw``:
    vector with yaw data (rotation around z axis). Must be same size
    as X!

Parameter ``pitch``:
    vector with pitch data (rotation around y axis). Must be same size
    as X!

Parameter ``roll``:
    vector with roll data (rotation around x axis). Must be same size
    as X!

Parameter ``input_in_degrees``:
    if true (default) yaw,pitch and roll are in °, otherwise [rad]

Parameter ``extrapolation_mode``:
    :py:class:`t_extr_mode
    <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>`
    object that describes the extrapolation mode)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_SlerpInterpolator_4 =
R"doc(Construct a new Slerp Interpolator object using vectors of x, yaw,
pitch and roll

Parameter ``X``:
    vector; must be unique and sorted in ascending order

Parameter ``YPR``:
    vector with yaw, pitch and roll data points. Must be same size as
    X!

Parameter ``input_in_degrees``:
    if true (default) yaw,pitch and roll are in °, otherwise [rad]

Parameter ``extrapolation_mode``:
    :py:class:`t_extr_mode
    <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>`
    object that describes the extrapolation mode)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_append =
R"doc(append an x, yaw, pitch, roll data point

Parameter ``X``:
    must be larger than all internal data points

Parameter ``yaw``:
    rotation around z axis

Parameter ``pitch``:
    rotation around y axis

Parameter ``roll``:
    rotation around x axis

Parameter ``input_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_append_2 =
R"doc(append an x, yaw, pitch, roll data point

Parameter ``X``:
    must be larger than all internal data points

Parameter ``ypr``:
    array with one yaw, pitch and roll data point

Parameter ``input_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_binary_hash =
R"doc(compute a 64 bit hash of the object using xxhash and the \ to_binary
function. This function is called binary because the \ to_binary
function of the object is used)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_class_name = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_extend =
R"doc(append data with lists of x, yaw, pitch, roll data (vectorized call)

Parameter ``X``:
    vector; must be unique and sorted in ascending order

Parameter ``yaw``:
    vector with yaw data (rotation around z axis). Must be same size
    as X!

Parameter ``pitch``:
    vector with pitch data (rotation around y axis). Must be same size
    as X!

Parameter ``roll``:
    vector with roll data (rotation around x axis). Must be same size
    as X!

Parameter ``input_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_extend_2 =
R"doc(append data with list of x, yaw, pitch, roll data (vectorized call)

Parameter ``X``:
    vector; must be unique and sorted in ascending order

Parameter ``ypr``:
    vector with yaw, pitch and roll data points. Must be same size as
    X!

Parameter ``input_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_from_binary =
R"doc(convert object to vector of bytes \ \

Parameter ``check_buffer_is_read_completely``:
    variable for interface compatibility, does not do \ anything \ \

Returns:
    vector of bytes \)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_from_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_get_data_YPR =
R"doc(return the internal yrp data vector

Parameter ``output_in_degrees``:
    convert yaw, pitch and roll to degrees (default = True)

Returns:
    std::vector<std::array<3, YType>> YPR)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_info_string =
R"doc(\ return an info string using the class __printer__ object \

Parameter ``float_precision``:
    number of digits for floating point values \

Parameter ``superscript_exponents``:
    print exponents in superscript \

Returns:
    std::string \)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_insert =
R"doc(append data with lists of x, yaw, pitch, roll data (vectorized call)

Parameter ``X``:
    vector; must be unique

Parameter ``yaw``:
    vector with yaw data (rotation around z axis). Must be same size
    as X!

Parameter ``pitch``:
    vector with pitch data (rotation around y axis). Must be same size
    as X!

Parameter ``roll``:
    vector with roll data (rotation around x axis). Must be same size
    as X!

Parameter ``input_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_insert_2 =
R"doc(append data with list of x, yaw, pitch, roll data (vectorized call)

Parameter ``X``:
    vector; must be unique

Parameter ``ypr``:
    vector with yaw, pitch and roll data points. Must be same size as
    X!

Parameter ``input_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_interpolate_pair =
R"doc(Interpolate: Slerp interpolation between two values

Parameter ``target_x:``:
    the target point [0.0 - 1.0]

Parameter ``y1``:
    : first quaternion (target_x = 0)

Parameter ``y2``:
    : second quaternion (target_x = 01)

Returns:
    Interpolated value for target position)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_print =
R"doc(\ print the object information to the given outpustream \ \

Parameter ``os``:
    output stream, e.g. file stream or std::out or std::cerr \

Parameter ``float_precision``:
    number of digits for floating point values \

Parameter ``superscript_exponents``:
    print exponents in superscript \)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_set_data_XYPR =
R"doc(change the input data to these X, yaw, pitch, roll vectors (will be
converted to quaternion)

Parameter ``X``:
    vector; must be unique and sorted in ascending order

Parameter ``yaw``:
    vector with yaw data (rotation around z axis). Must be same size
    as X!

Parameter ``pitch``:
    vector with pitch data (rotation around y axis). Must be same size
    as X!

Parameter ``roll``:
    vector with roll data (rotation around x axis). Must be same size
    as X!

Parameter ``input_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_set_data_XYPR_2 =
R"doc(change the input data to these X, yaw, pitch, roll vectors (will be
converted to quaternion)

Parameter ``X``:
    vector; must be unique and sorted in ascending order

Parameter ``yaw``:
    vector with yaw data (rotation around z axis). Must be same size
    as X!

Parameter ``pitch``:
    vector with pitch data (rotation around y axis). Must be same size
    as X!

Parameter ``roll``:
    vector with roll data (rotation around x axis). Must be same size
    as X!

Parameter ``input_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_to_binary =
R"doc(convert object to vector of bytes \ \

Parameter ``resize_buffer``:
    variable for interface compatibility, does not do anything \ \

Returns:
    vector of bytes \)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_to_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_ypr =
R"doc(get the interpolated yaw, pitch and roll values for given x target

Parameter ``target_x``:
    find the corresponding y value for this x value

Parameter ``output_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad

Returns:
    corresponding y value)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_ypr_2 =
R"doc(get the interpolated yaw, pitch and roll values for given x target
(vectorized call)

Parameter ``targets_x``:
    vector of x values. For each of these values find the corrsponding
    yaw, pitch and roll value

Parameter ``output_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad

Returns:
    corresponding y value)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


