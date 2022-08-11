// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/iostream.h>
#include <pybind11/pybind11.h>

#include "m_timeconv.hpp"
#include "vectorinterpolators/module.hpp"
#include "classhelpers/module.hpp"

PYBIND11_MODULE(PYTHON_LIB, m)
{
    pybind11::add_ostream_redirect(m, "ostream_redirect");

    m.doc() = "Small python tool functions for themachinethatgoesping";

    init_m_timeconv(m);
    init_m_vectorinterpolators(m);
    init_m_classhelpers(m);
}
