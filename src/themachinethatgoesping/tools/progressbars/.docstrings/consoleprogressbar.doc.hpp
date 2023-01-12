//sourcehash: e99c45a864f2b43d056c61e4ccdb607865805bc04e8c3a0ee07599f986684b03

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


static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar =
R"doc(Old-school progress bar that prints to terminal. For reference only,
might be removed in the future.

This class is based in I_ProgressBarTimed such that the callbacks are
guarded by a timer.)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_ConsoleProgressBar = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_callback_close = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_callback_current = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_callback_init = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_callback_set_postfix = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_callback_set_progress = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_callback_tick = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_current = R"doc(< current value)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_currentStep = R"doc(< step (step "/" of _numOf_steps))doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_first = R"doc(< starting value)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_initialized = R"doc(< flag to control if the progressbar is initialized)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_last = R"doc(< ending value)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_numOf_steps = R"doc(< steps till 100% (equals linesize))doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_os = R"doc(< output stream)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


