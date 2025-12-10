//sourcehash: 2b69c4658a32723cc90daac4bd4b1e6b9de33fdd7e9fbdd718a009ae7e387eb2

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


static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer =
R"doc(A class to compute python style indexing Allow for negative indexing
(starting from the stop of the container) Allow for sliced indexing
(start, stop, step))doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyIndexer = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyIndexer_2 =
R"doc(Construct a new Py Indexer object   * Allow for negative indexing
(starting from the stop of the container)

Args:
    vector_size: Size of the vector to be indexed)doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyIndexer_3 =
R"doc(Construct a new Py Indexer object Allow for negative indexing
(starting from the stop of the container) Allow for sliced indexing
(start, stop, step)

Args:
    vector_size: Size of the vector to be indexed
    start: Start index of the slice
    stop: Stop index of the slice
    step: Step size of the slice)doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyIndexer_4 =
R"doc(Construct a new Py Indexer object Allow for negative indexing
(starting from the stop of the container) Allow for sliced indexing
(start, stop, step)

Args:
    vector_size: Size of the vector to be indexed
    slice: PyIndexer::Slice structure (contains, start, stop, step))doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyRangeIterator = R"doc(Simple iterator class to allow for range-based for loops)doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyRangeIterator_PyRangeIterator = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyRangeIterator_operator_inc = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyRangeIterator_operator_mul = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyRangeIterator_operator_ne =
R"doc(operator != for range-based for loops Only compare _val, since _step
is not relevant for the it != stop comparison

Args:
    rhs: 

Returns:
    true false)doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyRangeIterator_step = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_PyRangeIterator_val = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice = R"doc(A structure to hold a slice)doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_Slice = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_Slice_2 = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_binary_hash =
R"doc(compute a 64 bit hash of the object using xxhash and the       \
to_binary function. This  function is called binary because the
\ to_binary  function of the object is used)doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_from_binary =
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

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_from_stream = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_info_string =
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

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_operator_eq = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_print =
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

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_printer = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_start = R"doc(the start index of the slice (None if not sliced))doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_step = R"doc(the step size of the slice (1 if not sliced))doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_stop = R"doc(the stop index of the slice (None if not sliced) (stop is exclusive))doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_to_binary =
R"doc(convert object to vector of bytes
\
                                                                                            \
Args:
    resize_buffer: variable for interface compatibility, does not do
                   anything             \ \

Returns:
    vector of bytes
    \)doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_Slice_to_stream = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_begin =
R"doc(Get the begin iterator (for range-based for loops)

Returns:
    PyRangeIterator)doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_binary_hash =
R"doc(compute a 64 bit hash of the object using xxhash and the       \
to_binary function. This  function is called binary because the
\ to_binary  function of the object is used)doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_end =
R"doc(Get the stop iterator (for range-based for loops)

Returns:
    PyRangeIterator)doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_from_binary =
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

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_from_stream =
R"doc(Return a PyIndexer read from a binary stream

Args:
    is: input stream

Returns:
    PyIndexer)doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_index_max = R"doc(the maximum index of the slice (_vector_size - 1 if not sliced))doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_index_min = R"doc(the minimum index of the slice (0 if not sliced))doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_index_start = R"doc(the start index of the slice (0 if not sliced))doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_index_step = R"doc(the step size of the slice (1 if not sliced))doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_index_stop =
R"doc(the stop index of the slice (_vector_size if not sliced) (stop is
exclusive) (int64_t because can be negative under some circumstances
(see below) this index is used for out of bounds)doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_info_string =
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

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_is_slice = R"doc(is this a slice?)doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_operator_call =
R"doc(Get the index of the element at position i

Args:
    index: (python style) index of the element (can be negative)

Returns:
    size_t)doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_operator_eq = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_print =
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

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_printer =
R"doc(Print function, needs __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__ macro
See also: classhelper/objectprinter.hpp

Args:
    float_precision: Precision of floating point numbers

Returns:
    classhelper::ObjectPrinter)doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_reset =
R"doc(Reset the indexer (deactivates slicing)

Args:
    vector_size: Size of the vector to be indexed)doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_reset_2 =
R"doc(Reset the indexer (set up new slicing)

Args:
    vector_size: Size of the vector to be indexed
    start: Start index of the slice
    stop: Stop index of the slice
    step: Step size of the slice)doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_reset_3 =
R"doc(Reset the indexer (set up new slicing)

Args:
    vector_size: Size of the vector to be indexed
    slice: PyIndexer::Slice structure (contains, start, stop, step))doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_reversed =
R"doc(Get a reversed PyIndexer object

Returns:
    PyIndexer)doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_set_slice_indexing =
R"doc(Setup slice indexing after construction

Args:
    slice: PyIndexer::Slice structure (contains, start, stop, step))doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_set_slice_indexing_2 =
R"doc(Setup slice indexing after construction

Args:
    start: Start index of the slice
    stop: Stop index of the slice
    step: Step size of the slice)doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_size = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_slice_size = R"doc(the size of the slice (_vector_size if not sliced))doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_to_binary =
R"doc(convert object to vector of bytes
\
                                                                                            \
Args:
    resize_buffer: variable for interface compatibility, does not do
                   anything             \ \

Returns:
    vector of bytes
    \)doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_to_slice = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_to_stream =
R"doc(Write a PyIndexer to a binary stream

Args:
    os: output stream)doc";

static const char *mkd_doc_themachinethatgoesping_tools_pyhelper_PyIndexer_vector_size = R"doc(the size of the vector to be indexed)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


