// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief A fast output stream that writes directly into a caller-owned std::string.
 *
 * std::stringstream has significant overhead due to locale facets, virtual dispatch,
 * and an extra copy on .str(). This class writes directly into a std::string provided
 * by the caller, so the result can be returned via NRVO with zero copies or moves.
 *
 * @authors Peter Urban
 */

#pragma once

/* generated doc strings */
#include ".docstrings/osstream.doc.hpp"

#include <cstring>
#include <ostream>
#include <streambuf>
#include <string>

namespace themachinethatgoesping::tools::helper {

/**
 * std::streambuf implementation that writes into a caller-owned std::string.
 * Supports seekp/tellp for serialization code that uses two-pass write patterns
 * (e.g. writing placeholder values, then seeking back to fill them in).
 */
class string_output_buf : public std::streambuf
{
  public:
    explicit string_output_buf(std::string& buffer, std::size_t initial_capacity = 256)
        : _buffer(buffer)
        , _pos(0)
    {
        _buffer.clear();
        if (_buffer.capacity() < initial_capacity)
            _buffer.reserve(initial_capacity);
    }

    /// Get the current size of the buffer.
    std::size_t size() const { return _buffer.size(); }

  protected:
    std::streamsize xsputn(const char* s, std::streamsize n) override
    {
        const auto count = static_cast<std::size_t>(n);
        const auto end   = _pos + count;

        if (end > _buffer.size())
            _buffer.resize(end);

        std::memcpy(_buffer.data() + _pos, s, count);
        _pos = end;
        return n;
    }

    int_type overflow(int_type ch) override
    {
        if (ch != traits_type::eof())
        {
            const auto c = static_cast<char>(ch);
            if (_pos >= _buffer.size())
                _buffer.push_back(c);
            else
                _buffer[_pos] = c;
            ++_pos;
        }
        return ch;
    }

    pos_type seekoff(off_type                off,
                     std::ios_base::seekdir  dir,
                     std::ios_base::openmode /*which*/ = std::ios_base::out) override
    {
        std::size_t new_pos;
        if (dir == std::ios_base::beg)
            new_pos = static_cast<std::size_t>(off);
        else if (dir == std::ios_base::cur)
            new_pos = _pos + static_cast<std::size_t>(off);
        else // end
            new_pos = _buffer.size() + static_cast<std::size_t>(off);

        _pos = new_pos;
        return static_cast<pos_type>(_pos);
    }

    pos_type seekpos(pos_type                sp,
                     std::ios_base::openmode which = std::ios_base::out) override
    {
        return seekoff(static_cast<off_type>(sp), std::ios_base::beg, which);
    }

  private:
    std::string&  _buffer;
    std::size_t   _pos;
};

/**
 * A fast std::ostream that writes directly into a caller-owned std::string.
 * Drop-in replacement for std::ostringstream in serialization code.
 *
 * Usage:
 *   std::string result;
 *   osstream os(result);
 *   obj.to_stream(os);
 *   return result;  // NRVO, zero copies
 */
class osstream
    : private string_output_buf
    , public std::ostream
{
  public:
    explicit osstream(std::string& buffer, std::size_t initial_capacity = 256)
        : string_output_buf(buffer, initial_capacity)
        , std::ostream(static_cast<std::streambuf*>(this))
    {
    }

    /// Get the current size of the buffer.
    using string_output_buf::size;
};

} // namespace themachinethatgoesping::tools::helper
