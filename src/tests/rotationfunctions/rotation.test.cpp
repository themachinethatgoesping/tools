// SPDX-FileCopyrightText: 2022 - 2026 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// Tests for the Rotation class (rotationfunctions). Rotation wraps an Eigen
// quaternion and adds yaw/pitch/roll construction + extraction, vector rotation
// (scalar and vectorized) and copy/stream/print. The tests check that it stays
// consistent with the free rotationfunctions (quaternion_from_ypr / rotateXYZ),
// that the vectorized rotate matches the scalar rotate, and that copy / binary /
// stream round-trips reproduce the object.

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <array>
#include <sstream>

#include <boost/random.hpp>

#include <xtensor/containers/xtensor.hpp>

#include "../../themachinethatgoesping/tools/rotationfunctions/quaternions.hpp"
#include "../../themachinethatgoesping/tools/rotationfunctions/rotation.hpp"

using namespace themachinethatgoesping::tools::rotationfunctions;

#define TESTTAG "[rotationfunctions][rotation]"

TEST_CASE("Rotation: default is identity", TESTTAG)
{
    Rotation<float>  rf;
    Rotation<double> rd;

    // identity rotates any vector onto itself
    const auto vf = rf.rotate(1.f, 2.f, 3.f);
    REQUIRE_THAT(vf[0], Catch::Matchers::WithinAbs(1.f, 1e-6f));
    REQUIRE_THAT(vf[1], Catch::Matchers::WithinAbs(2.f, 1e-6f));
    REQUIRE_THAT(vf[2], Catch::Matchers::WithinAbs(3.f, 1e-6f));

    const auto ypr = rd.ypr();
    REQUIRE_THAT(ypr[0], Catch::Matchers::WithinAbs(0.0, 1e-9));
    REQUIRE_THAT(ypr[1], Catch::Matchers::WithinAbs(0.0, 1e-9));
    REQUIRE_THAT(ypr[2], Catch::Matchers::WithinAbs(0.0, 1e-9));
}

TEST_CASE("Rotation: ypr construction/extraction matches the free functions", TESTTAG)
{
    boost::random::mt19937                           gen(4242);
    boost::random::uniform_real_distribution<double> yaw_dist(0., 360.);
    boost::random::uniform_real_distribution<double> pitch_dist(-89., 89.);
    boost::random::uniform_real_distribution<double> roll_dist(-179., 179.);

    for (unsigned int i = 0; i < 500; ++i)
    {
        const double yaw = yaw_dist(gen), pitch = pitch_dist(gen), roll = roll_dist(gen);

        Rotation<double> rotation(yaw, pitch, roll);

        // same quaternion as the free function
        const auto reference = quaternion_from_ypr<double>(yaw, pitch, roll);
        REQUIRE(rotation == Rotation<double>(reference));

        // extraction matches ypr_from_quaternion and reproduces the input
        const auto ypr           = rotation.ypr();
        const auto ypr_reference = ypr_from_quaternion<double>(reference);
        for (int k = 0; k < 3; ++k)
            REQUIRE_THAT(ypr[k], Catch::Matchers::WithinAbs(ypr_reference[k], 1e-9));

        REQUIRE_THAT(ypr[0], Catch::Matchers::WithinAbs(yaw, 1e-6));
        REQUIRE_THAT(ypr[1], Catch::Matchers::WithinAbs(pitch, 1e-6));
        REQUIRE_THAT(ypr[2], Catch::Matchers::WithinAbs(roll, 1e-6));

        // array constructor is equivalent
        REQUIRE(rotation == Rotation<double>(std::array<double, 3>{ yaw, pitch, roll }));
    }
}

TEST_CASE("Rotation: rotate a single vector matches rotateXYZ", TESTTAG)
{
    // yaw +90 deg about z (down) sends forward (1,0,0) to starboard (0,1,0)
    Rotation<double> yaw90(90.0, 0.0, 0.0);
    const auto       rotated = yaw90.rotate(1.0, 0.0, 0.0);
    REQUIRE_THAT(rotated[0], Catch::Matchers::WithinAbs(0.0, 1e-9));
    REQUIRE_THAT(rotated[1], Catch::Matchers::WithinAbs(1.0, 1e-9));
    REQUIRE_THAT(rotated[2], Catch::Matchers::WithinAbs(0.0, 1e-9));

    boost::random::mt19937                           gen(99);
    boost::random::uniform_real_distribution<double> angle(-180., 180.), coord(-10., 10.);
    for (unsigned int i = 0; i < 200; ++i)
    {
        Rotation<double> rotation(angle(gen), 0.5 * angle(gen), angle(gen));
        const double     x = coord(gen), y = coord(gen), z = coord(gen);

        const auto by_class = rotation.rotate(x, y, z);
        const auto by_free  = rotateXYZ<double>(rotation, x, y, z);
        REQUIRE_THAT(by_class[0], Catch::Matchers::WithinAbs(by_free[0], 1e-9));
        REQUIRE_THAT(by_class[1], Catch::Matchers::WithinAbs(by_free[1], 1e-9));
        REQUIRE_THAT(by_class[2], Catch::Matchers::WithinAbs(by_free[2], 1e-9));

        // array overload agrees with the scalar overload
        const auto by_array = rotation.rotate(std::array<double, 3>{ x, y, z });
        REQUIRE(by_array == by_class);
    }
}

