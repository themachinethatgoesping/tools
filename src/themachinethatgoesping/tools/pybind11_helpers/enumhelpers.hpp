
// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief some macros to easily implement common enum capabilities for for pybind classes
 *
 * @authors Peter Urban
 */

#pragma once

#include <fmt/core.h>
#include <magic_enum.hpp>

namespace themachinethatgoesping {
namespace tools {
namespace pybind_helpers {

/**
 * @brief Convert a string to an enum using magic_enum
 *
 * @tparam T_ENUM
 * @param self enum class that is to be changes
 * @param str string that is to be converted
 */
#define __PYENUM_FROM_STRING__(T_ENUM)                                                             \
    .def(py::init([](const std::string& str) {                                                     \
             auto enum_value = magic_enum::enum_cast<T_ENUM>(str);                                 \
             if (!enum_value.has_value())                                                          \
             {                                                                                     \
                                                                                                   \
                 constexpr auto enum_values = magic_enum::enum_names<T_ENUM>();                    \
                 std::string    enum_info;                                                         \
                 for (unsigned int i = 0; i < enum_values.size(); ++i)                             \
                 {                                                                                 \
                     if (i != 0)                                                                   \
                         enum_info += ", ";                                                        \
                                                                                                   \
                     enum_info += "\"";                                                            \
                     enum_info += enum_values[i];                                                  \
                     enum_info += "\"";                                                            \
                 }                                                                                 \
                                                                                                   \
                 pybind11::print(                                                                  \
                     fmt::format("ERROR: unknown value option '{}'! Try: [{}]", str, enum_info));  \
                                                                                                   \
                 throw std::invalid_argument(                                                      \
                     fmt::format("ERROR: unknown value option '{}'! Try: [{}]", str, enum_info));  \
             }                                                                                     \
                                                                                                   \
             return enum_value.value();                                                            \
         }),                                                                                       \
         "Construct this enum type from string",                                                   \
         py::arg("str"))

}
}
}