// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University GEOMAR Helmholtz Centre for Ocean
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
#include ".docstrings/bivectorinterpolator.doc.hpp"

#include <utility>
#include <vector>
#include <xtensor/containers/xcontainer.hpp>
#include <xtensor/containers/xtensor.hpp>

#include "i_interpolator.hpp"

#include "../classhelper/objectprinter.hpp"
#include "../classhelper/stream.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace vectorinterpolators {

template<typename t_interpolator>
class BiVectorInterpolator
{
  public:
    using CoordinateType = typename t_interpolator::t_XType;
    using ValueType      = typename t_interpolator::t_YType;

  protected:
    t_extr_mode                 _extr_mode; ///< extrapolation mod
    std::vector<t_interpolator> _col_interpolator_per_row;
    std::vector<CoordinateType> _row_coordinates; // same size as _col_interpolator_per_row

  public:
    BiVectorInterpolator(t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
        : _extr_mode(extrapolation_mode)
    {
    }
    virtual ~BiVectorInterpolator() = default;

    bool operator==(const BiVectorInterpolator& other) const = default;

    /**
     * @brief Get the interpolator name (for debugging)
     *
     * @return std::string_view
     */
    std::string class_name() const { return fmt::format("BiVectorInterpolator"); }

    bool empty() const { return _col_interpolator_per_row.empty(); }

    void append_row(CoordinateType                     row_coordinate,
                    const std::vector<CoordinateType>& column_coordinates,
                    const std::vector<ValueType>&      values)
    {
        _col_interpolator_per_row.push_back(t_interpolator(_extr_mode));
        _col_interpolator_per_row.back().set_data_XY(column_coordinates, values);
        _row_coordinates.push_back(row_coordinate);
    }

    // -----------------------
    // getter functions
    // -----------------------
    // /**
    //  * @brief return the x component of the internal data vector
    //  *
    //  * @return std::vector<CoordinateType>
    //  */
    // virtual const std::vector<CoordinateType>& get_data_X() const = 0;

    // /**
    //  * @brief return the y component of the internal data vector
    //  *
    //  * @return std::vector<ValueType>
    //  */
    // virtual const std::vector<ValueType>& get_data_Y() const = 0;

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

        for (auto& interpolator : _col_interpolator_per_row)
            interpolator.set_extrapolation_mode(extrapolation_mode);
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
    // ValueType operator()(CoordinateType row_coordinate, CoordinateType column_coordinate) const =
    // 0;

    /**
     * @brief get interpolated y values for given x targets (vectorized call)
     *
     * @param targets_x vector of x values. For each of these values find the corrsponding y value
     * @return corresponding y value
     */
    xt::xtensor<ValueType, 2> operator()(const std::vector<CoordinateType>& row_coordinates,
                                         const std::vector<CoordinateType>& column_coordinates,
                                         int                                mp_cores = 1) const
    {
        // output tensor with the requested row and row size
        auto interpolated_values = xt::xtensor<ValueType, 2>::from_shape(
            { row_coordinates.size(), column_coordinates.size() });

// interpolate each column for the requested column coordinates
#pragma omp parallel for num_threads(mp_cores)
        for (size_t c = 0; c < column_coordinates.size(); ++c)
        {
            // interpolate values for each internal row
            std::vector<ValueType> value_per_row(_row_coordinates.size());

            for (size_t r = 0; r < _row_coordinates.size(); ++r)
                value_per_row[r] = _col_interpolator_per_row[r](column_coordinates[c]);

            t_interpolator interpolator(_extr_mode);
            interpolator.set_data_XY(_row_coordinates, std::move(value_per_row));

            // interpolate the values for each requested row coordinate
            for (size_t r = 0; r < row_coordinates.size(); ++r)
                interpolated_values.unchecked(r, c) = interpolator(row_coordinates[r]);
        }

        return interpolated_values;
    }

    // /**
    //  * @brief append an x- and the corresponding y value to the interpolator data.
    //  * Exception: raises domain error, strong exception guarantee
    //  *
    //  * @param x value, must be > than all existing x values
    //  * @param y corresponding y value
    //  */
    // virtual void append(CoordinateType x, ValueType y) = 0;

    // /**
    //  * @brief append x and y value lists to the interpolator data (vectorized call)
    //  * Exception: raises domain error, strong exception guarantee
    //  *
    //  * @param X list of x values. Must be sorted in ascending order. All x values must be larger
    //  * than the largest x value in the interpolator data.
    //  * @param Y list of corresponding Y values. Must be same size as X
    //  */
    // virtual void extend(const std::vector<CoordinateType>& X, const std::vector<ValueType>& Y) =
    // 0;

    // /**
    //  * @brief append x and y value lists to the interpolator data (vectorized call)
    //  * This call is much more expensive than extend as it requires copying data and sorting.
    //  * Exception: raises domain error, strong exception guarantee
    //  *
    //  * @param X list of x values. (Does not have to be sorted. But must be unique)
    //  * @param Y list of corresponding Y values. Must be same size as X
    //  * @param is_sorted this indicates that X is already sorted in ascending order. (default:
    //  false)
    //  */
    // virtual void insert(const std::vector<CoordinateType>& X,
    //                     const std::vector<ValueType>&      Y,
    //                     bool                               is_sorted = false) = 0;

    static BiVectorInterpolator from_stream(std::istream& is)
    {
        using tools::classhelper::stream::container_from_stream;

        t_extr_mode extr_mode;

        is.read(reinterpret_cast<char*>(&(extr_mode)), sizeof(extr_mode));

        auto interpolator = BiVectorInterpolator(extr_mode);

        interpolator._row_coordinates = container_from_stream<std::vector<CoordinateType>>(is);
        interpolator._col_interpolator_per_row.reserve(interpolator._row_coordinates.size());
        for (size_t i = 0; i < interpolator._row_coordinates.size(); ++i)
            interpolator._col_interpolator_per_row.push_back(t_interpolator::from_stream(is));

        return interpolator;
    }

    void to_stream(std::ostream& os) const
    {
        using tools::classhelper::stream::container_to_stream;

        os.write(reinterpret_cast<const char*>(&(this->_extr_mode)), sizeof(this->_extr_mode));
        container_to_stream(os, this->_row_coordinates);
        for (const auto& row : _col_interpolator_per_row)
            row.to_stream(os);
    }
    /**
     * @brief return a printer object
     *
     * @param float_precision number of digits for floating point numbers
     * @return classhelper::ObjectPrinter
     */
    classhelper::ObjectPrinter __printer__(unsigned int float_precision,
                                           bool         superscript_exponents) const
    {
        return classhelper::ObjectPrinter(class_name(), float_precision, superscript_exponents);
    }

    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
    // define to_binary and from_binary functions (based on to/from stream)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(BiVectorInterpolator)
};

} // namespace interpolation
} // namespace tools
} // namespace themachinethatgoesping
