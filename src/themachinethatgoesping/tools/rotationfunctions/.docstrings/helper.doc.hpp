//sourcehash: 27f8b9c78f7dc8532ebca214b8a213647c33761b0ac75b69ab94e17b77678a85

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


static const char *__doc_themachinethatgoesping_tools_rotationfunctions_compute_heading =
R"doc(compute heading from northing and easting north 0°/360°, east 90°,
south 180°, west 270

Parameter ``northing``:
    northing in m

Parameter ``easting``:
    easting in m

Parameter ``radians``:
    return as rad, otherwise as degrees

Returns:
    heading in rad or degrees)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_normalize_angles_degrees =
R"doc(Shift angles into specified angular range: yaw [0°,359.99°], pitch
[-90°, 90°], roll [-180¶, 179.99°]

Template parameter ``floattype``:
    double or gloat

Parameter ``ypr``:
    Matrix with yaw, pitch and roll value in °

Returns:
    std::array<floattype, 3> (Matrix with yaw, pitch and roll value in
    °))doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_normalize_angles_rad =
R"doc(Shift angles into specified angular range: yaw [0,2pi], pitch [-p/2°,
p/2°], roll [-pi, pi]

Template parameter ``floattype``:
    double or gloat

Parameter ``ypr``:
    Matrix with yaw, pitch and roll value in rad

Returns:
    std::array<floattype, 3> (Matrix with yaw, pitch and roll value in
    rad))doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


