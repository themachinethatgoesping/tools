// SPDX-FileCopyrightText: 2022 - 2026 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief A rotation class that wraps an Eigen quaternion and adds convenient
 * yaw/pitch/roll construction and extraction, vector rotation (scalar and
 * vectorized) and the machinery to copy, stream and print it like the other
 * themachinethatgoesping classes.
 *
 * Rotation derives from Eigen::Quaternion, so every quaternion operation
 * (multiplication, inverse, slerp, normalization, ...) is available directly.
 * The internal representation is always the (normalized) quaternion; yaw, pitch
 * and roll are only a convenience input/output (rotation order yaw (Z), pitch
 * (Y), roll (X), matching rotationfunctions::quaternion_from_ypr).
 *
 * @authors Peter Urban
 */

#pragma once

/* generated doc strings */
#include ".docstrings/rotation.doc.hpp"

#include <array>
#include <concepts>
#include <iostream>
#include <stdexcept>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <fmt/format.h>

#include <xtensor/containers/xtensor.hpp>

#include "../classhelper/objectprinter.hpp"
#include "../classhelper/stream.hpp"
#include "quaternions.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace rotationfunctions {

/**
 * @brief A rotation stored as a normalized Eigen quaternion.
 *
 * Rotation is an Eigen::Quaternion, so it can be used directly in any quaternion
 * expression (composition, inverse, slerp, ...). On top of that it offers:
 *   * (implicit) construction from yaw/pitch/roll (degrees by default),
 *   * extraction to yaw/pitch/roll and roll/pitch/yaw,
 *   * rotation of a single xyz vector, of another Rotation (composition) and of a
 *     batch of xyz vectors (vectorized, one shared rotation matrix),
 *   * copy, binary streaming and object printing like the other classes.
 *
 * The quaternion is kept normalized after every construction so vector rotation is
 * always metric. yaw/pitch/roll follow the ping convention: yaw about z (down,
 * 0 deg = north), pitch about y (starboard, positive = bow up), roll about x
 * (forward, positive = port up); rotations are applied yaw, then pitch, then roll.
 *
 * @tparam t_float floating point type of the quaternion coefficients (float or double).
 */
template<std::floating_point t_float>
class Rotation : public Eigen::Quaternion<t_float>
{
    using t_base = Eigen::Quaternion<t_float>;

  public:
    /// @brief The floating point type of the quaternion coefficients.
    using value_type = t_float;

    // ----- constructors -----

    /// @brief Construct an identity rotation (no rotation).
    Rotation()
        : t_base(t_base::Identity())
    {
    }

    /**
     * @brief Construct a Rotation from yaw, pitch and roll (implicit).
     *
     * @param ypr array containing {yaw, pitch, roll}.
     * @param input_in_degrees if true (default) yaw/pitch/roll are in degrees, otherwise radians.
     */
    Rotation(const std::array<t_float, 3>& ypr, bool input_in_degrees = true)
        : t_base(quaternion_from_ypr<t_float>(ypr, input_in_degrees))
    {
    }

    /**
     * @brief Construct a Rotation from yaw, pitch and roll.
     *
     * @param yaw rotation around z (down) [deg or rad], 0 deg = north.
     * @param pitch rotation around y (starboard) [deg or rad], positive = bow up.
     * @param roll rotation around x (forward) [deg or rad], positive = port up.
     * @param input_in_degrees if true (default) yaw/pitch/roll are in degrees, otherwise radians.
     */
    Rotation(t_float yaw, t_float pitch, t_float roll, bool input_in_degrees = true)
        : t_base(quaternion_from_ypr<t_float>(yaw, pitch, roll, input_in_degrees))
    {
    }

    /**
     * @brief Construct a Rotation from an Eigen quaternion (implicit, normalized).
     *
     * This makes every function that returns an Eigen::Quaternion (e.g.
     * rotationfunctions::quaternion_from_ypr) usable to build a Rotation.
     *
     * @param quaternion Eigen quaternion; a copy is stored and normalized.
     */
    Rotation(const t_base& quaternion)
        : t_base(quaternion)
    {
        this->normalize();
    }

    // ----- named factories -----

    /**
     * @brief Build a Rotation from raw quaternion coefficients (w, x, y, z).
     *
     * @param w scalar (real) part.
     * @param x i coefficient.
     * @param y j coefficient.
     * @param z k coefficient.
     * @return normalized Rotation.
     */
    static Rotation from_quaternion(t_float w, t_float x, t_float y, t_float z)
    {
        return Rotation(t_base(w, x, y, z));
    }

