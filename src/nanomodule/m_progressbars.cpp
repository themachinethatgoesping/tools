// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- c++ library headers
#include <memory>
#include <random>
#include <type_traits>

// -- include nanobind headers
#include <nanobind/nanobind.h>
#include <nanobind/stl/chrono.h>
#include <nanobind/stl/string.h>
#include <nanobind/trampoline.h>

// ping headers
#include <themachinethatgoesping/tools_nanobind/ostream_redirect.hpp>
#include <themachinethatgoesping/tools_nanobind/scoped_ostream_redirect.hpp>

#include <themachinethatgoesping/tools/progressbars/consoleprogressbar.hpp>
#include <themachinethatgoesping/tools/progressbars/i_progressbar.hpp>
#include <themachinethatgoesping/tools/progressbars/noindicator.hpp>
#include <themachinethatgoesping/tools/progressbars/progressbarchooser.hpp>
#include <themachinethatgoesping/tools/progressbars/progressindicator.hpp>
#include <themachinethatgoesping/tools/progressbars/progresstqdm_nano.hpp>

// Disable automatic type caster for ProgressTqdmNano since it inherits from nanobind::object
NB_MAKE_OPAQUE(themachinethatgoesping::tools::progressbars::ProgressTqdmNano);

namespace nb = nanobind;
using namespace themachinethatgoesping::tools::progressbars;

// nanobind trampoline class for virtual I_ProgressBar class
class I_ProgressBar_NanobindTrampoline : public I_ProgressBar
{
  public:
    NB_TRAMPOLINE(I_ProgressBar, 8);

    /* Override the virtual functions */
    bool is_initialized() const override { NB_OVERRIDE_PURE(is_initialized); }

    void init(double first, double last, const std::string& process_name = "process") override
    {
        NB_OVERRIDE_PURE(init, first, last, process_name);
    }

    void close(const std::string& msg = "done") override { NB_OVERRIDE_PURE(close, msg); }

    void tick(double increment = 1) override { NB_OVERRIDE_PURE(tick, increment); }

    void set_progress(double new_progress) override
    {
        NB_OVERRIDE_PURE(set_progress, new_progress);
    }

    void set_postfix(const std::string& postfix) override
    {
        NB_OVERRIDE_PURE(set_postfix, postfix);
    }

    void set_prefix(const std::string& prefix) override { NB_OVERRIDE_PURE(set_prefix, prefix); }

    double current() const override { NB_OVERRIDE_PURE(current); }
};

// nanobind trampoline class for virtual I_ProgressBarTimed class
class I_ProgressBarTimed_NanobindTrampoline : public I_ProgressBarTimed
{
  public:
    NB_TRAMPOLINE(I_ProgressBarTimed, 7);

    /* Override the virtual functions */
    void callback_init(double             first,
                       double             last,
                       const std::string& process_name = "process") override
    {
        NB_OVERRIDE_PURE(callback_init, first, last, process_name);
    }

    void callback_close(const std::string& msg = "done") override
    {
        NB_OVERRIDE_PURE(callback_close, msg);
    }

    void callback_tick(double increment = 1) override
    {
        NB_OVERRIDE_PURE(callback_tick, increment);
    }

    void callback_set_progress(double new_progress) override
    {
        NB_OVERRIDE_PURE(callback_set_progress, new_progress);
    }

    void callback_set_postfix(const std::string& postfix) override
    {
        NB_OVERRIDE_PURE(callback_set_postfix, postfix);
    }

    void callback_set_prefix(const std::string& prefix) override
    {
        NB_OVERRIDE_PURE(callback_set_prefix, prefix);
    }

    double callback_current() const override { NB_OVERRIDE_PURE(callback_current); }
};

// dummy config class
class config
{};

