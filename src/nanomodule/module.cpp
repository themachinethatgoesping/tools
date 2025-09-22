// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <nanobind/nanobind.h>

#include "m_timeconv.hpp"

namespace nb = nanobind;

NB_MODULE(MODULE_NAME, m)
{
    m.attr("__version__") = MODULE_VERSION;
    m.doc() = "Small python tool functions for themachinethatgoesping";

    init_m_timeconv(m);
}
