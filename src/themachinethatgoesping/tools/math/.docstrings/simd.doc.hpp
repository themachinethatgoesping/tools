//sourcehash: 9a63ce8dca80ff174e731587c7be32cddd9bc68bd4c1a6d0f7aea788503f1aa4

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


static const char *mkd_doc_themachinethatgoesping_tools_math_fma_dispatch = R"doc(Returning variant: out = fma_dispatch(x, slope, base))doc";

static const char *mkd_doc_themachinethatgoesping_tools_math_fma_dispatch_2 =
R"doc(Write into an xtensor view/container: fma_dispatch(view, x, slope,
base)

Accepts any xtensor expression with contiguous .data() and .size(),
such as xt::view(tensor, row, xt::all()).)doc";

static const char *mkd_doc_themachinethatgoesping_tools_math_fma_dispatch_arch =
R"doc(Return the name of the SIMD architecture selected by fma_dispatch at
runtime. E.g. "avx2", "sse2", "avx512bw", etc.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_math_fma_dispatch_kernel = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_math_fma_dispatch_kernel_operator_call = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_math_fma_xtensor = R"doc(Returning variant: out = fma_xtensor(x, slope, base))doc";

static const char *mkd_doc_themachinethatgoesping_tools_math_fma_xtensor_2 =
R"doc(Write into an xtensor view/container: fma_xtensor(view, x, slope,
base))doc";

static const char *mkd_doc_themachinethatgoesping_tools_math_fmab_dispatch = R"doc(Returning variant: out = fmab_dispatch(x, slope, base_arr))doc";

static const char *mkd_doc_themachinethatgoesping_tools_math_fmab_dispatch_2 =
R"doc(Write into an xtensor view/container: fmab_dispatch(view, x, slope,
base_arr))doc";

static const char *mkd_doc_themachinethatgoesping_tools_math_fmab_dispatch_kernel = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_math_fmab_dispatch_kernel_operator_call = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_math_operator_call = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_math_operator_call_2 = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


