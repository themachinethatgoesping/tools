//sourcehash: ebf57ba5493feeb855bc02aeddc42d46eca3917f90e000bd4150e06446706481

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


static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBar =
R"doc(This is a generic (abstract) class for progress bars. Usage: call
init() and close() to initialize and finalize the progress bar. Then
call set_progress() or tick() to update the progress bar.
set_postfix() can be used to set a postfix message.

Note: Functions the set_progress and tick functions can significantly
slow down processes that use the progressbar. Consider using the
ProgressBarTimed interface instead.)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_I_ProgressBar = R"doc(Construct a new i progressbar object)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_close =
R"doc(Finalize the progressbar

Parameter ``msg``:
    A message that can be appended as postfix)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_current =
R"doc(Get the current progress state

Returns:
    progress state)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_init =
R"doc(Initialize a new progressbar within the given range

Parameter ``first``:
    lowest number in the range (typically 0.0)

Parameter ``last``:
    highest number in the range (typically 100.0)

Parameter ``process_name``:
    Name of the progress)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_is_initialized = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_set_postfix =
R"doc(Append a postfix message to the progressbar

Parameter ``postfix``:
    postfix message)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_set_prefix =
R"doc(Append a prefix message to the progressbar

Parameter ``prefix``:
    prefix message)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_set_progress =
R"doc(Set the progress state to the given value. Note some implementations
may require the new_progress to be higher than the current progress!

Parameter ``new_progress``:
    New progress state (within the given first/last range))doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_tick =
R"doc(Increment the progress state by the given amount

Parameter ``increment``:
    Number of steps to increment the progress by)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


