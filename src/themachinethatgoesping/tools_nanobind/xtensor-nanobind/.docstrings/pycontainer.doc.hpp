//sourcehash: 0bef1c9642d47d608276d1ceb54105d30d1baf1ebb47a3aa1d2401a57a48e5a9

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


static const char *__doc_xt_check = R"doc()doc";

static const char *__doc_xt_derived_cast = R"doc()doc";

static const char *__doc_xt_derived_cast_2 = R"doc()doc";

static const char *__doc_xt_detail_check_array = R"doc()doc";

static const char *__doc_xt_detail_check_dims = R"doc()doc";

static const char *__doc_xt_detail_check_dims_run = R"doc()doc";

static const char *__doc_xt_detail_compute_numpy_type_num = R"doc()doc";

static const char *__doc_xt_detail_default_initialize = R"doc()doc";

static const char *__doc_xt_detail_default_initialize_impl = R"doc()doc";

static const char *__doc_xt_detail_default_initialize_impl_2 = R"doc()doc";

static const char *__doc_xt_detail_numpy_descr = R"doc()doc";

static const char *__doc_xt_detail_numpy_dtype_callable = R"doc()doc";

static const char *__doc_xt_detail_numpy_enum_adjuster = R"doc()doc";

static const char *__doc_xt_detail_numpy_enum_adjuster_2 = R"doc()doc";

static const char *__doc_xt_detail_numpy_enum_adjuster_pyarray_type = R"doc()doc";

static const char *__doc_xt_detail_numpy_enum_adjuster_pyarray_type_2 = R"doc()doc";

static const char *__doc_xt_detail_pyarray_type = R"doc()doc";

static const char *__doc_xt_ensure = R"doc()doc";

static const char *__doc_xt_get_buffer_size = R"doc()doc";

static const char *__doc_xt_import_numpy = R"doc()doc";

static const char *__doc_xt_is_contiguous =
R"doc(Return whether or not the container uses contiguous buffer

Returns:
    Boolean for contiguous buffer)doc";

static const char *__doc_xt_layout =
R"doc(Return the layout_type of the container

Returns:
    layout_type of the container)doc";

static const char *__doc_xt_pycontainer =
R"doc(@class pycontainer Base class for xtensor containers wrapping numpy
arrays using nanobind.

The pycontainer class should not be instantiated directly. Instead,
users should use pytensor and pyarray instances.

Template parameter ``D``:
    The derived type, i.e. the inheriting class for which pycontainer
    provides the interface.)doc";

static const char *__doc_xt_pycontainer_2 = R"doc(pycontainer implementation *)doc";

static const char *__doc_xt_pycontainer_3 = R"doc()doc";

static const char *__doc_xt_pycontainer_4 = R"doc()doc";

static const char *__doc_xt_pycontainer_5 = R"doc()doc";

static const char *__doc_xt_pycontainer_check = R"doc()doc";

static const char *__doc_xt_pycontainer_derived_cast = R"doc()doc";

static const char *__doc_xt_pycontainer_derived_cast_2 = R"doc()doc";

static const char *__doc_xt_pycontainer_ensure = R"doc()doc";

static const char *__doc_xt_pycontainer_get_buffer_size = R"doc()doc";

static const char *__doc_xt_pycontainer_is_contiguous =
R"doc(Return whether or not the container uses contiguous buffer

Returns:
    Boolean for contiguous buffer)doc";

static const char *__doc_xt_pycontainer_layout = R"doc()doc";

static const char *__doc_xt_pycontainer_operator_assign = R"doc()doc";

static const char *__doc_xt_pycontainer_operator_assign_2 = R"doc()doc";

static const char *__doc_xt_pycontainer_pycontainer = R"doc(pycontainer implementation *)doc";

static const char *__doc_xt_pycontainer_pycontainer_2 = R"doc()doc";

static const char *__doc_xt_pycontainer_pycontainer_3 = R"doc()doc";

static const char *__doc_xt_pycontainer_pycontainer_4 = R"doc()doc";

static const char *__doc_xt_pycontainer_pycontainer_5 = R"doc()doc";

static const char *__doc_xt_pycontainer_pycontainer_6 = R"doc()doc";

static const char *__doc_xt_pycontainer_python_array = R"doc()doc";

static const char *__doc_xt_pycontainer_raw_array_t = R"doc()doc";

static const char *__doc_xt_pycontainer_reshape = R"doc()doc";

static const char *__doc_xt_pycontainer_resize =
R"doc(resizes the container.

Parameter ``shape``:
    the new shape)doc";

static const char *__doc_xt_pycontainer_resize_2 = R"doc()doc";

static const char *__doc_xt_pycontainer_resize_3 = R"doc()doc";

static const char *__doc_xt_python_array = R"doc()doc";

static const char *__doc_xt_raw_array_t = R"doc()doc";

static const char *__doc_xt_reshape = R"doc()doc";

static const char *__doc_xt_resize =
R"doc(resizes the container.

Parameter ``shape``:
    the new shape)doc";

static const char *__doc_xt_resize_2 =
R"doc(resizes the container.

Parameter ``shape``:
    the new shape

Parameter ``l``:
    the new layout)doc";

static const char *__doc_xt_resize_3 =
R"doc(resizes the container.

Parameter ``shape``:
    the new shape

Parameter ``strides``:
    the new strides)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


