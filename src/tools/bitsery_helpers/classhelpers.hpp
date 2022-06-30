// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief some macros to easily implement comon class capabilities for for pybind classes
 *
 * @authors Peter Urban
 */

#pragma once

#include "helpers.hpp"
#include <bitsery/adapter/buffer.h>
#include <bitsery/adapter/stream.h>
#include <bitsery/bitsery.h>
#include <bitsery/traits/vector.h>
#include <iostream>

#define __BITSERY_DEFAULT_TO_BINARY__                                                              \
    /** @brief convert object to vector of bytes                                                   \
     *                                                                                             \
     * @param resize_buffer resize vector to written bytes after read                              \
     * @return vector of bytes                                                                     \
     * */                                                                                          \
    std::vector<uint8_t> to_binary(bool resize_buffer = true) const                                \
    {                                                                                              \
        std::vector<uint8_t> buffer;                                                               \
                                                                                                   \
        auto writtensize =                                                                         \
            bitsery::quickSerialization<bitsery::OutputBufferAdapter<std::vector<uint8_t>>>(       \
                buffer, *this);                                                                    \
                                                                                                   \
        if (resize_buffer)                                                                         \
            buffer.resize(writtensize);                                                            \
                                                                                                   \
        return buffer;                                                                             \
    };

#define __BITSERY_DEFAULT_FROM_BINARY__(T_CLASS)                                                    \
    /** @brief read object from vector of bytes                                                     \
     *                                                                                              \
     * @param buffer vector of bytes                                                                \
     * @param check_buffer_is_read_completely fail if buffer is not read completely                 \
     * @return T_CLASS object                                                                       \
     * */                                                                                           \
    static T_CLASS from_binary(const std::vector<uint8_t>& buffer,                                  \
                               bool                        check_buffer_is_read_completely = false) \
    {                                                                                               \
        T_CLASS object;                                                                             \
        auto    state =                                                                             \
            bitsery::quickDeserialization<bitsery::InputBufferAdapter<std::vector<uint8_t>>>(       \
                { buffer.begin(), buffer.end() }, object);                                          \
                                                                                                    \
        if (state.first != bitsery::ReaderError::NoError)                                           \
            throw(std::runtime_error("ERROR[T_CLASS::from_binary]: readerror"));                    \
                                                                                                    \
        if (check_buffer_is_read_completely)                                                        \
            if (!state.second)                                                                      \
                throw(std::runtime_error(                                                           \
                    "ERROR[T_CLASS::from_binary]: buffer was not read completely"));                \
                                                                                                    \
        return object;                                                                              \
    }

#define __BITSERY_DEFAULT_TO_STREAM__                                                              \
    /** @brief convert object to vector of bytes and write it to a ostream                         \
     *                                                                                             \
     * @param os reference to output stream (must be opened)                                       \
     * */                                                                                          \
    void to_stream(std::ostream& os)                                                               \
    {                                                                                              \
        bitsery::Serializer<bitsery::OutputBufferedStreamAdapter> ser{ os };                       \
                                                                                                   \
        ser.object(*this);                                               \
                                                                                                   \
        ser.adapter().flush();                                                                     \
    }
// return pybind11::bytes(&buffer[0],buffer.size());
#define __BITSERY_DEFAULT_FROM_STREAM__(T_CLASS)                                                   \
    /** @brief read object from input stream                                                       \
     *                                                                                             \
     * @param is reference to input stream                                                         \
     * @return T_CLASS object                                                                      \
     * */                                                                                          \
    static T_CLASS from_stream(std::istream& is)                                                   \
    {                                                                                              \
        T_CLASS object;                                                                            \
                                                                                                   \
        auto state = bitsery::quickDeserialization<bitsery::InputStreamAdapter>(is, object);       \
                                                                                                   \
        if (state.first != bitsery::ReaderError::NoError)                                          \
            throw(std::runtime_error("ERROR[T_CLASS::from_stream]: readerror"));                   \
                                                                                                   \
        return object;                                                                             \
    }

#define __BITSERY_DEFAULT_TOFROM_BINARY_FUNCTIONS__(T_CLASS)                                       \
    __BITSERY_DEFAULT_TO_BINARY__                                                                  \
    __BITSERY_DEFAULT_FROM_BINARY__(T_CLASS)                                                       \
    __BITSERY_DEFAULT_TO_STREAM__                                                                  \
    __BITSERY_DEFAULT_FROM_STREAM__(T_CLASS)
