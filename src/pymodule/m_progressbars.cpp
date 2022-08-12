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
        PYBIND11_OVERRIDE_PURE(
            double,               /* Return type */
            I_ProgressBar,        /* Parent class */
            current, /* Name of function in C++ (must match Python name) */
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

    py::class_<NoIndicator, I_ProgressBar>(
        m_progressbars,
        "NoIndicator",
        DOC(themachinethatgoesping, tools, progressbars, NoIndicator))
        .def(py::init<>(),
             DOC(themachinethatgoesping, tools, progressbars, ProgressIndicator, ProgressIndicator))
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
             DOC(themachinethatgoesping, tools, progressbars, ProgressIndicator, ProgressIndicator))
        // end ProgressIndicator
        ;
}
