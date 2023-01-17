//sourcehash: ff9f3308953ea7243b4ce4f78205e26b45a81c251a2ca0c08d80588dbca1f3b6

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


static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator = R"doc(Interpolator class to find nearest neighbors within vector data)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_NearestInterpolator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_NearestInterpolator_2 =
R"doc(Construct a new Nearest Interpolator object from a vector of pairs
usage: interpolated_y_value = interpolator.interpolate(x_value)

Parameter ``X``:
    X vector; must be unique and sorted in ascending order. same size
    as Y!

Parameter ``Y``:
    Y vector; must be unique and sorted in ascending order. same size
    as X!

Parameter ``extrapolation_mode``:
    extrapolation mode (nearest or fail))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_from_binary = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_from_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_info_string = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_interpolate_pair =
R"doc(Interpolate interpolation between two values

Parameter ``target_x:``:
    the target point [0.0 - 1.0]

Parameter ``y1``:
    : first y value (target_x = 0)

Parameter ``y2``:
    : second value (target_x = 01) between)

Returns:
    Interpolated value for target position)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_print = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_slow_hash = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_to_binary = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_to_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_type_to_string = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

