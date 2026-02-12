//sourcehash: 60be23ffab95b5ffdfed2cfcc3fb9748e42d7fbfa2bbbb6bf680744ec17e3d03

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


static const char *mkd_doc_themachinethatgoesping_tools_helper_osstream =
R"doc(A fast std::ostream that writes directly into a caller-owned
std::string. Drop-in replacement for std::ostringstream in
serialization code.

Usage:
  std::string result;
  osstream os(result); obj.to_stream(os); return result;  // NRVO,
  zero copies)doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_osstream_osstream = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_string_output_buf =
R"doc(std::streambuf implementation that writes into a caller-owned
    std::string.
Supports seekp/tellp for serialization code that uses two-pass write
patterns (e.g. writing placeholder values, then seeking back to fill
them in).)doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_string_output_buf_buffer = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_string_output_buf_overflow = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_string_output_buf_pos = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_string_output_buf_seekoff = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_string_output_buf_seekpos = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_string_output_buf_size = R"doc(Get the current size of the buffer.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_string_output_buf_string_output_buf = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_helper_string_output_buf_xsputn = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


