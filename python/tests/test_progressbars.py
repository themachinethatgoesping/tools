# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.tools import progressbars as prg

import time
import pytest
import tqdm


class tqdm_wrapper(prg.I_ProgressBarTimed):
    """This is a progressbar wrapper for tqdm for testing purposes.
    It is for testing purposes only and should not be used in production code.
    The main problem is that it does not not play well with tqdm.auto (notebooks).
    """

    def __init__(self):
        # initialize prg.I_ProgressBarTimed base class
        super().__init__()

    # ----- I_ProgressBarTimed callback interface -----
    # These are virtual methods that are called by the I_ProgressBarTimed interface
    # to update the progressbar. The callbacks are protected by a 100ms timer to avoid
    # too frequent updates.

    def callback_init(self, first, last, process_name="process"):
        self.first = first  # first value of progressbar (usually 0)
        self.tqdm = tqdm.tqdm(total=last - first, desc=process_name, ncols=100)

    def callback_close(self, msg="done"):
        self.tqdm.set_postfix_str("[" + msg + "]")

    def callback_set_progress(self, new_progress):
        self.tqdm.update(new_progress - self.first - self.tqdm.n)

    def callback_set_postfix(self, postfix):
        self.tqdm.set_postfix_str("[" + postfix + "]")

    def callback_tick(self, increment=1):
        self.tqdm.update(increment)

    def callback_current(self):
        self.tqdm.n


# define class for grouping (test sections)
class Test_tools_progressbars:
    def test_progressbars_should_not_add_large_overhead_in_test_loops(self):
        N = 1000000  # number of iterations in test loop
        t = 15       # time between iterations in test loop (in iterations of complicated operation)

        #t1 = time.time()

        # timing for noindicators (reference)
        time_no_progress = prg.test_loop(prg.NoIndicator(), N, t, False)
        time_no_indicator = prg.test_loop(prg.NoIndicator(), N, t)

        # timing for text progressbar implementations
        time_old_text = prg.test_loop(prg.ConsoleProgressBar(), N, t)
        time_indicators = prg.test_loop(prg.ProgressIndicator(), N, t)

        def relative_time_diff(timing, reference):
            return (timing - reference - 500) / reference * 100 - 100 # 500 is the overhead of the test loop

        # check if relative time difference is within tolerance (in %)
        # this should be 2,5 and 15% respectively but for now I relax this for ci building purposes
        assert relative_time_diff(time_no_indicator, time_no_progress) < 20
        assert relative_time_diff(time_old_text, time_no_progress) < 100 #this can have a rather large overhead
        assert relative_time_diff(time_indicators, time_no_progress) < 50

        #assert time.time() - t1 < 1  # check if test loop took less than 1 second

    # def test_progressbar_tqdm_cpp_should_not_add_large_overhead_in_test_loops(self):
    #     N = 1000000  # number of iterations in test loop
    #     t = 15       # time between iterations in test loop (in iterations of complicated operation)

    #     #t1 = time.time()

    #     # timing for noindicators (reference)
    #     time_no_progress = prg.test_loop(prg.NoIndicator(), N, t, False)

    #     # timing for tqdm test implementations
    #     time_tqdm_cpp = prg.test_loop(prg.ProgressTqdm(tqdm.tqdm(ncols=100)), N, t)


    #     def relative_time_diff(timing, reference):
    #         return (timing - reference - 500) / reference * 100 - 100 # 500 is the overhead of the test loop

    #     assert relative_time_diff(time_tqdm_cpp, time_no_progress) < 50

    def test_progressbar_tqdm_wrapper_should_not_add_large_overhead_in_test_loops(self):
        N = 1000000  # number of iterations in test loop
        t = 15       # time between iterations in test loop (in iterations of complicated operation)

        t1 = time.time()

        # timing for noindicators (reference)
        time_no_progress = prg.test_loop(prg.NoIndicator(), N, t, False)

        # timing for tqdm test implementations
        time_tqdm_wrapper = prg.test_loop(tqdm_wrapper(), N, t)


        def relative_time_diff(timing, reference):
            return (timing - reference - 500) / reference * 100 - 100 # 500 is the overhead of the test loop

        assert relative_time_diff(time_tqdm_wrapper, time_no_progress) < 50
    
    # def test_progressbar_tqdm_should_not_cause_a_crash(self):
    #     a=0
    #     for i in tqdm(range(100000)):
    #         a += i**2