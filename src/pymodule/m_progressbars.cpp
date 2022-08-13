// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// -- c++ library headers
#include <memory>

// -- include pybind11 headers
#include <pybind11/iostream.h>
#include <pybind11/stl.h>

// -- module header
#include "../themachinethatgoesping/tools/progressbars.hpp"
#include "../themachinethatgoesping/tools/progressbars/progresstqdm.hpp"
#include "docstrings.hpp" //automatically gernerated using  python -m pybind11_mkdoc -o docstrings.h <headerfiles>

namespace py = pybind11;
using namespace themachinethatgoesping::tools::progressbars;

// pybind trampoline class for virtual I_ProgressBar class
class I_ProgressBar_PybindTrampoline : public I_ProgressBar
{
  public:
    /* Inherit the constructors */
    using I_ProgressBar::I_ProgressBar;

    /* Override the virtual functions */
    void init(double first, double last, const std::string& process_name = "process") override
    {
        PYBIND11_OVERRIDE_PURE(void,          /* Return type */
                               I_ProgressBar, /* Parent class */
                               init,          /* Name of function in C++ (must match Python name) */
                               first,
                               last,
                               process_name /* Argument(s) */
        );
    }

    void close(const std::string& msg = "done") override
    {
        PYBIND11_OVERRIDE_PURE(void,          /* Return type */
                               I_ProgressBar, /* Parent class */
                               close,         /* Name of function in C++ (must match Python name) */
                               msg            /* Argument(s) */
        );
    }

    void tick(double increment = 1) override
    {
        PYBIND11_OVERRIDE_PURE(void,          /* Return type */
                               I_ProgressBar, /* Parent class */
                               tick,          /* Name of function in C++ (must match Python name) */
                               increment      /* Argument(s) */
        );
    }

    void set_progress(double new_progress) override
    {
        PYBIND11_OVERRIDE_PURE(void,          /* Return type */
                               I_ProgressBar, /* Parent class */
                               set_progress,  /* Name of function in C++ (must match Python name) */
                               new_progress   /* Argument(s) */
        );
    }

    void set_postfix(const std::string& postfix) override
    {
        PYBIND11_OVERRIDE_PURE(void,          /* Return type */
                               I_ProgressBar, /* Parent class */
                               set_postfix,   /* Name of function in C++ (must match Python name) */
                               postfix        /* Argument(s) */
        );
    }

    double current() const override
    {
        PYBIND11_OVERRIDE_PURE(double,        /* Return type */
                               I_ProgressBar, /* Parent class */
                               current,       /* Name of function in C++ (must match Python name) */
        );
    }
};

// pybind trampoline class for virtual I_ProgressBar class
class I_ProgressBarTimed_PybindTrampoline : public I_ProgressBarTimed
{
  public:
    /* Inherit the constructors */
    using I_ProgressBarTimed::I_ProgressBarTimed;

    /* Override the virtual functions */
    void callback_init(double first, double last, const std::string& process_name = "process") override
    {
        PYBIND11_OVERRIDE_PURE(void,          /* Return type */
                               I_ProgressBarTimed, /* Parent class */
                               callback_init,          /* Name of function in C++ (must match Python name) */
                               first,
                               last,
                               process_name /* Argument(s) */
        );
    }

    void callback_close(const std::string& msg = "done") override
    {
        PYBIND11_OVERRIDE_PURE(void,          /* Return type */
                               I_ProgressBarTimed, /* Parent class */
                               callback_close,         /* Name of function in C++ (must match Python name) */
                               msg            /* Argument(s) */
        );
    }

    void callback_tick(double increment = 1) override
    {
        PYBIND11_OVERRIDE_PURE(void,          /* Return type */
                               I_ProgressBarTimed, /* Parent class */
                               callback_tick,          /* Name of function in C++ (must match Python name) */
                               increment      /* Argument(s) */
        );
    }

    void callback_set_progress(double new_progress) override
    {
        PYBIND11_OVERRIDE_PURE(void,          /* Return type */
                               I_ProgressBarTimed, /* Parent class */
                               callback_set_progress,  /* Name of function in C++ (must match Python name) */
                               new_progress   /* Argument(s) */
        );
    }

    void callback_set_postfix(const std::string& postfix) override
    {
        PYBIND11_OVERRIDE_PURE(void,          /* Return type */
                               I_ProgressBarTimed, /* Parent class */
                               callback_set_postfix,   /* Name of function in C++ (must match Python name) */
                               postfix        /* Argument(s) */
        );
    }

    double callback_current() const override
    {
        PYBIND11_OVERRIDE_PURE(double,        /* Return type */
                               I_ProgressBarTimed, /* Parent class */
                               callback_current,       /* Name of function in C++ (must match Python name) */
        );
    }
};

