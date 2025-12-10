//sourcehash: 5aa6a5f973b3e682d04cf37ea63fe0718f1ae0e6a11e3ab3f4fccf2c2704c932

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


static const char *mkd_doc_themachinethatgoesping_tools_helper_get_index_downsampling =
R"doc(Compute indices for downsampling a sorted data container

This function takes a container of sorted values and returns indices
of values that should be kept when downsampling at a specified
interval. It also detects gaps in the data and does not bridge them
(i.e., does not return indices that would require interpolating across
a gap larger than max_gap).

The function selects the first value, then selects subsequent values
that are at least downsample_interval apart from the last selected
value. When a gap larger than max_gap is encountered, the sampling
restarts from the first value after the gap.

Args:
    data: Container of values, must be sorted in ascending order
    downsample_interval: Interval between samples. Use 0, negative, or
                         NaN to disable downsampling (return all
                         indices)
    max_gap: Maximum allowed gap in the original data before
             considering it a data gap. When a gap larger than this is
             encountered, sampling restarts after the gap. If <= 0 or
             NaN, defaults to 2x downsample_interval (or 10 if no
             downsampling)

Template Args:
    T: Container type (must support .size() and element access,
       contain floating point values)

Returns:
    xt::xtensor<size_t, 1> containing indices of values to keep

@note The data must be sorted in ascending order. Behavior is
undefined for unsorted input.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_get_value_downsampling =
R"doc(Downsample a sorted data container and return the downsampled values

This function takes a container of sorted values and returns a new
container with values at exact intervals starting from the first
value. It also detects gaps in the data and restarts sampling after
gaps.

Unlike get_index_downsampling which returns indices into the original
data, this function generates exact sample points at regular
intervals.

Args:
    data: Container of values, must be sorted in ascending order
    downsample_interval: Interval between samples. Use 0, negative, or
                         NaN to disable downsampling (return copy of
                         data)
    max_gap: Maximum allowed gap in the original data before
             considering it a data gap. When a gap larger than this is
             encountered, sampling restarts after the gap. If <= 0 or
             NaN, defaults to 2x downsample_interval (or 10 if no
             downsampling)

Template Args:
    T: Container type (must support .size() and element access,
       contain floating point values)

Returns:
    std::vector<double> containing the downsampled values at exact
        intervals

@note The data must be sorted in ascending order. Behavior is
undefined for unsorted input.)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


