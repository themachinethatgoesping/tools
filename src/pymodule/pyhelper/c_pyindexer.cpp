// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0



#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "../../themachinethatgoesping/tools/pyhelper/pyindexer.hpp"
#include "../../themachinethatgoesping/tools_pybind/classhelper.hpp"

#include "module.hpp"

namespace py = pybind11;
using namespace themachinethatgoesping::tools::pyhelper;

void init_c_pyindexer(pybind11::module& m)
{
    py::class_<PyIndexer::Slice>(
        m, "PyIndexerSlice", DOC(themachinethatgoesping, tools, pyhelper, PyIndexer, Slice))
        .def(py::init<int64_t, int64_t, int64_t>(),
             DOC(themachinethatgoesping, tools, pyhelper, PyIndexer, Slice, Slice_2),
             py::arg("start") = std::numeric_limits<int64_t>::max(),
             py::arg("stop")  = std::numeric_limits<int64_t>::max(),
             py::arg("step")  = 1)
        .def(py::init([](const py::object& pyslice) {
                 auto pystart = pyslice.attr("start");
                 auto pystop  = pyslice.attr("stop");
                 auto pystep  = pyslice.attr("step");

                 int64_t start = py::cast<py::object>(pystart).is(py::none())
                                  ? std::numeric_limits<int64_t>::max()
                                  : py::cast<int64_t>(pystart);
                 int64_t stop  = py::cast<py::object>(pystop).is(py::none())
                                  ? std::numeric_limits<int64_t>::max()
                                  : py::cast<int64_t>(pystop);
                 int64_t step  = py::cast<py::object>(pystep).is(py::none())
                                  ? std::numeric_limits<int64_t>::max()
                                  : py::cast<int64_t>(pystep);

                 return PyIndexer::Slice(start, stop, step);
             }),
             DOC(themachinethatgoesping, tools, pyhelper, PyIndexer, Slice, Slice_2),
             py::arg("slice"))
        .def_readwrite("start",
                       &PyIndexer::Slice::start,
                       DOC(themachinethatgoesping, tools, pyhelper, PyIndexer, Slice, start))
        .def_readwrite("stop",
                       &PyIndexer::Slice::stop,
                       DOC(themachinethatgoesping, tools, pyhelper, PyIndexer, Slice, stop))
        .def_readwrite("step",
                       &PyIndexer::Slice::step,
                       DOC(themachinethatgoesping, tools, pyhelper, PyIndexer, Slice, step))

        .def("__eq__",
             &PyIndexer::Slice::operator==,
             DOC(themachinethatgoesping, tools, pyhelper, PyIndexer, Slice, operator_eq),
             py::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(PyIndexer::Slice)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(PyIndexer::Slice)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(PyIndexer::Slice)
        // stop LinearInterpolator
        ;

    py::implicitly_convertible<py::slice, PyIndexer::Slice>();
}
