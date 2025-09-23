// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0



#include <nanobind/nanobind.h>

#include "../../themachinethatgoesping/tools/pyhelper/pyindexer.hpp"
#include "../../themachinethatgoesping/tools_nanobind/classhelper.hpp"

#include "module.hpp"

namespace nb = nanobind;
using namespace themachinethatgoesping::tools::pyhelper;

void init_c_pyindexer(nanobind::module_& m)
{
    nb::class_<PyIndexer::Slice>(
        m, "PyIndexerSlice", DOC(themachinethatgoesping, tools, pyhelper, PyIndexer, Slice))
        .def(nb::init<int64_t, int64_t, int64_t>(),
             DOC(themachinethatgoesping, tools, pyhelper, PyIndexer, Slice, Slice_2),
             nb::arg("start") = std::numeric_limits<int64_t>::max(),
             nb::arg("stop")  = std::numeric_limits<int64_t>::max(),
             nb::arg("step")  = 1)
        .def("__init__", [](PyIndexer::Slice* self, const nb::object& pyslice) {
                 auto pystart = pyslice.attr("start");
                 auto pystop  = pyslice.attr("stop");
                 auto pystep  = pyslice.attr("step");

                 int64_t start = nb::cast<nb::object>(pystart).is(nb::none())
                                  ? std::numeric_limits<int64_t>::max()
                                  : nb::cast<int64_t>(pystart);
                 int64_t stop  = nb::cast<nb::object>(pystop).is(nb::none())
                                  ? std::numeric_limits<int64_t>::max()
                                  : nb::cast<int64_t>(pystop);
                 int64_t step  = nb::cast<nb::object>(pystep).is(nb::none())
                                  ? std::numeric_limits<int64_t>::max()
                                  : nb::cast<int64_t>(pystep);

                 new (self) PyIndexer::Slice(start, stop, step);
             },
             DOC(themachinethatgoesping, tools, pyhelper, PyIndexer, Slice, Slice_2),
             nb::arg("slice"))
        .def_rw("start",
                       &PyIndexer::Slice::start,
                       DOC(themachinethatgoesping, tools, pyhelper, PyIndexer, Slice, start))
        .def_rw("stop",
                       &PyIndexer::Slice::stop,
                       DOC(themachinethatgoesping, tools, pyhelper, PyIndexer, Slice, stop))
        .def_rw("step",
                       &PyIndexer::Slice::step,
                       DOC(themachinethatgoesping, tools, pyhelper, PyIndexer, Slice, step))

        .def("__eq__",
             &PyIndexer::Slice::operator==,
             DOC(themachinethatgoesping, tools, pyhelper, PyIndexer, Slice, operator_eq),
             nb::arg("other"))
        // default copy functions
        __PYCLASS_DEFAULT_COPY__(PyIndexer::Slice)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(PyIndexer::Slice)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(PyIndexer::Slice)
        // stop LinearInterpolator
        ;

    nb::implicitly_convertible<nb::slice, PyIndexer::Slice>();
}
