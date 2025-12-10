// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
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

#include <array>
#include <cmath>
#include <concepts>
#include <omp.h>
#include <stdexcept>
#include <vector>
#include <xtensor/containers/xtensor.hpp>

#include "../classhelper/objectprinter.hpp"
#include "../classhelper/option.hpp"
#include "../helper/downsampling.hpp"
#include "../helper/xtensor.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace vectorinterpolators {

/**
 * @brief extrapolation mode type.
 *
 */
enum class t_extr_mode : uint8_t
{
    extrapolate = 0, ///< interpolate using the closest value pair in the internal x vector
    fail    = 1, ///< throw out_of_range exception if x value exceeds boundaries of internal vector
    nearest = 2, ///< return nearest value in the vector.
    nan     = 3  ///< return NaN if x value exceeds boundaries of internal vector (only for floating
                 ///< point types)
};

using o_extr_mode = classhelper::Option<t_extr_mode>;

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
  public:
    using t_XType = XType;
    using t_YType = YType;

  protected:
    o_extr_mode _extr_mode; ///< extrapolation mode

  public:
    /**
     * @brief Construct a new Interpolator object from two vectors
     * usage: interpolated_y_value = interpolator.interpolate(x_value)
     *
     * @param extrapolation_mode extrapolation mode (nearest or fail)
     */
    I_Interpolator(o_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
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

    /**
     * @brief Get downsampled x values from the interpolator data.
     *
     * This function returns x values at regular intervals, respecting gaps in the data.
     * Useful for reducing the number of interpolation points when dealing with large datasets.
     *
     * @param downsample_interval The interval between consecutive sampled x values
     * @param max_gap Maximum allowed gap between consecutive x values. If the gap between
     *                consecutive x values exceeds this, a new sampling segment is started.
     * @return xt::xtensor<XType, 1> A 1D tensor containing the downsampled x values
     *
     * @note The returned values are actual x values from the data, not interpolated positions.
     *       Use these values with the interpolator to get corresponding y values.
     */
    xt::xtensor<XType, 1> get_sampled_X(
        double downsample_interval,
        double max_gap = std::numeric_limits<double>::quiet_NaN()) const
    {
        return helper::get_value_downsampling(get_data_X(), downsample_interval, max_gap);
    }

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
    void set_extrapolation_mode(const o_extr_mode extrapolation_mode)
    {
        _extr_mode = extrapolation_mode;
    }

    /**
     * @brief Get the currently set extrapolation mode
     *
     * @return :o_extr_mode
     */
    o_extr_mode get_extrapolation_mode() const { return _extr_mode; }

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
     * @brief get interpolated y values for given x targets (vectorized call)
     *
     * @param targets_x vector of x values. For each of these values find the corresponding y value
     * @param mp_cores Number of OpenMP threads to use for parallelization. Default is 1 (no
     *                 parallelism). Set to higher values to enable parallel interpolation.
     * @return std::vector<YType> corresponding y values
     */
    std::vector<YType> operator()(const std::vector<XType>& targetsX, int mp_cores = 1) const
    {
        std::vector<YType> y_values(targetsX.size());
        const auto         n = static_cast<long>(targetsX.size());

#pragma omp parallel for num_threads(mp_cores)
        for (long i = 0; i < n; ++i)
        {
            y_values[i] = operator()(targetsX[i]);
        }

        return y_values;
    }

    /**
     * @brief get interpolated y values for given x targets (xtensor vectorized call)
     *
     * This overload accepts xtensor containers and returns an xtensor result.
     * The return type matches the value type of the interpolator (YType).
     *
     * @tparam XTensor An xtensor-compatible 1D container type
     * @param targets_x xtensor of x values. For each of these values find the corresponding y value
     * @param mp_cores Number of OpenMP threads to use for parallelization. Default is 1 (no
     *                 parallelism). Set to higher values to enable parallel interpolation.
     * @return xt::xtensor<YType, 1> corresponding y values as a 1D xtensor
     *
     * @note This function requires YType to be a scalar type (not a compound type like Quaternion).
     *       For SlerpInterpolator, use the vector overload or the ypr() method instead.
     */
    template<tools::helper::c_xtensor_1d t_xtensor_1d>
    xt::xtensor<YType, 1> operator()(const t_xtensor_1d& targetsX, int mp_cores = 1) const
    {
        const auto            n        = static_cast<long>(targetsX.size());
        xt::xtensor<YType, 1> y_values = xt::empty<YType>({ static_cast<size_t>(n) });

#pragma omp parallel for num_threads(mp_cores)
        for (long i = 0; i < n; ++i)
        {
            y_values(i) = operator()(static_cast<XType>(targetsX(i)));
        }

        return y_values;
    }

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
     * @brief append an x- and the corresponding y value to the interpolator data.
     * Exception: raises domain error, strong exception guarantee
     *
     * @param x value, must be > than all existing x values
     * @param y corresponding y value
     */
    virtual void append(XType x, YType y) = 0;

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
                        const std::vector<YType>& Y,
                        bool                      is_sorted = false) = 0;

    /**
     * @brief return a printer object
     *
     * @param float_precision number of digits for floating point numbers
     * @return classhelper::ObjectPrinter
     */
    virtual classhelper::ObjectPrinter __printer__(unsigned int float_precision,
                                                   bool         superscript_exponents) const = 0;

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

// Explicit template instantiation declaration
extern template class themachinethatgoesping::tools::classhelper::Option<
    themachinethatgoesping::tools::vectorinterpolators::t_extr_mode>;