//sourcehash: 24869a4b9889bf8ea4e927ed19a9c1060a1853729a0acb3274e24f0ac4266c9b

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


static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator =
R"doc(Interpolator class to perform a (modified) akima interpolation. Uses
boost makima interpolator. Note: this interpolator acts as linear
interpolator if less than 4 values are stored.

Template Args:
    XYType:: type of the x and y values (must be floating point)))doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_AkimaInterpolator = R"doc(Construct a new (uninitialized) Akima Interpolator object)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_AkimaInterpolator_2 =
R"doc(Construct a new Akima Spline Interpolator object from a vector of
pairs This class uses the modified akima interpolation of boost c++
https://www.boost.org/doc/libs/1_79_0/libs/math/doc/html/math_toolkit/
      makima.html
usage: interpolated_y_value = interpolator(x_value)

Args:
    X: X vector; must be unique and sorted in ascending order. same
       size as Y!
    Y: Y vector; must be unique and sorted in ascending order. same
       size as X!
    extrapolation_mode: :py:class:`t_extr_mode <themachinethatgoesping
                        .tools.vectorinterpolators.t_extr_mode>`
                        object that describes the extrapolation mode)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_X = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_Y = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_akima_spline = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_append = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_binary_hash =
R"doc(compute a 64 bit hash of the object using xxhash and the       \
to_binary function. This  function is called binary because the
\ to_binary  function of the object is used)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_class_name = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_empty = R"doc(check if the interpolator contains data)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_extend = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_from_binary =
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

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_from_stream = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_get_data_X =
R"doc(return the x component of the internal data vector

Returns:
    std::vector<XYType>)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_get_data_Y =
R"doc(return the y component of the internal data vector

Returns:
    std::vector<XYType>)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_get_y = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_info_string =
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

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_init_linearextrapolators =
R"doc(internal function to initialize the linear extrapolation objects _X,
_Y and the _akima_spline must be set/initialized before calling this
function)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_insert = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_max_linearextrapolator = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_min_linearextrapolator = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_operator_call =
R"doc(get the interpolated y value for given x target

Args:
    target_x: find the corresponding y value for this x value

Returns:
    corresponding y value)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_operator_call_2 =
R"doc(get nearest y values for given x targets (vectorized call)

Args:
    targets_x: vector of x values. For each of these values find the
               corrsponding y value

Returns:
    corresponding y value)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_operator_eq = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_operator_ne = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_print =
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

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_printer = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_set_data_XY =
R"doc(change the input data to these X and Y vectors

Args:
    X:: x vector (must be same size)
    Y:: y vector (must be same size))doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_to_binary =
R"doc(convert object to vector of bytes
\
                                                                                            \
Args:
    resize_buffer: variable for interface compatibility, does not do
                   anything             \ \

Returns:
    vector of bytes
    \)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_to_stream = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


