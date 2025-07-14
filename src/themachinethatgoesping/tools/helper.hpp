// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Drew Dormann (stackoverflow)
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/helper.doc.hpp"

#include <concepts>

#include <cmath>
#include <complex>
#include <string>
#include <variant>
#include <vector>
#include <optional>
#include <limits>
#include <cstring>

namespace themachinethatgoesping {
namespace tools {
namespace helper {

template<typename t_out, typename t_in1, typename t_in2>
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


} // namespace helper
} // namespace tools
} // namespace themachinethatgoesping
