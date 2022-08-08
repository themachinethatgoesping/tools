// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch.hpp>

#include <boost/algorithm/algorithm.hpp>
#include <chrono>
#include <filesystem>
#include <fstream>

#include "../../themachinethatgoesping/tools/vectorinterpolators.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::tools;

#define TESTTAG "[vectorinterpolators]"

#include <bitsery/adapter/buffer.h>
#include <bitsery/bitsery.h>
#include <bitsery/traits/vector.h>

// use fixed-size buffer
using Buffer        = std::vector<uint8_t>;
using OutputAdapter = bitsery::OutputBufferAdapter<Buffer>;
using InputAdapter  = bitsery::InputBufferAdapter<Buffer>;

// update the written testdata
#define __UPDATE_TEST_DATA__ false
// __PROJECT_TESTDATADIR__ is set in meson build file of the test folder
const std::string TESTDIR = __PROJECT_TESTDATADIR__ + std::string("/");

// -- teamplated functions to avoid code repetition for different interpolators --
template<typename t_interpolator>
void test_interpolator_serialize(t_interpolator& ip)
{
    cerr << "test_interpolator_serialize: " << ip.type_to_string() << endl;
    t_interpolator ip2;

    // create buffer to store data
    Buffer buffer;
    // use quick serialization function,
    // it will use default configuration to setup all the nesessary steps
    // and serialize data to container
    auto writtenSize = bitsery::quickSerialization<OutputAdapter>(buffer, ip);
    bitsery::quickSerialization<OutputAdapter>(buffer, ip);
    for (unsigned int i = 0; i < 100; ++i)
    {
        buffer.push_back(0);
        buffer.push_back(1);
        buffer.push_back(1);
        buffer.push_back(10);
    }

    // interpolators should not be the same before serialization
    REQUIRE(ip != ip2);

    // same as serialization, but returns deserialization state as a pair
    // first = error code, second = is buffer was successfully read from begin to the end.
    //#auto state = bitsery::quickDeserialization<InputAdapter>({ buffer.begin(), writtenSize },
    // ip2);
    // auto state = bitsery::quickDeserialization<InputAdapter>({buffer.begin(), buffer.end()},ip2);
    auto state = bitsery::quickDeserialization<InputAdapter>({ buffer.begin(), writtenSize }, ip2);
    REQUIRE(state.first == bitsery::ReaderError::NoError);
    REQUIRE(state.second);

    // test internal to/from binary functions
    auto buffer2 = ip2.to_binary();
    auto ip3     = t_interpolator::from_binary(buffer2);

    // test internal to/from stream functions
    std::ofstream ofs(TESTDIR + "interpolator.tmp", std::ios::binary);
    ip3.to_stream(ofs);
    ofs.close();
    // write file if it does not exist or is only an empty reference
    auto test_file = TESTDIR + "vectorinterpolators/" + ip3.type_to_string() + ".binary";

    std::filesystem::create_directories(TESTDIR + "vectorinterpolators/");
    bool recreate_test_file = false;
    if (!std::filesystem::exists(test_file))
        recreate_test_file = true;
    else if (std::filesystem::file_size(test_file) < 100)
        recreate_test_file = true;

    if (__UPDATE_TEST_DATA__ || recreate_test_file || true)
    {
        ofs.open(test_file, std::ios::binary);
        ip3.to_stream(ofs);
        ofs.close();
    }

    // read test data created during this test
    std::ifstream ifs(TESTDIR + "interpolator.tmp", std::ios::binary);
    auto          ip4 = t_interpolator::from_stream(ifs);
    ifs.close();

    // read permanently created test data
    ifs.open(test_file);
    // ifs.open(TESTDIR + "interpolator.tmp", std::ios::binary);
    auto ip5 = t_interpolator::from_stream(ifs);
    ifs.close();

    for (auto ipx : { ip2, ip3, ip4, ip5 })
    {
        // this is a copy so no approx should be necessar
        REQUIRE(ip == ipx);
        REQUIRE(ip(0.5) == ipx(0.5));
        REQUIRE(ip(-100) == ipx(-100));
        REQUIRE(ip(100) == ipx(100));
    }
}

