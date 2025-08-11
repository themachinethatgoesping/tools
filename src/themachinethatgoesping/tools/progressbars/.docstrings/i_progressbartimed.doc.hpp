//sourcehash: 9260e151cae1d3abd1f4bfe6a23961bf53f6b8d388e0b7e60b2fdb00d7725308

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


static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed =
R"doc(This is a generic (abstract) class for progress bars. Usage: call
init() and close() to initialize and finalize the progress bar. Then
call set_progress() or tick() to update the progress bar.
set_postfix() can be used to set a postfix message.

The above name functions are guarded by a timer (100ms). The timer is
started when calling set_progress() or tick(). Repetitively calling of
these functions (in a loop) will update the internal state but not
update the progress bar until the timer (100ms) expires.

This ensures a low overhead even for slow progressbar implementations.

All functions are thread-safe.

To implement this interface the abstract callback_ functions must be
implemented.)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_I_ProgressBarTimed = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_apply_state = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_callback_close = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_callback_current = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_callback_init = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_callback_set_postfix = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_callback_set_prefix = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_callback_set_progress = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_callback_tick = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_check_timer_every_step = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_close = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_current = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_init = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_is_initialized = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_is_initialized_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_max_skips = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_set_postfix = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_set_prefix = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_set_progress = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_skip = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_skips = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_state_increment = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_state_postfix = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_state_prefix = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_state_progress = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_tick = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_x_ms = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


