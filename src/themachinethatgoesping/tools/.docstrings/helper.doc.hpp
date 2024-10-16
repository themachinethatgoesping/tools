//sourcehash: b27aeb68e23227dea59f7ebd5a91ab73dfc9e78f8d0f2b358db4230c3291be67

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


static const char *__doc_themachinethatgoesping_tools_helper_approx =
R"doc(compare to floats using a relative difference factor

Template parameter ``t_float``:
    floating point type

Parameter ``f1``:
    float/double 1

Parameter ``f2``:
    float/double 1

Parameter ``relative_difference_factor``:
    relative factor by which the 2 numbers must be comparable (default
    0.01%)

Returns:
    true/false)doc";

static const char *__doc_themachinethatgoesping_tools_helper_approx_complex = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_helper_approx_container = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_helper_approx_container_complex = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_helper_compare_containers = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_helper_float_equals = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_helper_float_is_finite_and_not_zero = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_helper_get_from_map_with_default = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_helper_int_as_string = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_helper_make_overload = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_helper_make_overload_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_helper_string_as_int = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_helper_string_to_floattype =
R"doc(convert a string to float using fast_float::from_chars Fast_float
conforms to std::from_chars (c++20, but not completely implemented in
clang yet) The conversion is locale independent (. is the decimal
separator) see also: https://github.com/fastfloat/fast_float

Template parameter ``t_float``:
    : double or float

Parameter ``str``:
    if empty or non-numeric a NAN is returned

Returns:
    double)doc";

static const char *__doc_themachinethatgoesping_tools_helper_substract_set_zero_if_negative = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_helper_visit_variant = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_helper_visit_variant_no_return = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


