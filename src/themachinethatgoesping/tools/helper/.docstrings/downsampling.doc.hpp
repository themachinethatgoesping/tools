//sourcehash: e0d9f52b7750b21e90ba00930a88a8049bfc493d2e08d28509c55684974079f4

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


static const char *mkd_doc_themachinethatgoesping_tools_helper_DownsamplingResult =
R"doc(Result structure for downsampling operations

Contains the indices of timestamps that should be kept after
downsampling, respecting both the downsample interval and maximum gap
constraints.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_DownsamplingResult_empty =
R"doc(Check if the result is empty
Returns:
    true if no indices were selected)doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_DownsamplingResult_indices = R"doc(Indices into the original timestamps that should be kept)doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_DownsamplingResult_size =
R"doc(Get the number of selected indices
Returns:
    Number of indices)doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_compute_downsampling_indices =
R"doc(Compute indices for downsampling a sorted timestamp container

This function takes a container of sorted timestamps and returns
indices of timestamps that should be kept when downsampling at a
specified interval. It also detects gaps in the data and does not
bridge them (i.e., does not return indices that would require
interpolating across a gap larger than max_gap_sec).

The function selects the first timestamp, then selects subsequent
timestamps that are at least downsample_interval_sec apart from the
last selected timestamp. When a gap larger than max_gap_sec is
encountered, the sampling restarts from the first timestamp after the
gap.

Args:
    timestamps: Container of timestamps in seconds, must be sorted in
                ascending order
    downsample_interval_sec: Time interval between samples in seconds.
                             Use 0 or negative to disable downsampling
                             (return all indices)
    max_gap_sec: Maximum allowed gap in the original data before
                 considering it a data gap. When a gap larger than
                 this is encountered, sampling restarts after the gap.
                 If <= 0, defaults to 2x downsample_interval_sec (or
                 10 seconds if no downsampling)

Template Args:
    T: Container type (must support .size(), .begin(), .end() and
       contain floating point values)

Returns:
    DownsamplingResult containing indices of timestamps to keep

Raises:
    std::invalid_argument: if timestamps container is empty

@note The timestamps must be sorted in ascending order. Behavior is
undefined for unsorted input.)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


