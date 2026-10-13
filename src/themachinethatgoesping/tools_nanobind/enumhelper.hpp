
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

#include <fmt/format.h>
#include <magic_enum/magic_enum.hpp>
#include <nanobind/nanobind.h>
#include <nanobind/operators.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/string_view.h>
#include <algorithm>
#include <new>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include <themachinethatgoesping/tools/classhelper/option.hpp>
#include <themachinethatgoesping/tools_nanobind/classhelper.hpp>
#include <stdexcept>

namespace themachinethatgoesping {
namespace tools {
namespace nanobind_helper {

/**
 * @brief Levenshtein edit distance between two strings (used for did-you-mean suggestions).
 */
inline std::size_t levenshtein_distance(std::string_view a, std::string_view b)
{
    std::vector<std::size_t> prev(b.size() + 1), curr(b.size() + 1);
    for (std::size_t j = 0; j <= b.size(); ++j)
        prev[j] = j;
    for (std::size_t i = 1; i <= a.size(); ++i)
    {
        curr[0] = i;
        for (std::size_t j = 1; j <= b.size(); ++j)
        {
            const std::size_t cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
            curr[j] = std::min({ prev[j] + 1, curr[j - 1] + 1, prev[j - 1] + cost });
        }
        std::swap(prev, curr);
    }
    return prev[b.size()];
}

/**
 * @brief Build a helpful "did you mean" error message for an invalid enum value name. Suggests
 *        substring matches first, otherwise the closest names by edit distance.
 */
template<typename t_enum>
std::string invalid_enum_name_message(std::string_view name, std::string_view what)
{
    const auto all_names = magic_enum::enum_names<t_enum>();

    std::vector<std::string_view> suggestions;
    for (auto n : all_names)
        if (!n.empty() && (n.find(name) != std::string_view::npos ||
                           (!name.empty() && name.find(n) != std::string_view::npos)))
            suggestions.push_back(n);

    if (suggestions.empty())
    {
        std::vector<std::pair<std::size_t, std::string_view>> scored;
        for (auto n : all_names)
            scored.emplace_back(levenshtein_distance(name, n), n);
        std::sort(scored.begin(), scored.end(), [](const auto& l, const auto& r) {
            return l.first < r.first;
        });
        for (std::size_t i = 0; i < std::min<std::size_t>(3, scored.size()); ++i)
            suggestions.push_back(scored[i].second);
    }

    return fmt::format("'{}' is not a valid {}.\n  Did you mean: [{}]?\n  Possible values: [{}]",
                       name,
                       what,
                       fmt::join(suggestions, ", "),
                       fmt::join(all_names, ", "));
}

/**
 * @brief Cast a string to an Option, throwing a helpful "did you mean" ValueError if the name is
 *        not a valid enum value. Use in bindings (as an explicit std::string overload) to avoid
 *        nanobind's opaque "implicit conversion failed" TypeError for invalid option strings.
 */
template<typename T_OPTION>
T_OPTION option_from_string_verbose(std::string_view name, std::string_view what)
{
    const auto value = magic_enum::enum_cast<typename T_OPTION::t_enum>(name);
    if (!value.has_value())
        throw nanobind::value_error(
            invalid_enum_name_message<typename T_OPTION::t_enum>(name, what).c_str());
    return T_OPTION(value.value());
}

/**
 * @brief Return the enum value name of an Option/OptionFrozen, falling back to the raw numeric
 *        value if the held value is not part of the registered enum. This keeps __str__/__repr__
 *        from throwing for options that legitimately hold an unregistered value (e.g. a
 *        proprietary datagram identifier read from a file).
 */
template<typename T_OPTION>
std::string option_value_name(const T_OPTION& self)
{
    try
    {
        return static_cast<std::string>(self);
    }
    catch (const std::exception&)
    {
        return fmt::format("0x{:X}", static_cast<typename T_OPTION::t_underlying>(self.value));
    }
}

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

            // __eq__ operators
            .def(nb::self == nb::self)
            .def(nb::self == t_enum())
            .def(nb::self == t_underlying())
            .def(nb::self == std::string_view())

        // default copy functions
        __PYCLASS_DEFAULT_COPY__(T_OPTION)
        // default binary functions
        __PYCLASS_DEFAULT_BINARY__(T_OPTION)
            // string conversion (unknown-safe): an OptionFrozen may legitimately hold a value that
            // is not part of the registered enum (e.g. a proprietary datagram identifier), in which
            // case name() throws -> option_value_name falls back to the raw numeric value.
            .def(
                "__str__",
                [](const T_OPTION& self) { return option_value_name(self); },
                "Return the name of the enum value (safe for unregistered values)")
            .def(
                "__repr__",
                [](const T_OPTION& self) {
                    return fmt::format("{}.{}", self.type_name(), option_value_name(self));
                },
                "Return object information as string")
            .def(
                "info_string",
                [](const T_OPTION& self,
                   unsigned int    float_precision,
                   bool            superscript_exponents) {
                    return self.__printer__(float_precision, superscript_exponents).create_str();
                },
                "Return object information as string",
                nb::arg("float_precision")       = 3,
                nb::arg("superscript_exponents") = true)
            .def(
                "print",
                [](const T_OPTION& self,
                   unsigned int    float_precision,
                   bool            superscript_exponents) {
                    nb::print(self.__printer__(float_precision, superscript_exponents)
                                  .create_str()
                                  .c_str());
                },
                "Print object information",
                nb::arg("float_precision")       = 3,
                nb::arg("superscript_exponents") = true)
        // end
        ;
}

/**
 * @brief Extend a nanobind enum with string conversion helpers using magic_enum
 */
template<typename T_ENUM, typename T_NB_ENUM>
void add_string_to_enum_conversion(T_NB_ENUM& t_enum)
{
    t_enum.def("__init__",
               [](T_ENUM* self, const std::string& str) {
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

                       auto error_message =
                           fmt::format("ERROR: unknown value option '{}'! Try: [{}]",
                                       str,
                                       enum_info);
                       nb::print(error_message.c_str());
                       throw std::invalid_argument(error_message);
                   }

                   new (self) T_ENUM(enum_value.value());
               },
               nb::arg("str"),
               "Construct this enum type from string");

    t_enum.def("str", [](const T_ENUM& self) { return magic_enum::enum_name(self); });

    nb::implicitly_convertible<std::string, T_ENUM>();
}

}
}
}
