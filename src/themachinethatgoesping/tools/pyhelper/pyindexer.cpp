// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "pyindexer.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace pyhelper {

// PyIndexer::Slice implementations
PyIndexer::Slice::Slice(int64_t start, int64_t stop, int64_t step)
    : start(start), stop(stop), step(step)
{
}

classhelper::ObjectPrinter PyIndexer::Slice::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    std::string start_ = start == PyIndexer::None ? "" : std::to_string(start);
    std::string stop_  = stop == PyIndexer::None ? "" : std::to_string(stop);
    std::string step_  = step == PyIndexer::None ? "" : std::to_string(step);

    classhelper::ObjectPrinter printer(
        fmt::format("PyIndexer::Slice({}:{}:{})", start_, stop_, step_), float_precision, superscript_exponents);

    return printer;
}

PyIndexer::Slice PyIndexer::Slice::from_stream(std::istream& is)
{
    PyIndexer::Slice slice;
    is.read(reinterpret_cast<char*>(&slice.start), sizeof(PyIndexer::Slice));
    return slice;
}

void PyIndexer::Slice::to_stream(std::ostream& os) const
{
    os.write(reinterpret_cast<const char*>(&start), sizeof(PyIndexer::Slice));
}

// PyIndexer implementations
PyIndexer::Slice PyIndexer::to_slice() const
{
    if (_index_stop < 0)
        return Slice(_index_start, PyIndexer::None, _index_step);

    return Slice(_index_start, _index_stop, _index_step);
}

PyIndexer::PyIndexer(size_t vector_size)
    : _vector_size(vector_size)
    , _slice_size(vector_size)
    , _index_max(int64_t(vector_size - 1))
    , _index_stop(int64_t(vector_size))
{
}

PyIndexer::PyIndexer(size_t vector_size, int64_t start, int64_t stop, int64_t step)
    : _vector_size(vector_size), _slice_size(vector_size)
{
    set_slice_indexing(start, stop, step);
}

PyIndexer::PyIndexer(size_t vector_size, const PyIndexer::Slice& slice)
    : _vector_size(vector_size), _slice_size(vector_size)
{
    set_slice_indexing(slice);
}

PyIndexer PyIndexer::reversed() const
{
    int64_t new_start = _index_stop - _index_step;
    int64_t new_stop  = _index_start - _index_step;

    if (new_stop < 0)
        new_stop = PyIndexer::None;

    return PyIndexer(_vector_size, new_start, new_stop, -_index_step);
}

void PyIndexer::set_slice_indexing(const PyIndexer::Slice& slice)
{
    set_slice_indexing(slice.start, slice.stop, slice.step);
}

void PyIndexer::set_slice_indexing(int64_t start, int64_t stop, int64_t step)
{
    if (step == 0)
        throw(std::out_of_range("PyIndexer: step is zero!"));
    else if (step == PyIndexer::None)
        step = 1;

    if (stop < 0)
        stop += int64_t(_vector_size);
    else if (stop == PyIndexer::None)
    {
        if (step > 0)
            stop = int64_t(_vector_size);
        else
            stop = -1;
    }

    if (start < 0)
        start += int64_t(_vector_size);
    else if (start == PyIndexer::None)
    {
        if (step > 0)
            start = 0;
        else
            start = int64_t(_vector_size - 1);
    }

    if (start < stop && step > 0)
    {
        _is_slice    = true;
        _index_start = start;
        _index_step  = step;
        _slice_size  = size_t(std::ceil(float(stop - start) / float(_index_step)));
        _index_stop  = _index_start + int64_t(_slice_size) * _index_step;

        if (_index_start >= int64_t(_vector_size))
        {
            throw(std::out_of_range(fmt::format(
                "PyIndexer({}, {}, {}): index_start is out of bounds!\n--- indexer ---\n{}",
                start,
                stop,
                step,
                info_string())));
        }
    }
    else if (start > stop && step < 0)
    {
        _is_slice    = true;
        _index_start = start;
        _index_step  = step;
        _slice_size  = size_t(std::ceil(float(stop - start) / float(_index_step)));

        _index_stop = _index_start + int64_t(_slice_size) * _index_step;

        if (_index_start >= int64_t(_vector_size))
            throw(std::out_of_range(fmt::format(
                "PyIndexer({}, {}, {}): Start is out of bounds!\n--- indexer ---\n{}",
                start,
                stop,
                step,
                info_string())));
    }
    else
    {
        _is_slice    = true;
        _index_start = start;
        _index_stop  = stop;
        _index_step  = step;
        _slice_size  = 0;

        throw(std::out_of_range(
            fmt::format("PyIndexer({}, {}, {}): Slice with zero size!\n--- indexer ---\n{}",
                        start,
                        stop,
                        step,
                        info_string())));
    }

    _index_min = std::min(_index_start, _index_stop - _index_step);
    _index_max = std::max(_index_start, _index_stop - _index_step);
    if (_index_min >= _vector_size)
    {
        throw(std::out_of_range(fmt::format(
            "PyIndexer({}, {}, {}): _index_min is out of bounds!\n--- indexer ---\n{}",
            start,
            stop,
            step,
            info_string())));
    }
    if (_index_max >= _vector_size)
    {
        throw(std::out_of_range(fmt::format(
            "PyIndexer({}, {}, {}): _index_max is out of bounds!\n--- indexer ---\n{}",
            start,
            stop,
            step,
            info_string())));
    }
}

