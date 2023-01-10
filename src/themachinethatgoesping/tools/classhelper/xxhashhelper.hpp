// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief class some macro to easily implement hashing for classes using xxhash_cpp
 *
 * @authors Peter Urban
 */

#pragma once

#include <xxhash.hpp>

#define __SLOW_HASH_NOT_CONST__                                                                    \
    /** @brief compute a 64 bit hash of the object using xxhash and the to_binary function. This   \
     * function is called slow because the to_binary function creates an unnecessary copy of the   \
     * object */                                                                                   \
    xxh::hash_t<64> slow_hash()                                                                    \
    {                                                                                              \
        return xxh::xxhash3<64>(this->to_binary());                                                \
    }

#define __SLOW_HASH__                                                                              \
    /** @brief compute a 64 bit hash of the object using xxhash and the to_binary function. This   \
     * function is called slow because the to_binary function creates an unnecessary copy of the   \
     * object */                                                                                   \
    xxh::hash_t<64> slow_hash() const                                                              \
    {                                                                                              \
        return xxh::xxhash3<64>(this->to_binary());                                                \
    }

// // inject object.hash() into namespace std
//   template <> struct std::hash<>
//   {
//     size_t
//     operator()(themachinethatgoesping::echosounders::simrad::datagrams::xml_datagrams::XML_Parameter_Channel
//     & arg) const
//     {
//         return arg.slow_hash();
//     }
//   };