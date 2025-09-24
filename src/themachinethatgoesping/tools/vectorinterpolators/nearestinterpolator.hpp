// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean
// Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief Nearest neighbor vector interpolator class.
 *
 * @authors Peter Urban
 *
 */

#pragma once

/* generated doc strings */
#include ".docstrings/nearestinterpolator.doc.hpp"

#include <vector>

#include <fmt/core.h>

#include "i_pairinterpolator.hpp"

#include "../classhelper/objectprinter.hpp"
#include "../classhelper/stream.hpp"
#include "../helper/approx.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace vectorinterpolators {

/**
 * @brief Interpolator class to find nearest neighbors within vector data
 *
 * @tparam XType: type of the x values (must be floating point)
 * @tparam YType: type of the y values (must be floating point)
 */
template<std::floating_point XType, typename YType>
class NearestInterpolator : public I_PairInterpolator<XType, YType>
{

  public:
    NearestInterpolator(o_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
        : I_PairInterpolator<XType, YType>(extrapolation_mode)
    {
    }

    /**
     * @brief Construct a new Nearest Interpolator object from a vector of pairs
     * usage: interpolated_y_value = interpolator.interpolate(x_value)
     *
     * @param X X vector; must be unique and sorted in ascending order. same size as Y!
     * @param Y Y vector; must be unique and sorted in ascending order. same size as X!
     * @param extrapolation_mode extrapolation mode (nearest or fail)
     */
    NearestInterpolator(const std::vector<XType>& X,
                        const std::vector<YType>& Y,
                        o_extr_mode               extrapolation_mode = t_extr_mode::extrapolate)
        : I_PairInterpolator<XType, YType>(X, Y, extrapolation_mode)
    {
    }
    ~NearestInterpolator() = default;

    std::string class_name() const override { return "NearestInterpolator"; }

    bool operator!=(const NearestInterpolator<XType, YType>& rhs) const { return !(rhs == *this); }
    bool operator==(const NearestInterpolator<XType, YType>& rhs) const
    {
        // compare extrapolation mode
        if (this->_extr_mode != rhs.get_extrapolation_mode())
            return false;

        // compare data
        if (!helper::approx_container(this->_X, rhs._X))
            return false;

        if constexpr (std::is_floating_point_v<YType>)
        {
            if (!helper::approx_container(this->_Y, rhs._Y))
                return false;
        }
        else
        {
            // Handle nb::object comparison using nanobind's .equal() method
            if constexpr (requires(YType a, YType b) { a.equal(b); })
            {
                if (this->_Y.size() != rhs._Y.size())
                    return false;
                for (size_t i = 0; i < this->_Y.size(); ++i)
                {
                    if (!this->_Y[i].equal(rhs._Y[i]))
                        return false;
                }
            }
            else
            {
                if (this->_Y != rhs._Y)
                    return false;
            }
        }

        return true;
    }

    /**
     * @brief Interpolate interpolation between two values
     * @param target_x: the target point [0.0 - 1.0]
     * @param y1     : first y value (target_x = 0)
     * @param y2     : second value (target_x = 01)
     * between)
     * @return Interpolated value for target position
     */
    YType interpolate_pair(XType target_x, YType y1, YType y2) const final
    {
        if (target_x < 0.5)
            return y1;

        return y2;
    }

    static NearestInterpolator<XType, YType> from_stream(std::istream& is)
    {
        using tools::classhelper::stream::container_from_stream;

        NearestInterpolator<XType, YType> obj;

        is.read(reinterpret_cast<char*>(&(obj._extr_mode)), sizeof(obj._extr_mode));

        obj._X = container_from_stream<std::vector<XType>>(is);
        obj._Y = container_from_stream<std::vector<YType>>(is);

        return obj;
    }

    void to_stream(std::ostream& os) const
    {
        using tools::classhelper::stream::container_to_stream;

        os.write(reinterpret_cast<const char*>(&(this->_extr_mode)), sizeof(this->_extr_mode));

        container_to_stream(os, this->_X);
        container_to_stream(os, this->_Y);
    }

  public:
    classhelper::ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const override
    {
        classhelper::ObjectPrinter printer(this->class_name(), float_precision, superscript_exponents);

        printer.register_enum("extr_mode", this->_extr_mode.value);
        printer.register_section("data lists");
        printer.register_container("X", this->_X);

        if constexpr (fmt::is_formattable<YType>::value)
            printer.register_container("Y", this->_Y);
        else
            printer.register_value("Y elements", this->_Y.size(), "not printable");

        return printer;
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs to/from stream function)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(NearestInterpolator)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

extern template class NearestInterpolator<float, float>;
extern template class NearestInterpolator<double, double>;
extern template class NearestInterpolator<float, double>;
extern template class NearestInterpolator<double, float>;

extern template class NearestInterpolator<float, uint8_t>;
extern template class NearestInterpolator<float, int8_t>;
extern template class NearestInterpolator<double, uint8_t>;
extern template class NearestInterpolator<double, int8_t>;
extern template class NearestInterpolator<float, uint16_t>;
extern template class NearestInterpolator<float, int16_t>;
extern template class NearestInterpolator<double, uint16_t>;
extern template class NearestInterpolator<double, int16_t>;
extern template class NearestInterpolator<float, uint32_t>;
extern template class NearestInterpolator<float, int32_t>;
extern template class NearestInterpolator<double, uint32_t>;
extern template class NearestInterpolator<double, int32_t>;
extern template class NearestInterpolator<float, uint64_t>;
extern template class NearestInterpolator<float, int64_t>;
extern template class NearestInterpolator<double, uint64_t>;
extern template class NearestInterpolator<double, int64_t>;
} // namespace interpolation
} // namespace tools
} // namespace themachinethatgoesping