    /**
     * @brief Build a Rotation from yaw, pitch and roll.
     * @param yaw rotation around z (down) [deg or rad].
     * @param pitch rotation around y (starboard) [deg or rad].
     * @param roll rotation around x (forward) [deg or rad].
     * @param input_in_degrees if true (default) inputs are degrees, otherwise radians.
     * @return normalized Rotation.
     */
    static Rotation from_ypr(t_float yaw, t_float pitch, t_float roll, bool input_in_degrees = true)
    {
        return Rotation(yaw, pitch, roll, input_in_degrees);
    }

    /**
     * @brief Build a Rotation from a {yaw, pitch, roll} array.
     * @param ypr array containing {yaw, pitch, roll}.
     * @param input_in_degrees if true (default) inputs are degrees, otherwise radians.
     * @return normalized Rotation.
     */
    static Rotation from_ypr(const std::array<t_float, 3>& ypr, bool input_in_degrees = true)
    {
        return Rotation(ypr, input_in_degrees);
    }

    /**
     * @brief Build a Rotation from roll, pitch and yaw.
     * @param roll rotation around x (forward) [deg or rad].
     * @param pitch rotation around y (starboard) [deg or rad].
     * @param yaw rotation around z (down) [deg or rad].
     * @param input_in_degrees if true (default) inputs are degrees, otherwise radians.
     * @return normalized Rotation.
     */
    static Rotation from_rpy(t_float roll, t_float pitch, t_float yaw, bool input_in_degrees = true)
    {
        return Rotation(quaternion_from_rpy<t_float>(roll, pitch, yaw, input_in_degrees));
    }

    /**
     * @brief Build a Rotation from a {roll, pitch, yaw} array.
     * @param rpy array containing {roll, pitch, yaw}.
     * @param input_in_degrees if true (default) inputs are degrees, otherwise radians.
     * @return normalized Rotation.
     */
    static Rotation from_rpy(const std::array<t_float, 3>& rpy, bool input_in_degrees = true)
    {
        return Rotation(quaternion_from_rpy<t_float>(rpy, input_in_degrees));
    }

    // ----- extraction -----

    /**
     * @brief Extract yaw, pitch and roll from the rotation.
     * @param output_in_degrees if true (default) the output is in degrees, otherwise radians.
     * @return array containing {yaw, pitch, roll}.
     */
    std::array<t_float, 3> ypr(bool output_in_degrees = true) const
    {
        return ypr_from_quaternion<t_float>(*this, output_in_degrees);
    }

    /**
     * @brief Extract roll, pitch and yaw from the rotation.
     * @param output_in_degrees if true (default) the output is in degrees, otherwise radians.
     * @return array containing {roll, pitch, yaw}.
     */
    std::array<t_float, 3> rpy(bool output_in_degrees = true) const
    {
        return rpy_from_quaternion<t_float>(*this, output_in_degrees);
    }

    /**
     * @brief Get the raw quaternion coefficients as {w, x, y, z}.
     * @return array containing {w, x, y, z}.
     */
    std::array<t_float, 4> wxyz() const
    {
        return { this->w(), this->x(), this->y(), this->z() };
    }

    // ----- rotate -----

    /**
     * @brief Rotate a single 3D vector by this rotation.
     * @param x x component (forward).
     * @param y y component (starboard).
     * @param z z component (down).
     * @return the rotated {x, y, z} vector.
     */
    std::array<t_float, 3> rotate(t_float x, t_float y, t_float z) const
    {
        const Eigen::Matrix<t_float, 3, 1> rotated =
            (*this) * Eigen::Matrix<t_float, 3, 1>(x, y, z);
        return { rotated.x(), rotated.y(), rotated.z() };
    }

    /**
     * @brief Rotate a single 3D vector by this rotation.
     * @param xyz the {x, y, z} vector to rotate.
     * @return the rotated {x, y, z} vector.
     */
    std::array<t_float, 3> rotate(const std::array<t_float, 3>& xyz) const
    {
        return rotate(xyz[0], xyz[1], xyz[2]);
    }

    /**
     * @brief Rotate (compose with) another rotation: apply this rotation to @p rotation.
     * @param rotation the rotation to be rotated.
     * @return the combined rotation (this * rotation).
     */
    Rotation rotate(const Rotation& rotation) const { return (*this) * rotation; }

