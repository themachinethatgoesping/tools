// SPDX-FileCopyrightText: 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/hashhelper.doc.hpp"

#ifdef __arm__
    #define XXH_VECTOR 0
#endif
#include <xxhash.hpp>

/**
 * @brief boost hash specializations for some types
 *
 */

/**
 * @brief boost hash function for xt arrays
 *
 */
namespace xt {
/**
 * @brief Boost hash function for xt tensors
 *
 * @tparam T
 * @param b
 * @return std::size_t
 */
template<typename T, size_t d>
std::size_t hash_value(const xt::xtensor<T, d>& array)
{
    return xxh::xxhash3<64>(array.data(), array.size() * sizeof(T));
}

}
