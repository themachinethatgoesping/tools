//sourcehash: ebf57ba5493feeb855bc02aeddc42d46eca3917f90e000bd4150e06446706481

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


static const char *mkd_doc_themachinethatgoesping_tools_progressbars_I_ProgressBar =
R"doc(This is a generic (abstract) class for progress bars.
Usage: call init() and close() to initialize and finalize the progress
       bar.
Then call set_progress() or tick() to update the progress bar.
set_postfix() can be used to set a postfix message.

Note: Functions the set_progress and tick functions can significantly
      slow down processes that
use the progressbar. Consider using the ProgressBarTimed interface
instead.)doc";

static const char *mkd_doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_I_ProgressBar = R"doc(Construct a new i progressbar object)doc";

static const char *mkd_doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_close =
R"doc(Finalize the progressbar

Args:
    msg: A message that can be appended as postfix)doc";

static const char *mkd_doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_current =
R"doc(Get the current progress state

Returns:
    progress state)doc";

static const char *mkd_doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_init =
R"doc(Initialize a new progressbar within the given range

Args:
    first: lowest number in the range (typically 0.0)
    last: highest number in the range (typically 100.0)
    process_name: Name of the progress)doc";

static const char *mkd_doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_is_initialized = R"doc()doc";

static const char *mkd_doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_set_postfix =
R"doc(Append a postfix message to the progressbar

Args:
    postfix: postfix message)doc";

static const char *mkd_doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_set_prefix =
R"doc(Append a prefix message to the progressbar

Args:
    prefix: prefix message)doc";

static const char *mkd_doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_set_progress =
R"doc(Set the progress state to the given value. Note some implementations
may require the new_progress to be higher than the current progress!

Args:
    new_progress: New progress state (within the given first/last
                  range))doc";

static const char *mkd_doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_tick =
R"doc(Increment the progress state by the given amount

Args:
    increment: Number of steps to increment the progress by)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


