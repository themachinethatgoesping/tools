// SPDX-FileCopyrightText: 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <pybind11/stl.h>

#include "m_datetime.h"



PYBIND11_MODULE(PYTHON_LIB,m)
{
    pybind11::add_ostream_redirect(m, "ostream_redirect");

    init_m_datetime(m);
    m.doc() ="Small python tool functions for themachinethatgoesping";


}
