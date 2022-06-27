// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <boost/algorithm/algorithm.hpp>
#include <chrono>

#include "../../src/tools/vectorinterpolators.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::tools;

#define TESTTAG "[vectorinterpolators]"

#include <bitsery/bitsery.h>
#include <bitsery/adapter/buffer.h>
#include <bitsery/traits/vector.h>


template<typename t_interpolator>
void check_interpolators_are_equal(t_interpolator& lhs, t_interpolator& rhs)
{
    REQUIRE(lhs == rhs);
    REQUIRE(lhs(0.5) == Approx(rhs(0.5)));
    REQUIRE(lhs(-100) == Approx(rhs(-100)));
    REQUIRE(lhs(100) == Approx(rhs(100)));
}

//use fixed-size buffer
using Buffer = std::vector<uint8_t>;
using OutputAdapter = bitsery::OutputBufferAdapter<Buffer>;
using InputAdapter = bitsery::InputBufferAdapter<Buffer>;
TEST_CASE("VectorInterpolators should serializable", TESTTAG)
{
    std::vector<double> x     = { -10, -5, 0, 6, 12 };
    std::vector<double> y     = { 1, 0, 1, 0, -1 };
    std::vector<double> yaw   = { 1, 0, 1, 0, -1 };
    std::vector<double> pitch = { 1, 0, 1, 0, -1 };
    std::vector<double> roll  = { 1, 0, 1, 0, -1 };

    vectorinterpolators::LinearInterpolator  lip(x, y), lip2;

    //create buffer to store data
    Buffer buffer;
    //use quick serialization function,
    //it will use default configuration to setup all the nesessary steps
    //and serialize data to container
    auto writtenSize = bitsery::quickSerialization<OutputAdapter>(buffer, lip);

    //same as serialization, but returns deserialization state as a pair
    //first = error code, second = is buffer was successfully read from begin to the end.
    auto state = bitsery::quickDeserialization<InputAdapter>({ buffer.begin(), writtenSize }, lip2);

    REQUIRE(state.first == bitsery::ReaderError::NoError );
    REQUIRE(state.second);
    check_interpolators_are_equal(lip,lip2);
}

/**
 * @brief This test is more of a compile time check actually, it makes sure that the interpolators
 * implement all virtual functions such that they can actually be copied (had problems with this)
 *
 */
TEST_CASE("VectorInterpolators should support common operations", TESTTAG)
{
    std::vector<double> x     = { -10, -5, 0, 6, 12 };
    std::vector<double> y     = { 1, 0, 1, 0, -1 };
    std::vector<double> yaw   = { 1, 0, 1, 0, -1 };
    std::vector<double> pitch = { 1, 0, 1, 0, -1 };
    std::vector<double> roll  = { 1, 0, 1, 0, -1 };

    vectorinterpolators::LinearInterpolator  lip(x, y);
    vectorinterpolators::NearestInterpolator nip(x, y);
    vectorinterpolators::AkimaInterpolator   aip(x, y);
    vectorinterpolators::SlerpInterpolator   slerp(x, yaw, pitch, roll);

    // copy operator
    auto tl = lip;
    auto t2 = nip;
    auto t3 = aip;
    auto t4 = slerp;

    // copy initialization
    auto tlip = vectorinterpolators::LinearInterpolator(x, y);
    auto tnip = vectorinterpolators::NearestInterpolator(x, y);
    auto taip = vectorinterpolators::AkimaInterpolator(x, y);
    auto tslerp = vectorinterpolators::SlerpInterpolator(x, yaw, pitch, roll);
}

/**
 * @brief Test that the interpolators throw expected excetions
 * 
 */
