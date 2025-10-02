//sourcehash: c0cfcaf227d769518e2960d27285d9090d339df5c12d6b576b32c6ce9a7a9448

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


static const char *__doc_xt_back = R"doc()doc";

static const char *__doc_xt_begin = R"doc()doc";

static const char *__doc_xt_cbegin = R"doc()doc";

static const char *__doc_xt_cend = R"doc()doc";

static const char *__doc_xt_crbegin = R"doc()doc";

static const char *__doc_xt_crend = R"doc()doc";

static const char *__doc_xt_empty = R"doc()doc";

static const char *__doc_xt_end = R"doc()doc";

static const char *__doc_xt_front = R"doc()doc";

static const char *__doc_xt_operator_array = R"doc()doc";

static const char *__doc_xt_operator_eq = R"doc()doc";

static const char *__doc_xt_operator_ge = R"doc()doc";

static const char *__doc_xt_operator_gt = R"doc()doc";

static const char *__doc_xt_operator_le = R"doc()doc";

static const char *__doc_xt_operator_lt = R"doc()doc";

static const char *__doc_xt_operator_ne = R"doc()doc";

static const char *__doc_xt_pystrides_adaptor = R"doc(pystrides_adaptor declaration *)doc";

static const char *__doc_xt_pystrides_adaptor_2 = R"doc(pystrides_adaptor implementation *)doc";

static const char *__doc_xt_pystrides_adaptor_back = R"doc()doc";

static const char *__doc_xt_pystrides_adaptor_begin = R"doc()doc";

static const char *__doc_xt_pystrides_adaptor_cbegin = R"doc()doc";

static const char *__doc_xt_pystrides_adaptor_cend = R"doc()doc";

static const char *__doc_xt_pystrides_adaptor_crbegin = R"doc()doc";

static const char *__doc_xt_pystrides_adaptor_crend = R"doc()doc";

static const char *__doc_xt_pystrides_adaptor_empty = R"doc()doc";

static const char *__doc_xt_pystrides_adaptor_end = R"doc()doc";

static const char *__doc_xt_pystrides_adaptor_front = R"doc()doc";

static const char *__doc_xt_pystrides_adaptor_m_size = R"doc()doc";

static const char *__doc_xt_pystrides_adaptor_operator_array = R"doc()doc";

static const char *__doc_xt_pystrides_adaptor_p_data = R"doc()doc";

static const char *__doc_xt_pystrides_adaptor_p_shape = R"doc()doc";

static const char *__doc_xt_pystrides_adaptor_pystrides_adaptor = R"doc()doc";

static const char *__doc_xt_pystrides_adaptor_pystrides_adaptor_2 = R"doc(pystrides_adaptor implementation *)doc";

static const char *__doc_xt_pystrides_adaptor_rbegin = R"doc()doc";

static const char *__doc_xt_pystrides_adaptor_rend = R"doc()doc";

static const char *__doc_xt_pystrides_adaptor_size = R"doc()doc";

static const char *__doc_xt_pystrides_iterator = R"doc(pystrides_iterator declaration *)doc";

static const char *__doc_xt_pystrides_iterator_2 = R"doc(pystrides_iterator declaration *)doc";

static const char *__doc_xt_pystrides_iterator_get_pointer = R"doc()doc";

static const char *__doc_xt_pystrides_iterator_operator_add = R"doc()doc";

static const char *__doc_xt_pystrides_iterator_operator_array = R"doc()doc";

static const char *__doc_xt_pystrides_iterator_operator_dec = R"doc()doc";

static const char *__doc_xt_pystrides_iterator_operator_dec_2 = R"doc()doc";

static const char *__doc_xt_pystrides_iterator_operator_iadd = R"doc()doc";

static const char *__doc_xt_pystrides_iterator_operator_inc = R"doc()doc";

static const char *__doc_xt_pystrides_iterator_operator_inc_2 = R"doc()doc";

static const char *__doc_xt_pystrides_iterator_operator_isub = R"doc()doc";

static const char *__doc_xt_pystrides_iterator_operator_mul = R"doc()doc";

static const char *__doc_xt_pystrides_iterator_operator_sub = R"doc()doc";

static const char *__doc_xt_pystrides_iterator_operator_sub_2 = R"doc()doc";

static const char *__doc_xt_pystrides_iterator_operator_sub_3 = R"doc()doc";

static const char *__doc_xt_pystrides_iterator_p_current = R"doc()doc";

static const char *__doc_xt_pystrides_iterator_p_shape = R"doc()doc";

static const char *__doc_xt_pystrides_iterator_pystrides_iterator = R"doc()doc";

static const char *__doc_xt_rbegin = R"doc()doc";

static const char *__doc_xt_rend = R"doc()doc";

static const char *__doc_xt_size = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


