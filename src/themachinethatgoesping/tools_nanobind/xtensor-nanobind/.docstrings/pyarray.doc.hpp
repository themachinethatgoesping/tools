//sourcehash: 50bd11558160e681000105dc27a8f7dd230156a071e59739dd5afeea7ef91879

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


static const char *__doc_xt_backstrides_impl = R"doc()doc";

static const char *__doc_xt_check = R"doc()doc";

static const char *__doc_xt_default_dynamic_layout = R"doc()doc";

static const char *__doc_xt_ensure = R"doc()doc";

static const char *__doc_xt_from_shape =
R"doc(Allocates and returns an pyarray with the specified shape.

Parameter ``shape``:
    the shape of the pyarray)doc";

static const char *__doc_xt_init_array = R"doc()doc";

static const char *__doc_xt_init_from_python = R"doc()doc";

static const char *__doc_xt_operator_assign = R"doc(The assignment operator.)doc";

static const char *__doc_xt_operator_assign_2 = R"doc(The extended assignment operator.)doc";

static const char *__doc_xt_pyarray =
R"doc(@class pyarray Multidimensional container providing the xtensor
container semantics to a numpy array.

pyarray is similar to the xarray container in that it has a dynamic
dimensionality. Reshapes of a pyarray container are reflected in the
underlying numpy array.

Template parameter ``T``:
    The type of the element stored in the pyarray.

Template parameter ``L``:
    Static layout of the pyarray

See also:
    pytensor)doc";

static const char *__doc_xt_pyarray_2 =
R"doc(@class pyarray Multidimensional container providing the xtensor
container semantics to a numpy array.

pyarray is similar to the xarray container in that it has a dynamic
dimensionality. Reshapes of a pyarray container are reflected in the
underlying numpy array.

Template parameter ``T``:
    The type of the element stored in the pyarray.

Template parameter ``L``:
    Static layout of the pyarray

See also:
    pytensor)doc";

static const char *__doc_xt_pyarray_3 = R"doc()doc";

static const char *__doc_xt_pyarray_4 = R"doc(Allocates a pyarray with nested initializer lists.)doc";

static const char *__doc_xt_pyarray_5 = R"doc()doc";

static const char *__doc_xt_pyarray_6 = R"doc()doc";

static const char *__doc_xt_pyarray_7 = R"doc()doc";

static const char *__doc_xt_pyarray_8 = R"doc()doc";

static const char *__doc_xt_pyarray_9 = R"doc()doc";

static const char *__doc_xt_pyarray_10 = R"doc()doc";

static const char *__doc_xt_pyarray_11 = R"doc()doc";

static const char *__doc_xt_pyarray_12 = R"doc()doc";

static const char *__doc_xt_pyarray_13 =
R"doc(Allocates an uninitialized pyarray with the specified shape and
layout.

Parameter ``shape``:
    the shape of the pyarray

Parameter ``l``:
    the layout of the pyarray)doc";

static const char *__doc_xt_pyarray_14 =
R"doc(Allocates a pyarray with the specified shape and layout. Elements are
initialized to the specified value.

Parameter ``shape``:
    the shape of the pyarray

Parameter ``value``:
    the value of the elements

Parameter ``l``:
    the layout of the pyarray)doc";

static const char *__doc_xt_pyarray_15 =
R"doc(Allocates an uninitialized pyarray with the specified shape and
strides. Elements are initialized to the specified value.

Parameter ``shape``:
    the shape of the pyarray

Parameter ``strides``:
    the strides of the pyarray

Parameter ``value``:
    the value of the elements)doc";

static const char *__doc_xt_pyarray_16 =
R"doc(Allocates an uninitialized pyarray with the specified shape and
strides.

Parameter ``shape``:
    the shape of the pyarray

Parameter ``strides``:
    the strides of the pyarray)doc";

static const char *__doc_xt_pyarray_17 = R"doc(The copy constructor.)doc";

