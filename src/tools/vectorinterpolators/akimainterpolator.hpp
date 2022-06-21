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
    double _min_x, _min_y, _max_x, _max_y; ///< min/max x and y values
    double _min_x_1, _max_x_1;             ///< one value above min and max x

    LinearInterpolator _min_linearextrapolator, _max_linearextrapolator;
    std::unique_ptr<boost::math::interpolators::makima<std::vector<double>>> _akima_spline;

  public:
    AkimaInterpolator()
        : I_Interpolator<double>()
    {
        set_data_XY({ 0, 1 }, { 0, 1 });
    }

    /**
     * @brief Construct a new Akima Spline Interpolator object from a vector of
     * pairs This class uses the modified akima interpolation of boost c++
     * https://www.boost.org/doc/libs/1_79_0/libs/math/doc/html/math_toolkit/makima.html
     * usage: interpolated_y_value = interpolator.interpolate(x_value)
     *
     * @param XY vector of x,y pairs. X must be unique and sorted in ascending
     * order
     * @param extrapolation_mode :py:class:`t_extr_mode
     * <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>` object
     * that describes the extrapolation mode
     */
    AkimaInterpolator(const std::vector<std::pair<double, double>>& XY,
                      t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
        : I_Interpolator<double>(extrapolation_mode)
    {
        set_data_XY(XY);
    }
    /**
     * @brief Construct a new Akima Spline Interpolator object from a vector of
     * pairs This class uses the modified akima interpolation of boost c++
     * https://www.boost.org/doc/libs/1_79_0/libs/math/doc/html/math_toolkit/makima.html
     * usage: interpolated_y_value = interpolator.interpolate(x_value)
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

    /**
     * @brief get the interolated y value for given x target
     *
     * @param target_x find the corresponding y value for this x value
     * @return corresponding y value
     */
    double interpolate(double target_x) final
    {
        if (target_x < _min_x)
        {
            switch (I_Interpolator::_extr_mode)
            {
                case t_extr_mode::nearest:
                    return _min_y;

                case t_extr_mode::extrapolate:
                    return _min_linearextrapolator.interpolate(target_x);

                default: // fail
                    std::string msg;
                    msg += "ERROR[INTERPOLATE]: x value [" + std::to_string(target_x) +
                           "] is out of range (too small)(" + std::to_string(_min_x) + "/" +
                           std::to_string(_max_x) + ")! (and fail on extrapolate was set)";
                    throw(std::out_of_range(msg));
            }
        }
        else if (target_x > _max_x)
        {
            switch (I_Interpolator::_extr_mode)
            {
                case t_extr_mode::nearest:
                    return _max_y;

                case t_extr_mode::extrapolate:
                    return _max_linearextrapolator.interpolate(target_x);

                default: // fail
                    std::string msg;
                    msg += "ERROR[INTERPOLATE]: x value [" + std::to_string(target_x) +
                           "] is out of range  (too large)(" + std::to_string(_min_x) + "/" +
                           std::to_string(_max_x) + ")! (and fail on extrapolate was set)";
                    throw(std::out_of_range(msg));
            }
        }

        return _akima_spline->operator()(target_x);
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

        auto x = X;
        auto y = Y;

        // save min/max xy for extrapolation
        _min_x   = x[0];
        _min_x_1 = x[1];
        _max_x   = x[x.size() - 1];
        _max_x_1 = x[x.size() - 2];
        _min_y   = y[0];
        _max_y   = y[y.size() - 1];

        _akima_spline = std::make_unique<boost::math::interpolators::makima<std::vector<double>>>(
            std::move(x), std::move(y));

        _init_linearextrapolators();
    }

    void append(double x, double y) final
    {
        _akima_spline->push_back(x, y);

        // _akime_spline push back only accepts x > max_x
        _max_x_1 = _max_x;
        _max_x   = x;
        _max_y   = y;

        _init_linearextrapolators();
    }

    void append(std::pair<double, double> xy) final
    {
        _akima_spline->push_back(std::get<0>(xy), std::get<1>(xy));

        // _akime_spline push back only accepts x > max_x
        _max_x_1 = _max_x;
        _max_x   = std::get<0>(xy);
        _max_y   = std::get<1>(xy);

        _init_linearextrapolators();
    }

    void extend(const std::vector<double>& X, const std::vector<double>& Y) final
    {
        if (X.size() != Y.size())
            throw(std::invalid_argument("ERROR[Interpolator::extend]: list sizes do not match"));

        for (unsigned int i = 0; i < X.size(); ++i)
        {
            _akima_spline->push_back(X[i], Y[i]);
        }

        // _akime_spline push back only accepts x > max_x
        _max_x_1 = _max_x;
        _max_x   = X.back();
        _max_y   = Y.back();

        _init_linearextrapolators();
    }

    void extend(const std::vector<std::pair<double, double>>& XY) final
    {
        for (const auto& xy : XY)
        {
            _akima_spline->push_back(std::get<0>(xy), std::get<1>(xy));
        }

        // initialize extrapolation
        // no error checking necessary because _akime_spline push back only
        // accepts x > max_x
        _max_x_1 = _max_x;
        _max_x   = std::get<0>(XY.back());
        _max_y   = std::get<1>(XY.back());

        _init_linearextrapolators();
    }

    /**
     * @brief change the input data to this vector of XY pairs
     *
     * @param XY: input data vector given as vector<pair<X,Y>>
     */
    void set_data_XY(const std::vector<std::pair<double, double>>& XY) final
    {
        std::vector<double> X, Y;
        X.reserve(XY.size());
        Y.reserve(XY.size());
        for (const auto& xy : XY)
        {
            X.push_back(xy.first);
            X.push_back(xy.second);
        }

        set_data_XY(X, Y);
    }

    /**
     * @brief get nearest y values for given x targets (vectorized call)
     *
     * @param targets_x vector of x values. For each of these values find the
     * corrspondig y value
     * @return corresponding y value
     */
    std::vector<double> interpolate(const std::vector<double>& targetsX)
    {
        return I_Interpolator<double>::interpolate(targetsX);
    }

  private:
    /**
     * @brief internal function to initialize the linear extrapolation objects
     * _min_x, _min_x1, _max_x, _max_x_1, _min_y, _max_y and the _akima_spline
     * must be set/initialized before calling this function
     *
     */
    void _init_linearextrapolators()
    {
        double min_x_dx = _min_x + (_min_x_1 - _min_x) * 0.01;
        double max_x_dx = _max_x - (_max_x - _max_x_1) * 0.01;

        std::vector<std::pair<double, double>> min_elements, max_elements;
        min_elements.push_back(std::make_pair(_min_x, _min_y));
        min_elements.push_back(std::make_pair(min_x_dx, _akima_spline->operator()(min_x_dx)));
        max_elements.push_back(std::make_pair(max_x_dx, _akima_spline->operator()(max_x_dx)));
        max_elements.push_back(std::make_pair(_max_x, _max_y));

        _min_linearextrapolator = LinearInterpolator(min_elements);
        _max_linearextrapolator = LinearInterpolator(max_elements);
    }
};

} // namespace vectorinterpolators
} // namespace tools
} // namespace themachinethatgoesping