    /**
     * @brief Rotate a batch of 3D vectors by this rotation (vectorized).
     *
     * The rotation matrix is built once and applied to every row, which is the fast
     * path for rotating many points by the same rotation.
     *
     * @param points [n, 3] tensor of (x, y, z) row vectors.
     * @return [n, 3] tensor of rotated row vectors.
     * @throws std::invalid_argument if the second dimension is not 3.
     */
    xt::xtensor<t_float, 2> rotate(const xt::xtensor<t_float, 2>& points) const
    {
        if (points.shape(1) != 3)
            throw std::invalid_argument(
                fmt::format("Rotation::rotate: points must have shape [n, 3], got [{}, {}]",
                            points.shape(0),
                            points.shape(1)));

        const size_t            number_of_points = points.shape(0);
        xt::xtensor<t_float, 2> rotated =
            xt::xtensor<t_float, 2>::from_shape({ number_of_points, size_t(3) });

        // row vectors: rotated = points * R^T (single shared rotation matrix)
        const Eigen::Matrix<t_float, 3, 3> rotation_matrix = this->toRotationMatrix();
        auto input_map  = adapt_xtensor_to_eigen(points);
        auto output_map = adapt_xtensor_to_eigen(rotated);
        output_map.noalias() = input_map * rotation_matrix.transpose();

        return rotated;
    }

    // ----- operators -----

    // keep Eigen's quaternion*quaternion and quaternion*vector operators visible (not hidden by the
    // Rotation*Rotation overload below)
    using t_base::operator*;

    /**
     * @brief Compose two rotations (quaternion product); the result is a Rotation.
     *
     * The product of two normalized quaternions is already normalized, so (unlike an
     * Eigen::Quaternion product that is then converted back) no re-normalization is done.
     * @param other the rotation applied after this one.
     * @return the combined rotation (this * other).
     */
    Rotation operator*(const Rotation& other) const
    {
        Rotation result;
        static_cast<t_base&>(result) =
            static_cast<const t_base&>(*this) * static_cast<const t_base&>(other);
        return result;
    }

    /// @brief Two rotations are equal if their quaternions describe the same orientation (q == -q).
    bool operator==(const Rotation& other) const
    {
        return this->coeffs().isApprox(other.coeffs()) ||
               this->coeffs().isApprox((-other.coeffs()).eval());
    }
    /// @brief Inequality (negation of operator==).
    bool operator!=(const Rotation& other) const { return !(operator==(other)); }

  public:
    // ----- file I/O -----

    /**
     * @brief Read a Rotation from a binary stream (4 coefficients w, x, y, z).
     * @param is input stream.
     * @return the read Rotation.
     */
    static Rotation from_stream(std::istream& is)
    {
        std::array<t_float, 4> wxyz{};
        is.read(reinterpret_cast<char*>(wxyz.data()), 4 * sizeof(t_float));

        Rotation rotation;
        rotation.w() = wxyz[0];
        rotation.x() = wxyz[1];
        rotation.y() = wxyz[2];
        rotation.z() = wxyz[3];
        return rotation;
    }

    /**
     * @brief Write the Rotation to a binary stream (4 coefficients w, x, y, z).
     * @param os output stream.
     */
    void to_stream(std::ostream& os) const
    {
        const std::array<t_float, 4> wxyz = { this->w(), this->x(), this->y(), this->z() };
        os.write(reinterpret_cast<const char*>(wxyz.data()), 4 * sizeof(t_float));
    }

  public:
    // ----- objectprinter -----
    tools::classhelper::ObjectPrinter __printer__(unsigned int float_precision,
                                                  bool         superscript_exponents) const
    {
        tools::classhelper::ObjectPrinter printer(
            "Rotation", float_precision, superscript_exponents);

        printer.register_value("w", this->w());
        printer.register_value("x", this->x());
        printer.register_value("y", this->y());
        printer.register_value("z", this->z());

        printer.register_section("derived (yaw, pitch, roll)");
        const auto yaw_pitch_roll = ypr(true);
        printer.register_value("yaw", yaw_pitch_roll[0], "°");
        printer.register_value("pitch", yaw_pitch_roll[1], "°");
        printer.register_value("roll", yaw_pitch_roll[2], "°");

        return printer;
    }

  public:
    // -- class helper function macros --
    // define to_binary and from_binary functions (needs to_stream and from_stream)
    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(Rotation)
    // define info_string and print functions (needs the __printer__ function)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__
};

// explicit template instantiation declarations (definitions live in rotation.cpp).
// Only float and double are provided; instantiating Rotation with any other type will fail to link.
extern template class Rotation<float>;
extern template class Rotation<double>;

} // namespace rotationfunctions
} // namespace tools
} // namespace themachinethatgoesping
