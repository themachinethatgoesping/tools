// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief A class to compute python style indexing
 *
 * @authors Peter Urban
 */

#include <fmt/format.h>

#include "../classhelper/objectprinter.hpp"
#include "../classhelper/stream.hpp"

#pragma once

/* generated doc strings */
#include ".docstrings/pyindexer.doc.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace pyhelper {

/**
 * @brief A class to compute python style indexing
 * Allow for negative indexing (starting from the stop of the container)
 * Allow for sliced indexing (start, stop, step)
 *
 */
class PyIndexer
{
    size_t _vector_size; ///< the size of the vector to be indexed

    size_t _slice_size; ///< the size of the slice (_vector_size if not sliced)
    size_t _index_min  = 0;            ///< the minimum index of the slice (0 if not sliced)
    size_t _index_max; ///< the maximum index of the slice (_vector_size - 1 if not sliced)

    int64_t _index_start = 0;    ///< the start index of the slice (0 if not sliced)
    int64_t _index_stop;         ///< the stop index of the slice (_vector_size if not sliced)
                              ///< (stop is exclusive) (int64_t because can be negative under some
                              ///< circumstances (see below) this index is used for out of bounds
    int64_t _index_step = 1;     ///< the step size of the slice (1 if not sliced)
    bool _is_slice   = false; ///< is this a slice?

    // make this private (only allowed in factory functions)
    PyIndexer() = default;

  public:
    const static int64_t None = std::numeric_limits<int64_t>::max(); ///< a static value to indicate None

    /**
     * @brief A structure to hold a slice
     *
     */
    struct Slice
    {
        int64_t start = PyIndexer::None; ///< the start index of the slice (None if not sliced)
        int64_t stop  = PyIndexer::None; ///< the stop index of the slice (None if not sliced)
                                      ///< (stop is exclusive)
        int64_t step = 1;                ///< the step size of the slice (1 if not sliced)

        Slice() = default;
        Slice(int64_t start, int64_t stop, int64_t step = 1);

        // operators
        bool operator==(const Slice& other) const = default;

        classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const;

        static PyIndexer::Slice from_stream(std::istream& is);
        void to_stream(std::ostream& os) const;

        // -- class helper function macros --
        // define to_binary and from_binary functions (needs to_stream and from_stream)
        __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(PyIndexer::Slice)
        // define info_string and print functions (needs the __printer__ function)
        __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
    };

    Slice to_slice() const;

    /**
     * @brief Construct a new Py Indexer object   *
     * Allow for negative indexing (starting from the stop of the container)
     *
     * @param vector_size Size of the vector to be indexed
     */
    PyIndexer(size_t vector_size);

    /**
     * @brief Construct a new Py Indexer object
     * Allow for negative indexing (starting from the stop of the container)
     * Allow for sliced indexing (start, stop, step)
     *
     * @param vector_size Size of the vector to be indexed
     * @param start Start index of the slice
     * @param stop Stop index of the slice
     * @param step Step size of the slice
     */
    PyIndexer(size_t vector_size, int64_t start, int64_t stop, int64_t step = 1);

    /**
     * @brief Construct a new Py Indexer object
     * Allow for negative indexing (starting from the stop of the container)
     * Allow for sliced indexing (start, stop, step)
     *
     * @param vector_size Size of the vector to be indexed
     * @param slice PyIndexer::Slice structure (contains, start, stop, step)
     */
    PyIndexer(size_t vector_size, const PyIndexer::Slice& slice);

    /**
     * @brief Get a reversed PyIndexer object
     *
     * @return PyIndexer
     */
    PyIndexer reversed() const;

    /**
     * @brief Setup slice indexing after construction
     *
     * @param slice PyIndexer::Slice structure (contains, start, stop, step)
     */
    void set_slice_indexing(const PyIndexer::Slice& slice);

    /**
     * @brief Setup slice indexing after construction
     *
     * @param start Start index of the slice
     * @param stop Stop index of the slice
     * @param step Step size of the slice
     */
    void set_slice_indexing(int64_t start, int64_t stop, int64_t step = 1);

    /**
     * @brief Reset the indexer (deactivates slicing)
     *
     * @param vector_size Size of the vector to be indexed
     */
    void reset(size_t vector_size);

    /**
     * @brief Reset the indexer (set up new slicing)
     *
     * @param vector_size Size of the vector to be indexed
     * @param start Start index of the slice
     * @param stop Stop index of the slice
     * @param step Step size of the slice
     */
    void reset(size_t vector_size, int64_t start, int64_t stop, int64_t step = 1);

    /**
     * @brief Reset the indexer (set up new slicing)
     *
     * @param vector_size Size of the vector to be indexed
     * @param slice PyIndexer::Slice structure (contains, start, stop, step)
     */
    void reset(size_t vector_size, PyIndexer::Slice slice);

    // ----- operators (index) -----
    /**
     * @brief Get the index of the element at position i
     *
     * @param index (python style) index of the element (can be negative)
     * @return size_t
     */
    size_t operator()(int64_t index) const;

    // ----- common functions -----
    size_t size() const;

    // ----- operators (common) -----
    bool operator==(const PyIndexer& rhs) const = default;

    // ----- operators (iteration) -----
    /**
     * @brief Simple iterator class to allow for range-based for loops
     *
     */
    struct PyRangeIterator
    {
        size_t _val;
        int64_t   _step;

        PyRangeIterator(size_t val, int64_t step);

        /**
         * @brief operator != for range-based for loops
         * Only compare _val, since _step is not relevant for the it != stop comparison
         *
         * @param rhs
         * @return true
         * @return false
         */
        bool operator!=(const PyRangeIterator& rhs);
        size_t& operator*();
        void operator++();
    };

    /**
     * @brief Get the begin iterator (for range-based for loops)
     *
     * @return PyRangeIterator
     */
    PyRangeIterator begin() const;

    /**
     * @brief Get the stop iterator (for range-based for loops)
     *
     * @return PyRangeIterator
     */
    PyRangeIterator end() const;

    // ----- from/to binary -----
    /**
     * @brief Return a PyIndexer read from a binary stream
     *
     * @param is input stream
     * @return PyIndexer
     */
    static PyIndexer from_stream(std::istream& is);

    /**
     * @brief Write a PyIndexer to a binary stream
     *
     * @param os output stream
     */
    void to_stream(std::ostream& os) const;

    // ----- printing -----
    /**
     * @brief Print function, needs __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__ macro
     * See also: classhelper/objectprinter.hpp
     *
     * @param float_precision Precision of floating point numbers
     * @return classhelper::ObjectPrinter
     */
    classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const;

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs to_stream and from_stream)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(PyIndexer)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

}
}
}