void init_m_progressbars(nb::module_& m)
{
    using ostream_redirect =
        themachinethatgoesping::tools::nanobind_helper::scoped_ostream_redirect;

    auto m_progressbars = m.def_submodule("progressbars",
                                          "Progress indicators that can be called directly or "
                                          "passed to specific themachinethatgoesping functions");


    // // BuiltInProgressBars enum
    // py::native_enum<t_BuiltInProgressBar>(m_progressbars, "t_BuiltInProgressBar")
    //     .value("pbar_NoIndicator", t_BuiltInProgressBar::pbar_NoIndicator)
    //     .value("pbar_Indicator", t_BuiltInProgressBar::pbar_Indicator)
    //     .value("pbar_Classic", t_BuiltInProgressBar::pbar_Classic)
    //     .finalize()
    //     // pybind enum helper
    //     __PYENUM_FROM_STRING__(t_BuiltInProgressBar)
    //     // end
    //     ;

    // py::implicitly_convertible<std::string, t_BuiltInProgressBar>();

    // interface class
    nb::class_<I_ProgressBar, I_ProgressBar_NanobindTrampoline>(
        m_progressbars,
        "I_ProgressBar",
        DOC(themachinethatgoesping, tools, progressbars, I_ProgressBar))
        .def(nb::init<>(),
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBar, I_ProgressBar))
        .def("init",
             &I_ProgressBar::init,
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBar, init),
             nb::arg("first"),
             nb::arg("last"),
             nb::arg("process_name") = "process") //,
        //             nb::call_guard<scoped_ostream_redirect>())
        .def("close",
             &I_ProgressBar::close,
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBar, close),
             nb::arg("msg") = "done") //,
                                      //             nb::call_guard<scoped_ostream_redirect>())
        .def("tick",
             &I_ProgressBar::tick,
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBar, tick),
             nb::arg("increment") = 1) //,
                                       //             nb::call_guard<scoped_ostream_redirect>())
        .def("set_progress",
             &I_ProgressBar::set_progress,
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBar, set_progress),
             nb::arg("progress")) //,
                                  //             nb::call_guard<scoped_ostream_redirect>())
        .def("set_postfix",
             &I_ProgressBar::set_postfix,
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBar, set_postfix),
             nb::arg("postfix")) //,
                                 //             nb::call_guard<scoped_ostream_redirect>())
        .def("set_prefix",
             &I_ProgressBar::set_prefix,
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBar, set_prefix),
             nb::arg("prefix")) //,
                                //             nb::call_guard<scoped_ostream_redirect>())
        .def("current",
             &I_ProgressBar::current,
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBar, current)) //,
        //             nb::call_guard<scoped_ostream_redirect>())
        // end I_ProgressBar
        ;

    // interface class
    nb::class_<I_ProgressBarTimed, I_ProgressBarTimed_NanobindTrampoline, I_ProgressBar>(
        m_progressbars,
        "I_ProgressBarTimed",
        DOC(themachinethatgoesping, tools, progressbars, I_ProgressBarTimed))
        .def(nb::init<>(),
             DOC(themachinethatgoesping,
                 tools,
                 progressbars,
                 I_ProgressBarTimed,
                 I_ProgressBarTimed))
        .def("callback_init",
             &I_ProgressBarTimed::init,
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBarTimed, callback_init),
             nb::arg("first"),
             nb::arg("last"),
             nb::arg("process_name") = "process") //,
        //             nb::call_guard<scoped_ostream_redirect>())
        .def("callback_close",
             &I_ProgressBarTimed::callback_close,
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBarTimed, callback_close),
             nb::arg("msg") = "done") //,
                                      //             nb::call_guard<scoped_ostream_redirect>())
        .def("callback_tick",
             &I_ProgressBarTimed::callback_tick,
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBarTimed, callback_tick),
             nb::arg("increment") = 1) //,
                                       //             nb::call_guard<scoped_ostream_redirect>())
        .def("callback_set_progress",
             &I_ProgressBarTimed::callback_set_progress,
             DOC(themachinethatgoesping,
                 tools,
                 progressbars,
                 I_ProgressBarTimed,
                 callback_set_progress),
             nb::arg("progress")) //,
                                  //             nb::call_guard<scoped_ostream_redirect>())
        .def("callback_set_postfix",
             &I_ProgressBarTimed::callback_set_postfix,
             DOC(themachinethatgoesping,
                 tools,
                 progressbars,
                 I_ProgressBarTimed,
                 callback_set_postfix),
             nb::arg("postfix")) //,
                                 //             nb::call_guard<scoped_ostream_redirect>())
        .def("callback_set_prefix",
             &I_ProgressBarTimed::callback_set_prefix,
             DOC(themachinethatgoesping,
                 tools,
                 progressbars,
                 I_ProgressBarTimed,
                 callback_set_prefix),
             nb::arg("prefix")) //,
                                //             nb::call_guard<scoped_ostream_redirect>())
        .def("callback_current",
             &I_ProgressBarTimed::callback_current,
             DOC(themachinethatgoesping,
                 tools,
                 progressbars,
                 I_ProgressBarTimed,
                 callback_current)) //,
                                    //             nb::call_guard<scoped_ostream_redirect>())
        // end I_ProgressBar
        ;

    nb::class_<NoIndicator, I_ProgressBar>(
        m_progressbars,
        "NoIndicator",
        DOC(themachinethatgoesping, tools, progressbars, NoIndicator))
        .def(nb::init<>(),
             DOC(themachinethatgoesping, tools, progressbars, NoIndicator, NoIndicator))
        // end ProgressIndicator
        ;

    nb::class_<ProgressIndicator, I_ProgressBar>(
        m_progressbars,
        "ProgressIndicator",
        DOC(themachinethatgoesping, tools, progressbars, ProgressIndicator))
        .def(nb::init<>(),
             DOC(themachinethatgoesping, tools, progressbars, ProgressIndicator, ProgressIndicator))
        // end ProgressIndicator
        ;

    nb::class_<ConsoleProgressBar, I_ProgressBar>(
        m_progressbars,
        "ConsoleProgressBar",
        DOC(themachinethatgoesping, tools, progressbars, ConsoleProgressBar))
        .def(nb::init<>(),
             DOC(themachinethatgoesping,
                 tools,
                 progressbars,
                 ConsoleProgressBar,
                 ConsoleProgressBar))
        // end ProgressIndicator
        ;

    nb::class_<ProgressTqdmNano, I_ProgressBar>(
        m_progressbars,
        "ProgressTqdm",
        DOC(themachinethatgoesping, tools, progressbars, ProgressTqdmNano))
        .def(nb::init<nanobind::object>(),
             DOC(themachinethatgoesping, tools, progressbars, ProgressTqdmNano, ProgressTqdmNano),
             nb::arg("tqdm"))
        // end ProgressIndicator
        ;

    // py::implicitly_convertible<ProgressTqdmNano,I_ProgressBar>();
    nb::implicitly_convertible<nanobind::object, ProgressTqdmNano>();
    // py::implicitly_convertible<ProgressTqdmNano,py::object&>();

    m_progressbars.def(
        "test_loop",
        [](I_ProgressBar& progress, size_t loops, size_t sleep_us, bool show_progress) {
            // get current time
            auto start = std::chrono::high_resolution_clock::now();

            // initialize random number generator
            std::random_device                     r;
            std::default_random_engine             e1(r());
            std::uniform_real_distribution<double> dist(-100, 100);

            if (show_progress)
                progress.init(0., double(loops), "test loop");
            for (unsigned int i = 0; i < loops; ++i)
            {
                // std::this_thread::sleep_for(std::chrono::microseconds(sleep_us));

                //  do something computation
                [[maybe_unused]] double val = 0;
                for (size_t j = 0; j < sleep_us; ++j)
                {
                    val *= 10 * std::log10(std::pow(dist(e1), 2));
                }

                if (show_progress)
                    progress.tick();
            }
            if (show_progress)
                progress.close();

            // return elapsed time as double in milliseconds
            auto end = std::chrono::high_resolution_clock::now();
            return std::chrono::duration<double, std::milli>(end - start).count();
        },
        nb::arg("ProgressBar"),
        nb::arg("loops")         = 1000,
        nb::arg("sleep_us")      = 10,
        nb::arg("show_progress") = true);

    // // for some reason stream redirection only works if we define it here again?
    // nb::class_<themachinethatgoesping::tools::nanobind_helper::ostream_redirect>(
    //     m_progressbars,
    //     "ostream_redirect_progressbars",
    //     "Context manager that redirects C++ stdout/stderr to Python sys.stdout/sys.stderr. "
    //     "Use as 'with ostream_redirect():' to capture C++ output in Python.")
    //     .def(nb::init<>(), "Create ostream redirect with automatic start (RAII behavior)")
    //     .def(nb::init<bool>(),
    //          "Create ostream redirect with optional auto-start",
    //          nb::arg("auto_start") = true)
    //     .def("enter",
    //          &themachinethatgoesping::tools::nanobind_helper::ostream_redirect::enter,
    //          "Start redirection")
    //     .def("exit",
    //          &themachinethatgoesping::tools::nanobind_helper::ostream_redirect::exit,
    //          "Stop redirection")
    //     .def(
    //         "__enter__",
    //         [](themachinethatgoesping::tools::nanobind_helper::ostream_redirect& self)
    //             -> themachinethatgoesping::tools::nanobind_helper::ostream_redirect& {
    //             self.enter();
    //             return self;
    //         },
    //         nb::rv_policy::reference_internal,
    //         "Enter the runtime context")
    //     .def(
    //         "__exit__",
    //         [](themachinethatgoesping::tools::nanobind_helper::ostream_redirect& self,
    //            nb::handle                                                        exc_type,
    //            nb::handle                                                        exc_value,
    //            nb::handle traceback) -> bool {
    //             self.exit();
    //             return false; // Don't suppress exceptions - return Python bool explicitly
    //         },
    //         "Exit the runtime context",
    //         nb::arg("exc_type")  = nb::none(),
    //         nb::arg("exc_value") = nb::none(),
    //         nb::arg("traceback") = nb::none());
}
