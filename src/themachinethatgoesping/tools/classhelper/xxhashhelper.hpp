// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief class some macro to easily implement hashing for classes using xxhash_cpp
 *
 * @authors Peter Urban
 */

#pragma once

#include <xxhash.hpp>

#define __SLOW_HASH__                                                                              \
    /** @brief compute a 64 bit hash of the object using xxhash and the to_binary function. This function is called slow because the to_binary function creates an unnecessary copy of the object */ \
    xxh::hash_t<64> slow_hash()                                                                    \
    {                                                                                              \
        return xxh::xxhash3<64>(this->to_binary());                                                \
    }

// inject object.hash() into namespace std
// not used so far
#define __HASHABLE__(T_OBJECT) \
namespace std { \
template<typename T_OBJECT> \
struct hash<T_OBJECT> \
{ \
    std::size_t operator()(const T_OBJECT& object) const \
    { \
        return object.slow_hash(); \
    } \
}; \
}


// namespace themachinethatgoesping {
// namespace tools {
// namespace classhelper {
// } // classhelper
// } // tools
// } // themachinethatgoesping
