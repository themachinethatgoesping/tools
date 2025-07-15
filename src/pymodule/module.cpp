// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>

#define FORCE_IMPORT_ARRAY // this is needed for xtensor-python but must only be included once
#include <xtensor-python/pytensor.hpp> // Numpy bindings

#include "classhelper/module.hpp"
#include "m_helper.hpp"
#include "m_progressbars.hpp"
#include "m_timeconv.hpp"
#include "pyhelper/module.hpp"
#include "rotationfunctions/module.hpp"
#include "vectorinterpolators/module.hpp"

PYBIND11_MODULE(MODULE_NAME, m)
{
    xt::import_numpy(); // import numpy for xtensor (otherwise there will be weird segfaults)

    pybind11::add_ostream_redirect(m, "ostream_redirect");

    m.attr("__version__") = MODULE_VERSION;
    m.doc()               = "Small python tool functions for themachinethatgoesping";

    init_m_timeconv(m);
    init_m_helper(m);
    init_m_progressbars(m);
    init_m_vectorinterpolators(m);
    init_m_rotationfunctions(m);
    init_m_classhelper(m);
    init_m_pyhelper(m);
}
