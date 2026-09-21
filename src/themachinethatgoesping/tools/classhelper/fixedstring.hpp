// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief A structural, compile-time fixed-size string that can be used as a non-type
 *        template parameter (NTTP).
 *
 * Neither std::string nor std::string_view can be used as non-type template parameters,
 * because they are not "structural types" (their data members are private). FixedString
 * stores the characters in a public array and therefore qualifies as a structural type,
 * e.g. template<FixedString Name = "default"> class Foo { ... };
 *
 * @authors Peter Urban
 */

#pragma once

/* generated doc strings */
#include ".docstrings/fixedstring.doc.hpp"

#include <algorithm>
#include <cstddef>
#include <string>
#include <string_view>

namespace themachinethatgoesping {
namespace tools {
namespace classhelper {

/**
 * @brief Compile-time fixed-size string usable as a non-type template parameter.
 *
 * @tparam N Size of the character buffer including the terminating null character.
 */
template<std::size_t N>
struct FixedString
{
    char value[N]{}; ///< character buffer (public -> structural type), includes the trailing '\0'

    /**
     * @brief Construct from a string literal (copies all N characters incl. the trailing null).
     *
     * @param str string literal to copy
     */
    consteval FixedString(const char (&str)[N]) noexcept { std::copy_n(str, N, value); }

    /**
     * @brief Number of characters, excluding the terminating null character.
     *
     * @return number of characters
     */
    static constexpr std::size_t size() noexcept { return N - 1; }

    /**
     * @brief Get the string as a std::string_view (without the terminating null).
     *
     * @return std::string_view referencing the internal buffer
     */
    constexpr std::string_view sv() const noexcept { return std::string_view(value, N - 1); }

    /**
     * @brief Get the string as a std::string (without the terminating null).
     *
     * @return std::string copy of the characters
     */
    std::string str() const { return std::string(value, N - 1); }

    /**
     * @brief Implicit conversion to std::string_view (without the terminating null).
     */
    constexpr operator std::string_view() const noexcept { return sv(); }

    auto operator<=>(const FixedString&) const = default;
};

/// @brief deduction guide so a FixedString can be deduced from a string literal
template<std::size_t N>
FixedString(const char (&)[N]) -> FixedString<N>;

} // namespace classhelper
} // namespace tools
} // namespace themachinethatgoesping
