//sourcehash: 3c0d4feadbff0131d234be02026952f1d91aae273da61f904d59d0c6e19c3337

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


static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer =
R"doc(A class to compute python style indexing Allow for negative indexing
(starting from the stop of the container) Allow for sliced indexing
(start, stop, step))doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyIndexer = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyIndexer_2 =
R"doc(Construct a new Py Indexer object * Allow for negative indexing
(starting from the stop of the container)

Parameter ``vector_size``:
    Size of the vector to be indexed)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyIndexer_3 =
R"doc(Construct a new Py Indexer object Allow for negative indexing
(starting from the stop of the container) Allow for sliced indexing
(start, stop, step)

Parameter ``vector_size``:
    Size of the vector to be indexed

Parameter ``start``:
    Start index of the slice

Parameter ``stop``:
    Stop index of the slice

Parameter ``step``:
    Step size of the slice)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyIndexer_4 =
R"doc(Construct a new Py Indexer object Allow for negative indexing
(starting from the stop of the container) Allow for sliced indexing
(start, stop, step)

Parameter ``vector_size``:
    Size of the vector to be indexed

Parameter ``slice``:
    PyIndexer::Slice structure (contains, start, stop, step))doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyRangeIterator = R"doc(Simple iterator class to allow for range-based for loops)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyRangeIterator_PyRangeIterator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyRangeIterator_operator_inc = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyRangeIterator_operator_mul = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyRangeIterator_operator_ne =
R"doc(operator != for range-based for loops Only compare _val, since _step
is not relevant for the it != stop comparison

Parameter ``rhs``:
    $Returns:

true

Returns:
    false)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyRangeIterator_step = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyRangeIterator_val = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice = R"doc(A structure to hold a slice)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_Slice = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_Slice_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_binary_hash =
R"doc(compute a 64 bit hash of the object using xxhash and the \ to_binary
function. This function is called binary because the \ to_binary
function of the object is used)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_from_binary =
R"doc(convert object to vector of bytes \ \

Parameter ``check_buffer_is_read_completely``:
    variable for interface compatibility, does not do \ anything \ \

Returns:
    vector of bytes \)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_from_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_info_string =
R"doc(\ return an info string using the class __printer__ object \

Parameter ``float_precision``:
    number of digits for floating point values \

Returns:
    std::string \)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_print =
R"doc(\ print the object information to the given outpustream \ \

Parameter ``os``:
    output stream, e.g. file stream or std::out or std::cerr \

Parameter ``float_precision``:
    number of digits for floating point values \)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_slow_hash =
R"doc(compute a 64 bit hash of the object using xxhash and the \ to_binary
function. This function is called binary because the to_binary
function creates \ a copy)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_start = R"doc(< the start index of the slice (None if not sliced))doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_step = R"doc(< the step size of the slice (1 if not sliced))doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_stop =
R"doc(< the stop index of the slice (None if not sliced) < (stop is
exclusive))doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_to_binary =
R"doc(convert object to vector of bytes \ \

Parameter ``resize_buffer``:
    variable for interface compatibility, does not do anything \ \

Returns:
    vector of bytes \)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_to_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_begin =
R"doc(Get the begin iterator (for range-based for loops)

Returns:
    PyRangeIterator)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_binary_hash =
R"doc(compute a 64 bit hash of the object using xxhash and the \ to_binary
function. This function is called binary because the \ to_binary
function of the object is used)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_end =
R"doc(Get the stop iterator (for range-based for loops)

Returns:
    PyRangeIterator)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_from_binary =
R"doc(convert object to vector of bytes \ \

Parameter ``check_buffer_is_read_completely``:
    variable for interface compatibility, does not do \ anything \ \

Returns:
    vector of bytes \)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_from_stream =
R"doc(Return a PyIndexer read from a binary stream

Parameter ``is``:
    input stream

Returns:
    PyIndexer)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_index_max = R"doc(< the maximum index of the slice (_vector_size - 1 if not sliced))doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_index_min = R"doc(< the minimum index of the slice (0 if not sliced))doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_index_start = R"doc(< the start index of the slice (0 if not sliced))doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_index_step = R"doc(< the step size of the slice (1 if not sliced))doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_index_stop =
R"doc(< the stop index of the slice (_vector_size if not sliced) < (stop is
exclusive) (long because can be negative under some < circumstances
(see below) this index is used for out of bounds)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_info_string =
R"doc(\ return an info string using the class __printer__ object \

Parameter ``float_precision``:
    number of digits for floating point values \

Returns:
    std::string \)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_is_slice = R"doc(< is this a slice?)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_operator_call =
R"doc(Get the index of the element at position i

Parameter ``index``:
    (python style) index of the element (can be negative)

Returns:
    size_t)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_print =
R"doc(\ print the object information to the given outpustream \ \

Parameter ``os``:
    output stream, e.g. file stream or std::out or std::cerr \

Parameter ``float_precision``:
    number of digits for floating point values \)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_printer =
R"doc(Print function, needs __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__ macro
See also: classhelper/objectprinter.hpp

Parameter ``float_precision``:
    Precision of floating point numbers

Returns:
    classhelper::ObjectPrinter)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_reset =
R"doc(Reset the indexer (deactivates slicing)

Parameter ``vector_size``:
    Size of the vector to be indexed)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_reset_2 =
R"doc(Reset the indexer (set up new slicing)

Parameter ``vector_size``:
    Size of the vector to be indexed

Parameter ``start``:
    Start index of the slice

Parameter ``stop``:
    Stop index of the slice

Parameter ``step``:
    Step size of the slice)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_reset_3 =
R"doc(Reset the indexer (set up new slicing)

Parameter ``vector_size``:
    Size of the vector to be indexed

Parameter ``slice``:
    PyIndexer::Slice structure (contains, start, stop, step))doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_reversed =
R"doc(Get a reversed PyIndexer object

Returns:
    PyIndexer)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_set_slice_indexing =
R"doc(Setup slice indexing after construction

Parameter ``slice``:
    PyIndexer::Slice structure (contains, start, stop, step))doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_set_slice_indexing_2 =
R"doc(Setup slice indexing after construction

Parameter ``start``:
    Start index of the slice

Parameter ``stop``:
    Stop index of the slice

Parameter ``step``:
    Step size of the slice)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_size = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_slice_size = R"doc(< the size of the slice (_vector_size if not sliced))doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_slow_hash =
R"doc(compute a 64 bit hash of the object using xxhash and the \ to_binary
function. This function is called binary because the to_binary
function creates \ a copy)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_to_binary =
R"doc(convert object to vector of bytes \ \

Parameter ``resize_buffer``:
    variable for interface compatibility, does not do anything \ \

Returns:
    vector of bytes \)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_to_slice = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_to_stream =
R"doc(Write a PyIndexer to a binary stream

Parameter ``os``:
    output stream)doc";

static const char *__doc_themachinethatgoesping_tools_pyhelper_PyIndexer_vector_size = R"doc(< the size of the vector to be indexed)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


