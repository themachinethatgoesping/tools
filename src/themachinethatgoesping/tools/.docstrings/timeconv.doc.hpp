//sourcehash: ef3178a7bb51268fe33ca2a536c6e22f05e0229c13221d50bfeaeb8e91721b17

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


static const char *__doc_themachinethatgoesping_tools_timeconv_datestring_to_unixtime =
R"doc(Converting between date strings and unixtime stamps (ref 1970)

Parameter ``DateString:``:
    DateString to be converted. Must fit format string.

Parameter ``format:``:
    Format string to convert Date string. Default Format:
    "%z__%d-%m-%Y__%H:%M:%S" see
    https://m.cplusplus.com/reference/ctime/strftime/ * https://themac
    hinethatgoesping.readthedocs.io/en/latest/modules/tools/timeconv.h
    tml#format-string

Returns:
    unixtime as double (seconds since 01.01.1970))doc";

static const char *__doc_themachinethatgoesping_tools_timeconv_timepoint_to_unixtime =
R"doc(timepoint_to_unixtime IMPORTANT: Conversion does only have
microseconds precision!

Parameter ``TimePoint:``:
    chrono::system_clock::time_point

Returns:
    Unix time stamp (seconds since 01.01.1970) as double)doc";

static const char *__doc_themachinethatgoesping_tools_timeconv_unixtime_to_datestring =
R"doc(Converting between date strings and unixtime stamps (ref 1970)

Parameter ``unixtime:``:
    seconds since 01.01.1970 as double

Parameter ``fractionalSecondsDigits:``:
    How many digits to use for the split seconds. Minimum is 0 (second
    resolution) Maximum is 6 (microsecond resolution)

Parameter ``format:``:
    Format string to convert Date string. Default Format:
    "%z__%d-%m-%Y__%H:%M:%S" see:
    https://m.cplusplus.com/reference/ctime/strftime/ * https://themac
    hinethatgoesping.readthedocs.io/en/latest/modules/tools/timeconv.h
    tml#format-string

Returns:
    DateString that fits to the specified format)doc";

static const char *__doc_themachinethatgoesping_tools_timeconv_unixtime_to_timepoint =
R"doc(unixtime_to_timepoint IMPORTANT: return value will only have
microseconds precision!

Parameter ``unixtime:``:
    Unix time stamp (seconds since 01.01.1970) as double

Returns:
    chrono::system_clock::time_point)doc";

static const char *__doc_themachinethatgoesping_tools_timeconv_unixtime_to_windows_filetime =
R"doc(Convert a unix timestamp to a windows 32bit Filetime conversion to 2 x
32 bit word see: https://support.microsoft.com/en-us/help/188768/info-
working-with-the-filetime-structure

Parameter ``unixtime``:
    in seconds since 1970

Returns:
    std::pair<uint32_t, uint32_t>)doc";

static const char *__doc_themachinethatgoesping_tools_timeconv_windows_filetime_to_unixtime =
R"doc(Convert a windows 32bit Filetime to a unix timestamp conversion to
unixtime see: http://www.frenk.com/2009/12/convert-filetime-to-unix-
timestamp/

WARNING: converting to unixtime and then back causes small (100 ns )
rounding error *

Parameter ``highDateTime``:
    $Parameter ``lowDateTime``:

Returns:
    double)doc";

static const char *__doc_themachinethatgoesping_tools_timeconv_year_month_day_to_unixtime =
R"doc(Convert a year, month and day to a unixtime stamp (ref 1970)

Parameter ``year``:
    $Parameter ``month``:

Parameter ``day``:
    $Parameter ``micro_seconds``:

microseconds since midnight

Returns:
    double)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


