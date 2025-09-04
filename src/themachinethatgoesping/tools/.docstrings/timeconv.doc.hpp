//sourcehash: 477afdadb4eeaebcb192d1a416f01cc30b3a70131765400315e8340ec53ea675

/*
  This file contains docstrings for use in the Python bindings.
  Do not edit! They were automatically extracted by pybind11_mkdoc.

  This is a modified version which allows for more than 8 arguments and includes def-guard
 */

#pragma once

#ifndef __DOCSTRINGS_TOOLS_DOCSTRINGS_TIMECONV_DOC_HPP__

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

#endif // __DOCSTRINGS_TOOLS_DOCSTRINGS_TIMECONV_DOC_HPP__
#if defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif


static const char *__doc_themachinethatgoesping_tools_timeconv_datestring_to_unixtime =
R"doc(Parses a date/time string to a UNIX timestamp using the specified
format.

Parameter ``DateString``:
    Date/time string to parse

Parameter ``format``:
    Format string (default: "%z__%d-%m-%Y__%H:%M:%S")

Returns:
    UNIX timestamp as double (seconds since 1970-01-01T00:00:00Z))doc";

static const char *__doc_themachinethatgoesping_tools_timeconv_timepoint_to_unixtime =
R"doc(Converts a std::chrono::system_clock::time_point to a UNIX timestamp
(seconds since epoch, UTC).

Parameter ``TimePoint``:
    Time point to convert

Returns:
    UNIX timestamp as double (seconds since 1970-01-01T00:00:00Z))doc";

static const char *__doc_themachinethatgoesping_tools_timeconv_unixtime_to_datestring =
R"doc(Converts a UNIX timestamp to a formatted date/time string.

Parameter ``unixtime``:
    UNIX timestamp as double (seconds since 1970-01-01T00:00:00Z)

Parameter ``fractionalSecondsDigits``:
    Number of digits for fractional seconds (default: 0)

Parameter ``format``:
    Format string (default: "%z__%d-%m-%Y__%H:%M:%S")

Returns:
    Formatted date/time string)doc";

static const char *__doc_themachinethatgoesping_tools_timeconv_unixtime_to_timepoint =
R"doc(Converts a UNIX timestamp (seconds since epoch, UTC) to a
std::chrono::system_clock::time_point.

Parameter ``unixtime``:
    UNIX timestamp as double (seconds since 1970-01-01T00:00:00Z)

Returns:
    Corresponding std::chrono::system_clock::time_point)doc";

static const char *__doc_themachinethatgoesping_tools_timeconv_unixtime_to_windows_filetime =
R"doc(Converts a UNIX timestamp to Windows FILETIME (high/low 32-bit
values).

Parameter ``unixtime``:
    UNIX timestamp as double (seconds since 1970-01-01T00:00:00Z)

Returns:
    Pair of high and low 32-bit FILETIME values)doc";

static const char *__doc_themachinethatgoesping_tools_timeconv_windows_filetime_to_unixtime =
R"doc(Converts Windows FILETIME (high/low 32-bit values) to UNIX timestamp.

Parameter ``highDateTime``:
    High 32 bits of FILETIME

Parameter ``lowDateTime``:
    Low 32 bits of FILETIME

Returns:
    UNIX timestamp as double (seconds since 1970-01-01T00:00:00Z))doc";

static const char *__doc_themachinethatgoesping_tools_timeconv_year_month_day_to_unixtime =
R"doc(Converts a calendar date (year, month, day) and optional microseconds
to a UNIX timestamp.

Parameter ``year``:
    Year (e.g. 2024)

Parameter ``month``:
    Month (1-12)

Parameter ``day``:
    Day (1-31)

Parameter ``micro_seconds``:
    Optional microseconds to add

Returns:
    UNIX timestamp as double (seconds since 1970-01-01T00:00:00Z))doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


