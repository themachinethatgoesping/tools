// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief some macros to easily implement common class capabilities for for pybind classes
 *
 * @authors Peter Urban
 */

#pragma once

/* generated doc strings */
#include ".docstrings/stream.doc.hpp"

#include "xxhashhelper.hpp"
#include <iostream>
#include <optional>
#include <set>
#include <sstream>

#include "../helper/isviewstream.hpp"
#include "../helper/osstream.hpp"

#define __STREAM_DEFAULT_TO_BINARY__                                                               \
    /** @brief convert object to vector of bytes                                                   \
     *                                                                                             \
     * @param resize_buffer variable for interface compatibility, does not do anything             \
     *                                                                                             \
     * @return vector of bytes                                                                     \
     * */                                                                                          \
    std::string to_binary([[maybe_unused]] bool resize_buffer = true) const                        \
    {                                                                                              \
        std::string result;                                                                        \
        themachinethatgoesping::tools::helper::osstream buffer_stream(result);                     \
                                                                                                   \
        to_stream(buffer_stream);                                                                  \
        return result;                                                                             \
    };

#define __STREAM_DEFAULT_TO_BINARY_NOT_CONST__                                                     \
    /** @brief convert object to vector of bytes                                                   \
     *                                                                                             \
     * @param resize_buffer variable for interface compatibility, does not do anything             \
     *                                                                                             \
     * @return vector of bytes                                                                     \
     * */                                                                                          \
    std::string to_binary([[maybe_unused]] bool resize_buffer = true)                              \
    {                                                                                              \
        std::string result;                                                                        \
        themachinethatgoesping::tools::helper::osstream buffer_stream(result);                     \
                                                                                                   \
        to_stream(buffer_stream);                                                                  \
        return result;                                                                             \
    };

#define __STREAM_DEFAULT_FROM_BINARY__(T_CLASS)                                                    \
    /** @brief convert object to vector of bytes                                                   \
     *                                                                                             \
     * @param check_buffer_is_read_completely variable for interface compatibility, does not do    \
     * anything                                                                                    \
     *                                                                                             \
     * @return vector of bytes                                                                     \
     * */                                                                                          \
    static T_CLASS from_binary(std::string_view      buffer,                                       \
                               [[maybe_unused]] bool check_buffer_is_read_completely = false)      \
    {                                                                                              \
        themachinethatgoesping::tools::helper::isviewstream buffer_stream(buffer);                 \
                                                                                                   \
        return from_stream(buffer_stream);                                                         \
    };
// this assumes that T_CLASS has from_stream and to_stream functions
#define __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS_NO_HASH__(T_CLASS)                                \
    __STREAM_DEFAULT_TO_BINARY__                                                                   \
    __STREAM_DEFAULT_FROM_BINARY__(T_CLASS)

// this assumes that T_CLASS has from_stream and to_stream functions
#define __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(T_CLASS)                                        \
    __STREAM_DEFAULT_TO_BINARY__                                                                   \
    __STREAM_DEFAULT_FROM_BINARY__(T_CLASS)                                                        \
    __BINARY_HASH__

// this assumes that T_CLASS has from_stream and to_stream functions
#define __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS_NOT_CONST__(T_CLASS)                              \
    __STREAM_DEFAULT_TO_BINARY_NOT_CONST__                                                         \
    __STREAM_DEFAULT_FROM_BINARY__(T_CLASS)                                                        \
    __BINARY_HASH_NOT_CONST__

namespace themachinethatgoesping {
namespace tools {
namespace classhelper {
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

template<typename t_map>
inline void map_to_stream(std::ostream& os, const t_map& map)
{
    size_t size = map.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
    for (const auto& [key, value] : map)
    {
        os.write(reinterpret_cast<const char*>(&key), sizeof(typename t_map::key_type));
        os.write(reinterpret_cast<const char*>(&value), sizeof(typename t_map::mapped_type));
    }
}

template<typename t_map>
inline t_map map_from_stream(std::istream& is)
{
    t_map  map;
    size_t size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size_t));
    for (size_t i = 0; i < size; ++i)
    {
        typename t_map::key_type    key;
        typename t_map::mapped_type value;
        is.read(reinterpret_cast<char*>(&key), sizeof(typename t_map::key_type));
        is.read(reinterpret_cast<char*>(&value), sizeof(typename t_map::mapped_type));
        map[key] = value;
    }

