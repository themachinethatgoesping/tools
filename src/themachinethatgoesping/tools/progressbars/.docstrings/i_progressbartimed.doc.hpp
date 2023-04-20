//sourcehash: a5a395facae50f839cea3a5702ac7a05d6008032a1809f2c37aa8a8b943e4566

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
set_postfix() can be used to set a postfix message. *

The above name functions are guarded by a timer (100ms). The timer is
started when calling set_progress() or tick(). Repetitively calling of
these functions (in a loop) will update the internal state but not
update the progress bar until the timer (100ms) expires.

This ensures a low overhead even for slow progressbar implementations.

All functions are thread-safe.

To implement this interface the abstract callback_ functions must be
implemented.)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_I_ProgressBarTimed = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_apply_state =
R"doc(Apply (call appropriate callback) and reset the internal states to the
progress bar)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_callback_close =
R"doc(Finalize the progressbar

Parameter ``msg``:
    A message that can be appended as postfix)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_callback_current =
R"doc(Get the current progress state

Returns:
    progress state)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_callback_init =
R"doc(Initialize a new progressbar within the given range

Parameter ``first``:
    lowest number in the range (typically 0.0)

Parameter ``last``:
    highest number in the range (typically 100.0)

Parameter ``process_name``:
    Name of the progress)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_callback_set_postfix =
R"doc(Append a postfix message to the progressbar

This callback is guarded by a timer (100ms). If skipped, the postfix
is stored to the internal state and will be applied with the next
successful call to set_progress(), tick() or set_postfix().

Parameter ``postfix``:
    postfix message)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_callback_set_prefix =
R"doc(Set the prefix message to the progressbar

This callback is guarded by a timer (100ms). If skipped, the prefix is
stored to the internal state and will be applied with the next
successful call to set_progress(), tick() or set_prefix().

Parameter ``prefix``:
    prefix message)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_callback_set_progress =
R"doc(Set the progress state to the given value. Note some implementations
may require the new_progress to be higher than the current progress!

This callback is guarded by a timer (100ms). If skipped, the progress
is stored to the internal state and will be applied with the next
successful call to set_progress(), tick() or set_postfix().

Parameter ``new_progress``:
    New progress state (within the given first/last range))doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_callback_tick =
R"doc(Increment the progress state by the given amount This callback is
guarded a timer (100ms).

If skipped, the increment is added to the internal counter and will be
applied with the next unskipped call to tick().

Parameter ``increment``:
    Number of steps to increment the progress by)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_check_timer_every_step = R"doc(< check the timer every n steps (set in apply_state))doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_close =
R"doc(Finalize the progressbar

Parameter ``msg``:
    A message that can be appended as postfix)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_current =
R"doc(Get the current progress state

Returns:
    progress state)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_init =
R"doc(Initialize a new progressbar within the given range

Parameter ``first``:
    lowest number in the range (typically 0.0)

Parameter ``last``:
    highest number in the range (typically 100.0)

Parameter ``process_name``:
    Name of the progress)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_initialized = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_is_initialized = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_max_skips = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_set_postfix =
R"doc(Append a postfix message to the progressbar

This function is guarded a timer. Calls that happen more frequent than
100ms are added to the internal state, but not to the progressbar.

Parameter ``postfix``:
    postfix message)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_set_prefix =
R"doc(Append a prefix message to the progressbar

This function is guarded a timer. Calls that happen more frequent than
100ms are added to the internal state, but not to the progressbar.

Parameter ``prefix``:
    prefix message)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_set_progress =
R"doc(Set the progress state to the given value. Note some implementations
may require the new_progress to be higher than the current progress!

This function is guarded by a timer. Calls that happen more frequent
than 100ms are added to the internal state, but not to the
progressbar.

Parameter ``new_progress``:
    New progress state (within the given first/last range))doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_skip = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_skips = R"doc(< number of skipped progressbar updates (set in apply_state))doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_state_increment = R"doc(< internal counter for the skipped increments)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_state_postfix = R"doc(< internal state for the skipped postfix)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_state_prefix = R"doc(< internal state for the skipped prefix)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_state_progress = R"doc(< internal state for the skipped progress)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_tick =
R"doc(Increment the progress state by the given amount

This function is guarded by a timer. Calls that happen more frequent
than 100ms are added to the internal state, but not to the
progressbar.

Parameter ``increment``:
    Number of steps to increment the progress by)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_x_ms = R"doc(< time to wait for a new progress update (100ms))doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_lock_mutex_for_x_ms = R"doc()doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


