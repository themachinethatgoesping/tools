//sourcehash: ee826bdbdd329303461654dcedf29a29900f63d4222d54ed14d4833b76391814

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


static const char *mkd_doc_pytensor_xtensor_caster_impl = R"doc()doc";

static const char *mkd_doc_pytensor_xtensor_caster_impl_NB_TYPE_CASTER = R"doc()doc";

static const char *mkd_doc_type_caster = R"doc()doc";

static const char *mkd_doc_xt_detail_is_crtp_base_of_impl = R"doc()doc";

static const char *mkd_doc_xt_detail_select_xfunction_expression = R"doc()doc";

static const char *mkd_doc_xt_extension_nanobind_expression_base = R"doc()doc";

static const char *mkd_doc_xt_extension_xbroadcast_base_impl = R"doc()doc";

static const char *mkd_doc_xt_extension_xfunction_base_impl = R"doc()doc";

static const char *mkd_doc_xt_extension_xindex_view_base_impl = R"doc()doc";

static const char *mkd_doc_xt_extension_xreducer_base_impl = R"doc()doc";

static const char *mkd_doc_xt_extension_xview_base_impl = R"doc()doc";

static const char *mkd_doc_xt_has_assign_conversion = R"doc()doc";

static const char *mkd_doc_xt_index_view = R"doc()doc";

static const char *mkd_doc_xt_nanobind_detail_compute_contiguous_strides_column_major = R"doc()doc";

static const char *mkd_doc_xt_nanobind_detail_compute_contiguous_strides_row_major = R"doc()doc";

static const char *mkd_doc_xt_nanobind_detail_is_column_major = R"doc()doc";

static const char *mkd_doc_xt_nanobind_detail_is_row_major = R"doc()doc";

static const char *mkd_doc_xt_nanobind_detail_ndarray_type_helper = R"doc()doc";

static const char *mkd_doc_xt_nanobind_detail_pytensor_index_view = R"doc()doc";

static const char *mkd_doc_xt_nanobind_detail_pytensor_index_view_assign_element = R"doc()doc";

static const char *mkd_doc_xt_nanobind_detail_pytensor_index_view_assign_element_impl = R"doc()doc";

static const char *mkd_doc_xt_nanobind_detail_pytensor_index_view_m_indices = R"doc()doc";

static const char *mkd_doc_xt_nanobind_detail_pytensor_index_view_m_tensor = R"doc()doc";

static const char *mkd_doc_xt_nanobind_detail_pytensor_index_view_operator_assign = R"doc()doc";

static const char *mkd_doc_xt_nanobind_detail_pytensor_index_view_pytensor_index_view = R"doc()doc";

static const char *mkd_doc_xt_nanobind_pytensor = R"doc()doc";

static const char *mkd_doc_xt_nanobind_pytensor_expression_tag = R"doc()doc";

static const char *mkd_doc_xt_nanobind_pytensor_from_shape = R"doc()doc";

static const char *mkd_doc_xt_nanobind_pytensor_operator_assign = R"doc()doc";

static const char *mkd_doc_xt_nanobind_pytensor_operator_assign_2 = R"doc()doc";

static const char *mkd_doc_xt_nanobind_pytensor_pytensor = R"doc()doc";

static const char *mkd_doc_xt_nanobind_pytensor_pytensor_2 = R"doc()doc";

static const char *mkd_doc_xt_nanobind_pytensor_pytensor_3 = R"doc()doc";

static const char *mkd_doc_xt_nanobind_pytensor_scalar_type = R"doc()doc";

static const char *mkd_doc_xt_temporary_type_from_tag = R"doc()doc";

static const char *mkd_doc_xt_xcontainer_inner_types = R"doc()doc";

static const char *mkd_doc_xt_xexpression_assigner_base = R"doc()doc";

static const char *mkd_doc_xt_xiterable_inner_types = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


