// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/slerpinterpolator.doc.hpp"

#include <Eigen/Eigen>
#include <Eigen/Geometry>
#include <array>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "../rotationfunctions/quaternions.hpp"
#include "i_pairinterpolator.hpp"

#include "../classhelper/objectprinter.hpp"
#include "../classhelper/stream.hpp"
#include "../helper.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace vectorinterpolators {

/**
 * @brief Class that implements a slerp interpolation for vectors.
 * Data is internally represented in quaternions using lib eigen.
 * Interfaces to represent the data in yaw, pitch, roll angles are provided.
 * the __call__ equivalent to get interpolated yaw pitch roll is the ypr function
 *
 * @tparam XType: type of the x values (must be floating point)
 * @tparam YType: floating point type of the y quaternion values (must be floating point)
 */
template<std::floating_point XType, std::floating_point YType>
class SlerpInterpolator : public I_PairInterpolator<XType, Eigen::Quaternion<YType>>
{
    using t_quaternion = Eigen::Quaternion<YType>;

  public:
    // explicitly ignore hidden overloaded virtual warning (clang)
    using I_PairInterpolator<XType, t_quaternion>::append;
    using I_PairInterpolator<XType, t_quaternion>::extend;
    using I_PairInterpolator<XType, t_quaternion>::insert;