    return map;
}

template<typename t_map>
inline void map_container_to_stream(std::ostream& os, const t_map& map)
{
    size_t size = map.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
    for (const auto& [key, value] : map)
    {
        os.write(reinterpret_cast<const char*>(&key), sizeof(typename t_map::key_type));
        container_to_stream(os, value);
    }
}

template<typename t_map>
inline t_map map_container_from_stream(std::istream& is)
{
    t_map  map;
    size_t size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size_t));
    for (size_t i = 0; i < size; ++i)
    {
        typename t_map::key_type    key;
        typename t_map::mapped_type value;
        is.read(reinterpret_cast<char*>(&key), sizeof(typename t_map::key_type));
        value               = container_from_stream<typename t_map::mapped_type>(is);
        map[std::move(key)] = std::move(value);
    }

    return map;
}

template<typename T_set_value>
inline void set_to_stream(std::ostream& os, const std::set<T_set_value>& set)
{
    size_t size = set.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
    for (const auto& value : set)
    {
        os.write(reinterpret_cast<const char*>(&value), sizeof(T_set_value));
    }
}

template<typename T_set_value>
inline std::set<T_set_value> set_from_stream(std::istream& is)
{
    std::set<T_set_value> set;
    size_t                size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size_t));
    for (size_t i = 0; i < size; ++i)
    {
        T_set_value value;
        is.read(reinterpret_cast<char*>(&value), sizeof(T_set_value));
        set.insert(value);
    }

    return set;
}

template<unsigned int level, typename T_container>
inline void container_container_to_stream(std::ostream& os, const T_container& container)
{
    size_t size = container.size();
    os.write(reinterpret_cast<const char*>(&size), sizeof(size_t));

    if constexpr (level > 1)
    {
        for (const auto& sub_container : container)
        {
            container_container_to_stream<level - 1, typename T_container::value_type>(
                os, sub_container);
        }
    }
    else
    {
        for (const auto& sub_container : container)
        {
            container_to_stream(os, sub_container);
        }
    }
}

template<unsigned int level, typename T_container>
inline T_container container_container_from_stream(std::istream& is)
{
    T_container container;
    size_t      size;
    is.read(reinterpret_cast<char*>(&size), sizeof(size_t));
    container.resize(size);

    if constexpr (level > 1)
    {
        for (auto& sub_container : container)
        {
            sub_container =
                container_container_from_stream<level - 1, typename T_container::value_type>(is);
        }
    }
    else
    {
        for (auto& sub_container : container)
        {
            sub_container = container_from_stream<typename T_container::value_type>(is);
        }
    }

    return container;
}

template<typename T_optional>
inline void optional_to_stream(std::ostream& os, const std::optional<T_optional>& optional)
{
    bool has_value = optional.has_value();
    os.write(reinterpret_cast<const char*>(&has_value), sizeof(bool));

    if (has_value)
    {
        os.write(reinterpret_cast<const char*>(&optional.value()), sizeof(T_optional));
    }
}

template<typename T_optional>
inline std::optional<T_optional> optional_from_stream(std::istream& is)
{
    bool has_value;
    is.read(reinterpret_cast<char*>(&has_value), sizeof(bool));

    if (has_value)
    {
        T_optional value;
        is.read(reinterpret_cast<char*>(&value), sizeof(T_optional));
        return value;
    }
    else
    {
        return std::nullopt;
    }
}

template<typename T_optional>
inline void optional_container_to_stream(std::ostream&                    os,
                                         const std::optional<T_optional>& optional)
{

    bool has_value = optional.has_value();
    os.write(reinterpret_cast<const char*>(&has_value), sizeof(bool));

    if (has_value)
    {
        container_to_stream(os, optional.value());
    }
}

template<typename T_optional>
inline std::optional<T_optional> optional_container_from_stream(std::istream& is)
{
    bool has_value;
    is.read(reinterpret_cast<char*>(&has_value), sizeof(bool));

    if (has_value)
    {
        return container_from_stream<T_optional>(is);
    }
    else
    {
        return std::nullopt;
    }
}

template<typename T_optional_set_value>
inline void optional_set_to_stream(std::ostream&                                        os,
                                   const std::optional<std::set<T_optional_set_value>>& optional)
{

    bool has_value = optional.has_value();
    os.write(reinterpret_cast<const char*>(&has_value), sizeof(bool));

    if (has_value)
    {
        set_to_stream(os, optional.value());
    }
}

template<typename T_optional_set_value>
inline std::optional<std::set<T_optional_set_value>> optional_set_from_stream(std::istream& is)
{
    bool has_value;
    is.read(reinterpret_cast<char*>(&has_value), sizeof(bool));

    if (has_value)
    {
        return set_from_stream<T_optional_set_value>(is);
    }
    else
    {
        return std::nullopt;
    }
}

} // stream
} // classhelper
} // tools
} // themachinethatgoesping