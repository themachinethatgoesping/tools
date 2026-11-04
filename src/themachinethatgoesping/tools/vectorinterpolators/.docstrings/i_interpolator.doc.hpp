//sourcehash: 22fbb1dc0dc5c3d099c82981d70763602da7ce6ef24906ae33f235e26d97c124

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
    extrapolation_mode: extrapolation mode (nearest or fail)

)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_append =
R"doc(append an x- and the corresponding y value to the interpolator data.

Exception: raises domain error, strong exception guarantee

Args:
    x: value, must be > than all existing x values
    y: corresponding y value

)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_check_XY = R"doc(check if input data is valid (e.g. sorted, no duplicated x values))doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_class_name =
R"doc(Get the interpolator name (for debugging)

Returns:
    std::string_view

)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_collapse_sorted_pairs =
R"doc(Collapse groups of equal x in an already-sorted pair vector.

Exact (x, y) duplicates are dropped; a conflict (same x, different y)
is resolved via ``duplicate_mode`` (throw in fail mode, else keep the
first / last occurrence). The output (out_X / out_Y) is sorted with
unique x values.

Args:
    pairs: input pairs, already sorted ascending by x
    duplicate_mode: conflict resolution for same-x / different-y
    out_X: output x values (sorted, unique)
    out_Y: output y values (same size as out_X)

)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_extend =
R"doc(append x and y value lists to the interpolator data (vectorized call)
Exception: raises domain error, strong exception guarantee

Args:
    X: list of x values. Must be sorted in ascending order. All x
       values must be larger than the largest x value in the
       interpolator data.
    Y: list of corresponding Y values. Must be same size as X

)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_extr_mode = R"doc(extrapolation mode)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_get_data_X =
R"doc(return the x component of the internal data vector

Returns:
    std::vector<XType>

)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_get_data_Y =
R"doc(return the y component of the internal data vector

Returns:
    std::vector<YType>

)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_get_extrapolation_mode =
R"doc(Get the currently set extrapolation mode

Returns:
    :o_extr_mode

)doc";

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

Note:
    The returned values are actual x values from the data, not
    interpolated positions. Use these values with the interpolator to
    get corresponding y values.

)doc";

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
    \

)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_insert =
R"doc(Insert x and y value lists into the interpolator data (vectorized
call).

The new values are merged into the existing (already sorted) data.
Only the NEW values are sorted and then merged with the existing run,
which is much faster than re-sorting everything.

EXACT duplicates (same x AND exactly the same y) are always dropped
silently. A CONFLICT (same x but a DIFFERENT y) is resolved according
to ``duplicate_mode.``

Exception: raises domain_error, strong exception guarantee.

Args:
    X: list of x values. Does not have to be sorted.
    Y: list of corresponding Y values. Must be the same size as X.
    is_sorted: set to true if X is already sorted in ascending order
               (skips sorting the new values). (default: false)
    duplicate_mode: how to resolve a conflict where the same x value
                    is present with a different y value: fail (throw,
                    the default), keep_first or keep_last. Exact (x,
                    y) duplicates are always removed regardless of
                    this.

)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_is_strictly_increasing =
R"doc(Return true if X is strictly increasing (no equal or decreasing
neighbours).

)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_merge_insert =
R"doc(Merge the already-sorted existing data with the new data.

Only the new values are sorted; they are then merged with the existing
run (O(n + m log m)). Exact (x, y) duplicates are dropped; conflicts
(same x, different y) are resolved via ``duplicate_mode`` (or throw in
fail mode). The result (out_X / out_Y) is sorted by x with unique x
values.

Args:
    old_X: existing x values (sorted ascending, unique)
    old_Y: existing y values (same size as old_X)
    X: new x values to merge in
    Y: new y values (same size as X)
    is_sorted: set to true if X is already sorted ascending (skips
               sorting)
    duplicate_mode: conflict resolution for same-x / different-y
    out_X: output x values (sorted, unique)
    out_Y: output y values (same size as out_X)

)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_operator_call =
R"doc(get the interpolated y value for given x target

Args:
    target_x: find the corresponding y value for this x value

Returns:
    corresponding y value

)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_operator_call_2 =
R"doc(get interpolated y values for given x targets (vectorized call)

Args:
    targets_x: vector of x values. For each of these values find the
               corresponding y value
    mp_cores: Number of OpenMP threads to use for parallelization.
              Default is 1 (no parallelism). Set to higher values to
              enable parallel interpolation.

Returns:
    std::vector<YType> corresponding y values

)doc";

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

Note:
    This function requires YType to be a scalar type (not a compound
    type like Quaternion). For SlerpInterpolator, use the vector
    overload or the ypr() method instead.

)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_print =
R"doc(                                                                                           \
print the object information to the given outpustream
\ \

Args:
    os: output stream, e.g. file stream or std::out or std::cerr
        \
    float_precision: number of digits for floating point values
                     \
    superscript_exponents: print exponents in superscript
                           \

)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_printer =
R"doc(return a printer object

Args:
    float_precision: number of digits for floating point numbers

Returns:
    classhelper::ObjectPrinter

)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_set_data_XY =
R"doc(change the input data to these X and Y vectors

Args:
    X:: x vector (must be same size, must be sorted in ascending
        order)
    Y:: y vector (must be same size)

)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_set_extrapolation_mode =
R"doc(Set the extrapolation mode

Args:
    extrapolation_mode: :py:class:`t_extr_mode <themachinethatgoesping
                        .tools.vectorinterpolators.t_extr_mode>`
                        object (enumerator) that describes the
                        extrapolation mode

)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_sort_and_dedup =
R"doc(Sort a single (possibly unsorted) X/Y vector and remove duplicates.

Used by the deferred-merge finalizer (sort_and_finalize): sorts the
accumulated data once (O(n log n)), drops exact (x, y) duplicates and
resolves same-x / different-y conflicts via ``duplicate_mode.`` A
stable sort is used so keep_first / keep_last follow the original
append order.

Args:
    X: accumulated x values (any order)
    Y: accumulated y values (same size as X)
    duplicate_mode: conflict resolution for same-x / different-y
    out_X: output x values (sorted, unique)
    out_Y: output y values (same size as out_X)

)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_validate_finite =
R"doc(Validate that X (and floating-point Y) contain only finite values.

Throws domain_error on NaN / infinite values so such inputs are never
sorted (keeps a strong exception guarantee: nothing is modified before
this check).

)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_y_values_equal =
R"doc(Equality test for two y values.

Handles the different y types used by the interpolators: a plain
operator== (arithmetic types), Eigen::Quaternion (compare
coefficients, slerp) and nanobind::object (Python equality, nearest-
object interpolator). Types for which no equality can be determined
are never treated as equal, so same-x values are handled as a conflict
rather than silently merged.

)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_t_dup_mode =
R"doc(Duplicate-handling mode for insert().

insert() always silently drops EXACT duplicates (same x AND exactly
the same y). This mode only controls what happens on a genuine
CONFLICT: the same x value present with a DIFFERENT y value.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_t_dup_mode_fail = R"doc(throw a domain_error on a conflicting duplicate x value (default))doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_t_dup_mode_keep_first = R"doc(on conflict keep the first occurrence (the existing / earlier value))doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_t_dup_mode_keep_last =
R"doc(on conflict keep the last occurrence (the newly inserted / later
value))doc";

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


