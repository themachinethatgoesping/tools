//sourcehash: 1047b093c516e5786754fb9e973c309a2afc038237505969871d04214836e715

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


static const char *mkd_doc__unnamed_class_at_themachinethatgoesping_tools_vectorinterpolators_i_interpolator_hpp_310_67 = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator =
R"doc(Interface class for interpolator classes Create an interpolator object
by providing vectors for x and y (same size). X must be sorted and no
duplicates are allowed. then call interpolator(new x value) to get a
corresponding y value at this x position.

Template Args:
    XType:: type of the x values (must be floating point)
    YType:: type of the y values (typically double or float, but will
          be a vector for the slerp interpolator class))doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_I_Interpolator =
R"doc(Construct a new Interpolator object from two vectors
usage: interpolated_y_value = interpolator.interpolate(x_value)

Args:
    extrapolation_mode: extrapolation mode (nearest or fail))doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_append =
R"doc(append an x- and the corresponding y value to the interpolator data.
Exception: raises domain error, strong exception guarantee

Args:
    x: value, must be > than all existing x values
    y: corresponding y value)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_check_XY = R"doc(check if input data is valid (e.g. sorted, no duplicated x values))doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_class_name =
R"doc(Get the interpolator name (for debugging)

Returns:
    std::string_view)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_extend =
R"doc(append x and y value lists to the interpolator data (vectorized call)
Exception: raises domain error, strong exception guarantee

Args:
    X: list of x values. Must be sorted in ascending order. All x
       values must be larger than the largest x value in the
       interpolator data.
    Y: list of corresponding Y values. Must be same size as X)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_extr_mode = R"doc(extrapolation mode)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_get_data_X =
R"doc(return the x component of the internal data vector

Returns:
    std::vector<XType>)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_get_data_Y =
R"doc(return the y component of the internal data vector

Returns:
    std::vector<YType>)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_get_extrapolation_mode =
R"doc(Get the currently set extrapolation mode

Returns:
    :o_extr_mode)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_get_sampled_X =
R"doc(Get downsampled x values from the interpolator data.

This function returns x values at regular intervals, respecting gaps
in the data. Useful for reducing the number of interpolation points
when dealing with large datasets.

Args:
    downsample_interval: The interval between consecutive sampled x
                         values
    max_gap: Maximum allowed gap between consecutive x values. If the
             gap between consecutive x values exceeds this, a new
             sampling segment is started.

Returns:
    xt::xtensor<XType, 1> A 1D tensor containing the downsampled x
       values

@note The returned values are actual x values from the data, not
interpolated positions.
      Use these values with the interpolator to get corresponding y
      values.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_info_string =
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

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_insert =
R"doc(append x and y value lists to the interpolator data (vectorized call)
This call is much more expensive than extend as it requires copying
data and sorting.
Exception: raises domain error, strong exception guarantee

Args:
    X: list of x values. (Does not have to be sorted. But must be
       unique)
    Y: list of corresponding Y values. Must be same size as X
    is_sorted: this indicates that X is already sorted in ascending
               order. (default: false))doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_operator_call =
R"doc(get the interpolated y value for given x target

Args:
    target_x: find the corresponding y value for this x value

Returns:
    corresponding y value)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_operator_call_2 =
R"doc(get interpolated y values for given x targets (vectorized call)

Args:
    targets_x: vector of x values. For each of these values find the
               corresponding y value
    mp_cores: Number of OpenMP threads to use for parallelization.
              Default is 1 (no parallelism). Set to higher values to
              enable parallel interpolation.

Returns:
    std::vector<YType> corresponding y values)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_operator_call_3 =
R"doc(get interpolated y values for given x targets (xtensor vectorized
call)

This overload accepts xtensor containers and returns an xtensor
result. The return type matches the value type of the interpolator
(YType).

Args:
    targets_x: xtensor of x values. For each of these values find the
               corresponding y value
    mp_cores: Number of OpenMP threads to use for parallelization.
              Default is 1 (no parallelism). Set to higher values to
              enable parallel interpolation.

Template Args:
    XTensor: An xtensor-compatible 1D container type

Returns:
    xt::xtensor<YType, 1> corresponding y values as a 1D xtensor

@note This function requires YType to be a scalar type (not a compound
type like Quaternion).
      For SlerpInterpolator, use the vector overload or the ypr()
      method instead.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_print =
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

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_printer =
R"doc(return a printer object

Args:
    float_precision: number of digits for floating point numbers

Returns:
    classhelper::ObjectPrinter)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_set_data_XY =
R"doc(change the input data to these X and Y vectors

Args:
    X:: x vector (must be same size, must be sorted in ascending
      order)
    Y:: y vector (must be same size))doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_set_extrapolation_mode =
R"doc(Set the extrapolation mode

Args:
    extrapolation_mode: :py:class:`t_extr_mode <themachinethatgoesping
                        .tools.vectorinterpolators.t_extr_mode>`
                        object (enumerator) that describes the
                        extrapolation mode)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_t_extr_mode = R"doc(extrapolation mode type.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_t_extr_mode_extrapolate = R"doc(interpolate using the closest value pair in the internal x vector)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_t_extr_mode_fail =
R"doc(throw out_of_range exception if x value exceeds boundaries of internal
vector)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_t_extr_mode_nan =
R"doc(return NaN if x value exceeds boundaries of internal vector (only for
floating point types))doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_t_extr_mode_nearest = R"doc(return nearest value in the vector.)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


