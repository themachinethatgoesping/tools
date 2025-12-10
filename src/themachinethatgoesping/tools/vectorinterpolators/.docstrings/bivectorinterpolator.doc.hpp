//sourcehash: d8bb7c09c6e5445b58ff7aa6013d136c0ac76b4cdf7af07696b2962a005979d4

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


static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_BiVectorInterpolator = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_append_row = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_append_row_2 = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_binary_hash =
R"doc(compute a 64 bit hash of the object using xxhash and the       \
to_binary function. This  function is called binary because the
\ to_binary  function of the object is used)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_class_name =
R"doc(Get the interpolator name (for debugging)

Returns:
    std::string_view)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_clear = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_col_interpolator_per_row = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_empty = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_extr_mode = R"doc(extrapolation mod)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_from_binary =
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

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_from_stream = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_get_col_interpolators = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_get_extrapolation_mode =
R"doc(Get the currently set extrapolation mode

Returns:
    :py:class:`t_extr_mode
    <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>`
    object (enumerator) that describes the extrapolation mode)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_get_row_coordinates = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_info_string =
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

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_insert_row = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_operator_call =
R"doc(get interpolated y values for given x targets (vectorized call)

Args:
    targets_x: vector of x values. For each of these values find the
               corrsponding y value

Returns:
    corresponding y value)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_operator_call_2 =
R"doc(get interpolated y values for given x targets (vectorized call)

Args:
    targets_x: vector of x values. For each of these values find the
               corrsponding y value

Returns:
    corresponding y value)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_operator_eq = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_print =
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

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_printer =
R"doc(return a printer object

Args:
    float_precision: number of digits for floating point numbers

Returns:
    classhelper::ObjectPrinter)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_row_coordinates = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_set_extrapolation_mode =
R"doc(Set the extrapolation mode

Args:
    extrapolation_mode: :py:class:`t_extr_mode <themachinethatgoesping
                        .tools.vectorinterpolators.t_extr_mode>`
                        object (enumerator) that describes the
                        extrapolation mode)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_size = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_to_binary =
R"doc(convert object to vector of bytes
\
                                                                                            \
Args:
    resize_buffer: variable for interface compatibility, does not do
                   anything             \ \

Returns:
    vector of bytes
    \)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_BiVectorInterpolator_to_stream = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