static const char *__doc_xt_pyarray_18 = R"doc(The extended copy constructor.)doc";

static const char *__doc_xt_pyarray_backstrides_impl = R"doc()doc";

static const char *__doc_xt_pyarray_check = R"doc()doc";

static const char *__doc_xt_pyarray_default_dynamic_layout = R"doc()doc";

static const char *__doc_xt_pyarray_ensure = R"doc()doc";

static const char *__doc_xt_pyarray_from_shape =
R"doc(Allocates and returns an pyarray with the specified shape.

Parameter ``shape``:
    the shape of the pyarray)doc";

static const char *__doc_xt_pyarray_init_array = R"doc()doc";

static const char *__doc_xt_pyarray_init_from_python = R"doc()doc";

static const char *__doc_xt_pyarray_m_backstrides = R"doc()doc";

static const char *__doc_xt_pyarray_m_shape = R"doc()doc";

static const char *__doc_xt_pyarray_m_storage = R"doc()doc";

static const char *__doc_xt_pyarray_m_strides = R"doc()doc";

static const char *__doc_xt_pyarray_nested_initializer_list_t = R"doc()doc";

static const char *__doc_xt_pyarray_operator_assign = R"doc(The assignment operator.)doc";

static const char *__doc_xt_pyarray_operator_assign_2 = R"doc()doc";

static const char *__doc_xt_pyarray_operator_assign_3 = R"doc()doc";

static const char *__doc_xt_pyarray_pyarray = R"doc()doc";

static const char *__doc_xt_pyarray_pyarray_2 = R"doc(Allocates a pyarray with nested initializer lists.)doc";

static const char *__doc_xt_pyarray_pyarray_3 = R"doc()doc";

static const char *__doc_xt_pyarray_pyarray_4 = R"doc()doc";

static const char *__doc_xt_pyarray_pyarray_5 = R"doc()doc";

static const char *__doc_xt_pyarray_pyarray_6 = R"doc()doc";

static const char *__doc_xt_pyarray_pyarray_7 = R"doc()doc";

static const char *__doc_xt_pyarray_pyarray_8 = R"doc()doc";

static const char *__doc_xt_pyarray_pyarray_9 = R"doc()doc";

static const char *__doc_xt_pyarray_pyarray_10 = R"doc()doc";

static const char *__doc_xt_pyarray_pyarray_11 = R"doc()doc";

static const char *__doc_xt_pyarray_pyarray_12 =
R"doc(Allocates an uninitialized pyarray with the specified shape and
strides. Elements are initialized to the specified value.

Parameter ``shape``:
    the shape of the pyarray

Parameter ``strides``:
    the strides of the pyarray

Parameter ``value``:
    the value of the elements)doc";

static const char *__doc_xt_pyarray_pyarray_13 =
R"doc(Allocates an uninitialized pyarray with the specified shape and
strides.

Parameter ``shape``:
    the shape of the pyarray

Parameter ``strides``:
    the strides of the pyarray)doc";

static const char *__doc_xt_pyarray_pyarray_14 = R"doc(The copy constructor.)doc";

static const char *__doc_xt_pyarray_pyarray_15 = R"doc()doc";

static const char *__doc_xt_pyarray_pyarray_16 = R"doc()doc";

static const char *__doc_xt_pyarray_shape_impl = R"doc()doc";

static const char *__doc_xt_pyarray_storage_impl = R"doc()doc";

static const char *__doc_xt_pyarray_storage_impl_2 = R"doc()doc";

static const char *__doc_xt_pyarray_strides_impl = R"doc()doc";

static const char *__doc_xt_shape_impl = R"doc()doc";

static const char *__doc_xt_storage_impl = R"doc()doc";

static const char *__doc_xt_storage_impl_2 = R"doc()doc";

static const char *__doc_xt_strides_impl = R"doc()doc";

static const char *__doc_xt_xcontainer_inner_types = R"doc()doc";

static const char *__doc_xt_xiterable_inner_types = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


