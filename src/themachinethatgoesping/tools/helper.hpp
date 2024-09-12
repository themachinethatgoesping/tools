// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Drew Dormann (stackoverflow)
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/helper.doc.hpp"

#include <cmath>
#include <complex>
#include <string>
#include <variant>
#include <vector>

#include "fast_float/fast_float.h"

#include "helper/defaultmap.hpp"
#include "helper/defaultsharedpointermap.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace helper {

template <typename t_out, typename t_in1, typename t_in2>
inline t_out substract_set_zero_if_negative(t_in1 a, t_in2 b)
{
    return a > b ? a - b : 0;
}

// source https://gist.github.com/s3rvac/d1f30364ce1f732d75ef0c89a1c8c1ef
template<typename... Ts>
struct make_overload : Ts...
{
    using Ts::operator()...;
};
template<typename... Ts>
make_overload(Ts...) -> make_overload<Ts...>;

template<typename Variant, typename... Alternatives>
decltype(auto) visit_variant(Variant&& variant, Alternatives&&... alternatives)
{
    return std::visit(make_overload{ std::forward<Alternatives>(alternatives)... },
                      std::forward<Variant>(variant));
}

template<typename Variant, typename... Alternatives>
decltype(auto) visit_variant_no_return(Variant&& variant, Alternatives&&... alternatives)
{
    std::visit(make_overload{ std::forward<Alternatives>(alternatives)... },
               std::forward<Variant>(variant));
}

// source https://stackoverflow.com/a/33799784
// map get with default
template<template<class, class, class...> class C, typename K, typename V, typename... Args>
V get_from_map_with_default(const C<K, V, Args...>& m, K const& key, const V& defval)
{
    typename C<K, V, Args...>::const_iterator it = m.find(key);
    if (it == m.end())
        return defval;
    return it->second;
}

// usage:
//  visit_variant(v,
//          [](int i) { std::cout << i << '\n'; },
//          [](double d) { std::cout << d << '\n'; },
//          [](const std::string& s) { std::cout << s << '\n'; }
//      );

/**
 * @brief compare to floats using a relative difference factor
 *
 * @tparam t_float floating point type
 * @param f1 float/double 1
 * @param f2 float/double 1
 * @param relative_difference_factor relative factor by which the 2 numbers must be comparable
 * (default 0.01%)
 * @return true/false
 */
template<typename t_float>
bool approx(t_float f1, t_float f2, t_float relative_difference_factor = 0.0001 // 0.01%
)
{
    // if both are NAN return true
    if (std ::isnan(f1))
        if (std::isnan(f2))
            return true;

    // if both are inf (and same sign) return true
    if (std::isinf(f1))
        if (std::isinf(f2))
        {
            if (f1 < 0)
            {
                if (f2 < 0)
                    return true;
            }
            else
            {
                if (f2 > 0)
                    return true;
            }
        }

    if (f1 == f2)
        return true;

    // if the difference between both is smaller than the relative difference factor (compared to
    // the larger float) return true
    return std::abs(f1 - f2) <= relative_difference_factor * std::max(std::abs(f1), std::abs(f2));
}

template<typename t_float>
bool approx_complex(std::complex<t_float> f1,
                    std::complex<t_float> f2,
                    t_float               relative_difference_factor = 0.0001 /* 0.01% */)
{
    return approx(f1.real(), f2.real(), relative_difference_factor) &&
           approx(f1.imag(), f2.imag(), relative_difference_factor);
}

template<typename t_container>
bool approx_container(const t_container&               c1,
                      const t_container&               c2,
                      typename t_container::value_type relative_difference_factor = 0.0001 // 0.01%
)
{
    if (c1.size() != c2.size())
        return false;

    for (size_t i = 0; i < c1.size(); i++)
        if (!approx(c1[i], c2[i], relative_difference_factor))
            return false;

    return true;
}

template<typename t_container>
bool approx_container_complex(
    const t_container&                           c1,
    const t_container&                           c2,
    typename t_container::value_type::value_type relative_difference_factor = 0.0001f /* 0.01% */
)
{
    if (c1.size() != c2.size())
        return false;

    for (size_t i = 0; i < c1.size(); i++)
        if (!approx_complex(c1[i], c2[i], relative_difference_factor))
            return false;

    return true;
}

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
template<typename t_float>
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

template<typename t_float>
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

template<typename t_container1, typename t_container2>
inline bool compare_containers(const t_container1& c1, const t_container2& c2)
{
    if (c1.size() != c2.size())
        return false;

    // comparison that also works for non random access containers
    for (auto it1 = c1.begin(), it2 = c2.begin(); it1 != c1.end(); ++it1, ++it2)
        if (*it1 != *it2)
            return false;
}

template<typename t_float>
bool float_equals(t_float a, t_float b, t_float epsilon = 0.0001)
{
    return std::abs(a - b) < epsilon || (std::isnan(a) && std::isnan(b)) ||
           (std::isinf(a) && std::isinf(b));
}

} // namespace helper
} // namespace tools
} // namespace themachinethatgoesping
