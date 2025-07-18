//sourcehash: fe78b2fc3ac7d4d6d641e71dc2a690be5ff48d1eca974e3fcb75803abe62bcf4

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


static const char *__doc_themachinethatgoesping_tools_progressbars_ProgressBarChooser =
R"doc(This class allows choosing between different progress bars It will be
extended in the future to allow setting the default progressbar using
a configuration file)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ProgressBarChooser_ProgressBarChooser = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ProgressBarChooser_ProgressBarChooser_2 =
R"doc(Construct a new Progress Bar Chooser. This will select the default
progress bar type if show_progress is true and NoIndicator otherwise.

Parameter ``show_progress``:)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ProgressBarChooser_builtin_progress_bar = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ProgressBarChooser_get =
R"doc(get the ProgressBarInterface

Returns:
    I_ProgressBar&)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ProgressBarChooser_operator_call =
R"doc(This is the visitor function that implicitly converts t_ProgressBar to
I_ProgressBar (the common interface)

Template parameter ``t_ProgressBar``:
    $Parameter ``progress_bar``:

ProgressBar class that is derived from I_ProgressBar

Returns:
    I_ProgressBar&)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_t_BuiltInProgressBar = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_t_BuiltInProgressBar_pbar_Classic = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_t_BuiltInProgressBar_pbar_Indicator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_t_BuiltInProgressBar_pbar_NoIndicator = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