TEST_CASE("VectorInterpolators: should throw expected exceptions", TESTTAG)
{
    SECTION("single value interpolators")
    { // initialize test data (correct order)
        std::vector<double> x = { -10, -5, 0, 6, 12 };
        std::vector<double> y = { 1, 0, 1, 0, -1 };

        std::vector<std::shared_ptr<vectorinterpolators::I_Interpolator<double>>> interpolators;
        interpolators.push_back(std::make_shared<vectorinterpolators::LinearInterpolator>(x, y));
        interpolators.push_back(std::make_shared<vectorinterpolators::NearestInterpolator>(x, y));
        interpolators.push_back(std::make_shared<vectorinterpolators::AkimaInterpolator>(x, y));

        for (auto interpolator : interpolators)
        {

            // interpolator should fail if double x elements are appended
            REQUIRE_THROWS(interpolator->append(12, -1));
            interpolator->set_data_XY(x, y);
            REQUIRE_THROWS(interpolator->append(11, -1));
            interpolator->set_data_XY(x, y);
            interpolator->append(13, -1);

            // same for extending lists
            REQUIRE_THROWS(interpolator->extend({ 12, 13 }, { -1, 1 }));
            interpolator->set_data_XY(x, y);
            REQUIRE_THROWS(interpolator->extend({ 11, 13 }, { -1, 1 }));
            interpolator->set_data_XY(x, y);
            REQUIRE_THROWS(interpolator->extend({ 14, 13 }, { -1, 1 }));
            interpolator->set_data_XY(x, y);
            REQUIRE_THROWS(interpolator->extend({ 14, 14 }, { -1, 1 }));
            interpolator->set_data_XY(x, y);
            interpolator->extend({ 13, 14 }, { -1, 1 });

            // initialize test data (wrong order)
            std::vector<double> x_wrong_order_ = { -5, -10, 0, 6, 12 };

            // throw because x is nort sorted
            REQUIRE_THROWS(interpolator->set_data_XY(x_wrong_order_, y));

            // initialize test data (duplicates)
            std::vector<double> x_duplicates_ = { -5, -10, 0, 0, 6, 12 };

            // interpolator should fail if there is a double x element!
            REQUIRE_THROWS(interpolator->set_data_XY(x_duplicates_, y));
        }

        // initialize test data (wrong order)
        std::vector<double> x_wrong_order = { -5, -10, 0, 6, 12 };

        // throw because x is nort sorted
        REQUIRE_THROWS(vectorinterpolators::LinearInterpolator(x_wrong_order, y));
        REQUIRE_THROWS(vectorinterpolators::NearestInterpolator(x_wrong_order, y));
        REQUIRE_THROWS(vectorinterpolators::AkimaInterpolator(x_wrong_order, y));

        // initialize test data (duplicates)
        std::vector<double> x_duplicates = { -5, -10, 0, 0, 6, 12 };

        // interpolator should fail if there is a double x element!
        REQUIRE_THROWS(vectorinterpolators::AkimaInterpolator(x_duplicates, y));
        REQUIRE_THROWS(vectorinterpolators::NearestInterpolator(x_duplicates, y));
        REQUIRE_THROWS(vectorinterpolators::AkimaInterpolator(x_duplicates, y));
    }

    SECTION("slerp interpolator")
    { // initialize test data (correct order)
        std::vector<double> x     = { -10, -5, 0, 6, 12 };
        std::vector<double> yaw   = { 1, 0, 1, 0, -1 };
        std::vector<double> pitch = { 1, 0, 1, 0, -1 };
        std::vector<double> roll  = { 1, 0, 1, 0, -1 };

        vectorinterpolators::SlerpInterpolator interpolator(x, yaw, pitch, roll);

        // interpolator should fail if double x elements are appended
        REQUIRE_THROWS(interpolator.append(12, { -1, -1, -1 }));
        interpolator.set_data_XYPR(x, yaw, pitch, roll);
        REQUIRE_THROWS(interpolator.append(11, { -1, -1, -1 }));
        interpolator.set_data_XYPR(x, yaw, pitch, roll);
        interpolator.append(13, { -1, -1, -1 });

        // same for extending lists
        REQUIRE_THROWS(interpolator.extend(
            {
                12, 13
        },
            { { -1, -1, -1 }, { 1, 1, 1 } }));
        interpolator.set_data_XYPR(x, yaw, pitch, roll);
        REQUIRE_THROWS(interpolator.extend(
            {
                11, 13
        },
            { { -1, -1, -1 }, { 1, 1, 1 } }));
        interpolator.set_data_XYPR(x, yaw, pitch, roll);
        REQUIRE_THROWS(interpolator.extend(
            {
                14, 13
        },
            { { -1, -1, -1 }, { 1, 1, 1 } }));
        interpolator.set_data_XYPR(x, yaw, pitch, roll);
        REQUIRE_THROWS(interpolator.extend(
            {
                14, 14
        },
            { { -1, -1, -1 }, { 1, 1, 1 } }));
        interpolator.set_data_XYPR(x, yaw, pitch, roll);
        interpolator.extend(
            {
                13, 14
        },
            { { -1, -1, -1 }, { 1, 1, 1 } });

        // initialize test data (wrong order)
        std::vector<double> x_wrong_order = { -5, -10, 0, 6, 12 };

        // throw because x is nort sorted
        REQUIRE_THROWS(vectorinterpolators::SlerpInterpolator(x_wrong_order, yaw, pitch, roll));
        REQUIRE_THROWS(interpolator.set_data_XYPR(x_wrong_order, yaw, pitch, roll));

        // initialize test data (duplicates)
        std::vector<double> x_duplicates = { -5, -10, 0, 0, 6, 12 };

        // interpolator should fail if there is a double x element!
        REQUIRE_THROWS(vectorinterpolators::SlerpInterpolator(x_duplicates, yaw, pitch, roll));
        REQUIRE_THROWS(interpolator.set_data_XYPR(x_duplicates, yaw, pitch, roll));
    }
}
