// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean
// Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief Linear vector interpolator class.
 *
 * @authors Peter Urban
 *
 */

#pragma once

/* generated doc strings */
#include ".docstrings/linearinterpolator.doc.hpp"

#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "i_pairinterpolator.hpp"

#include "../classhelper/objectprinter.hpp"
#include "../classhelper/stream.hpp"
#include "../helper/approx.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace vectorinterpolators {

/**
 * @brief Find linear interpolated values within vector data
 *
 * @tparam XType: type of the x values (must be floating point)
 * @tparam YType: type of the y values (must be floating point)
 */
template<std::floating_point XType, typename YType>
class LinearInterpolator : public I_PairInterpolator<XType, YType>
{

  public:
    LinearInterpolator(t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
        : I_PairInterpolator<XType, YType>(extrapolation_mode)
    {
    }

    LinearInterpolator(const std::vector<XType>& X,
                       const std::vector<YType>& Y,
                       t_extr_mode               extrapolation_mode = t_extr_mode::extrapolate)
        : I_PairInterpolator<XType, YType>(X, Y, extrapolation_mode)
    {
    }

    virtual ~LinearInterpolator() = default;

    bool operator!=(const LinearInterpolator<XType, YType>& rhs) const { return !(rhs == *this); }
    bool operator==(const LinearInterpolator<XType, YType>& rhs) const
    {
        // compare extrapolation mode
        if (this->_extr_mode != rhs.get_extrapolation_mode())
            return false;

        // compare data
        if (!helper::approx_container(this->_X, rhs._X))
            return false;
        if (!helper::approx_container(this->_Y, rhs._Y))
            return false;

        return true;
    }

    /**
     * @brief Interpolate: Interpolate interpolation between two values
     * @param target_x: the target point [0.0 - 1.0]
     * @param y1     : first y value (target_x = 0)
     * @param y2     : second value (target_x = 01)
     * between)
     * @return Interpolated value for target position
     */
    YType interpolate_pair(XType target_x, YType y1, YType y2) const final
    {
        return (YType)(target_x * (y2) + (YType(1.0) - target_x) * (y1));
    }

    std::string class_name() const override { return "LinearInterpolator"; }

    // ----- to/from stream -----
    static LinearInterpolator<XType, YType> from_stream(std::istream& is)
    {
        using tools::classhelper::stream::container_from_stream;

        LinearInterpolator<XType, YType> obj;

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

        printer.register_enum("extr_mode", this->_extr_mode);
        printer.register_section("data lists");
        printer.register_container("X", this->_X);
        printer.register_container("Y", this->_Y);

        return printer;
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs to/from stream function)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(LinearInterpolator)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

} // namespace interpolation
} // namespace tools
} // namespace themachinethatgoesping