TEST_CASE("Rotation: composing rotations", TESTTAG)
{
    // two yaw rotations about the same axis add up
    Rotation<double> a(30.0, 0.0, 0.0);
    Rotation<double> b(40.0, 0.0, 0.0);
    const auto       ypr = a.rotate(b).ypr();
    REQUIRE_THAT(ypr[0], Catch::Matchers::WithinAbs(70.0, 1e-6));

    // rotate(Rotation) equals quaternion multiplication
    Rotation<double> c(12.0, -7.0, 33.0);
    Rotation<double> d(-40.0, 15.0, -8.0);
    REQUIRE(c.rotate(d) == Rotation<double>(Eigen::Quaterniond(c) * Eigen::Quaterniond(d)));
}

TEST_CASE("Rotation: vectorized rotate matches the scalar rotate", TESTTAG)
{
    Rotation<double> rotation(37.0, -12.0, 61.0);

    xt::xtensor<double, 2> points = {
        { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 1.0, 2.0, 3.0 }, { -4.0, 5.0, -6.0 }
    };

    const auto rotated = rotation.rotate(points);
    REQUIRE(rotated.shape(0) == points.shape(0));
    REQUIRE(rotated.shape(1) == 3);

    for (size_t i = 0; i < points.shape(0); ++i)
    {
        const auto expected =
            rotation.rotate(points(i, 0), points(i, 1), points(i, 2));
        REQUIRE_THAT(rotated(i, 0), Catch::Matchers::WithinAbs(expected[0], 1e-9));
        REQUIRE_THAT(rotated(i, 1), Catch::Matchers::WithinAbs(expected[1], 1e-9));
        REQUIRE_THAT(rotated(i, 2), Catch::Matchers::WithinAbs(expected[2], 1e-9));
    }
}

TEST_CASE("Rotation: rpy round-trip and wxyz", TESTTAG)
{
    Rotation<double> rotation = Rotation<double>::from_rpy(20.0, -35.0, 110.0);
    const auto       rpy      = rotation.rpy();
    REQUIRE_THAT(rpy[0], Catch::Matchers::WithinAbs(20.0, 1e-6));
    REQUIRE_THAT(rpy[1], Catch::Matchers::WithinAbs(-35.0, 1e-6));
    REQUIRE_THAT(rpy[2], Catch::Matchers::WithinAbs(110.0, 1e-6));

    const auto wxyz = rotation.wxyz();
    REQUIRE(Rotation<double>::from_quaternion(wxyz[0], wxyz[1], wxyz[2], wxyz[3]) == rotation);
}

TEST_CASE("Rotation: copy, equality (q == -q), stream and binary round-trips", TESTTAG)
{
    Rotation<double> rotation(123.0, -45.0, 67.0);

    // copy
    auto rotation_copy = rotation;
    REQUIRE(rotation_copy == rotation);

    // a quaternion and its negation represent the same rotation
    Rotation<double> negated =
        Rotation<double>::from_quaternion(-rotation.w(), -rotation.x(), -rotation.y(), -rotation.z());
    REQUIRE(negated == rotation);

    // inequality
    Rotation<double> different(0.0, 0.0, 0.0);
    REQUIRE(different != rotation);

    // printing does not crash and is non-empty
    REQUIRE(rotation.info_string().size() != 0);
    std::stringstream ss;
    rotation.print(ss);

    // to/from binary
    auto buffer                = rotation.to_binary();
    auto rotation_from_binary  = Rotation<double>::from_binary(buffer);
    REQUIRE(rotation_from_binary == rotation);

    // to/from stream
    std::stringstream stream;
    rotation.to_stream(stream);
    auto rotation_from_stream = Rotation<double>::from_stream(stream);
    REQUIRE(rotation_from_stream == rotation);

    // float variant round-trips too
    Rotation<float> rotation_float(12.f, 34.f, -56.f);
    REQUIRE(Rotation<float>::from_binary(rotation_float.to_binary()) == rotation_float);
}
