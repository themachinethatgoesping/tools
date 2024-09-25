
// SPDX-FileCopyrightText: 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0
#pragma once

/* generated doc strings */
#include ".docstrings/xtensor.doc.hpp"
#include <xtensor/xcontainer.hpp>

namespace themachinethatgoesping {
namespace tools {
namespace helper {

// // define a xcontainer concept that works for both xtensor and pytensor
// template<typename T>
// concept XContainerConcept = std::is_base_of<xt::xcontainer<T>, T>::value;

template<typename T>
concept c_xtensor = requires {
    { std::is_base_of<xt::xexpression<T>, T>::value };
    { std::tuple_size<typename T::shape_type>::value } -> std::convertible_to<std::size_t>;
};

template<typename T>
concept c_xtensor_2d =
    c_xtensor<T> && requires { requires std::tuple_size<typename T::shape_type>::value == 2; };

template<typename T>
concept c_xtensor_1d =
    c_xtensor<T> && requires { requires std::tuple_size<typename T::shape_type>::value == 1; };

// Type trait to extract the data type from an xtensor
template<typename T>
struct xtensor_datatype
{
    using type = std::decay_t<decltype(std::declval<T>()(0))>;
};

// Helper alias template
template<typename T>
using xtensor_datatype_t = typename xtensor_datatype<T>::type;

}
}
}