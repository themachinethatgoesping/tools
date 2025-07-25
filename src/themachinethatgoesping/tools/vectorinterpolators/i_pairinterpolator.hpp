// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean
// Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief Interface class for vector pair interpolators.
 * Pair interpolator means that the actual interpolation only uses two values
 * This interface class implements functions to search for the correct interpolation pair within the
 * vector.
 *
 * @authors Peter Urban
 *
 */

#pragma once

/* generated doc strings */
#include ".docstrings/i_pairinterpolator.doc.hpp"

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "../classhelper/stream.hpp"
#include "i_interpolator.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace vectorinterpolators {

/**
 * @brief Interface class for interpolator classes
 * This template class implements base functions interpolators that interpolate between two values
 * (pairs). This interface implements the search for the x position within this vector (closest 2
 * x/y value pair) and computes an x interpolation value (target_x) Then it call the __call__
 * functions of the implementation classes that use this interface to interpolate between these
 * pairs.
 *
 * @tparam XType: type of the x values (must be floating point)
 * @tparam YType: type of the y values (typically double or float, but will be a vector
 * for the slerp interpolator class)
 */
template<std::floating_point XType, typename YType>
class I_PairInterpolator : public I_Interpolator<XType, YType>
{
  protected:
    struct _t_x_pair
    {
        size_t _xmin_index; ///< index of the smaller x value (in the internal vector)
        size_t _xmax_index; ///< index of the larger x value (in the internal vector)
        XType  _xmin;       ///< smaller xvalue
        XType  _xmax;       ///< larger xvalue
        XType  _xfactor;    ///< 1/(xmax-xmin)

        _t_x_pair(size_t xmin_index, size_t xmax_index, XType xmin, XType xmax)
            : _xmin_index(xmin_index)
            , _xmax_index(xmax_index)
            , _xmin(xmin)
            , _xmax(xmax)
            , _xfactor(1 / (_xmax - _xmin))
        {
        }

        /**
         * @brief compute the interpolation factor between xmin and xmax
         *
         * @param target_x x value for which we want to know the interpolation factor
         * @return interpolation factor
         */
        XType calc_target_x(XType target_x) { return (target_x - _xmin) * _xfactor; }

    }; ///< last pair (for faster consecutive searches)

    /**
     * @brief extrapolation mode type.
     *
     */
    std::vector<XType> _X; ///< main data vector containing pairs of corresponding x datapoints
    std::vector<YType> _Y; ///< main data vector containing pairs of corresponding y datapoints

  public:
    /**
     * @brief Construct a new Interpolator object from a vector of pairs
     * usage: interpolated_y_value = interpolator.interpolate(x_value)
     *
     * @param X X vector; must be unique and sorted in ascending order. same size as Y!
     * @param Y Y vector; must be unique and sorted in ascending order. same size as X!
     * @param extrapolation_mode :py:class:`t_extr_mode
     * <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>` object that describes the
     * extrapolation mode
     */
    I_PairInterpolator(std::vector<XType> X,
                       std::vector<YType> Y,
                       t_extr_mode        extrapolation_mode = t_extr_mode::extrapolate)
        : I_Interpolator<XType, YType>(extrapolation_mode)
    {
        set_data_XY(std::move(X), std::move(Y));
    }

