
// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief some macros to easily implement common enum capabilities for nanobind classes
 *
 * @authors Peter Urban
 */

#pragma once

/* generated doc strings */
#include ".docstrings/enumhelper.doc.hpp"

#include <fmt/core.h>
#include <magic_enum/magic_enum.hpp>
#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/string_view.h>
#include <string>

#include <themachinethatgoesping/tools/classhelper/option.hpp>
#include <themachinethatgoesping/tools_nanobind/classhelper.hpp>

namespace themachinethatgoesping {
namespace tools {
namespace nanobind_helper {

template<typename T_OPTION>
void make_option_class(nanobind::module_& m, const std::string& name)
{
    using t_enum       = typename T_OPTION::t_enum;
    using t_underlying = typename T_OPTION::t_underlying;

    static auto enum_class =
        nb::class_<T_OPTION>(
            m,
            name.c_str(),
            fmt::format("Helper class to convert between strings and enum values of type '{}'",
                        magic_enum::enum_type_name<t_enum>())
                .c_str())
            .def(nb::init_implicit<t_enum>(),
                 "Construct from enum value",
                 nb::arg("value") = T_OPTION::default_value)
            .def(nb::init_implicit<std::string_view>(), "Construct from string", nb::arg("value"))
            .def(nb::init_implicit<t_underlying>(), "Construct from string", nb::arg("value"))

            .def_rw("value", &T_OPTION::value, "enum value", nb::rv_policy::reference_internal)
            .def_ro_static("__default_value__",
                           &T_OPTION::default_value,
                           "default enum value when constructing without arguments")
            .def("__str__", &T_OPTION::operator std::string)

            // __eq__ operators
            .def(nb::self == nb::self)
            .def(nb::self == t_enum())
            .def(nb::self == t_underlying())
            .def(nb::self == std::string_view())

        // default copy functions
        __PYCLASS_DEFAULT_COPY__(T_OPTION)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(T_OPTION)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(T_OPTION)
            .def("__repr__",
                 [](T_OPTION& self) {
                     nb::print(fmt::format("{}.{}", self.type_name(), self.name()).c_str());
                 })
        // end
        ;
}

}
}
}
