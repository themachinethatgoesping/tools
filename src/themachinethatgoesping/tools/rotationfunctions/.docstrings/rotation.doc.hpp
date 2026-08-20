//sourcehash: b02caec87801bacd27300e4d0a813a6ea39f229ebf1ae8e289ed59d115416484

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


static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation =
R"doc(A rotation stored as a normalized Eigen quaternion.

Rotation is an Eigen::Quaternion, so it can be used directly in any
quaternion expression (composition, inverse, slerp, ...). On top of
that it offers:
  * (implicit) construction from yaw/pitch/roll (degrees by default),
    * extraction to yaw/pitch/roll and roll/pitch/yaw, * rotation of a
    single xyz vector, of another Rotation (composition) and of a
    batch of xyz vectors (vectorized, one shared rotation matrix),
  * copy, binary streaming and object printing like the other classes.

The quaternion is kept normalized after every construction so vector
rotation is always metric. yaw/pitch/roll follow the ping convention:
yaw about z (down, 0 deg = north), pitch about y (starboard, positive
= bow up), roll about x (forward, positive = port up); rotations are
applied yaw, then pitch, then roll.

Template Args:
    t_float: floating point type of the quaternion coefficients (float
             or double).)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_Rotation = R"doc(Construct an identity rotation (no rotation).)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_Rotation_2 =
R"doc(Construct a Rotation from yaw, pitch and roll (implicit).

Args:
    ypr: array containing {yaw, pitch, roll}.
    input_in_degrees: if true (default) yaw/pitch/roll are in degrees,
                      otherwise radians.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_Rotation_3 =
R"doc(Construct a Rotation from yaw, pitch and roll.

Args:
    yaw: rotation around z (down) [deg or rad], 0 deg = north.
    pitch: rotation around y (starboard) [deg or rad], positive = bow
           up.
    roll: rotation around x (forward) [deg or rad], positive = port
          up.
    input_in_degrees: if true (default) yaw/pitch/roll are in degrees,
                      otherwise radians.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_Rotation_4 =
R"doc(Construct a Rotation from an Eigen quaternion (implicit, normalized).

This makes every function that returns an Eigen::Quaternion (e.g.
rotationfunctions::quaternion_from_ypr) usable to build a Rotation.

Args:
    quaternion: Eigen quaternion; a copy is stored and normalized.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_binary_hash =
R"doc(compute a 64 bit hash of the object using xxhash and the       \
to_binary function. This  function is called binary because the
\ to_binary  function of the object is used)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_from_binary =
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

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_from_quaternion =
R"doc(Build a Rotation from raw quaternion coefficients (w, x, y, z).

Args:
    w: scalar (real) part.
    x: i coefficient.
    y: j coefficient.
    z: k coefficient.

Returns:
    normalized Rotation.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_from_rpy =
R"doc(Build a Rotation from roll, pitch and yaw.
Args:
    roll: rotation around x (forward) [deg or rad].
    pitch: rotation around y (starboard) [deg or rad].
    yaw: rotation around z (down) [deg or rad].
    input_in_degrees: if true (default) inputs are degrees, otherwise
                      radians.

Returns:
    normalized Rotation.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_from_rpy_2 =
R"doc(Build a Rotation from a {roll, pitch, yaw} array.
Args:
    rpy: array containing {roll, pitch, yaw}.
    input_in_degrees: if true (default) inputs are degrees, otherwise
                      radians.

Returns:
    normalized Rotation.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_from_stream =
R"doc(Read a Rotation from a binary stream (4 coefficients w, x, y, z).
Args:
    is: input stream.

Returns:
    the read Rotation.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_from_ypr =
R"doc(Build a Rotation from yaw, pitch and roll.
Args:
    yaw: rotation around z (down) [deg or rad].
    pitch: rotation around y (starboard) [deg or rad].
    roll: rotation around x (forward) [deg or rad].
    input_in_degrees: if true (default) inputs are degrees, otherwise
                      radians.

Returns:
    normalized Rotation.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_from_ypr_2 =
R"doc(Build a Rotation from a {yaw, pitch, roll} array.
Args:
    ypr: array containing {yaw, pitch, roll}.
    input_in_degrees: if true (default) inputs are degrees, otherwise
                      radians.

Returns:
    normalized Rotation.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_info_string =
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

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_operator_eq =
R"doc(Two rotations are equal if their quaternions describe the same
orientation (q == -q).)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_operator_mul =
R"doc(Compose two rotations (quaternion product); the result is a Rotation.

The product of two normalized quaternions is already normalized, so
(unlike an
Eigen::Quaternion product that is then converted back) no re-
      normalization is done.
Args:
    other: the rotation applied after this one.

Returns:
    the combined rotation (this * other).)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_operator_ne = R"doc(Inequality (negation of operator==).)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_print =
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

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_printer = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_rotate =
R"doc(Rotate a single 3D vector by this rotation.
Args:
    x: x component (forward).
    y: y component (starboard).
    z: z component (down).

Returns:
    the rotated {x, y, z} vector.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_rotate_2 =
R"doc(Rotate a single 3D vector by this rotation.
Args:
    xyz: the {x, y, z} vector to rotate.

Returns:
    the rotated {x, y, z} vector.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_rotate_3 =
R"doc(Rotate (compose with) another rotation: apply this rotation to
``rotation.``
Args:
    rotation: the rotation to be rotated.

Returns:
    the combined rotation (this * rotation).)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_rotate_4 =
R"doc(Rotate a batch of 3D vectors by this rotation (vectorized).

The rotation matrix is built once and applied to every row, which is
the fast path for rotating many points by the same rotation.

Args:
    points: [n, 3] tensor of (x, y, z) row vectors.

Returns:
    [n, 3] tensor of rotated row vectors.

Raises:
    std::invalid_argument: if the second dimension is not 3.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_rpy =
R"doc(Extract roll, pitch and yaw from the rotation.
Args:
    output_in_degrees: if true (default) the output is in degrees,
                       otherwise radians.

Returns:
    array containing {roll, pitch, yaw}.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_to_binary =
R"doc(convert object to vector of bytes
\
                                                                                            \
Args:
    resize_buffer: variable for interface compatibility, does not do
                   anything             \ \

Returns:
    vector of bytes
    \)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_to_stream =
R"doc(Write the Rotation to a binary stream (4 coefficients w, x, y, z).
Args:
    os: output stream.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_wxyz =
R"doc(Get the raw quaternion coefficients as {w, x, y, z}.
Returns:
    array containing {w, x, y, z}.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_rotationfunctions_Rotation_ypr =
R"doc(Extract yaw, pitch and roll from the rotation.
Args:
    output_in_degrees: if true (default) the output is in degrees,
                       otherwise radians.

Returns:
    array containing {yaw, pitch, roll}.)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


