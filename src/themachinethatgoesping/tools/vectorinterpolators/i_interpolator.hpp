// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean
// Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief Interface class for vector interpolators
 *
 * @authors Peter Urban
 *
 */

#pragma once

/* generated doc strings */
#include ".docstrings/i_interpolator.doc.hpp"

#include <algorithm>
#include <array>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include <concepts>
#include <stdexcept>

#include "../classhelper/objectprinter.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace vectorinterpolators {

/**
 * @brief extrapolation mode type.
 *
 */
enum class t_extr_mode: uint8_t
{
    extrapolate = 0, ///< interpolate using the closest value pair in the internal x vector
    fail    = 1, ///< throw out_of_range exception if x value exceeds boundaries of internal vector
    nearest = 2, ///< return nearest value in the vector.
};

static const std::array<t_extr_mode, 3> t_extr_mode_all = { t_extr_mode::extrapolate,
                                                            t_extr_mode::fail,
                                                            t_extr_mode::nearest };

/**
 * @brief Interface class for interpolator classes
 * Create an interpolator object by providing vectors for x and y (same size). X
 * must be sorted and no duplicates are allowed. then call interpolator(new
 * x value) to get a corresponding y value at this x position.
 *
 * @tparam XType: type of the x values (must be floating point)
 * @tparam YType: type of the y values (typically double or float, but will be a vector
 * for the slerp interpolator class)
 */
template<std::floating_point XType, typename YType>
class I_Interpolator
{
  protected:
    t_extr_mode      _extr_mode; ///< extrapolation mode

  public:
    /**
     * @brief Construct a new Interpolator object from two vectors
     * usage: interpolated_y_value = interpolator.interpolate(x_value)
     *
     * @param extrapolation_mode extrapolation mode (nearest or fail)
     */
    I_Interpolator(t_extr_mode      extrapolation_mode = t_extr_mode::extrapolate)
        : _extr_mode(extrapolation_mode)
    {
    }
    virtual ~I_Interpolator() = default;

    /**
     * @brief Get the interpolator name (for debugging)
     *
     * @return std::string_view
     */
    virtual std::string class_name() const { return "I_Interpolator"; }

    /**
     * @brief change the input data to these X and Y vectors
     *
     * @param X: x vector (must be same size, must be sorted in ascending order)
     * @param Y: y vector (must be same size)
     */
    virtual void set_data_XY(std::vector<XType> X, std::vector<YType> Y) = 0;

    // -----------------------
    // getter functions
    // -----------------------
    /**
     * @brief return the x component of the internal data vector
     *
     * @return std::vector<XType>
     */
    virtual const std::vector<XType>& get_data_X() const = 0;

    /**
     * @brief return the y component of the internal data vector
     *
     * @return std::vector<YType>
     */
    virtual const std::vector<YType>& get_data_Y() const = 0;

    // -----------------------
    // getter setter functions
    // -----------------------
    /**
     * @brief Set the extrapolation mode
     *
     * @param extrapolation_mode :py:class:`t_extr_mode
     * <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>` object (enumerator) that
     * describes the extrapolation mode
     */
    void set_extrapolation_mode(const t_extr_mode extrapolation_mode)
    {
        _extr_mode = extrapolation_mode;
    }

    /**
     * @brief Get the currently set extrapolation mode
     *
     * @return :py:class:`t_extr_mode
     * <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>` object (enumerator) that
     * describes the extrapolation mode
     */
    t_extr_mode get_extrapolation_mode() const { return _extr_mode; }

    //-------------------------
    // interpolation functions
    //-------------------------

    /**
     * @brief get the interpolated y value for given x target
     *
     * @param target_x find the corresponding y value for this x value
     * @return corresponding y value
     */
    virtual YType operator()(XType target_x) const = 0;

    /**
     * @brief get nearest y values for given x targets (vectorized call)
     *
     * @param targets_x vector of x values. For each of these values find the corrsponding y value
     * @return corresponding y value
     */
    std::vector<YType> operator()(const std::vector<XType>& targetsX) const
    {
        std::vector<YType> y_values;
        y_values.reserve(targetsX.size());
        for (const auto target_x : targetsX)
        {
            y_values.push_back(operator()(target_x));
        }

        return y_values;
    }

    /**
     * @brief append an x- and the corresponding y value to the interpolator data.
     * Exception: raises domain error, strong exception guarantee
     *
     * @param x value, must be > than all existing x values
     * @param y corresponding y value
     */
    virtual void append(XType x, YType y) = 0;

    /**
     * @brief append x and y value lists to the interpolator data (vectorized call)
     * Exception: raises domain error, strong exception guarantee
     *
     * @param X list of x values. Must be sorted in ascending order. All x values must be larger
     * than the largest x value in the interpolator data.
     * @param Y list of corresponding Y values. Must be same size as X
     */
    virtual void extend(const std::vector<XType>& X, const std::vector<YType>& Y) = 0;

    /**
     * @brief append x and y value lists to the interpolator data (vectorized call)
     * This call is much more expensive than extend as it requires copying data and sorting.
     * Exception: raises domain error, strong exception guarantee
     *
     * @param X list of x values. (Does not have to be sorted. But must be unique)
     * @param Y list of corresponding Y values. Must be same size as X
     * @param is_sorted this indicates that X is already sorted in ascending order. (default: false)
     */
    virtual void insert(const std::vector<XType>& X,
                        const std::vector<YType>&  Y,
                        bool                       is_sorted = false) = 0;

    /**
     * @brief return a printer object
     *
     * @param float_precision number of digits for floating point numbers
     * @return classhelper::ObjectPrinter
     */
    virtual classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const = 0;

    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__

  protected:
    /**
     * @brief check if input data is valid (e.g. sorted, no duplicated x values)
     *
     */
    static void _check_XY(const std::vector<XType>& X, const std::vector<YType>& Y)
    {
        // if (X.size() < 2)
        //     throw(std::domain_error("ERROR[Interpolation::_check_XY]: list size is < 2!"));
        if (X.size() != Y.size())
            throw(std::domain_error(
                "ERROR[Interpolation::_check_XY]: list X and Y list sizes do not match!"));

        for (size_t i = 0; i < X.size(); ++i)
        {
            if (i + 1 < X.size())
            {
                if (X[i] == X[i + 1])
                    throw(std::domain_error(
                        "ERROR[Interpolation::_check_XY]: X list contains XType x values!"));

                if (X[i] > X[i + 1])
                    throw(std::domain_error("ERROR[Interpolation::_check_XY]: X list is not "
                                            "sorted in ascending order!"));
            }

            if (!std::isfinite(X[i]))
                throw(std::domain_error(
                    "ERROR[Interpolation::_check_XY]: X List contains NAN or INFINITE values!"));

            if constexpr (std::is_floating_point<YType>())
                if (!std::isfinite(Y[i]))
                    throw(std::domain_error("ERROR[Interpolation::_check_XY]: Y List contains NAN "
                                            "or INFINITE values!"));
        }
    }
};

} // namespace interpolation
} // namespace tools
} // namespace themachinethatgoesping