    I_PairInterpolator(t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
        : I_Interpolator<XType, YType>(extrapolation_mode)
    {
    }

    virtual ~I_PairInterpolator() = default;

    /**
     * @brief check if the interpolator contains data
     */
    bool empty() const { return _X.empty(); }

    /**
     * @brief change the input data to these X and Y vectors
     * Exception: raises domain error, strong exception guarantee
     *
     * @param X: x vector (must be same size, must be sorted in ascending order)
     * @param Y: y vector (must be same size)
     */
    void set_data_XY(std::vector<XType> X, std::vector<YType> Y) final
    {
        if (X.size() != Y.size())
            throw(std::domain_error("ERROR[Interpolation::set_data_XY]: list sizes do not match"));

        I_Interpolator<XType, YType>::_check_XY(X, Y);

        _X = std::move(X);
        _Y = std::move(Y);
    }

    // -----------------------
    // append/extend functions
    // -----------------------
    void append(XType x, YType y) final
    {
        if (!_X.empty())
            if (x <= _X.back())
            {
                throw(std::domain_error("ERROR[Interpolation::append]: appended x value is not "
                                        "larger than existing x values in the interpolator."));
            }

        if (!std::isfinite(x))
            throw(std::domain_error(
                "ERROR[Interpolator::append]: X contains NAN or INFINITE values!"));
        if constexpr (std::is_floating_point<YType>())
            if (!std::isfinite(y))
                throw(std::domain_error(
                    "ERROR[Interpolator::append]: Y contains NAN or INFINITE values!"));

        // if the internal data is one element, call set data to initialize
        if (_X.size() == 1)
        {
            set_data_XY(std::vector<XType>{ _X[0], x }, std::vector<YType>{ _Y[0], y });
            return;
        }

        _X.push_back(x);
        _Y.push_back(y);
    }

    void extend(const std::vector<XType>& X, const std::vector<YType>& Y) final
    {
        if (X.size() != Y.size())
            throw(std::domain_error("ERROR[Interpolator::extend]: list sizes do not match"));

        // if no internal data yet, just set the data
        if (_X.size() == 0)
        {
            set_data_XY(X, Y);
            return;
        }

        size_t orig_size = _X.size();

        try
        {
            for (size_t i = 0; i < X.size(); ++i)
            {
                append(X[i], Y[i]);
            }
        }
        catch (...)
        {
            // restore original size if something went wrong
            _X.resize(orig_size);
            _Y.resize(orig_size);
            throw;
        }
    }

    void insert(const std::vector<XType>& X,
                const std::vector<YType>& Y,
                bool                      is_sorted = false) final
    {
        if (X.empty())
            return;

        if (_X.empty())
        {
            return set_data_XY(X, Y);
        }

        // if data is sorted and the first element is larger than the last element of the internal
        // the existing data can be extended, which is faster than inserting
        if (is_sorted)
        {
            if (X.front() > _X.back())
            {
                return extend(X, Y);
            }
        }

        if (X.size() != Y.size())
            throw(std::domain_error("ERROR[Interpolator::insert]: list sizes do not match"));

        std::vector<std::pair<XType, YType>> XY;
        XY.reserve(_X.size() + X.size());

        // sort _X and _Y by _X (ascending)
        for (size_t i = 0; i < _X.size(); ++i)
        {
            XY.push_back(std::pair<XType, YType>(_X[i], _Y[i]));
        }
        for (size_t i = 0; i < X.size(); ++i)
        {
            XY.push_back(std::pair<XType, YType>(X[i], Y[i]));
        }

        std::sort(
            XY.begin(), XY.end(), [](const auto& a, const auto& b) { return a.first < b.first; });

        // copy back to _X and _Y
        std::vector<XType> X_new;
        std::vector<YType> Y_new;
        X_new.resize(XY.size());
        Y_new.resize(XY.size());
        for (size_t i = 0; i < XY.size(); ++i)
        {
            X_new[i] = XY[i].first;
            Y_new[i] = XY[i].second;
        }

        set_data_XY(std::move(X_new), std::move(Y_new));
    }

    // -----------------------
    // getter functions
    // -----------------------
    /**
     * @brief return the x component of the internal data vector
     *
     * @return std::vector<XType>
     */
    const std::vector<XType>& get_data_X() const final { return _X; }

    /**
     * @brief return the y component of the internal data vector
     *
     * @return std::vector<YType>
     */
    const std::vector<YType>& get_data_Y() const final { return _Y; }

    //-------------------------
    // interpolation functions
    //-------------------------

    YType get_y(XType target_x) const
    {
        // check if _X (and _Y) are initialized (_X and _Y should always be the same size)
        if (_X.size() == 0)
            throw(std::domain_error(
                "ERROR[PairInterpolator::operator()]: data vectors are not initialized!"));

        // if size of _X is 1, return _Y[0]
        if (_X.size() == 1)
            return _Y[0];

        auto it = lower_bound(_X.begin(), _X.end(), target_x);

        // interpolation pair
        std::unique_ptr<_t_x_pair> pair;

        if (it == _X.begin())
        {
            switch (I_Interpolator<XType, YType>::_extr_mode)
            {
                case t_extr_mode::fail: {
                    // throw std::out_of_range("ERROR[INTERPOLATE]: x value out of range (too
                    // small), "
                    //                         "while fail on extrapolate was set!");
                    std::string msg;
                    msg += "ERROR[INTERPOLATE]: x value [" + std::to_string(target_x) +
                           "] is out of range (too small)(" + std::to_string(_X.front()) +
                           ")! (and fail on extrapolate was set)";
                    throw(std::out_of_range(msg));
                }
                case t_extr_mode::nearest:
                    return _Y[0];
                default:
                    pair = std::make_unique<_t_x_pair>(0, 1, _X[0], _X[1]);
                    break;
            }
        }
        else if (it == _X.end())
        {
            size_t last = _X.size() - 1;

            switch (I_Interpolator<XType, YType>::_extr_mode)
            {
                case t_extr_mode::fail: {
                    // throw std::out_of_range("ERROR[INTERPOLATE]: x value out of range (too
                    // large), "
                    //                         "while fail on extrapolate was set!");
                    std::string msg;
                    msg += "ERROR[INTERPOLATE]: x value [" + std::to_string(target_x) +
                           "] is out of range  (too large)(" + std::to_string(_X.front()) +
                           ")! (and fail on extrapolate was set)";
                    throw(std::out_of_range(msg));
                }

                case t_extr_mode::nearest:
                    return _Y[last];

                default:
                    pair = std::make_unique<_t_x_pair>(last - 1, last, _X[last - 1], _X[last]);
                    break;
            }
        }
        else
        {
            auto i = it - _X.begin();
            pair   = std::make_unique<_t_x_pair>(i - 1, i, _X[i - 1], _X[i]);
        }

        return interpolate_pair(
            pair->calc_target_x(target_x), _Y[pair->_xmin_index], _Y[pair->_xmax_index]);
    }

    /**
     * @brief get the interpolated y value for given x target
     *
     * @param target_x find the corresponding y value for this x value
     * @return corresponding y value
     */
    YType operator()(XType target_x) const final { return get_y(target_x); }

    /**
     * @brief get nearest y values for given x targets (vectorized call)
     *
     * @param targets_x vector of x values. For each of these values find the corrsponding y value
     * @return corresponding y value
     */
    std::vector<YType> operator()(const std::vector<XType>& targetsX) const
    {
        return I_Interpolator<XType, YType>::operator()(targetsX);
    }

    //--------------------------------
    // virtual (interface) functions
    //--------------------------------

    std::string class_name() const override { return "I_PairInterpolator"; }

    /**
     * @brief Interface for implementing an interpolation between two y values
     * using a given interpolation factor
     *
     * @param target_x interpolation factor. 0 means return smaller y value, 1
     * means return larger y value
     * @param y1 smaller y value
     * @param y1 larger y value
     * @return interpolated y value
     */
    virtual YType interpolate_pair(XType target_x, YType y1, YType y2) const = 0;
};

} // namespace interpolation
} // namespace tools
} // namespace themachinethatgoesping
