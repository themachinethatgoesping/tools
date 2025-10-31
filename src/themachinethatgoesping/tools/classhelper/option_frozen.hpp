// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0
#pragma once

/* generated doc strings */
#include ".docstrings/option_frozen.doc.hpp"

/* generated doc strings */
#include ".docstrings/option.doc.hpp"

#include <array>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <frozen/string.h>
#include <frozen/unordered_map.h>
#include <magic_enum/magic_enum.hpp>

#include "objectprinter.hpp"
#include "stream.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace classhelper {

template<typename t_enum_,
         std::size_t                                 __size,
         const std::array<t_enum_, __size>&          __enum_values,
         const std::array<std::string_view, __size>& __enum_names,
         const std::array<std::string_view, __size>& __enum_alt_names,
         t_enum_                                     default_value_ = __enum_values[0]>
requires std::is_enum_v<t_enum_>
struct OptionFrozen
{
    using t_enum       = t_enum_;
    using t_underlying = std::underlying_type_t<t_enum>;

    static constexpr t_enum default_value = default_value_;

  private:
    static constexpr frozen::string make_frozen_string(std::string_view text)
    {
        return frozen::string{ text.data(), text.size() };
    }

    static constexpr bool has_duplicate_strings(const std::array<std::string_view, __size>& arr)
    {
        for (std::size_t i = 0; i < __size; ++i)
            for (std::size_t j = i + 1; j < __size; ++j)
                if (arr[i] == arr[j])
                    return true;
        return false;
    }

    template<std::size_t... I>
    static constexpr auto make_enum_to_name_pairs(std::index_sequence<I...>)
    {
        return std::array<std::pair<t_enum, std::string_view>, __size>{ { std::pair{
            __enum_values[I], std::string_view{ __enum_names[I] } }... } };
    }

    template<std::size_t... I>
    static constexpr auto make_enum_to_alt_name_pairs(std::index_sequence<I...>)
    {
        return std::array<std::pair<t_enum, std::string_view>, __size>{ { std::pair{
            __enum_values[I], std::string_view{ __enum_alt_names[I] } }... } };
    }

    template<std::size_t... I>
    static constexpr auto make_name_to_enum_pairs(std::index_sequence<I...>)
    {
        return std::array<std::pair<frozen::string, t_enum>, __size * 2>{
            { std::pair{ make_frozen_string(__enum_names[I]), __enum_values[I] }...,
              std::pair{ make_frozen_string(__enum_alt_names[I]), __enum_values[I] }... }
        };
    }

    static constexpr std::size_t find_index(t_enum needle)
    {
        for (std::size_t i = 0; i < __size; ++i)
        {
            if (__enum_values[i] == needle)
            {
                return i;
            }
        }
        return __size;
    }

    static constexpr auto _s_enum_to_name =
        frozen::make_unordered_map(make_enum_to_name_pairs(std::make_index_sequence<__size>{}));
    static constexpr auto _s_enum_to_alt_name =
        frozen::make_unordered_map(make_enum_to_alt_name_pairs(std::make_index_sequence<__size>{}));
    static constexpr auto _s_name_to_enum = frozen::make_unordered_map<frozen::string, t_enum>(
        make_name_to_enum_pairs(std::make_index_sequence<__size>{}));

  public:
    t_enum value;

    OptionFrozen(t_enum v = default_value)
        : value(v)
    {
    }

    explicit OptionFrozen(t_underlying v) { set(v); }
    explicit OptionFrozen(std::string_view v) { set(v); }

    void set(t_enum v) { value = v; }

    void set(t_underlying v)
    {
        const auto converted = static_cast<t_enum>(v);
        if (_s_enum_to_name.find(converted) == _s_enum_to_name.end())
        {
            std::array<std::string, __size> value_name_pairs{};
            for (std::size_t i = 0; i < __size; ++i)
            {
                value_name_pairs[i] = fmt::format(
                    "'{}': {}", static_cast<t_underlying>(__enum_values[i]), __enum_names[i]);
            }

            throw std::invalid_argument(
                fmt::format("Invalid enum value: {}. Valid values are: [{}]",
                            v,
                            fmt::join(value_name_pairs, ", ")));
        }
        value = converted;
    }

    void set(std::string_view v) { value = to_value(v); }

    auto name() const { return _s_enum_to_name.at(value); }
    auto alt_name() const { return _s_enum_to_alt_name.at(value); }

    static constexpr auto to_name(t_enum val) { return _s_enum_to_name.at(val); }
    static constexpr auto to_alt_name(t_enum val) { return _s_enum_to_alt_name.at(val); }
    static constexpr auto to_value(std::string_view name)
    {
        if (auto it = _s_name_to_enum.find(name); it != _s_name_to_enum.end())
            return it->second;

        throw std::invalid_argument(
            fmt::format("Invalid enum name: '{}'. Valid names are: [{}]. Alt names: [{}]",
                        name,
                        fmt::join(__enum_names, ", "),
                        fmt::join(__enum_alt_names, ", ")));
    }

    [[nodiscard]] static constexpr auto underlying_values()
    {
        std::array<t_underlying, __size> underlying_vals{};
        for (std::size_t i = 0; i < __size; ++i)
        {
            underlying_vals[i] = static_cast<t_underlying>(__enum_values[i]);
        }
        return underlying_vals;
    }

    [[nodiscard]] static constexpr const auto& values() { return __enum_values; }

    [[nodiscard]] static constexpr auto names()
    {
        std::array<std::string_view, __size> names{};
        for (std::size_t i = 0; i < __size; ++i)
        {
            names[i] = std::string_view{ __enum_names[i] };
        }
        return names;
    }

    [[nodiscard]] static constexpr auto alt_names()
    {
        std::array<std::string_view, __size> names{};
        for (std::size_t i = 0; i < __size; ++i)
        {
            names[i] = std::string_view{ __enum_alt_names[i] };
        }
        return names;
    }

    [[nodiscard]] static constexpr std::size_t count() { return __size; }
    [[nodiscard]] static constexpr auto type_name() { return magic_enum::enum_type_name<t_enum>(); }

    bool enum_contains(t_underlying v) const
    {
        return _s_enum_to_name.find(static_cast<t_enum>(v)) != _s_enum_to_name.end();
    }

    operator t_enum() const { return value; }
    operator t_underlying() const { return static_cast<t_underlying>(value); }
    operator std::string() const { return std::string(name()); }

    bool operator==(const OptionFrozen& other) const = default;
    bool operator==(t_enum other) const { return value == other; }
    bool operator==(t_underlying other) const { return static_cast<t_underlying>(value) == other; }
    bool operator==(std::string_view other) const { return name() == other; }

    explicit operator bool() const { return enum_contains(static_cast<t_underlying>(value)); }

    static OptionFrozen from_stream(std::istream& is)
    {
        t_enum v{};
        is.read(reinterpret_cast<char*>(&v), sizeof(t_enum));
        return OptionFrozen(v);
    }

    void to_stream(std::ostream& os) const
    {
        os.write(reinterpret_cast<const char*>(&value), sizeof(t_enum));
    }

    ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const
    {
        ObjectPrinter printer(fmt::format("Option<{}> (struct)", type_name()),
                              float_precision,
                              superscript_exponents);

        printer.register_string("value", name(), alt_name());

        printer.register_section("Possible enum options");
        auto underlying = underlying_values();
        for (std::size_t i = 0; i < __size; ++i)
        {
            printer.register_string(
                std::to_string(underlying[i]), __enum_names[i], __enum_alt_names[i]);
        }

        return printer;
    }

    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(OptionFrozen)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

}
}
}
