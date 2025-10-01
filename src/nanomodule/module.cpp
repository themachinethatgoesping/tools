// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <nanobind/nanobind.h>

#include <themachinethatgoesping/tools_nanobind/ostream_redirect.hpp>

#include "classhelper/module.hpp"
#include "m_helper.hpp"
#include "m_progressbars.hpp"
#include "m_timeconv.hpp"
#include "pyhelper/module.hpp"
#include "vectorinterpolators/module.hpp"

namespace nb = nanobind;

NB_MODULE(MODULE_NAME, m)
{
    m.attr("__version__") = MODULE_VERSION;
    m.doc()               = "Small python tool functions for themachinethatgoesping";

    // Expose ostream_redirect class for direct use (like pybind11's scoped_ostream_redirect)
    nb::class_<themachinethatgoesping::tools::nanobind_helper::ostream_redirect>(
        m,
        "ostream_redirect",
        "Context manager that redirects C++ stdout/stderr to Python sys.stdout/sys.stderr. "
        "Use as 'with ostream_redirect():' to capture C++ output in Python.")
        .def(nb::init<>(), "Create ostream redirect with automatic start (RAII behavior)")
        .def(nb::init<bool>(),
             "Create ostream redirect with optional auto-start",
             nb::arg("auto_start") = true)
        .def("enter",
             &themachinethatgoesping::tools::nanobind_helper::ostream_redirect::enter,
             "Start redirection")
        .def("exit",
             &themachinethatgoesping::tools::nanobind_helper::ostream_redirect::exit,
             "Stop redirection")
        .def(
            "__enter__",
            [](themachinethatgoesping::tools::nanobind_helper::ostream_redirect& self)
                -> themachinethatgoesping::tools::nanobind_helper::ostream_redirect& {
                self.enter();
                return self;
            },
            nb::rv_policy::reference_internal,
            "Enter the runtime context")
        .def(
            "__exit__",
            [](themachinethatgoesping::tools::nanobind_helper::ostream_redirect& self,
               [[maybe_unused]] nb::handle                                       exc_type,
               [[maybe_unused]] nb::handle                                       exc_value,
               [[maybe_unused]] nb::handle traceback) -> bool {
                self.exit();
                return false; // Don't suppress exceptions - return Python bool explicitly
            },
            "Exit the runtime context",
            nb::arg("exc_type")  = nb::none(),
            nb::arg("exc_value") = nb::none(),
            nb::arg("traceback") = nb::none());

    init_m_helper(m);
    init_m_timeconv(m);
    init_m_progressbars(m);

    init_m_classhelper(m);
    init_m_pyhelper(m);
    init_m_vectorinterpolators(m);
}
