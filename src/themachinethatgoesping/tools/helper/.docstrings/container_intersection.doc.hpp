//sourcehash: cc01378feaafa8dc49e210ebad029ebdebf0aed69d5983770a2ec2fdf6d8fe59

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


static const char *mkd_doc_themachinethatgoesping_tools_helper_Range = R"doc(Structure representing a continuous range/section)doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_Range_Range = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_Range_contains = R"doc(Check if a value is within this range)doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_Range_intersection =
R"doc(Get the intersection of this range with another
Returns:
    The overlapping range, or an empty range if no overlap)doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_Range_is_valid = R"doc(Check if range is valid (min <= max))doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_Range_max = R"doc(Maximum value of the range (inclusive))doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_Range_min = R"doc(Minimum value of the range (inclusive))doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_Range_overlaps = R"doc(Check if this range overlaps with another)doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_get_sections =
R"doc(Extract continuous sections from a sorted container, splitting at gaps

This function analyzes a sorted container and identifies continuous
sections where consecutive values are no more than max_gap apart.

Args:
    data: Container of values, must be sorted in ascending order
    max_gap: Maximum allowed gap between consecutive values before
             starting a new section. If <= 0 or NaN, treats the entire
             container as one section.

Template Args:
    T: Container type (must support .size() and element access,
       contain floating point values)

Returns:
    std::vector<Range<value_type>> Vector of ranges representing
        continuous sections

@note The data must be sorted in ascending order. Behavior is
undefined for unsorted input.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_get_shared_section_values =
R"doc(Get values that fall within the shared sections (flattened)

This function takes multiple sorted containers and returns a single
container containing all unique values from any container that fall
within shared sections. This is useful when you need a common set of
values for interpolation or alignment.

Args:
    containers: Vector of containers, each must be sorted in ascending
                order
    max_gap: Maximum allowed gap between consecutive values in any
             container. If <= 0 or NaN, defaults to only considering
             container boundaries.

Template Args:
    T: Container type (must support .size() and element access,
       contain floating point values)

Returns:
    xt::xtensor<value_type, 1> Sorted unique values from all
       containers within shared sections

@note All containers must be sorted in ascending order. Behavior is
undefined for unsorted input.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_get_shared_sections =
R"doc(Find the intersection of sections from multiple containers

This function takes multiple sorted containers and finds the ranges
where all containers have data. It respects gaps in each container -
if any container has a gap larger than max_gap, the intersection is
split at that point.

Args:
    containers: Vector of containers, each must be sorted in ascending
                order
    max_gap: Maximum allowed gap between consecutive values in any
             container. If <= 0 or NaN, defaults to checking only
             container boundaries.

Template Args:
    T: Container type (must support .size() and element access,
       contain floating point values)

Returns:
    std::vector<Range<value_type>> Vector of ranges where all
        containers have overlapping data

@note All containers must be sorted in ascending order. Behavior is
undefined for unsorted input.)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