  public:
    /**
     * @brief Constructor to make default initialization possible (necessary?)
     */
    SlerpInterpolator(t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
        : I_PairInterpolator<XType, t_quaternion>(extrapolation_mode)
    {
    }

    SlerpInterpolator(const std::vector<XType>&        X,
                      const std::vector<t_quaternion>& Y,
                      t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
        : I_PairInterpolator<XType, t_quaternion>(X, Y, extrapolation_mode)
    {
    }

    /**
     * @brief Construct a new Slerp Interpolator object using vectors of x, yaw, pitch and roll
     *
     * @param X vector; must be unique and sorted in ascending order
     * @param yaw vector with yaw data (rotation around z axis). Must be same size as X!
     * @param pitch vector with pitch data (rotation around y axis). Must be same size as X!
     * @param roll vector with roll data (rotation around x axis). Must be same size as X!
     * @param input_in_degrees if true (default) yaw,pitch and roll are in °, otherwise [rad]
     * @param extrapolation_mode :py:class:`t_extr_mode
     * <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>` object that describes the
     * extrapolation mode
     */
    SlerpInterpolator(const std::vector<XType>& X,
                      const std::vector<YType>& Yaw,
                      const std::vector<YType>& Pitch,
                      const std::vector<YType>& Roll,
                      bool                      input_in_degrees   = true,
                      t_extr_mode               extrapolation_mode = t_extr_mode::extrapolate)
        : I_PairInterpolator<XType, t_quaternion>(
              X,
              rotationfunctions::quaternion_from_ypr(Yaw, Pitch, Roll, input_in_degrees),
              extrapolation_mode)
    {
    }

    /**
     * @brief Construct a new Slerp Interpolator object using vectors of x, yaw, pitch and roll
     *
     * @param X vector; must be unique and sorted in ascending order
     * @param YPR vector with yaw, pitch and roll data points. Must be same size as X!
     * @param input_in_degrees if true (default) yaw,pitch and roll are in °, otherwise [rad]
     * @param extrapolation_mode :py:class:`t_extr_mode
     * <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>` object that describes the
     * extrapolation mode
     */
    SlerpInterpolator(const std::vector<XType>&                X,
                      const std::vector<std::array<YType, 3>>& YPR,
                      bool                                     input_in_degrees = true,
                      t_extr_mode extrapolation_mode = t_extr_mode::extrapolate)
        : I_PairInterpolator<XType, t_quaternion>(
              X,
              rotationfunctions::quaternion_from_ypr(YPR, input_in_degrees),
              extrapolation_mode)
    {
    }

    std::string class_name() const override { return "SlerpInterpolator"; }

    bool operator!=(const SlerpInterpolator<XType, YType>& rhs) const { return !(rhs == *this); }
    bool operator==(const SlerpInterpolator<XType, YType>& rhs) const
    {
        // compare extrapolation mode
        if (this->_extr_mode != rhs.get_extrapolation_mode())
            return false;

        // compare size of vectors
        if (this->_X.size() != rhs._X.size())
            return false;
        if (this->_Y.size() != rhs._Y.size())
            return false;

        // compare data
        // TODO: what happens for empty/nan quaternions?
        if (!std::equal(this->_X.begin(), this->_X.end(), rhs.get_data_X().begin()))
            return false;
        if (!std::equal(this->_Y.begin(), this->_Y.end(), rhs.get_data_Y().begin()))
            return false;

        // compare data
        // if (!helper::approx_container(_X, rhs._X))
        //     return false;
        // if (!helper::approx_container(_Y, rhs._Y))
        //     return false;

        return true;
    }

    /**
     * @brief get the interpolated yaw, pitch and roll values for given x target
     *
     * @param target_x find the corresponding y value for this x value
     * @param output_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
     * @return corresponding y value
     */
    std::array<YType, 3> ypr(XType target_x, bool output_in_degrees = true)
    {
        return rotationfunctions::ypr_from_quaternion(
            I_PairInterpolator<XType, t_quaternion>::operator()(target_x), output_in_degrees);
    }

    /**
     * @brief get the interpolated yaw, pitch and roll values for given x target
     *
     * @param target_x find the corresponding y value for this x value
     * @param output_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
     * @return corresponding y value
     */
    std::array<YType, 3> ypr_const(XType target_x, bool output_in_degrees = true) const
    {
        return rotationfunctions::ypr_from_quaternion(
            I_PairInterpolator<XType, t_quaternion>::get_y_const(target_x), output_in_degrees);
    }

    /**
     * @brief get the interpolated yaw, pitch and roll values for given x target (vectorized call)
     *
     * @param targets_x vector of x values. For each of these values find the corrsponding yaw,
     * pitch and roll value
     * @param output_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
     * @return corresponding y value
     */
    std::vector<std::array<YType, 3>> ypr(const std::vector<XType>& targets_x,
                                          bool                      output_in_degrees = true)
    {
        std::vector<std::array<YType, 3>> y_values;
        y_values.reserve(targets_x.size());
        for (const auto target_x : targets_x)
        {
            y_values.push_back(ypr(target_x, output_in_degrees));
        }

        return y_values;
    }

    // /**
    //  * @brief get the interpolated yaw, pitch and roll values for given x target (vectorized call)
    //  *
    //  * @param targets_x vector of x values. For each of these values find the corrsponding yaw,
    //  * pitch and roll value
    //  * @param output_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
    //  * @return corresponding y value
    //  */
    // std::vector<std::array<YType, 3>> ypr_const(const std::vector<XType>& targets_x,
    //                                             bool output_in_degrees = true) const
    // {
    //     auto y_values = I_PairInterpolator<XType, t_quaternion>::get_y_const(targets_x);
    //     std::vector<std::array<YType, 3>> ypr_values;
    //     ypr_values.reserve(y_values.size());
    //     for (const auto& q : y_values)
    //     {
    //         ypr_values.push_back(rotationfunctions::ypr_from_quaternion(q, output_in_degrees));
    //     }

    //     return ypr_values;
    // }

    // ------------------
    // set data functions
    // ------------------
    /**
     * @brief change the input data to these X, yaw, pitch, roll vectors (will be converted to
     * quaternion)
     *
     * @param X vector; must be unique and sorted in ascending order
     * @param yaw vector with yaw data (rotation around z axis). Must be same size as X!
     * @param pitch vector with pitch data (rotation around y axis). Must be same size as X!
     * @param roll vector with roll data (rotation around x axis). Must be same size as X!
     * @param input_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
     */
    void set_data_XYPR(const std::vector<XType>& X,
                       const std::vector<YType>& Yaw,
                       const std::vector<YType>& Pitch,
                       const std::vector<YType>& Roll,
                       bool                      input_in_degrees = true)
    {
        I_PairInterpolator<XType, t_quaternion>::set_data_XY(
            X, rotationfunctions::quaternion_from_ypr(Yaw, Pitch, Roll, input_in_degrees));
    }

    /**
     * @brief change the input data to these X, yaw, pitch, roll vectors (will be converted to
     * quaternion)
     *
     * @param X vector; must be unique and sorted in ascending order
     * @param yaw vector with yaw data (rotation around z axis). Must be same size as X!
     * @param pitch vector with pitch data (rotation around y axis). Must be same size as X!
     * @param roll vector with roll data (rotation around x axis). Must be same size as X!
     * @param input_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
     */
    void set_data_XYPR(const std::vector<XType>&                X,
                       const std::vector<std::array<YType, 3>>& YPR,
                       bool                                     input_in_degrees = true)
    {
        I_PairInterpolator<XType, t_quaternion>::set_data_XY(
            X, rotationfunctions::quaternion_from_ypr(YPR, input_in_degrees));
    }

    // -----------------------
    // getter functions
    // -----------------------
    /**
     * @brief return the internal yrp data vector
     *
     * @param output_in_degrees convert yaw, pitch and roll to degrees (default = True)
     * @return std::vector<std::array<3, YType>> YPR
     */
    std::vector<std::array<YType, 3>> get_data_YPR(bool output_in_degrees = true) const
    {
        return rotationfunctions::ypr_from_quaternion(this->get_data_Y(), output_in_degrees);
    }

    // -----------------------
    // append/extend functions
    // -----------------------
    /**
     * @brief append an x, yaw, pitch, roll data point
     *
     * @param X must be larger than all internal data points
     * @param yaw rotation around z axis
     * @param pitch rotation around y axis
     * @param roll rotation around x axis
     * @param input_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
     */
    void append(XType x, YType yaw, YType pitch, YType roll, bool input_in_degrees = true)
    {
        I_PairInterpolator<XType, t_quaternion>::append(
            x, rotationfunctions::quaternion_from_ypr(yaw, pitch, roll, input_in_degrees));
    }

    /**
     * @brief append an x, yaw, pitch, roll data point
     *
     * @param X must be larger than all internal data points
     * @param ypr array with one yaw, pitch and roll data point
     * @param input_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
     */
    void append(XType x, std::array<YType, 3> ypr, bool input_in_degrees = true)
    {
        I_PairInterpolator<XType, t_quaternion>::append(
            x, rotationfunctions::quaternion_from_ypr(ypr, input_in_degrees));
    }

    /**
     * @brief append data with lists of x, yaw, pitch, roll data (vectorized call)
     *
     * @param X vector; must be unique and sorted in ascending order
     * @param yaw vector with yaw data (rotation around z axis). Must be same size as X!
     * @param pitch vector with pitch data (rotation around y axis). Must be same size as X!
     * @param roll vector with roll data (rotation around x axis). Must be same size as X!
     * @param input_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
     */
    void extend(const std::vector<XType>& x,
                const std::vector<YType>& yaw,
                const std::vector<YType>& pitch,
                const std::vector<YType>& roll,
                bool                      input_in_degrees = true)
    {
        I_PairInterpolator<XType, t_quaternion>::extend(
            x, rotationfunctions::quaternion_from_ypr(yaw, pitch, roll, input_in_degrees));
    }

    /**
     * @brief append data with list of x, yaw, pitch, roll data (vectorized call)
     *
     * @param X vector; must be unique and sorted in ascending order
     * @param ypr vector with yaw, pitch and roll data points. Must be same size as X!
     * @param input_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
     */
    void extend(const std::vector<XType>&                x,
                const std::vector<std::array<YType, 3>>& ypr,
                bool                                     input_in_degrees = true)
    {
        I_PairInterpolator<XType, t_quaternion>::extend(
            x, rotationfunctions::quaternion_from_ypr(ypr, input_in_degrees));
    }

    /**
     * @brief append data with lists of x, yaw, pitch, roll data (vectorized call)
     *
     * @param X vector; must be unique
     * @param yaw vector with yaw data (rotation around z axis). Must be same size as X!
     * @param pitch vector with pitch data (rotation around y axis). Must be same size as X!
     * @param roll vector with roll data (rotation around x axis). Must be same size as X!
     * @param input_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
     */
    void insert(const std::vector<XType>& x,
                const std::vector<YType>& yaw,
                const std::vector<YType>& pitch,
                const std::vector<YType>& roll,
                bool                      input_in_degrees = true,
                bool                      is_sorted        = false)
    {
        I_PairInterpolator<XType, t_quaternion>::insert(
            x,
            rotationfunctions::quaternion_from_ypr(yaw, pitch, roll, input_in_degrees),
            is_sorted);
    }

    /**
     * @brief append data with list of x, yaw, pitch, roll data (vectorized call)
     *
     * @param X vector; must be unique
     * @param ypr vector with yaw, pitch and roll data points. Must be same size as X!
     * @param input_in_degrees if true, yaw pitch and roll input values are in ° otherwise rad
     */
    void insert(const std::vector<XType>&                x,
                const std::vector<std::array<YType, 3>>& ypr,
                bool                                     input_in_degrees = true,
                bool                                     is_sorted        = false)
    {
        I_PairInterpolator<XType, t_quaternion>::insert(
            x, rotationfunctions::quaternion_from_ypr(ypr, input_in_degrees), is_sorted);
    }

    /**
     * @brief Interpolate: Slerp interpolation between two values
     * @param target_x: the target point [0.0 - 1.0]
     * @param y1     : first quaternion (target_x = 0)
     * @param y2     : second quaternion (target_x = 01)
     * @return Interpolated value for target position
     */
    t_quaternion interpolate_pair(XType target_x, t_quaternion y1, t_quaternion y2) const final
    {
        return y1.slerp(target_x, y2);
    }

    // ----- to/from stream functions

    static SlerpInterpolator from_stream(std::istream& is)
    {
        using tools::classhelper::stream::container_from_stream;

        SlerpInterpolator obj;

        is.read(reinterpret_cast<char*>(&(obj._extr_mode)), sizeof(obj._extr_mode));

        obj._X = container_from_stream<std::vector<XType>>(is);
        obj._Y = container_from_stream<std::vector<t_quaternion>>(is);

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
    classhelper::ObjectPrinter __printer__(unsigned int float_precision,
                                           bool         superscript_exponents) const override
    {
        classhelper::ObjectPrinter printer(
            this->class_name(), float_precision, superscript_exponents);

        printer.register_enum("extr_mode", this->_extr_mode);
        printer.register_section("data lists");
        printer.register_container("X", this->_X);

        auto               YPR = this->get_data_YPR();
        std::vector<YType> y, p, r;
        for (const auto& ypr : YPR)
        {
            y.push_back(ypr[0]);
            p.push_back(ypr[1]);
            r.push_back(ypr[2]);
        }
        printer.register_container("Yaw [°]", y, "");
        printer.register_container("Pitch [°]", p, "");
        printer.register_container("Roll [°]", r, "");

        return printer;
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs to/from stream functionsÍ)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(SlerpInterpolator)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

} // namespace vectorinterpolators
} // namespace tools
} // namespace themachinethatgoesping

// #endif
