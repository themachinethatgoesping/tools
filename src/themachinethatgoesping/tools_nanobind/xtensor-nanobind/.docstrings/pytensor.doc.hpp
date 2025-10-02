//sourcehash: 3e3ec9e6d5ef25c29ed0dc371b64eb7b75c4ddb715709cbba06fa1757055792f

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


static const char *__doc_type_caster = R"doc()doc";

static const char *__doc_xt_backstrides_impl = R"doc()doc";

static const char *__doc_xt_backstrides_impl_2 = R"doc()doc";

static const char *__doc_xt_check = R"doc()doc";

static const char *__doc_xt_detail_numpy_strides = R"doc()doc";

static const char *__doc_xt_detail_numpy_strides_2 = R"doc()doc";

static const char *__doc_xt_detail_numpy_strides_value = R"doc()doc";

static const char *__doc_xt_detail_numpy_strides_value_2 = R"doc()doc";

static const char *__doc_xt_ensure = R"doc()doc";

static const char *__doc_xt_from_shape =
R"doc(Allocates and returns an pytensor with the specified shape.

Parameter ``shape``:
    the shape of the pytensor)doc";

static const char *__doc_xt_init_from_python = R"doc()doc";

static const char *__doc_xt_init_tensor = R"doc()doc";

static const char *__doc_xt_operator_assign = R"doc(The assignment operator.)doc";

static const char *__doc_xt_operator_assign_2 = R"doc(The extended assignment operator.)doc";

static const char *__doc_xt_pytensor =
R"doc(@class pytensor Multidimensional container providing the xtensor
container semantics wrapping a numpy array.

pytensor is similar to the xtensor container in that it has a static
dimensionality.

Unlike the pyarray container, pytensor cannot be reshaped with a
different number of dimensions and reshapes are not reflected on the
Python side. However, pytensor has benefits compared to pyarray in
terms of performances. pytensor shapes are stack-allocated which makes
iteration upon pytensor faster than with pyarray.

Template parameter ``T``:
    The type of the element stored in the pyarray.

See also:
    pyarray)doc";

static const char *__doc_xt_pytensor_2 =
R"doc(@class pytensor Multidimensional container providing the xtensor
container semantics wrapping a numpy array.

pytensor is similar to the xtensor container in that it has a static
dimensionality.

Unlike the pyarray container, pytensor cannot be reshaped with a
different number of dimensions and reshapes are not reflected on the
Python side. However, pytensor has benefits compared to pyarray in
terms of performances. pytensor shapes are stack-allocated which makes
iteration upon pytensor faster than with pyarray.

Template parameter ``T``:
    The type of the element stored in the pyarray.

See also:
    pyarray)doc";

static const char *__doc_xt_pytensor_3 = R"doc(Allocates an uninitialized pytensor that holds 1 element.)doc";

static const char *__doc_xt_pytensor_4 = R"doc(Allocates a pytensor with a nested initializer list.)doc";

static const char *__doc_xt_pytensor_5 = R"doc()doc";

static const char *__doc_xt_pytensor_6 = R"doc()doc";

static const char *__doc_xt_pytensor_7 = R"doc()doc";

static const char *__doc_xt_pytensor_8 =
R"doc(Allocates an uninitialized pytensor with the specified shape and
layout.

Parameter ``shape``:
    the shape of the pytensor

Parameter ``l``:
    the layout_type of the pytensor)doc";

static const char *__doc_xt_pytensor_9 =
R"doc(Allocates a pytensor with the specified shape and layout. Elements are
initialized to the specified value.

Parameter ``shape``:
    the shape of the pytensor

Parameter ``value``:
    the value of the elements

Parameter ``l``:
    the layout_type of the pytensor)doc";

static const char *__doc_xt_pytensor_10 =
R"doc(Allocates an uninitialized pytensor with the specified shape and
strides. Elements are initialized to the specified value.

Parameter ``shape``:
    the shape of the pytensor

Parameter ``strides``:
    the strides of the pytensor

Parameter ``value``:
    the value of the elements)doc";

static const char *__doc_xt_pytensor_11 =
R"doc(Allocates an uninitialized pytensor with the specified shape and
strides.

