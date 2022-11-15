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

    size_t _slice_size = _vector_size; ///< the size of the slice (_vector_size if not sliced)
    size_t _index_min  = 0;            ///< the minimum index of the slice (0 if not sliced)
    size_t _index_max =
        _vector_size - 1; ///< the maximum index of the slice (_vector_size - 1 if not sliced)

    long _index_start = 0; ///< the start index of the slice (0 if not sliced)
    long _index_end =
        _vector_size;         ///< the end index of the slice (_vector_size if not sliced)
                              ///< (end is exclusive) (long because can be negative under some
                              ///< circumstances (see below) this index is used for out of bounds
    long _index_step = 1;     ///< the step size of the slice (1 if not sliced)
    bool _is_slice   = false; ///< is this a slice?

    // make this private (only allowed in factory functions)
    PyIndexer() = default;

  public:
    const static long None = std::numeric_limits<long>::max(); ///< a static value to indicate None

    /**
     * @brief A structure to hold a slice
     *
     */
    struct Slice
    {

        long start = PyIndexer::None; ///< the start index of the slice (None if not sliced)
        long end   = PyIndexer::None; ///< the end index of the slice (None if not sliced)
                                      ///< (end is exclusive)
        long step = 1;                ///< the step size of the slice (1 if not sliced)

        Slice() = default;

        Slice(long start, long end, long step = 1)
            : start(start)
            , end(end)
            , step(step)
        {
        }
    };

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
     * @brief Construct a new Py Indexer object
     * Allow for negative indexing (starting from the end of the container)
     * Allow for sliced indexing (start, stop, step)
     *
     * @param vector_size Size of the vector to be indexed
     * @param slice PyIndexer::Slice structure (contains, start, end, step)
     */
    PyIndexer(size_t vector_size, const PyIndexer::Slice& slice)
        : _vector_size(vector_size)
    {
        set_slice_indexing(slice);
    }

    /**
     * @brief Setup slice indexing after construction
     *
     * @param slice PyIndexer::Slice structure (contains, start, end, step)
     */
    void set_slice_indexing(const PyIndexer::Slice& slice)
    {
        set_slice_indexing(slice.start, slice.end, slice.step);
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
        else if (step == PyIndexer::None)
            step = 1;

        if (end < 0)
            end += _vector_size;
        else if (end == PyIndexer::None)
        {
            if (step > 0)
                end = _vector_size;
            else
                end = -1;
        }

        if (start < 0)
            start += _vector_size;
        else if (start == PyIndexer::None)
        {
            if (step > 0)
                start = 0;
            else
                start = _vector_size - 1;
        }

        if (start < end && step > 0)
        {
            _is_slice    = true;
            _index_start = start;
            _index_step  = step;
            _slice_size  = size_t(std::ceil(float(end - start) / float(_index_step)));
            _index_end   = _index_start + _slice_size * _index_step;

            if (_index_start >= long(_vector_size))
                throw(std::out_of_range(fmt::format(
                    "PyIndexer({}, {}, {}): index_start is out of bounds!\n--- indexer ---\n{}",
                    start,
                    end,
                    step,
                    info_string())));
        }
        else if (start > end && step < 0)
        {
            _is_slice    = true;
            _index_start = start;
            _index_step  = step;
            _slice_size  = size_t(std::ceil(float(end - start) / float(_index_step)));

            // _index end can be negative (if start is negative and end is positive, e.g. (start =
            // 5, end = 0, step = -2)) this is not a problem, because the index is only used to
            // check if it is out of bounds
            _index_end = _index_start + _slice_size * _index_step;

            if (_index_start >= long(_vector_size))
                throw(std::out_of_range(fmt::format(
                    "PyIndexer({}, {}, {}): Start is out of bounds!\n--- indexer ---\n{}",
                    start,
                    end,
                    step,
                    info_string())));
        }
        else
        {
            _is_slice    = true;
            _index_start = start;
            _index_end   = end;
            _index_step  = step;
            _slice_size  = 0;

            throw(std::out_of_range(
                fmt::format("PyIndexer({}, {}, {}): Slice with zero size!\n--- indexer ---\n{}",
                            start,
                            end,
                            step,
                            info_string())));
        }

        _index_min = std::min(_index_start, _index_end - _index_step);
        _index_max = std::max(_index_start, _index_end - _index_step);
        if (_index_min >= _vector_size)
            throw(std::out_of_range(fmt::format(
                "PyIndexer({}, {}, {}): _index_min is out of bounds!\n--- indexer ---\n{}",
                start,
                end,
                step,
                info_string())));
        if (_index_max >= _vector_size)
            throw(std::out_of_range(fmt::format(
                "PyIndexer({}, {}, {}): _index_max is out of bounds!\n--- indexer ---\n{}",
                start,
                end,
                step,
                info_string())));
    }

    /**
     * @brief Reset the indexer (deactivates slicing)
     *
     * @param vector_size Size of the vector to be indexed
     */
    void reset(size_t vector_size)
    {
        _vector_size = vector_size;
        _index_end   = vector_size;
        _slice_size  = vector_size;
        _index_min   = 0;
        _index_max   = vector_size - 1;

        if (_is_slice)
        {
            _is_slice    = false;
            _index_start = 0;
            _index_step  = 1;
        }
    }

    /**
     * @brief Reset the indexer (set up new slicing)
     *
     * @param vector_size Size of the vector to be indexed
     * @param start Start index of the slice
     * @param end End index of the slice
     * @param step Step size of the slice
     */
    void reset(size_t vector_size, long start, long end, long step = 1)
    {
        _vector_size = vector_size;
        set_slice_indexing(start, end, step);
    }

    /**
     * @brief Reset the indexer (set up new slicing)
     *
     * @param vector_size Size of the vector to be indexed
     * @param slice PyIndexer::Slice structure (contains, start, end, step)
     */
    void reset(size_t vector_size, PyIndexer::Slice slice)
    {
        _vector_size = vector_size;
        set_slice_indexing(slice);
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
            if (index < 0)
            {
                index += 1;

                if (_index_step < 0)
                {
                    index = long(_index_min) + (index)*_index_step;
                }
                else
                {
                    index = long(_index_max) + (index)*_index_step;
                }
            }
            else
            {
                if (_index_step < 0)
                {
                    index = long(_index_max) + (index)*_index_step;
                }
                else
                {
                    index = long(_index_min) + index * _index_step;
                }
            }

            // TODO: fix error messages
            if (index > long(_index_max))
                throw std::out_of_range(fmt::format("index[{} + ({} * {}) = {}] is >= max ({})! ",
                                                    _index_start,
                                                    (index - _index_start) / _index_step,
                                                    _index_step,
                                                    index,
                                                    _index_max));
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

        if (index < long(_index_min))
            throw std::out_of_range(fmt::format("Index [{}] is < min [{}]! ", index, _index_min));

        return size_t(index);
    }

    // ----- common functions -----
    size_t size() const { return _slice_size; }

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
        if (_index_min != rhs._index_min)
            return false;
        if (_index_max != rhs._index_max)
            return false;
        if (_index_step != rhs._index_step)
            return false;
        if (_slice_size != rhs._slice_size)
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
        long   _step;

        PyRangeIterator(size_t val, long step)
            : _val(val)
            , _step(step)
        {
        }

        /**
         * @brief operator != for range-based for loops
         * Only compare _val, since _step is not relevant for the it != end comparison
         *
         * @param rhs
         * @return true
         * @return false
         */
        bool operator!=(const PyRangeIterator& rhs) { return _val != rhs._val; }

        size_t& operator*() { return _val; }
        void    operator++() { _val += _step; }
    };

    /**
     * @brief Get the begin iterator (for range-based for loops)
     *
     * @return PyRangeIterator
     */
    PyRangeIterator begin() const { return PyRangeIterator(_index_start, _index_step); }

    /**
     * @brief Get the end iterator (for range-based for loops)
     *
     * @return PyRangeIterator
     */
    PyRangeIterator end() const { return PyRangeIterator(_index_end, _index_step); }

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
            printer.register_value("_slice_size", _slice_size);
            printer.register_value("_index_min", _index_min);
            printer.register_value("_index_max", _index_max);
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