// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief A class to compute python style indexing
 *
 * @authors Peter Urban
 */

#include "../classhelper/objectprinter.hpp"
#include "../classhelper/stream.hpp"

#pragma once

namespace themachinethatgoesping {
namespace tools {
namespace pyhelper {

/**
 * @brief A class to compute python style indexing
 * Allow for negative indexing (starting from the end of the container)
 * Allow for sliced indexing (start, stop, step)
 *
 */
class PyIndexer
{
    size_t _vector_size; ///< the size of the vector to be indexed

    bool   _is_slice    = false;                            ///< is this a slice?
    size_t _index_start = 0;                                ///< the start index of the slice
    size_t _index_end   = std::numeric_limits<long>::max(); ///< the end index of the slice
    long   _index_step  = 1;                                ///< the step size of the slice

    // make this private (only allowed in factory functions)
    PyIndexer() = default;

  public:
    /**
     * @brief Construct a new Py Indexer object   *
     * Allow for negative indexing (starting from the end of the container)
     *
     * @param vector_size Size of the vector to be indexed
     */
    PyIndexer(size_t vector_size)
        : _vector_size(vector_size)
    {
    }

    /**
     * @brief Construct a new Py Indexer object
     * Allow for negative indexing (starting from the end of the container)
     * Allow for sliced indexing (start, stop, step)
     *
     * @param vector_size Size of the vector to be indexed
     * @param start Start index of the slice
     * @param end End index of the slice
     * @param step Step size of the slice
     */
    PyIndexer(size_t vector_size, long start, long end, long step = 1)
        : _vector_size(vector_size)
    {
        set_slice_indexing(start, end, step);
    }

    /**
     * @brief Setup slice indexing after construction
     *
     * @param start Start index of the slice
     * @param end End index of the slice
     * @param step Step size of the slice
     */
    void set_slice_indexing(long start, long end, long step = 1)
    {
        if (step == 0)
            throw(std::out_of_range("PyIndexer: step is zero!"));

        if (end == std::numeric_limits<long>::max())
            end = _vector_size;

        bool ivn_max = false;
        bool ivn_min = false;
        if (end < 0)
        {
            end     = long(_vector_size) + end;
            ivn_max = true;
        }

        if (start < 0)
        {
            start   = long(_vector_size) + start;
            ivn_min = true;
        }

        if (start > end)
        {
            std::swap(start, end);
            step *= -1;
            ivn_max = ivn_min;
        }

        end = end - 1 * (!ivn_max);

        if (start < 0 || start >= long(_vector_size))
            throw(std::out_of_range("PyIndexer: start is out of bounds!"));
        if (end < 0 || end >= long(_vector_size))
            throw(std::out_of_range("PyIndexer: end is out of bounds!"));
        if (start >= end)
            throw(std::out_of_range("PyIndexer: _start >= _end!"));

        _is_slice    = true;
        _index_start = start;
        _index_end   = end;
        _index_step  = step;
    }

    /**
     * @brief Reset the indexer (deactivates slicing)
     *
     */
    void reset(size_t vector_size)
    {
        _vector_size = vector_size;

        if (_is_slice)
        {
            _is_slice    = false;
            _index_start = 0;
            _index_end   = std::numeric_limits<long>::max();
            _index_step  = 1;
        }
    }

    // ----- operators (index) -----
    /**
     * @brief Get the index of the element at position i
     *
     * @param index (python style) index of the element (can be negative)
     * @return size_t
     */
    size_t operator()(long index) const
    {
        if (_is_slice)
        {
            if (_index_step < 0)
                index += 1;

            // convert index to C++ index using _index_step, _index_start, _index_end
            index *= _index_step;

            if (index < 0)
                index += long(_index_end) + std::abs(_index_step); //_index_end == _vector_size-1
            else
                index += long(_index_start);

            // TODO: fix error messages
            if (size_t(index) > _index_end)
                throw std::out_of_range(
                    fmt::format("Index [{}] is > max [{}]! ", index - _index_start, _index_end));
        }
        else
        {
            // convert from python index (can be negative) to C++ index
            if (index < 0)
                index += long(_vector_size);
            // index = python_index < 0 ? _vector_size + python_index : python_index;

            if (size_t(index) >= _vector_size)
                throw std::out_of_range(
                    fmt::format("Index [{}] is >= max [{}]! ", index, _vector_size));
        }

        if (index < long(_index_start))
            throw std::out_of_range(fmt::format("Index [{}] is < min [{}]! ", index, _index_start));

        return size_t(index);
    }

