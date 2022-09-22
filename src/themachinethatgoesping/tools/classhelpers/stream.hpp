// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief some macros to easily implement common class capabilities for for pybind classes
 *
 * @authors Peter Urban
 */

#pragma once

#include <iostream>
#include <sstream>

#define __STREAM_DEFAULT_TO_BINARY__                                                               \
    /** @brief convert object to vector of bytes                                                   \
     *                                                                                             \
     * @param resize_buffer variable for interface compatibility, does not do anything             \
     *                                                                                             \
     * @return vector of bytes                                                                     \
     * */                                                                                          \
    std::string to_binary([[maybe_unused]] bool resize_buffer = true)                              \
    {                                                                                              \
        std::stringstream buffer_stream;                                                           \
                                                                                                   \
        to_stream(buffer_stream);                                                                  \
        return buffer_stream.str();                                                                \
    };

#define __STREAM_DEFAULT_FROM_BINARY__(T_CLASS)                                                    \
    /** @brief convert object to vector of bytes                                                   \
     *                                                                                             \
     * @param check_buffer_is_read_completely variable for interface compatibility, does not do    \
     * anything                                                                                    \
     *                                                                                             \
     * @return vector of bytes                                                                     \
     * */                                                                                          \
    static T_CLASS from_binary(const std::string&    buffer,                                       \
                               [[maybe_unused]] bool check_buffer_is_read_completely = false)      \
    {                                                                                              \
        std::stringstream buffer_stream{ buffer };                                                 \
                                                                                                   \
        return from_stream(buffer_stream);                                                         \
    };

// this assumes that T_CLASS has from_stream and to_stream functions
#define __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(T_CLASS)                                        \
    __STREAM_DEFAULT_TO_BINARY__                                                                   \
    __STREAM_DEFAULT_FROM_BINARY__(T_CLASS)

namespace themachinethatgoesping {
namespace tools {
namespace classhelpers {
namespace stream {

template<typename T_container>
inline void container_to_stream(std::ostream& os, const T_container& container)
{
    size_t size = container.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
    os.write(reinterpret_cast<const char*>(container.data()),
             size * sizeof(typename T_container::value_type));
}

template<typename T_container>
inline T_container container_from_stream(std::istream& is)
{
    T_container container;
    size_t      size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size_t));
    container.resize(size);
    is.read(reinterpret_cast<char*>(container.data()),
            size * sizeof(typename T_container::value_type));

    return container;
}

} // stream
} // classhelpers
} // tools
} // themachinethatgoesping