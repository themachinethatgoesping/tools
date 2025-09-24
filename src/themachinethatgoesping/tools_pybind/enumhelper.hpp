
// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief some macros to easily implement common enum capabilities for for pybind classes
 *
 * @authors Peter Urban
 */

#pragma once

/* generated doc strings */
#include ".docstrings/enumhelper.doc.hpp"

#include <fmt/core.h>
#include <magic_enum/magic_enum.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

#include <themachinethatgoesping/tools/classhelper/option.hpp>
#include <themachinethatgoesping/tools_pybind/classhelper.hpp>

namespace themachinethatgoesping {
namespace tools {
namespace pybind_helper {

template<typename T_OPTION>
void make_option_class(pybind11::module_& m, const std::string& name)
{
    using t_enum       = typename T_OPTION::t_enum;
    using t_underlying = typename T_OPTION::t_underlying;
    namespace py = pybind11;

    auto enum_class =
        pybind11::class_<T_OPTION>(
            m,
            name.c_str(),
            fmt::format("Helper class to convert between strings and enum values of type '{}'",
                        magic_enum::enum_type_name<t_enum>())
                .c_str())
            .def(pybind11::init<t_enum>(),
                 "Construct from enum value",
                 pybind11::arg("value") = T_OPTION::default_value)
            .def(pybind11::init<std::string_view>(), "Construct from string", pybind11::arg("value"))
            .def(pybind11::init<t_underlying>(), "Construct from string", pybind11::arg("value"))

            .def_readwrite("value", &T_OPTION::value, "enum value")
            .def_readonly_static("__default_value__",
                                &T_OPTION::default_value,
                                "default enum value when constructing without arguments")
            .def("__str__", &T_OPTION::operator std::string)

            // __eq__ operators
            .def(pybind11::self == pybind11::self)
            .def(pybind11::self == t_enum())
            .def(pybind11::self == t_underlying())
            .def(pybind11::self == std::string_view())

        // default copy functions
        __PYCLASS_DEFAULT_COPY__(T_OPTION)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(T_OPTION)
        // default printing functions
        __PYCLASS_DEFAULT_PRINTING__(T_OPTION)
            .def("__repr__",
                 [](T_OPTION& self) {
                     pybind11::print(fmt::format("{}.{}", self.type_name(), self.name()).c_str());
                 })
        // end
        ;

    // register implicit conversions
    pybind11::implicitly_convertible<t_enum, T_OPTION>();
    pybind11::implicitly_convertible<std::string, T_OPTION>();
    pybind11::implicitly_convertible<t_underlying, T_OPTION>();
}

/**
 * @brief Convert a string to an enum using magic_enum
 *
 * @tparam T_ENUM enum type
 * @tparam T_PYBIND_ENUM pybind11::native_enum<T_ENUM>
 * @param self enum class that is to be changes
 * @param str string that is to be converted
 */
template<typename T_ENUM, typename T_PYBIND_ENUM>
void add_string_to_enum_conversion(T_PYBIND_ENUM& t_enum)
{
    t_enum.def(pybind11::init([](const std::string& str) {
                   auto enum_value = magic_enum::enum_cast<T_ENUM>(str);
                   if (!enum_value.has_value())
                   {

                       constexpr auto enum_values = magic_enum::enum_names<T_ENUM>();
                       std::string    enum_info;
                       for (size_t i = 0; i < enum_values.size(); ++i)
                       {
                           if (i != 0)
                               enum_info += ", ";

                           enum_info += "\"";
                           enum_info += enum_values[i];
                           enum_info += "\"";
                       }

                       pybind11::print(fmt::format(
                           "ERROR: unknown value option '{}'! Try: [{}]", str, enum_info));

                       throw std::invalid_argument(fmt::format(
                           "ERROR: unknown value option '{}'! Try: [{}]", str, enum_info));
                   }

                   return enum_value.value();
               }),
               "Construct this enum type from string",
               pybind11::arg("str"));

    t_enum.def("str", [](const T_ENUM& self) { return magic_enum::enum_name(self); });

    pybind11::implicitly_convertible<std::string, T_ENUM>();
}

}
}
}