    // ----- common functions -----
    size_t size() const
    {
        if (_is_slice)
            return size_t((_index_end - _index_start) / std::abs(_index_step)) +
                   1; // TODO this needs to be checked
        return _vector_size;
    }

    // ----- operators (common) -----
    bool operator!=(const PyIndexer& rhs) const { return !(rhs == *this); }
    bool operator==(const PyIndexer& rhs) const
    {
        // compare data
        if (_vector_size != rhs._vector_size)
            return false;
        if (_is_slice != rhs._is_slice)
            return false;
        if (_index_start != rhs._index_start)
            return false;
        if (_index_end != rhs._index_end)
            return false;
        if (_index_step != rhs._index_step)
            return false;

        return true;
    }

    // ----- operators (iteration) -----
    /**
     * @brief Simple iterator class to allow for range-based for loops
     * 
     */
    struct PyRangeIterator
    {
        size_t _val;

        PyRangeIterator(size_t val)
            : _val(val)
        {
        }

        bool operator==(const PyRangeIterator& rhs)
        {
            if (_val != rhs._val)
                return false;
            return true;
        }
        bool operator!=(const PyRangeIterator& rhs) { return !(*this == rhs); }

        size_t& operator*() { return _val; }
        void    operator++() { ++_val; }
    };

    /**
     * @brief Get the begin iterator (for range-based for loops)
     * 
     * @return PyRangeIterator 
     */
    PyRangeIterator begin() const { 
        if (_is_slice)
            return PyRangeIterator(_index_start);
        return PyRangeIterator(0);
    }

    /**
     * @brief Get the end iterator (for range-based for loops)
     * 
     * @return PyRangeIterator 
     */
    PyRangeIterator end() const { return PyRangeIterator( this->size()); }

    // ----- from/to binary -----
    /**
     * @brief Return a PyIndexer read from a binary stream
     *
     * @param is input stream
     * @return PyIndexer
     */
    static PyIndexer from_stream(std::istream& is)
    {
        PyIndexer indexer;
        is.read(reinterpret_cast<char*>(&indexer._vector_size), sizeof(PyIndexer));

        return indexer;
    }

    /**
     * @brief Write a PyIndexer to a binary stream
     *
     * @param os output stream
     */
    void to_stream(std::ostream& os)
    {
        os.write(reinterpret_cast<char*>(&_vector_size), sizeof(PyIndexer));
    }

    // ----- printing -----
    /**
     * @brief Print function, needs __CLASShelper_DEFAULT_PRINTING_FUNCTIONS__ macro
     * See also: classhelper/objectprinter.hpp
     *
     * @param float_precision Precision of floating point numbers
     * @return classhelper::ObjectPrinter
     */
    classhelper::ObjectPrinter __printer__(unsigned int float_precision) const
    {
        classhelper::ObjectPrinter printer("PyIndexer", float_precision);

        printer.register_value("_vector_size", _vector_size);

        if (!_is_slice)
            printer.register_value("_is_slice", _is_slice);
        else
        {
            printer.register_section("Slice");
            printer.register_value("_index_start", _index_start);
            printer.register_value("_index_end", _index_end);
            printer.register_value("_index_step", _index_step);
        }

        return printer;
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs to_stream and from_stream)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(PyIndexer)
    // define info_string and print functions (needs the __printer__ function)
    __CLASShelper_DEFAULT_PRINTING_FUNCTIONS__
};

}
}
}