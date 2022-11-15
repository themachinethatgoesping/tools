// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>

#include "classhelper/module.hpp"
#include "m_helper.hpp"
#include "m_progressbars.hpp"
#include "m_timeconv.hpp"
#include "pyhelper/module.hpp"
#include "vectorinterpolators/module.hpp"

PYBIND11_MODULE(MODULE_NAME, m)
{
    pybind11::add_ostream_redirect(m, "ostream_redirect");

    m.attr("__version__") = MODULE_VERSION;
    m.doc()               = "Small python tool functions for themachinethatgoesping";

    init_m_timeconv(m);
    init_m_helper(m);
    init_m_progressbars(m);
    init_m_vectorinterpolators(m);
    init_m_classhelper(m);
    init_m_pyhelper(m);
}
