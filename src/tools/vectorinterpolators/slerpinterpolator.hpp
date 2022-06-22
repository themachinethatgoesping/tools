// SPDX-FileCopyrightText: 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

// this header only works if libeigen was found
//#ifdef USE_LIBEIGEN

#include <Eigen/Eigen>
#include <Eigen/Geometry>
#include <array>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "../rotationfunctions/quaternions.hpp"
#include "i_pairinterpolator.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace vectorinterpolators {

using t_quaternion = Eigen::Quaternion<double>;

class SlerpInterpolator : public I_PairInterpolator<t_quaternion>
{

  public:
    SlerpInterpolator()
        : I_PairInterpolator<t_quaternion>(
              {{ 0, rotationfunctions::quaternion_from_ypr<double>(0, -180, -89.99) }   ,
              { 1, rotationfunctions::quaternion_from_ypr<double>(360, 180, 89.99) }})
    {
    }

    SlerpInterpolator(const std::vector<std::pair<double, t_quaternion>>& XY,
                       t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
        : I_PairInterpolator<t_quaternion>(XY, extrapolation_mode)
    {
    }
    SlerpInterpolator(const std::vector<double>&       X,
                       const std::vector<t_quaternion>& Y,
                       t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
        : I_PairInterpolator<t_quaternion>(X, Y, extrapolation_mode)
    {
    }


    /**
     * @brief Interpolate: Slerp interpolation between two values
     * @param target_x: the target point [0.0 - 1.0]
     * @param y1     : first quaternion (target_x = 0)
     * @param y2     : second quaternion (target_x = 01)
     * inbetween)
     * @return Interpolated value for target position
     */
    t_quaternion interpolate_pair(double target_x, const t_quaternion& y1, const t_quaternion& y2) const final
    {
        return y1.slerp(target_x, y2);
    }
    
};

} // namespace vectorinterpolators
} // namespace tools
} // namespace themachinethatgoesping

//#endif