Parameter ``shape``:
    the shape of the pytensor

Parameter ``strides``:
    the strides of the pytensor)doc";

static const char *__doc_xt_pytensor_12 = R"doc(The copy constructor.)doc";

static const char *__doc_xt_pytensor_13 = R"doc(The extended copy constructor.)doc";

static const char *__doc_xt_pytensor_backstrides_impl = R"doc()doc";

static const char *__doc_xt_pytensor_backstrides_impl_2 = R"doc()doc";

static const char *__doc_xt_pytensor_check = R"doc()doc";

static const char *__doc_xt_pytensor_ensure = R"doc()doc";

static const char *__doc_xt_pytensor_from_shape =
R"doc(Allocates and returns an pytensor with the specified shape.

Parameter ``shape``:
    the shape of the pytensor)doc";

static const char *__doc_xt_pytensor_init_from_python = R"doc()doc";

static const char *__doc_xt_pytensor_init_tensor = R"doc()doc";

static const char *__doc_xt_pytensor_m_backstrides = R"doc()doc";

static const char *__doc_xt_pytensor_m_shape = R"doc()doc";

static const char *__doc_xt_pytensor_m_storage = R"doc()doc";

static const char *__doc_xt_pytensor_m_strides = R"doc()doc";

static const char *__doc_xt_pytensor_nested_initializer_list_t = R"doc()doc";

static const char *__doc_xt_pytensor_operator_assign = R"doc(The assignment operator.)doc";

static const char *__doc_xt_pytensor_operator_assign_2 = R"doc()doc";

static const char *__doc_xt_pytensor_operator_assign_3 = R"doc()doc";

static const char *__doc_xt_pytensor_pytensor = R"doc(Allocates an uninitialized pytensor that holds 1 element.)doc";

static const char *__doc_xt_pytensor_pytensor_2 = R"doc()doc";

static const char *__doc_xt_pytensor_pytensor_3 = R"doc()doc";

static const char *__doc_xt_pytensor_pytensor_4 = R"doc()doc";

static const char *__doc_xt_pytensor_pytensor_5 = R"doc()doc";

static const char *__doc_xt_pytensor_pytensor_6 = R"doc()doc";

static const char *__doc_xt_pytensor_pytensor_7 =
R"doc(Allocates an uninitialized pytensor with the specified shape and
strides. Elements are initialized to the specified value.

Parameter ``shape``:
    the shape of the pytensor

Parameter ``strides``:
    the strides of the pytensor

Parameter ``value``:
    the value of the elements)doc";

static const char *__doc_xt_pytensor_pytensor_8 =
R"doc(Allocates an uninitialized pytensor with the specified shape and
strides.

Parameter ``shape``:
    the shape of the pytensor

Parameter ``strides``:
    the strides of the pytensor)doc";

static const char *__doc_xt_pytensor_pytensor_9 = R"doc(The copy constructor.)doc";

static const char *__doc_xt_pytensor_pytensor_10 = R"doc()doc";

static const char *__doc_xt_pytensor_pytensor_11 = R"doc()doc";

static const char *__doc_xt_pytensor_shape_impl = R"doc()doc";

static const char *__doc_xt_pytensor_shape_impl_2 = R"doc()doc";

static const char *__doc_xt_pytensor_storage_impl = R"doc()doc";

static const char *__doc_xt_pytensor_storage_impl_2 = R"doc()doc";

static const char *__doc_xt_pytensor_strides_impl = R"doc()doc";

static const char *__doc_xt_pytensor_strides_impl_2 = R"doc()doc";

static const char *__doc_xt_shape_impl = R"doc()doc";

static const char *__doc_xt_shape_impl_2 = R"doc()doc";

static const char *__doc_xt_storage_impl = R"doc()doc";

static const char *__doc_xt_storage_impl_2 = R"doc()doc";

static const char *__doc_xt_strides_impl = R"doc()doc";

static const char *__doc_xt_strides_impl_2 = R"doc()doc";

static const char *__doc_xt_xcontainer_inner_types = R"doc()doc";

static const char *__doc_xt_xiterable_inner_types = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


