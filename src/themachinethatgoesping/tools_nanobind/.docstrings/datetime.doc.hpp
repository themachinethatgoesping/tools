//sourcehash: 6d977ecaca9a05316b9d825f54b0e0fd1fce13b0e3ff15a35b44e009795b17c5

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


static const char *__doc_themachinethatgoesping_tools_nanobind_helper_datestring_to_datetime =
R"doc(Converts a date string to a Python datetime object using the specified
format.)doc";

static const char *__doc_themachinethatgoesping_tools_nanobind_helper_datetime_to_datestring =
R"doc(Converts a Python datetime object to a formatted date string.

Parameter ``datetimeObject``:
    The Python datetime object to convert.

Parameter ``fractionalSecondsDigits``:
    Number of fractional seconds digits to include.

Parameter ``format``:
    The format string to use for conversion.

Returns:
    The formatted date string.)doc";

static const char *__doc_themachinethatgoesping_tools_nanobind_helper_datetime_to_unixtime =
R"doc(Converts a Python datetime object to a Unix timestamp.

Parameter ``datetimeObject``:
    The Python datetime object to convert.

Returns:
    The Unix timestamp representing the given datetime.)doc";

static const char *__doc_themachinethatgoesping_tools_nanobind_helper_unixtime_to_datetime =
R"doc(Converts a Unix timestamp to a Python datetime object.

Parameter ``timestamp``:
    The Unix timestamp to convert.

Parameter ``timezone_offset_hours``:
    The timezone offset in hours (default: 0).

Returns:
    The Python datetime object representing the given timestamp.)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


