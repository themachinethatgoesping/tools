// SPDX-FileCopyrightText: 2024 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0
#pragma once

/* generated doc strings */
#include ".docstrings/enum.doc.hpp"

#include <magic_enum/magic_enum.hpp>

namespace themachinethatgoesping {
namespace tools {
namespace helper {

template<typename T> // T is input
struct is_magic_enum_compatible
{
    using type                 = T;                 // type is output type
    static constexpr int value = std::is_enum_v<T>; // by default is compatible if it is an enum

    //static constexpr bool operator()() { return value; } TODO: add this in c++23
};

template<class T>
inline constexpr bool is_magic_enum_compatible_v = is_magic_enum_compatible<T>::value;

}
}
}