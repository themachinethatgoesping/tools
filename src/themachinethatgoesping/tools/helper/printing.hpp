#pragma once

/* generated doc strings */
#include ".docstrings/printing.doc.hpp"

#include <fmt/core.h>
#include <frozen/map.h>
#include <string>
#include <string_view>

namespace themachinethatgoesping::tools::helper {
// Function to convert an integer to its superscript representation
inline std::string superscript(int exponent)
{
    static constexpr frozen::map<char, std::string_view, 11> superscript_map = {
        { '0', "⁰" }, { '1', "¹" }, { '2', "²" }, { '3', "³" }, { '4', "⁴" }, { '5', "⁵" },
        { '6', "⁶" }, { '7', "⁷" }, { '8', "⁸" }, { '9', "⁹" }, { '-', "⁻" }
    };

    std::string result;

    for (char e : fmt::format("{}", exponent))
    {
        result += superscript_map.at(e);
    }

    return result;
}

} // namespace themachinethatgoesping::tools::helper