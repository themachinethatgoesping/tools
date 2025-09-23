
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
#include <nanobind/stl/string.h>
#include <nanobind/stl/string_view.h>
#include <string>

namespace themachinethatgoesping {
namespace tools {
namespace nanobind_helper {

// Your from_string function (assuming it returns std::optional<T_ENUM>)
template<typename T_ENUM>
T_ENUM from_string(const std::string& str)
{
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

        nanobind::print(
            fmt::format("ERROR: unknown value option '{}'! Try: [{}]", str, enum_info).c_str());

        throw std::invalid_argument(
            fmt::format("ERROR: unknown value option '{}'! Try: [{}]", str, enum_info));
    }

    return T_ENUM(enum_value.value());
}

template<typename T_ENUM>
void add_string_to_enum_conversion(nanobind::enum_<T_ENUM>& enum_class)
{
    enum_class.def("__init__",
                   [](T_ENUM* self, const std::string& str) {
                       new (self) T_ENUM(from_string<T_ENUM>(str));
                   },
                   "Construct from string",
                   nanobind::arg("str"));
    enum_class.def("__init__",
                   [](T_ENUM* self, uint8_t value) {
                       // Validate that the uint8_t value corresponds to a valid enum value
                       if (value >= magic_enum::enum_count<T_ENUM>())
                       {
                           throw std::invalid_argument(
                               fmt::format("Invalid enum value {}. Valid range is 0-{}",
                                           value,
                                           magic_enum::enum_count<T_ENUM>() - 1));
                       }
                       new (self) T_ENUM(static_cast<T_ENUM>(value));
                   },
                   "Construct from int",
                   nanobind::arg("int"));

    //nb::implicitly_convertible<std::string, T_ENUM>();
    //nb::implicitly_convertible<uint8_t, T_ENUM>();
}

template<typename T_ENUM>
void make_enum_string_class(nanobind::module_& m, const std::string& name)
{
    auto enum_class =
        nb::class_<T_ENUM>(
            m,
            name.c_str(),
            fmt::format("Helper class to convert between strings and enum values of type '{}'",
                        magic_enum::enum_type_name<T_ENUM>())
                .c_str())
            .def(nb::init<>(), "Default constructor")
            .def(nb::init<T_ENUM>(), "Construct from enum value", nb::arg("value"))
            .def(
                "__init__",
                [](T_ENUM* self, uint8_t value) {
                    // Validate that the uint8_t value corresponds to a valid enum value
                    if (value >= magic_enum::enum_count<T_ENUM>())
                    {
                        throw std::invalid_argument(
                            fmt::format("Invalid enum value {}. Valid range is 0-{}",
                                        value,
                                        magic_enum::enum_count<T_ENUM>() - 1));
                    }
                    new (self) T_ENUM(static_cast<T_ENUM>(value));
                },
                "Construct from int",
                nb::arg("int"))
            .def(
                "__init__",
                [](T_ENUM* self, const std::string& str) {
                    new (self) T_ENUM(from_string<T_ENUM>(str));
                },
                "Construct from string",
                nb::arg("str"))
            // .def(nb::init_implicit<const std::string&>())
            .def(
                "__eq__",
                [](const T_ENUM& e, const T_ENUM& other) { return e == e; },
                "Equality operator",
                nb::arg("other"))
            .def("to_string", [](const T_ENUM& e) { return std::string(magic_enum::enum_name(e)); })
            .def("__str__", [](const T_ENUM& e) { return std::string(magic_enum::enum_name(e)); })
            .def("__repr__", [](const T_ENUM& e) { return fmt::format("{}",magic_enum::enum_name(e)); })

        ;

    // Add implicit conversion from string
    //nb::implicitly_convertible<std::string, T_ENUM>();
    //nb::implicitly_convertible<uint8_t, T_ENUM>();

    // Automatically create enum-like interface for all values
    constexpr auto enum_values = magic_enum::enum_values<T_ENUM>();
    for (auto value : enum_values)
    {
        auto name = magic_enum::enum_name(value);
        enum_class.def_prop_ro_static(name.data(), [value](nanobind::handle) { return value; });
    }

    // Add from_string static method
    enum_class.def_static(
        "from_string",
        [](const std::string& str) { return from_string<T_ENUM>(str); },
        "Convert string to enum value",
        nb::arg("str"));

    // Add get_all_values static method
    enum_class.def_static(
        "values",
        []() {
            std::vector<T_ENUM> values;
            for (auto value : magic_enum::enum_values<T_ENUM>())
            {
                values.push_back(value);
            }
            return values;
        },
        "Get all possible enum values");

    // Add get_all_names static method
    enum_class.def_static(
        "names",
        []() {
            std::vector<std::string> names;
            for (auto name : magic_enum::enum_names<T_ENUM>())
            {
                names.emplace_back(name);
            }
            return names;
        },
        "Get all possible enum names");

    enum_class.def_static(
        "count",
        []() { return magic_enum::enum_count<T_ENUM>(); },
        "Get the number of enum values");
}

}
}
}