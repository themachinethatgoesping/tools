// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0
#pragma once

/* generated doc strings */
#include ".docstrings/option.doc.hpp"

#include <magic_enum/magic_enum.hpp>
#include <string>
#include <string_view>
#include <type_traits>

#include <fmt/format.h>
#include <fmt/ranges.h>

#include "objectprinter.hpp"
#include "stream.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace classhelper {

template<typename t_enum_, t_enum_ default_value_ = magic_enum::enum_values<t_enum_>()[0]>
requires std::is_enum_v<t_enum_>
struct Option
{
    // expose template parameters as types and constants
    using t_enum                          = t_enum_;
    using t_underlying                    = std::underlying_type_t<t_enum>;
    static constexpr t_enum default_value = default_value_;

    // actual enum value
    t_enum value;

    // initializers
    Option(t_enum v = default_value_)
        : value(v)
    {
    }
    Option(t_underlying v) { set(v); }
    Option(std::string_view v) { set(v); }

    // setters
    void set(t_enum v) { value = v; }
    void set(t_underlying v)
    {
        if (!magic_enum::enum_contains<t_enum>(v))
        {
            auto                     underlying_vals = underlying_values();
            auto                     enum_names      = names();
            std::vector<std::string> value_name_pairs;
            for (size_t i = 0; i < underlying_vals.size(); ++i)
            {
                value_name_pairs.push_back(
                    fmt::format("'{}': {}", underlying_vals[i], enum_names[i]));
            }
            throw std::invalid_argument(
                fmt::format("Invalid enum value: {}. Valid values are: [{}]",
                            v,
                            fmt::join(value_name_pairs, ", ")));
        }
        value = static_cast<t_enum>(v);
    }
    void set(std::string_view v)
    {
        auto enum_opt = magic_enum::enum_cast<t_enum>(v);

        if (!enum_opt.has_value())
        {
            throw std::invalid_argument(
                fmt::format("Invalid enum name: '{}'. Valid names are: [{}]",
                            v,
                            fmt::join(magic_enum::enum_names<t_enum>(), ", ")));
        }
        value = enum_opt.value();
    }

    // getters
    auto name() { return std::string(magic_enum::enum_name(value)); }
    // const auto& value() const { return value; }

    [[nodiscard]] static constexpr auto underlying_values()
    {
        std::array<t_underlying, magic_enum::enum_count<t_enum>()> underlying_vals{};
        auto enum_vals = magic_enum::enum_values<t_enum>();
        for (size_t i = 0; i < enum_vals.size(); ++i)
        {
            underlying_vals[i] = static_cast<t_underlying>(enum_vals[i]);
        }
        return underlying_vals;
    }
    [[nodiscard]] static constexpr auto values() { return magic_enum::enum_values<t_enum>(); }
    [[nodiscard]] static constexpr auto names() { return magic_enum::enum_names<t_enum>(); }
    [[nodiscard]] static constexpr auto count() { return magic_enum::enum_count<t_enum>(); }
    [[nodiscard]] static constexpr auto type_name() { return magic_enum::enum_type_name<t_enum>(); }

    // operators
    operator t_enum() const { return value; }
    operator t_underlying() const { return static_cast<t_underlying>(value); }
    operator std::string() const { return std::string(magic_enum::enum_name(value)); }
    bool operator==(const Option& other) const { return value == other.value; }
    bool operator==(t_enum other) const { return value == other; }
    bool operator==(t_underlying other) const { return static_cast<t_underlying>(value) == other; }
    bool operator==(std::string_view other) const
    {
        return std::string(magic_enum::enum_name(value)) == other;
    }
    operator bool() const
    {
        return magic_enum::enum_contains<t_enum>(static_cast<t_underlying>(value));
    }

    // binary and print
    static auto from_stream(std::istream& is)
    {
        t_enum v;
        is.read(reinterpret_cast<char*>(&v), sizeof(t_enum));
        return Option(v);
    }
    void to_stream(std::ostream& os) const
    {
        os.write(reinterpret_cast<const char*>(&value), sizeof(t_enum));
    }

    ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const
    {
        ObjectPrinter printer("Option (struct)", float_precision, superscript_exponents);
        printer.register_enum("value", value);
        return printer;
    }

    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(Option)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

}
}
}
