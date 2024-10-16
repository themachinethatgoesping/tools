// SPDX-FileCopyrightText: 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/hashhelper.doc.hpp"

#include <xxhash.hpp>
// xtensor includes
#include "helper/xtensor.hpp"

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
template<themachinethatgoesping::tools::helper::c_xtensor t_xtensor>
std::size_t hash_value(const t_xtensor& array)
{
    return xxh::xxhash3<64>(
        array.data(),
        array.size() *
            sizeof(
                typename themachinethatgoesping::tools::helper::xtensor_datatype<t_xtensor>::type));
}

}
