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

TEST_CASE("VectorInterpolators: should throw expected exceptiosn", TESTTAG)
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
            std::vector<double> x_wrong_order = { -5, -10, 0, 6, 12 };
            std::vector<double> y_wrong_order = { 0, 1, 1, 0, -1 };

            // throw because x is nort sorted
            REQUIRE_THROWS(vectorinterpolators::AkimaInterpolator(x_wrong_order, y_wrong_order));

            // initialize test data (duplicates)
            std::vector<double> x_duplicates = { -5, -10, 0, 0, 6, 12 };
            std::vector<double> y_duplicates = { 0, 1, 1, 0, 1, -1 };

            // interpolator should fail if there is a double x element!
            REQUIRE_THROWS(vectorinterpolators::AkimaInterpolator(x_duplicates, y_duplicates));
        }
    }
}
