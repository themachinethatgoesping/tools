
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

namespace themachinethatgoesping {
namespace tools {
namespace nanobind_helper {

/**
 * @brief Convert a string to an enum using magic_enum
 *
 * @tparam T_ENUM enum type
 * @tparam T_NANOBIND_ENUM nanobind::native_enum<T_ENUM>
 * @param self enum class that is to be changes
 * @param str string that is to be converted
 */
template<typename T_ENUM, typename T_NANOBIND_ENUM>
void add_string_to_enum_conversion(T_NANOBIND_ENUM& t_enum)
{
    namespace nb = nanobind;
    
    t_enum.def("__init__", [](T_ENUM* self, const std::string& str) {
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

                       nb::print(fmt::format(
                           "ERROR: unknown value option '{}'! Try: [{}]", str, enum_info).c_str());

                       throw std::invalid_argument(fmt::format(
                           "ERROR: unknown value option '{}'! Try: [{}]", str, enum_info));
                   }

                   new (self) T_ENUM(enum_value.value());
               },
               "Construct this enum type from string",
               nb::arg("str"));

    t_enum.def("str", [](const T_ENUM& self) { return std::string(magic_enum::enum_name(self)); });
    //t_enum.def("__str__", [](const T_ENUM& self) { return std::string(magic_enum::enum_name(self)); });

    nb::implicitly_convertible<std::string, T_ENUM>();
}

}
}
}