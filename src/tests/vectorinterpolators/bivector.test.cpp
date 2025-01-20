// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <boost/algorithm/algorithm.hpp>
#include <chrono>
#include <filesystem>
#include <fstream>

#include "../../themachinethatgoesping/tools/vectorinterpolators.hpp"

// using namespace testing;
using namespace std;
using namespace themachinethatgoesping::tools;

#define TESTTAG "[vectorinterpolators]"

// update the written test data
#define __UPDATE_TEST_DATA__ false
const std::string TESTDIR = __PROJECT_TESTDATADIR__ + std::string("/");

template<typename t_interpolator>
void test_interpolator_serialize(t_interpolator& ip)
{
    cerr << "test_interpolator_serialize: " << ip.class_name() << endl;
    t_interpolator ip2(ip);

    REQUIRE(ip == ip2);

    return; // 1

    // test internal to/from binary functions
    auto buffer2 = ip2.to_binary();
    auto ip3     = t_interpolator::from_binary(buffer2);

    // test internal to/from stream functions
    std::ofstream ofs(TESTDIR + "interpolator.tmp", std::ios::binary);
    ip3.to_stream(ofs);
    ofs.close();
    // write file if it does not exist or is only an empty reference
    auto test_file = TESTDIR + "vectorinterpolators/" + ip3.class_name() + ".binary";

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

    int i = 0;
    for (auto ipx : { ip2, ip3, ip4, ip5 })
    {
        INFO(fmt::format("comparing nr {}", i++));
        REQUIRE(ip == ipx);
    }
}

TEST_CASE("BiVectorInterpolator: should perform basic interpolations correctly", TESTTAG)
{
    // initialize test data
    // std::vector<double> x = { -10, -5, 0, 6, 12 };
    // std::vector<double> y = { 1, 0, 1, 0, -1 };
    std::vector<double> x        = { -10,  -5,  0, 6 };
    std::vector<double> y        = { -20, -15, -4, 3, 10 };
    std::vector<double> y_val    = {   2,   3,  2, 0, 12 };
    vectorinterpolators::BiVectorInterpolator<vectorinterpolators::AkimaInterpolator<double>>
        interpolator;

    // append some data
    for (unsigned int i = 0; i < x.size(); ++i)
        interpolator.append_row(x[i], y, y_val);

    // test_interpolator_serialize
    test_interpolator_serialize(interpolator);

    // hashing should stay stable
    REQUIRE(interpolator.binary_hash() == 2221036240740104729ULL);

    SECTION("existing values should be looked up correctly")
    {
        auto image = interpolator(x, y);

        for (unsigned int i = 0; i < x.size(); ++i)
            for (unsigned int j = 0; j < y.size(); ++j)
            {
                INFO(fmt::format("{}, {}", i,j));
                CHECK(image(i, j) == Catch::Approx(y_val[j]));
            }
    }

    REQUIRE(interpolator.binary_hash() ==
            2221036240740104729ULL); // lookup should not change the hash

    // SECTION("preset values should be interpolated correctly")
    // {
    //     CHECK(interpolator(-7.5) == Catch::Approx(0.2684859155));
    //     CHECK(interpolator(-2.6) == Catch::Approx(0.5509550555));
    //     CHECK(interpolator(3.0) == Catch::Approx(0.5808823529));

    //     CHECK(interpolator(8) == Catch::Approx(-1. / 3.));
    //     CHECK(interpolator(9.0) == Catch::Approx(-1. / 2.));
    //     CHECK(interpolator(10) == Catch::Approx(-2. / 3.));
    // }

    REQUIRE(interpolator.binary_hash() ==
            2221036240740104729ULL); // lookup should not change the hash

    // SECTION("preset value vectors should be interpolated correctly")
    // {
    //     std::vector<double> targets_x  = { -7.5, -2.6, 3.0, 8, 9.0, 10 };
    //     std::vector<double> expected_y = { 0.2684859155, 0.5509550555, 0.5808823529,
    //                                        -1. / 3.,     -1. / 2.,     -2. / 3. };

    //     auto comp_y = interpolator(targets_x);
    //     for (unsigned int i = 0; i < targets_x.size(); ++i)
    //         REQUIRE(comp_y[i] == Catch::Approx(expected_y[i]));
    // }

    REQUIRE(interpolator.binary_hash() ==
            2221036240740104729ULL); // lookup should not change the hash

    // SECTION("extrapolation mode should cause:")
    // {
    //     for (auto mode : vectorinterpolators::t_extr_mode_all)
    //     {
    //         interpolator.set_extrapolation_mode(mode);

    //         switch (mode)
    //         {
    //             case vectorinterpolators::t_extr_mode::fail:
    //                 SECTION(" - fail when set to fail")
    //                 {
    //                     REQUIRE_THROWS_AS(interpolator(-11), std::out_of_range);
    //                     REQUIRE_THROWS_AS(interpolator(13), std::out_of_range);
    //                 }
    //                 break;

    //             case vectorinterpolators::t_extr_mode::nearest:
    //                 SECTION(" - extrapolate nearest when set")
    //                 {
    //                     REQUIRE(interpolator(-11) == Catch::Approx(1));
    //                     REQUIRE(interpolator(13) == Catch::Approx(-1));
    //                 }
    //                 break;

    //             default:
    //                 SECTION(" - extrapolation in all other cases")
    //                 {
    //                     CHECK(interpolator(-100) == Catch::Approx(28.0618464789));
    //                     CHECK(interpolator(100) == Catch::Approx(-15 - 2 / 3.));
    //                 }
    //                 break;
    //         }
    //     }
    // }
}
