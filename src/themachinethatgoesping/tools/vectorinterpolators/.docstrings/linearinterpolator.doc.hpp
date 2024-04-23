//sourcehash: 8021d63d9fadfdc593e81c23601eee9860f3d31130419fdf17145a5fe2676951

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


static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator =
R"doc(Find linear interpolated values within vector data

Template parameter ``XType:``:
    type of the x values (must be floating point)

Template parameter ``YType:``:
    type of the y values (must be floating point))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_LinearInterpolator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_LinearInterpolator_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_binary_hash =
R"doc(compute a 64 bit hash of the object using xxhash and the \ to_binary
function. This function is called binary because the \ to_binary
function of the object is used)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_class_name = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_from_binary =
R"doc(convert object to vector of bytes \ \

Parameter ``check_buffer_is_read_completely``:
    variable for interface compatibility, does not do \ anything \ \

Returns:
    vector of bytes \)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_from_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_info_string =
R"doc(\ return an info string using the class __printer__ object \

Parameter ``float_precision``:
    number of digits for floating point values \

Returns:
    std::string \)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_interpolate_pair =
R"doc(Interpolate: Interpolate interpolation between two values

Parameter ``target_x:``:
    the target point [0.0 - 1.0]

Parameter ``y1``:
    : first y value (target_x = 0)

Parameter ``y2``:
    : second value (target_x = 01) between)

Returns:
    Interpolated value for target position)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_print =
R"doc(\ print the object information to the given outpustream \ \

Parameter ``os``:
    output stream, e.g. file stream or std::out or std::cerr \

Parameter ``float_precision``:
    number of digits for floating point values \)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_slow_hash =
R"doc(compute a 64 bit hash of the object using xxhash and the \ to_binary
function. This function is called binary because the to_binary
function creates \ a copy)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_to_binary =
R"doc(convert object to vector of bytes \ \

Parameter ``resize_buffer``:
    variable for interface compatibility, does not do anything \ \

Returns:
    vector of bytes \)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_to_stream = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


