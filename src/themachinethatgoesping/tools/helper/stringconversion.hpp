#pragma once

/* generated doc strings */
#include ".docstrings/stringconversion.doc.hpp"

#include <concepts>
#include <string>
#include <string_view>
#include <vector>
#include "fast_float/fast_float.h"

namespace themachinethatgoesping::tools::helper {

/**
 * @brief convert a string to float using fast_float::from_chars
 * Fast_float conforms to std::from_chars (c++20, but not completely implemented in clang yet)
 * The conversion is locale independent (. is the decimal separator)
 * see also: https://github.com/fastfloat/fast_float
 *
 * @tparam t_float : double or float
 * @param str if empty or non-numeric a NAN is returned
 * @return double
 */
template<std::floating_point t_float>
inline t_float string_to_floattype(std::string_view str)
{
    if (str.empty())
        return std::numeric_limits<t_float>::quiet_NaN();

    t_float result;
    auto    answer = fast_float::from_chars(str.data(), str.data() + str.size(), result);

    if (answer.ec != std::errc())
        return std::numeric_limits<t_float>::quiet_NaN();

    return result;
}

template<std::floating_point t_float>
inline std::vector<t_float> string_to_floattype_vector(std::string_view std, char delim = ',')
{
    std::vector<t_float>        result;
    std::string_view::size_type pos = 0;
    while (pos != std::string_view::npos)
    {
        auto next_pos = std.find(delim, pos);
        auto str      = std.substr(pos, next_pos - pos);
        result.push_back(string_to_floattype<t_float>(str));
        pos = next_pos;
        if (pos != std::string_view::npos)
            pos++;
    }
    return result;
}

template<typename int_type>
inline std::string int_as_string(int_type value)
{
    std::string valueAsString;
    valueAsString.resize(sizeof(value));
    memcpy(valueAsString.data(), &value, sizeof(value));

    return valueAsString;
}

template<typename int_type>
inline int_type string_as_int(std::string_view value)
{
    int_type valueAsFourByteInt;
    memcpy(&valueAsFourByteInt, value.data(), sizeof(valueAsFourByteInt));
    return valueAsFourByteInt;
}
} // namespace themachinethatgoesping::tools::helper