void init_m_progressbars(py::module& m)
{
    auto m_progressbars = m.def_submodule("progressbars",
                                          "Progress indicators that can be called directly or "
                                          "passed to specific themachinethatgoesping functions");

    // interface class
    py::class_<I_ProgressBar, I_ProgressBar_PybindTrampoline>(
        m_progressbars,
        "I_ProgressBar",
        DOC(themachinethatgoesping, tools, progressbars, I_ProgressBar))
        .def(py::init<>(),
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBar, I_ProgressBar))
        .def("init",
             &I_ProgressBar::init,
             py::call_guard<py::scoped_ostream_redirect>(),
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBar, init),
             py::arg("first"),
             py::arg("last"),
             py::arg("process_name") = "process")
        .def("close",
             &I_ProgressBar::close,
             py::call_guard<py::scoped_ostream_redirect>(),
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBar, close),
             py::arg("msg") = "done")
        .def("tick",
             &I_ProgressBar::tick,
             py::call_guard<py::scoped_ostream_redirect>(),
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBar, tick),
             py::arg("increment") = 1)
        .def("set_progress",
             &I_ProgressBar::set_progress,
             py::call_guard<py::scoped_ostream_redirect>(),
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBar, set_progress),
             py::arg("progress"))
        .def("set_postfix",
             &I_ProgressBar::set_postfix,
             py::call_guard<py::scoped_ostream_redirect>(),
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBar, set_postfix),
             py::arg("postfix"))
        .def("current",
             &I_ProgressBar::current,
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBar, current))
        // end I_ProgressBar
        ;

    // interface class
    py::class_<I_ProgressBarTimed, I_ProgressBarTimed_PybindTrampoline, I_ProgressBar>(
        m_progressbars,
        "I_ProgressBarTimed",
        DOC(themachinethatgoesping, tools, progressbars, I_ProgressBarTimed))
        .def(py::init<>(),
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBarTimed, I_ProgressBarTimed))
        .def("callback_init",
             &I_ProgressBarTimed::init,
             py::call_guard<py::scoped_ostream_redirect>(),
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBarTimed, callback_init),
             py::arg("first"),
             py::arg("last"),
             py::arg("process_name") = "process")
        .def("callback_close",
             &I_ProgressBarTimed::callback_close,
             py::call_guard<py::scoped_ostream_redirect>(),
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBarTimed, callback_close),
             py::arg("msg") = "done")
        .def("callback_tick",
             &I_ProgressBarTimed::callback_tick,
             py::call_guard<py::scoped_ostream_redirect>(),
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBarTimed, callback_tick),
             py::arg("increment") = 1)
        .def("callback_set_progress",
             &I_ProgressBarTimed::callback_set_progress,
             py::call_guard<py::scoped_ostream_redirect>(),
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBarTimed, callback_set_progress),
             py::arg("progress"))
        .def("callback_set_postfix",
             &I_ProgressBarTimed::callback_set_postfix,
             py::call_guard<py::scoped_ostream_redirect>(),
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBarTimed, callback_set_postfix),
             py::arg("postfix"))
        .def("callback_current",
             &I_ProgressBarTimed::callback_current,
             DOC(themachinethatgoesping, tools, progressbars, I_ProgressBarTimed, callback_current))
        // end I_ProgressBar
        ;

    py::class_<NoIndicator, I_ProgressBar>(
        m_progressbars,
        "NoIndicator",
        DOC(themachinethatgoesping, tools, progressbars, NoIndicator))
        .def(py::init<>(),
             DOC(themachinethatgoesping, tools, progressbars, NoIndicator, NoIndicator))
        // end ProgressIndicator
        ;

    py::class_<ProgressIndicator, I_ProgressBar>(
        m_progressbars,
        "ProgressIndicator",
        DOC(themachinethatgoesping, tools, progressbars, ProgressIndicator))
        .def(py::init<>(),
             DOC(themachinethatgoesping, tools, progressbars, ProgressIndicator, ProgressIndicator))
        // end ProgressIndicator
        ;

    py::class_<ConsoleProgressBar, I_ProgressBar>(
        m_progressbars,
        "ConsoleProgressBar",
        DOC(themachinethatgoesping, tools, progressbars, ConsoleProgressBar))
        .def(py::init<>(),
             DOC(themachinethatgoesping,
                 tools,
                 progressbars,
                 ConsoleProgressBar,
                 ConsoleProgressBar))
        // end ProgressIndicator
        ;

    py::class_<ProgressTqdm, I_ProgressBar>(
        m_progressbars,
        "ProgressTqdm",
        DOC(themachinethatgoesping, tools, progressbars, ProgressTqdm))
        .def(py::init<py::object&>(),
             DOC(themachinethatgoesping, tools, progressbars, ProgressTqdm, ProgressTqdm),
             py::arg("tqdm"))
        // end ProgressIndicator
        ;

    //py::implicitly_convertible<ProgressTqdm,I_ProgressBar>();
    py::implicitly_convertible<py::object,ProgressTqdm>();
    //py::implicitly_convertible<ProgressTqdm,py::object&>();

    m_progressbars.def(
        "test_loop",
        [](I_ProgressBar& progress, size_t loops, size_t sleep_us, bool show_progress) 
        {
        if (show_progress)
            progress.init(0, loops, "test loop");
        for (unsigned int i = 0; i < loops; ++i)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(sleep_us));
            if (show_progress)
                progress.tick();
        }
        if (show_progress)
            progress.close();
        },
        py::call_guard<py::scoped_ostream_redirect>(),
        py::arg("ProgressBar"),
        py::arg("loops")    = 1000,
        py::arg("sleep_us") = 10,
        py::arg("show_progress") = true);
}