void PyIndexer::reset(size_t vector_size)
{
    _vector_size = vector_size;
    _index_stop  = int64_t(vector_size);
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

void PyIndexer::reset(size_t vector_size, int64_t start, int64_t stop, int64_t step)
{
    _vector_size = vector_size;
    set_slice_indexing(start, stop, step);
}

void PyIndexer::reset(size_t vector_size, PyIndexer::Slice slice)
{
    _vector_size = vector_size;
    set_slice_indexing(slice);
}

size_t PyIndexer::operator()(int64_t index) const
{
    if (_is_slice)
    {
        if (index < 0)
        {
            index += 1;

            if (_index_step < 0)
            {
                index = int64_t(_index_min) + (index)*_index_step;
            }
            else
            {
                index = int64_t(_index_max) + (index)*_index_step;
            }
        }
        else
        {
            if (_index_step < 0)
            {
                index = int64_t(_index_max) + (index)*_index_step;
            }
            else
            {
                index = int64_t(_index_min) + index * _index_step;
            }
        }

        if (index > int64_t(_index_max))
        {
            throw std::out_of_range(fmt::format("index[{} + ({} * {}) = {}] is >= max ({})! ",
                                                _index_start,
                                                (index - _index_start) / _index_step,
                                                _index_step,
                                                index,
                                                _index_max));
        }
    }
    else
    {
        if (index < 0)
            index += int64_t(_vector_size);

        if (size_t(index) >= _vector_size)
        {
            throw std::out_of_range(
                fmt::format("Index [{}] is >= max [{}]! ", index, _vector_size));
        }
    }

    if (index < int64_t(_index_min))
    {
        throw std::out_of_range(fmt::format("Index [{}] is < min [{}]! ", index, _index_min));
    }

    return size_t(index);
}

size_t PyIndexer::size() const 
{ 
    return _slice_size; 
}

PyIndexer::PyRangeIterator::PyRangeIterator(size_t val, int64_t step)
    : _val(val), _step(step)
{
}

bool PyIndexer::PyRangeIterator::operator!=(const PyRangeIterator& rhs) 
{ 
    return _val != rhs._val; 
}

size_t& PyIndexer::PyRangeIterator::operator*() 
{ 
    return _val; 
}

void PyIndexer::PyRangeIterator::operator++() 
{ 
    _val += _step; 
}

PyIndexer::PyRangeIterator PyIndexer::begin() const 
{ 
    return PyRangeIterator(_index_start, _index_step); 
}

PyIndexer::PyRangeIterator PyIndexer::end() const 
{ 
    return PyRangeIterator(_index_stop, _index_step); 
}

PyIndexer PyIndexer::from_stream(std::istream& is)
{
    PyIndexer indexer;
    is.read(reinterpret_cast<char*>(&indexer._vector_size), sizeof(PyIndexer));
    return indexer;
}

void PyIndexer::to_stream(std::ostream& os) const
{
    os.write(reinterpret_cast<const char*>(&_vector_size), sizeof(PyIndexer));
}

classhelper::ObjectPrinter PyIndexer::__printer__(unsigned int float_precision, bool superscript_exponents) const
{
    classhelper::ObjectPrinter printer("PyIndexer", float_precision, superscript_exponents);

    printer.register_value("_vector_size", _vector_size);

    if (!_is_slice)
        printer.register_value("_is_slice", _is_slice);
    else
    {
        printer.register_section(this->to_slice().info_string());
        printer.register_value("_index_start", _index_start);
        printer.register_value("_index_stop", _index_stop);
        printer.register_value("_index_step", _index_step);
        printer.register_value("_slice_size", _slice_size);
        printer.register_value("_index_min", _index_min);
        printer.register_value("_index_max", _index_max);
    }

    return printer;
}

}
}
}