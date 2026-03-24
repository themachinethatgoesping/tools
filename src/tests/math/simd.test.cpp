// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>

#include <cmath>
#include <numeric>
#include <vector>

#include "../themachinethatgoesping/tools/math/simd.hpp"

using namespace themachinethatgoesping::tools::math;

#define TESTTAG "[math][simd]"

// Helper: reference computation
template <typename T>
std::vector<T> ref_fma(const std::vector<T>& x, T slope, T base)
{
    std::vector<T> r(x.size());
    for (size_t i = 0; i < x.size(); ++i)
        r[i] = std::fma(x[i], slope, base);
    return r;
}

// ---- fma_dispatch tests ----

TEMPLATE_TEST_CASE("fma_dispatch: basic", TESTTAG, float, double)
{
    constexpr size_t      N = 8;
    std::vector<TestType> x(N);
    std::iota(x.begin(), x.end(), TestType(0));
    std::vector<TestType> out(N);

    fma_dispatch(out.data(), x.data(), TestType(2), TestType(10), N);

    auto expected = ref_fma(x, TestType(2), TestType(10));
    for (size_t i = 0; i < N; ++i)
        REQUIRE(out[i] == Catch::Approx(expected[i]));
}

TEMPLATE_TEST_CASE("fma_dispatch: empty", TESTTAG, float, double)
{
    std::vector<TestType> out, x;
    fma_dispatch(out.data(), x.data(), TestType(1), TestType(0), 0);
    REQUIRE(out.empty());
}

TEMPLATE_TEST_CASE("fma_dispatch: tail handling (n=37)", TESTTAG, float, double)
{
    constexpr size_t      N = 37;
    std::vector<TestType> x(N);
    std::iota(x.begin(), x.end(), TestType(1));
    std::vector<TestType> out(N);

    fma_dispatch(out.data(), x.data(), TestType(-0.5), TestType(100), N);

    auto expected = ref_fma(x, TestType(-0.5), TestType(100));
    for (size_t i = 0; i < N; ++i)
        REQUIRE(out[i] == Catch::Approx(expected[i]));
}

TEMPLATE_TEST_CASE("fma_dispatch: large array (n=10007)", TESTTAG, float, double)
{
    constexpr size_t      N = 10007;
    std::vector<TestType> x(N);
    for (size_t i = 0; i < N; ++i)
        x[i] = static_cast<TestType>(i) * TestType(0.01);
    std::vector<TestType> out(N);

    fma_dispatch(out.data(), x.data(), TestType(2.5), TestType(-3.7), N);

    auto expected = ref_fma(x, TestType(2.5), TestType(-3.7));
    for (size_t i = 0; i < N; ++i)
        REQUIRE(out[i] == Catch::Approx(expected[i]));
}

// ---- fma_xtensor tests ----

TEMPLATE_TEST_CASE("fma_xtensor: basic", TESTTAG, float, double)
{
    constexpr size_t      N = 8;
    std::vector<TestType> x(N);
    std::iota(x.begin(), x.end(), TestType(0));
    std::vector<TestType> out(N);

    fma_xtensor(out.data(), x.data(), TestType(2), TestType(10), N);

    auto expected = ref_fma(x, TestType(2), TestType(10));
    for (size_t i = 0; i < N; ++i)
        REQUIRE(out[i] == Catch::Approx(expected[i]));
}

TEMPLATE_TEST_CASE("fma_xtensor: empty", TESTTAG, float, double)
{
    std::vector<TestType> out, x;
    fma_xtensor(out.data(), x.data(), TestType(1), TestType(0), 0);
    REQUIRE(out.empty());
}

TEMPLATE_TEST_CASE("fma_xtensor: tail handling (n=37)", TESTTAG, float, double)
{
    constexpr size_t      N = 37;
    std::vector<TestType> x(N);
    std::iota(x.begin(), x.end(), TestType(1));
    std::vector<TestType> out(N);

    fma_xtensor(out.data(), x.data(), TestType(-0.5), TestType(100), N);

    auto expected = ref_fma(x, TestType(-0.5), TestType(100));
    for (size_t i = 0; i < N; ++i)
        REQUIRE(out[i] == Catch::Approx(expected[i]));
}

TEMPLATE_TEST_CASE("fma_xtensor: large array (n=10007)", TESTTAG, float, double)
{
    constexpr size_t      N = 10007;
    std::vector<TestType> x(N);
    for (size_t i = 0; i < N; ++i)
        x[i] = static_cast<TestType>(i) * TestType(0.01);
    std::vector<TestType> out(N);

    fma_xtensor(out.data(), x.data(), TestType(2.5), TestType(-3.7), N);

    auto expected = ref_fma(x, TestType(2.5), TestType(-3.7));
    for (size_t i = 0; i < N; ++i)
        REQUIRE(out[i] == Catch::Approx(expected[i]).margin(1e-12));
}

// ---- cross-check: both implementations agree ----

TEMPLATE_TEST_CASE("fma_dispatch vs fma_xtensor: results match", TESTTAG, float, double)
{
    constexpr size_t      N = 1023;
    std::vector<TestType> x(N);
    for (size_t i = 0; i < N; ++i)
        x[i] = static_cast<TestType>(i) * TestType(0.1) - TestType(50);

    std::vector<TestType> out_dispatch(N), out_xtensor(N);
    TestType              slope = TestType(3.14);
    TestType              base  = TestType(-2.71);

    fma_dispatch(out_dispatch.data(), x.data(), slope, base, N);
    fma_xtensor(out_xtensor.data(), x.data(), slope, base, N);

    for (size_t i = 0; i < N; ++i)
        REQUIRE(out_dispatch[i] == Catch::Approx(out_xtensor[i]));
}
