//sourcehash: 5b38e8381844ce10c24c0ac281b8eff5d3098f4af415c84a08fe19dbff45a0b1

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


static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator =
R"doc(Interface class for interpolator classes This template class
implements base functions interpolators that interpolate between two
values (pairs). This interface implements the search for the x
position within this vector (closest 2 x/y value pair) and computes an
x interpolation value (target_x) Then it call the __call__ functions
of the implementation classes that use this interface to interpolate
between these pairs.

Template Args:
    XType:: type of the x values (must be floating point)
    YType:: type of the y values (typically double or float, but will
          be a vector for the slerp interpolator class))doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_I_PairInterpolator =
R"doc(Construct a new Interpolator object from a vector of pairs
usage: interpolated_y_value = interpolator.interpolate(x_value)

Args:
    X: X vector; must be unique and sorted in ascending order. same
       size as Y!
    Y: Y vector; must be unique and sorted in ascending order. same
       size as X!
    extrapolation_mode: :option o_extr_mode <themachinethatgoesping.to
                        ols.vectorinterpolators.t_extr_mode>` object
                        that describes the extrapolation mode)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_I_PairInterpolator_2 = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_X = R"doc(main data vector containing pairs of corresponding x datapoints)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_Y = R"doc(main data vector containing pairs of corresponding y datapoints)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_append = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_empty = R"doc(check if the interpolator contains data)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_extend = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_get_data_X =
R"doc(return the x component of the internal data vector

Returns:
    std::vector<XType>)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_get_data_Y =
R"doc(return the y component of the internal data vector

Returns:
    std::vector<YType>)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_get_y = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_insert = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_operator_call =
R"doc(get the interpolated y value for given x target

Args:
    target_x: find the corresponding y value for this x value

Returns:
    corresponding y value)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_operator_call_2 =
R"doc(get nearest y values for given x targets (vectorized call)

This function delegates to the base class I_Interpolator's vectorized
operator().

Args:
    targets_x: vector of x values. For each of these values find the
               corresponding y value
    mp_cores: Number of OpenMP threads to use for parallelization.
              Default is 1.

Returns:
    corresponding y values)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_set_data_XY =
R"doc(change the input data to these X and Y vectors
Exception: raises domain error, strong exception guarantee

Args:
    X:: x vector (must be same size, must be sorted in ascending
      order)
    Y:: y vector (must be same size))doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_calc_target_x =
R"doc(compute the interpolation factor between xmin and xmax

Args:
    target_x: x value for which we want to know the interpolation
              factor

Returns:
    interpolation factor)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_t_x_pair = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_xfactor = R"doc(1/(xmax-xmin))doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_xmax = R"doc(larger xvalue)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_xmax_index = R"doc(index of the larger x value (in the internal vector))doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_xmin = R"doc(smaller xvalue)doc";

static const char *mkd_doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_xmin_index = R"doc(index of the smaller x value (in the internal vector))doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