TEST_CASE("VectorInterpolators should serializable", TESTTAG)
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

    test_interpolator_serialize(nip);
    test_interpolator_serialize(lip);
    test_interpolator_serialize(aip);
    test_interpolator_serialize(slerp);
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
    auto t1 = lip;
    auto t2 = nip;
    auto t3 = aip;
    auto t4 = slerp;

    // copy initialization
    auto tlip   = vectorinterpolators::LinearInterpolator(t1);
    auto tnip   = vectorinterpolators::NearestInterpolator(t2);
    auto taip   = vectorinterpolators::AkimaInterpolator(t3);
    auto tslerp = vectorinterpolators::SlerpInterpolator(t4);

    // check if copies are correct
    REQUIRE(t1 == lip);
    REQUIRE(t2 == nip);
    REQUIRE(t3 == aip);
    REQUIRE(t4 == slerp);
    REQUIRE(t1 == tlip);
    REQUIRE(t2 == tnip);
    REQUIRE(t3 == taip);
    REQUIRE(t4 == tslerp);

    // check that common printing operations do not crash or produce empty strings
    REQUIRE(lip.info_string().size() > 1);
    REQUIRE(nip.info_string().size() > 1);
    REQUIRE(aip.info_string().size() > 1);
    REQUIRE(slerp.info_string().size() > 1);

    // check that printing to stream does not crash
    std::stringstream ss;
    lip.print(ss);
    nip.print(ss);
    aip.print(ss);
    slerp.print(ss);
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

            // throw because x is not sorted
            REQUIRE_THROWS(interpolator->set_data_XY(x_wrong_order_, y));

            // initialize test data (duplicates)
            std::vector<double> x_duplicates_ = { -5, -10, 0, 0, 6, 12 };

            // interpolator should fail if there is a double x element!
            REQUIRE_THROWS(interpolator->set_data_XY(x_duplicates_, y));
        }

        // initialize test data (wrong order)
        std::vector<double> x_wrong_order = { -5, -10, 0, 6, 12 };

        // throw because x is not sorted
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

        // throw because x is not sorted
        REQUIRE_THROWS(vectorinterpolators::SlerpInterpolator(x_wrong_order, yaw, pitch, roll));
        REQUIRE_THROWS(interpolator.set_data_XYPR(x_wrong_order, yaw, pitch, roll));

        // initialize test data (duplicates)
        std::vector<double> x_duplicates = { -5, -10, 0, 0, 6, 12 };

        // interpolator should fail if there is a double x element!
        REQUIRE_THROWS(vectorinterpolators::SlerpInterpolator(x_duplicates, yaw, pitch, roll));
        REQUIRE_THROWS(interpolator.set_data_XYPR(x_duplicates, yaw, pitch, roll));
    }
}

/**
 * @brief This test is more of a compile time check actually, it makes sure that the interpolators
 * implement all virtual functions such that they can actually be copied (had problems with this)
 *
 */
TEST_CASE("VectorInterpolators should react correctly to beeing underinitialized", TESTTAG)
{
    std::vector<double> x     = { -10, -5, 0, 6, 12 };
    std::vector<double> y     = { 1, 0, 1, 0, -1 };
    std::vector<double> yaw   = { 1, 0, 1, 0, -1 };
    std::vector<double> pitch = { 1, 0, 1, 0, -1 };
    std::vector<double> roll  = { 1, 0, 1, 0, -1 };

    vectorinterpolators::LinearInterpolator  lip;
    vectorinterpolators::NearestInterpolator nip;
    vectorinterpolators::AkimaInterpolator   aip;
    vectorinterpolators::SlerpInterpolator   slerp;

    // interpolators should fail if they are not initialized
    REQUIRE_THROWS_AS(lip(0), std::domain_error);
    REQUIRE_THROWS_AS(nip(0), std::domain_error);
    REQUIRE_THROWS_AS(aip(0), std::domain_error);
    REQUIRE_THROWS_AS(slerp(0), std::domain_error);

    // interpolators should return single value if they are initialized with a single value
    lip.append(10, 20);
    nip.append(10, 20);
    aip.append(10, 20);
    slerp.append(10, 20, 30, 40);

    REQUIRE(lip(-10) == 20);
    REQUIRE(nip(100) == 20);
    REQUIRE(aip(10) == 20);
    REQUIRE(slerp.ypr(10)[0] == Approx(20));
    REQUIRE(slerp.ypr(10)[1] == Approx(30));
    REQUIRE(slerp.ypr(10)[2] == Approx(40));

    // lip, nip and slerp interpolators should act normally if they are initialized with multiple values
    lip.append(20,30);
    nip.append(20,30);
    slerp.append(20,30,40,50);
    REQUIRE(lip(15) == 25);
    REQUIRE(lip(25) == 35);
    REQUIRE(nip(14) == 20);
    REQUIRE(nip(16) == 30);
    REQUIRE(slerp.ypr(15)[0] == Approx(24.579580303));
    REQUIRE(slerp.ypr(15)[1] == Approx(35.1774819807));
    REQUIRE(slerp.ypr(15)[2] == Approx(44.579580303));

    // aip should act as linear interpolator when initialized with 2 values
    aip.append(20,30);
    REQUIRE(aip(15) == 25);

    // aip should act as linear interpolator when initialized with 3 values
    aip.append(30,50);
    REQUIRE(aip(25) == 40);
    REQUIRE(aip(35) == 60);
    REQUIRE(aip(15) == 25);

    // aip should act as akima interpolator when initialized with 4 values
    aip.append(40,60);
    CHECK(aip(25) == 40);
    CHECK(aip(35) == Approx(56.25));
    REQUIRE(aip(15) == Approx(23.75));
}