// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean
// Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief (Modified) akima interpolator class. Uses boost makima interpolator
 *
 * @authors Peter Urban
 *
 */

#pragma once

#include <array>
#include <boost/math/interpolators/makima.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "i_interpolator.hpp"
#include "linearinterpolator.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace vectorinterpolators {

/**
 * @brief Interpolator class to perform a (modified) akima interpolation. Uses
 * boost makima interpolator.
 *
 */
class AkimaInterpolator : public I_Interpolator<double>
{
    // boost akima spline currently does not allow for accessing the internal data
    // therefore we need to keep synchrpnized copies of the data here as well to allow get_X and
    // get_Y functions
    std::vector<double> _X;
    std::vector<double> _Y;

    // initialize these interpolators with non-sense (will be initialized by calling set_data_XY)
    LinearInterpolator _min_linearextrapolator = LinearInterpolator({ 0, 1 }, { 0, 1 });
    LinearInterpolator _max_linearextrapolator = LinearInterpolator({ 0, 1 }, { 0, 1 });
    boost::math::interpolators::makima<std::vector<double>> _akima_spline =
        boost::math::interpolators::makima<std::vector<double>>({ 0, 1, 2, 3 }, { 0, 1, 2, 3 });

  public:
    // AkimaInterpolator()
    //     : I_Interpolator<double>()
    // {
    //     set_data_XY({ 0, 1 }, { 0, 1 });
    // }

    /**
     * @brief Construct a new Akima Spline Interpolator object from a vector of
     * pairs This class uses the modified akima interpolation of boost c++
     * https://www.boost.org/doc/libs/1_79_0/libs/math/doc/html/math_toolkit/makima.html
     * usage: interpolated_y_value = interpolator(x_value)
     *
     * @param X X vector; must be unique and sorted in ascending order. same
     * size as Y!
     * @param Y Y vector; must be unique and sorted in ascending order. same
     * size as X!
     * @param extrapolation_mode :py:class:`t_extr_mode
     * <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>` object
     * that describes the extrapolation mode
     */
    AkimaInterpolator(const std::vector<double>& X,
                      const std::vector<double>& Y,
                      t_extr_mode                extrapolation_mode = t_extr_mode::extrapolate)
        : I_Interpolator<double>(extrapolation_mode)
    {
        set_data_XY(X, Y);
    }
    ~AkimaInterpolator() = default;
    
    // -- convinience functions --
    bool operator==(const AkimaInterpolator& rhs) const
    {
        // compare extrapolation mode
        if (_extr_mode != rhs.get_extrapolation_mode())
            return false;

        // compare data
        if (!std::equal(_X.begin(), _X.end(), rhs.get_data_X().begin()))
            return false;
        if (!std::equal(_Y.begin(), _Y.end(), rhs.get_data_Y().begin()))
            return false;

        if (!std::equal(_Y.begin(), _Y.end(), rhs.get_data_Y().begin()))
            return false;

        return true;
    }
    
    /**
     * @brief get the interolated y value for given x target
     *
     * @param target_x find the corresponding y value for this x value
     * @return corresponding y value
     */
    double operator()(double target_x) final
    {
        if (target_x < _X[0])
        {
            switch (I_Interpolator::_extr_mode)
            {
                case t_extr_mode::nearest:
                    return _Y[0];

                case t_extr_mode::extrapolate:
                    return _min_linearextrapolator(target_x);

                default: // fail
                    std::string msg;
                    msg += "ERROR[INTERPOLATE]: x value [" + std::to_string(target_x) +
                           "] is out of range (too small)(" + std::to_string(_X[0]) + "/" +
                           std::to_string(_X.back()) + ")! (and fail on extrapolate was set)";
                    throw(std::out_of_range(msg));
            }
        }
        else if (target_x > _X.back())
        {
            switch (I_Interpolator::_extr_mode)
            {
                case t_extr_mode::nearest:
                    return _Y.back();

                case t_extr_mode::extrapolate:
                    return _max_linearextrapolator(target_x);

                default: // fail
                    std::string msg;
                    msg += "ERROR[INTERPOLATE]: x value [" + std::to_string(target_x) +
                           "] is out of range  (too large)(" + std::to_string(_X[0]) + "/" +
                           std::to_string(_X.back()) + ")! (and fail on extrapolate was set)";
                    throw(std::out_of_range(msg));
            }
        }

        return _akima_spline(target_x);
    }

    /**
     * @brief get nearest y values for given x targets (vectorized call)
     *
     * @param targets_x vector of x values. For each of these values find the
     * corrspondig y value
     * @return corresponding y value
     */
    std::vector<double> operator()(const std::vector<double>& targetsX)
    {
        return I_Interpolator<double>::operator()(targetsX);
    }

    /**
     * @brief change the input data to these X and Y vectors
     *
     * @param X: x vector (must be same size)
     * @param Y: y vector (must be same size)
     */
    void set_data_XY(const std::vector<double>& X, const std::vector<double>& Y) final
    {
        // check if vectors are same size
        if (X.size() != Y.size())
            throw(std::runtime_error("ERROR[Interpolation::set_data_XY]: list sizes do not match"));

        // copy data to allow get_X and get_Y functions
        _X = X;
        _Y = Y;

        // This should be easier: Move semantics of makima seem to be more in the way here than they
        // help ...
        auto x = X;
        auto y = Y;
        _akima_spline =
            boost::math::interpolators::makima<std::vector<double>>(std::move(x), std::move(y));

        _init_linearextrapolators();
    }

    void append(double x, double y) final
    {
        _akima_spline.push_back(x, y);

        // copy data to allow get_X and get_Y functions
        _X.push_back(x);
        _Y.push_back(y);

        _init_linearextrapolators();
    }

    void extend(const std::vector<double>& X, const std::vector<double>& Y) final
    {
        if (X.size() != Y.size())
            throw(std::invalid_argument("ERROR[Interpolator::extend]: list sizes do not match"));

        for (unsigned int i = 0; i < X.size(); ++i)
        {
            _akima_spline.push_back(X[i], Y[i]);

            // copy data to allow get_X and get_Y functions
            _X.push_back(X[i]);
            _Y.push_back(Y[i]);
        }

        _init_linearextrapolators();
    }

    // -----------------------
    // getter functions
    // -----------------------
    /**
     * @brief return the x component of the internal data vector
     *
     * @return std::vector<double>
     */
    const std::vector<double>& get_data_X() const final { return _X; }

    /**
     * @brief return the y component of the itnernal data vector
     *
     * @return std::vector<YType>
     */
    const std::vector<double>& get_data_Y() const final { return _Y; }

  private:
    /**
     * @brief internal function to initialize the linear extrapolation objects
     * _X, _Y and the _akima_spline
     * must be set/initialized before calling this function
     *
     */
    void _init_linearextrapolators()
    {
        // interpolated elements just (1%) before the min/max xvalue
        double min_x_dx = _X[0] + (_X[1] - _X[0]) * 0.01;
        double max_x_dx = _X.back() - (_X.back() - _X[_X.size() - 2]) * 0.01;

        _min_linearextrapolator =
            LinearInterpolator({ _X[0], min_x_dx }, { _Y[0], _akima_spline(min_x_dx) });
        _max_linearextrapolator =
            LinearInterpolator({ max_x_dx, _X.back() }, { _akima_spline(max_x_dx), _Y.back() });
    }
};

} // namespace vectorinterpolators
} // namespace tools
} // namespace themachinethatgoesping
