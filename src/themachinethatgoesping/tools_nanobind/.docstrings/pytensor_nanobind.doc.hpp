//sourcehash: 3e377766da69403b0f8344f0f1c96c5452ce05b1d1c017a270373f2f856c12ef

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


static const char *__doc_pytensor_xtensor_caster_impl = R"doc()doc";

static const char *__doc_pytensor_xtensor_caster_impl_NB_TYPE_CASTER = R"doc()doc";

static const char *__doc_type_caster = R"doc()doc";

static const char *__doc_xt_detail_is_crtp_base_of_impl = R"doc()doc";

static const char *__doc_xt_detail_select_xfunction_expression = R"doc()doc";

static const char *__doc_xt_extension_nanobind_expression_base = R"doc()doc";

static const char *__doc_xt_extension_xbroadcast_base_impl = R"doc()doc";

static const char *__doc_xt_extension_xfunction_base_impl = R"doc()doc";

static const char *__doc_xt_extension_xindex_view_base_impl = R"doc()doc";

static const char *__doc_xt_extension_xreducer_base_impl = R"doc()doc";

static const char *__doc_xt_extension_xview_base_impl = R"doc()doc";

static const char *__doc_xt_has_assign_conversion = R"doc()doc";

static const char *__doc_xt_index_view = R"doc()doc";

static const char *__doc_xt_nanobind_detail_compute_contiguous_strides_column_major = R"doc()doc";

static const char *__doc_xt_nanobind_detail_compute_contiguous_strides_row_major = R"doc()doc";

static const char *__doc_xt_nanobind_detail_is_column_major = R"doc()doc";

static const char *__doc_xt_nanobind_detail_is_row_major = R"doc()doc";

static const char *__doc_xt_nanobind_detail_ndarray_type_helper = R"doc()doc";

static const char *__doc_xt_nanobind_detail_pytensor_index_view = R"doc()doc";

static const char *__doc_xt_nanobind_detail_pytensor_index_view_assign_element = R"doc()doc";

static const char *__doc_xt_nanobind_detail_pytensor_index_view_assign_element_impl = R"doc()doc";

static const char *__doc_xt_nanobind_detail_pytensor_index_view_m_indices = R"doc()doc";

static const char *__doc_xt_nanobind_detail_pytensor_index_view_m_tensor = R"doc()doc";

static const char *__doc_xt_nanobind_detail_pytensor_index_view_operator_assign = R"doc()doc";

static const char *__doc_xt_nanobind_detail_pytensor_index_view_pytensor_index_view = R"doc()doc";

static const char *__doc_xt_nanobind_pytensor = R"doc()doc";

static const char *__doc_xt_nanobind_pytensor_expression_tag = R"doc()doc";

static const char *__doc_xt_nanobind_pytensor_from_shape = R"doc()doc";

static const char *__doc_xt_nanobind_pytensor_operator_assign = R"doc()doc";

static const char *__doc_xt_nanobind_pytensor_operator_assign_2 = R"doc()doc";

static const char *__doc_xt_nanobind_pytensor_pytensor = R"doc()doc";

static const char *__doc_xt_nanobind_pytensor_pytensor_2 = R"doc()doc";

static const char *__doc_xt_nanobind_pytensor_pytensor_3 = R"doc()doc";

static const char *__doc_xt_nanobind_pytensor_scalar_type = R"doc()doc";

static const char *__doc_xt_temporary_type_from_tag = R"doc()doc";

static const char *__doc_xt_xcontainer_inner_types = R"doc()doc";

static const char *__doc_xt_xexpression_assigner_base = R"doc()doc";

static const char *__doc_xt_xiterable_inner_types = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


