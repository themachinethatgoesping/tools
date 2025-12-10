//sourcehash: b3764e129425d07653fd49bece46ecedaa08852aa5422cdcd4f1fbe2cb0fd63d

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


static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator =
R"doc(Interpolator class to find nearest neighbors within vector data

Template Args:
    XType:: type of the x values (must be floating point)
    YType:: type of the y values (must be floating point))doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_NearestInterpolator = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_NearestInterpolator_2 =
R"doc(Construct a new Nearest Interpolator object from a vector of pairs
usage: interpolated_y_value = interpolator.interpolate(x_value)

Args:
    X: X vector; must be unique and sorted in ascending order. same
       size as Y!
    Y: Y vector; must be unique and sorted in ascending order. same
       size as X!
    extrapolation_mode: extrapolation mode (nearest or fail))doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_binary_hash =
R"doc(compute a 64 bit hash of the object using xxhash and the       \
to_binary function. This  function is called binary because the
\ to_binary  function of the object is used)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_class_name = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_from_binary =
R"doc(convert object to vector of bytes
\
                                                                                            \
Args:
    check_buffer_is_read_completely: variable for interface
                                     compatibility, does not do    \
                                     anything
                                     \ \

Returns:
    vector of bytes
    \)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_from_stream = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_info_string =
R"doc(                                                                                           \
return an info string using the class __printer__ object
\
Args:
    float_precision: number of digits for floating point values
                     \
    superscript_exponents: print exponents in superscript
                           \

Returns:
    std::string
        \)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_interpolate_pair =
R"doc(Interpolate interpolation between two values
Args:
    target_x:: the target point [0.0 - 1.0]
    y1: : first y value (target_x = 0)
    y2: : second value (target_x = 01) between)

Returns:
    Interpolated value for target position)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_operator_eq = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_operator_ne = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_print =
R"doc(                                                                                           \
print the object information to the given outpustream
\
                                                                                            \
Args:
    os: output stream, e.g. file stream or std::out or std::cerr
        \
    float_precision: number of digits for floating point values
                     \
    superscript_exponents: print exponents in superscript
                           \)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_printer = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_to_binary =
R"doc(convert object to vector of bytes
\
                                                                                            \
Args:
    resize_buffer: variable for interface compatibility, does not do
                   anything             \ \

Returns:
    vector of bytes
    \)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_to_stream = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


