// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief class some macro to easily implement hashing for classes using xxhash_cpp
 *
 * @authors Peter Urban
 */

#pragma once

/* generated doc strings */
#include ".docstrings/xxhashhelper.doc.hpp"

#include <boost/iostreams/concepts.hpp> // sink
#include <boost/iostreams/stream.hpp>

// #if defined(__x86_64__) || defined(_M_X64)
// #else
// #define _MM_PERM_ENUM int
// #endif
#if defined(__GNUC__)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Warray-bounds"
#endif

#include <xxhash.hpp>

#if defined(__GNUC__)
#  pragma GCC diagnostic pop
#endif

class XXHashSink : public boost::iostreams::sink
{
    xxh::hash3_state_t<64>& _hash_state;

  public:
    XXHashSink(xxh::hash3_state_t<64>& hash_state)
        : _hash_state(hash_state)
    {
    }

    std::streamsize write(const char* s, std::streamsize n)
    {
        _hash_state.update(s, n);
        return n;
    }

    xxh::hash_t<64> hash() { return _hash_state.digest(); }
};

#define __BINARY_HASH_NOT_CONST__                                                                  \
    /** @brief compute a 64 bit hash of the object using xxhash and the to_binary function.        \
     * This function is called binary because the to_binary function object is used                \
     */                                                                                            \
    xxh::hash_t<64> binary_hash()                                                                  \
    {                                                                                              \
        xxh::hash3_state_t<64>               hash;                                                 \
        boost::iostreams::stream<XXHashSink> stream(hash);                                         \
        this->to_stream(stream);                                                                   \
        stream.flush();                                                                            \
        return hash.digest();                                                                      \
    }                        

#define __BINARY_HASH__  /** @brief compute a 64 bit hash of the object using xxhash and the       \
                          * to_binary function. This  function is called binary because the        \
                          * to_binary  function of the object is used */                           \
    xxh::hash_t<64> binary_hash() const                                                            \
    {                                                                                              \
        xxh::hash3_state_t<64>               hash;                                                 \
        boost::iostreams::stream<XXHashSink> stream(hash);                                         \
        this->to_stream(stream);                                                                   \
        stream.flush();                                                                            \
        return hash.digest();                                                                      \
    }                                                                                              \

