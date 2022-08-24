# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

from themachinethatgoesping.tools import progressbars as prg

# import pytest
# import time
import tqdm


class tqdm_wrapper(prg.I_ProgressBarTimed):
    """This is a progressbar wrapper for tqdm for testing purposes.
    It is for testing purposes only and should not be used in production code.
    The main problem is that it does not not play well with tqdm.auto (notebooks).
    """

    # def __init__(self):
    #     # initialize prg.I_ProgressBarTimed base class
    #     super().__init__()

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
        return self.tqdm.n


# define class for grouping (test sections)
class Test_tools_progressbars:
    def test_progressbars_should_not_add_large_overhead_in_test_loops(self):
        N = 100000  # number of iterations in test loop
        t = 10  # time between iterations in test loop (in iterations of complicated operation)

        # t1 = time.time()

        # timing for noindicators (reference)
        time_no_progress = prg.test_loop(prg.NoIndicator(), N, t, False)
        time_no_indicator = prg.test_loop(prg.NoIndicator(), N, t)

        # tqdm wrapper
        time_tqdm_cpp = prg.test_loop(prg.ProgressTqdm(tqdm.tqdm(ncols=100)), N, t)
        time_tqdm_wrapper = prg.test_loop(tqdm_wrapper(), N, t)

        # timing for text progressbar implementations
        time_old_text = prg.test_loop(prg.ConsoleProgressBar(), N, t)
        time_indicators = prg.test_loop(prg.ProgressIndicator(), N, t)

        def relative_time_diff(timing, reference):
            return (timing - reference) / reference * 100

        min_ref = 1000

        print("time_no_progress:  {:3.6f} ms".format(time_no_progress))
        print(
            "time_no_indicator: {:3.6f} ms / {:3.2f} % / {:3.2f} %".format(
                time_no_indicator,
                relative_time_diff(time_no_indicator, time_no_progress),
                relative_time_diff(time_no_indicator, time_no_progress + min_ref),
            )
        )
        print(
            "time_tqdm_cpp:     {:3.6f} ms / {:3.2f} % / {:3.2f} %".format(
                time_tqdm_cpp,
                relative_time_diff(time_tqdm_cpp, time_no_progress),
                relative_time_diff(time_tqdm_cpp, time_no_progress + min_ref),
            )
        )
        print(
            "time_tqdm_wrapper: {:3.6f} ms / {:3.2f} % / {:3.2f} %".format(
                time_tqdm_wrapper,
                relative_time_diff(time_tqdm_wrapper, time_no_progress),
                relative_time_diff(time_tqdm_wrapper, time_no_progress + min_ref),
            )
        )
        print(
            "time_old_text:     {:3.6f} ms / {:3.2f} % / {:3.2f} %".format(
                time_old_text,
                relative_time_diff(time_old_text, time_no_progress),
                relative_time_diff(time_old_text, time_no_progress + min_ref),
            )
        )
        print(
            "time_indicators:   {:3.6f} ms / {:3.2f} % / {:3.2f} %".format(
                time_indicators,
                relative_time_diff(time_indicators, time_no_progress),
                relative_time_diff(time_indicators, time_no_progress + min_ref),
            )
        )

        # check if relative time difference is within tolerance (in %)
        # this should be 2,5 and 15% respectively but for now I relax this for ci building purposes
        assert relative_time_diff(time_no_indicator, time_no_progress + min_ref) < 20
        assert (
            relative_time_diff(time_old_text, time_no_progress + min_ref) < 100
        )  # this can have a rather large overhead
        assert relative_time_diff(time_indicators, time_no_progress + min_ref) < 50
        assert relative_time_diff(time_tqdm_wrapper, time_no_progress + min_ref) < 50
        assert relative_time_diff(time_tqdm_cpp, time_no_progress + min_ref) < 50

        # assert time.time() - t1 < 1  # check if test loop took less than 1 second

    def test_progressbars_should_support_common_functions(self):

        for progressbar in [
            prg.ProgressIndicator(),
            prg.ProgressTqdm(tqdm.tqdm(ncols=100)),
            tqdm_wrapper(),
            prg.ConsoleProgressBar(),
            prg.NoIndicator(),
        ]:
            # test loop
            progressbar.init(0, 100, "test1")
            for _ in range(100):
                progressbar.tick()

            # reinitialize
            progressbar.init(0, 20, "test2")
            for _ in range(20):
                progressbar.tick()
