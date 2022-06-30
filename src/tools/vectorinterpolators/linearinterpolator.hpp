// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
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

#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>

// bitsery
#include "../bitsery_helpers/classhelpers.hpp"
#include "../bitsery_helpers/helpers.hpp"

#include "i_pairinterpolator.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace vectorinterpolators {

/**
 * @brief Find linear interpolated values within vector data
 *
 */
class LinearInterpolator : public I_PairInterpolator<double>
{
  public:
    LinearInterpolator()
        : I_PairInterpolator<double>({ 0, 1 }, { 0, 1 })
    {
    }

    LinearInterpolator(const std::vector<double>& X,
                       const std::vector<double>& Y,
                       t_extr_mode                extrapolation_mode = t_extr_mode::extrapolate)
        : I_PairInterpolator<double>(X, Y, extrapolation_mode)
    {
    }

    static std::string type_to_string() { return "LinearInterpolator"; }

    bool operator!=(const LinearInterpolator& rhs) const { return !(rhs == *this); }
    bool operator==(const LinearInterpolator& rhs) const
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
     * @brief Interpolate: Interpolate interpolation between two values
     * @param target_x: the target point [0.0 - 1.0]
     * @param y1     : first y value (target_x = 0)
     * @param y2     : second value (target_x = 01)
     * inbetween)
     * @return Interpolated value for target position
     */
    double interpolate_pair(double target_x, double y1, double y2) const final
    {
        return (double)(target_x * (y2) + (double(1.0) - target_x) * (y1));
    }

    // define to_binary and from_binary functions
    __BITSERY_DEFAULT_TOFROM_BINARY_FUNCTIONS__(LinearInterpolator)

  private:
    // serialization support using bitsery
    friend bitsery::Access;
    template<typename S>
    void serialize(S& s)
    {
        s.value4b(_extr_mode);
        s.object(_last_x_pair);
        s.container8b(_X, SERIALIZER_DEFAULT_MAX_CONTAINER_SIZE);
        s.container8b(_Y, SERIALIZER_DEFAULT_MAX_CONTAINER_SIZE);
    }
};

} // namespace interpolation
} // namespace tools
} // namespace themachinethatgoesping
