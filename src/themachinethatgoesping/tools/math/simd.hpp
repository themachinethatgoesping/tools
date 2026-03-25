// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief SIMD-accelerated math primitives with runtime architecture dispatch.
 *
 * Provides two FMA implementations for performance comparison:
 *  - fma_dispatch: uses xsimd::dispatch for runtime SIMD selection (works without -march=native)
 *  - fma_xtensor:  uses xt::fma which relies on compile-time SIMD via -march=native
 *
 * The dispatch pattern follows the xsimd documentation:
 *   - The kernel template is declared in the struct but defined OUT OF CLASS
 *     (critical: in-class definitions bypass extern template).
 *   - Explicit template instantiations live in per-architecture .cpp files
 *     compiled with the appropriate flags (e.g. -mavx2 -mfma for AVX2).
 *   - extern template declarations below prevent implicit instantiation.
 *   - The dispatch call itself requires no special compiler flags.
 *
 * Dispatch paths (matching x86-64 microarchitecture levels):
 *   v4 — avx512bw : AMD Zen 4/5, Intel Ice Lake+
 *   v3 — fma3<avx2> : Intel 4th-14th gen, Core Ultra, AMD Zen 2/3
 *   v2 — sse4_2 : Intel Nehalem+, AMD Bulldozer+
 *   v1 — sse2 : baseline (all x86-64)
 *
 * @authors Peter Urban
 */

#pragma once

/* generated doc strings */
#include ".docstrings/simd.doc.hpp"

#include <cmath>
#include <concepts>
#include <cstddef>
#include <string>

#include <xsimd/xsimd.hpp>
#include <xtensor/containers/xtensor.hpp>

namespace themachinethatgoesping {
namespace tools {
namespace math {

/// Architecture list for runtime SIMD dispatch (x86-64 levels v4, v3, v2, v1).
using dispatch_arch_list = xsimd::arch_list<xsimd::avx512bw, xsimd::fma3<xsimd::avx2>, xsimd::sse4_2, xsimd::sse2>;

/**
 * @brief Return the name of the SIMD architecture selected by fma_dispatch at runtime.
 * E.g. "avx2", "sse2", "avx512bw", etc.
 */
std::string fma_dispatch_arch();

// ---------------------------------------------------------------------------
// fma_dispatch kernel — declared in-class, defined OUT OF CLASS.
// (In-class and inline definitions bypass the extern template mechanism.)
// ---------------------------------------------------------------------------

struct fma_dispatch_kernel
{
    template <class Arch, std::floating_point T>
    void operator()(Arch, T* out, const T* x, T slope, T base, size_t n) const noexcept;
};

// Out-of-class definition
template <class Arch, std::floating_point T>
void fma_dispatch_kernel::operator()(Arch, T* out, const T* x, T slope, T base, size_t n) const noexcept
{
    using batch_t              = xsimd::batch<T, Arch>;
    constexpr size_t simd_size = batch_t::size;

    const batch_t vslope = batch_t::broadcast(slope);
    const batch_t vbase  = batch_t::broadcast(base);

    size_t i = 0;
    for (; i + simd_size <= n; i += simd_size)
    {
        auto vx = batch_t::load_unaligned(x + i);
        auto vr = xsimd::fma(vx, vslope, vbase);
        vr.store_unaligned(out + i);
    }
    // scalar tail
    for (; i < n; ++i)
        out[i] = std::fma(x[i], slope, base);
}

// Suppress implicit instantiation — provided by per-arch .cpp files
// x86-64-v4 (avx512bw)  — simd_x86_64_v4.cpp
extern template void fma_dispatch_kernel::operator()<xsimd::avx512bw, float>(xsimd::avx512bw, float*, const float*, float, float, size_t) const noexcept;
extern template void fma_dispatch_kernel::operator()<xsimd::avx512bw, double>(xsimd::avx512bw, double*, const double*, double, double, size_t) const noexcept;
// x86-64-v3 (fma3<avx2>) — simd_x86_64_v3.cpp
extern template void fma_dispatch_kernel::operator()<xsimd::fma3<xsimd::avx2>, float>(xsimd::fma3<xsimd::avx2>, float*, const float*, float, float, size_t) const noexcept;
extern template void fma_dispatch_kernel::operator()<xsimd::fma3<xsimd::avx2>, double>(xsimd::fma3<xsimd::avx2>, double*, const double*, double, double, size_t) const noexcept;
// x86-64-v2 (sse4_2)    — simd_x86_64_v2.cpp
extern template void fma_dispatch_kernel::operator()<xsimd::sse4_2, float>(xsimd::sse4_2, float*, const float*, float, float, size_t) const noexcept;
extern template void fma_dispatch_kernel::operator()<xsimd::sse4_2, double>(xsimd::sse4_2, double*, const double*, double, double, size_t) const noexcept;
// x86-64-v1 (sse2)      — simd_x86_64_v1.cpp
extern template void fma_dispatch_kernel::operator()<xsimd::sse2, float>(xsimd::sse2, float*, const float*, float, float, size_t) const noexcept;
extern template void fma_dispatch_kernel::operator()<xsimd::sse2, double>(xsimd::sse2, double*, const double*, double, double, size_t) const noexcept;

// ---------------------------------------------------------------------------
// fma_dispatch — raw pointer interface
// ---------------------------------------------------------------------------

/**
 * @brief Compute out[i] = x[i] * slope + base  (fused multiply-add)
 *
 * Uses the best SIMD instruction set available on the current CPU,
 * detected at runtime via xsimd::dispatch.  Works even without -march=native.
 *
 * @tparam T  Floating-point element type (float or double).
 * @param out  Output array, must hold at least @p n elements.
 * @param x    Input array, must hold at least @p n elements.
 * @param slope  Scalar multiplier.
 * @param base   Scalar addend.
 * @param n      Number of elements to process.
 */
template<std::floating_point T>
void fma_dispatch(T* out, const T* x, T slope, T base, size_t n);

/**
 * @brief Compute out[i] = x[i] * slope + base  using xt::fma
 *
 * Wraps xtensor's fma which uses compile-time SIMD (requires -march=native
 * for best performance).  Provided for performance comparison with fma_dispatch.
 *
 * @tparam T  Floating-point element type (float or double).
 * @param out  Output array, must hold at least @p n elements.
 * @param x    Input array, must hold at least @p n elements.
 * @param slope  Scalar multiplier.
 * @param base   Scalar addend.
 * @param n      Number of elements to process.
 */
template<std::floating_point T>
void fma_xtensor(T* out, const T* x, T slope, T base, size_t n);

// ---------------------------------------------------------------------------
// fmab_dispatch kernel — FMA with array base: out[i] = x[i] * slope + base[i]
// ---------------------------------------------------------------------------

struct fmab_dispatch_kernel
{
    template <class Arch, std::floating_point T>
    void operator()(Arch, T* out, const T* x, T slope, const T* base, size_t n) const noexcept;
};

// Out-of-class definition
template <class Arch, std::floating_point T>
void fmab_dispatch_kernel::operator()(Arch, T* out, const T* x, T slope, const T* base, size_t n) const noexcept
{
    using batch_t              = xsimd::batch<T, Arch>;
    constexpr size_t simd_size = batch_t::size;

    const batch_t vslope = batch_t::broadcast(slope);

    size_t i = 0;
    for (; i + simd_size <= n; i += simd_size)
    {
        auto vx    = batch_t::load_unaligned(x + i);
        auto vbase = batch_t::load_unaligned(base + i);
        auto vr    = xsimd::fma(vx, vslope, vbase);
        vr.store_unaligned(out + i);
    }
    // scalar tail
    for (; i < n; ++i)
        out[i] = std::fma(x[i], slope, base[i]);
}

// Suppress implicit instantiation — provided by per-arch .cpp files
// x86-64-v4 (avx512bw)
extern template void fmab_dispatch_kernel::operator()<xsimd::avx512bw, float>(xsimd::avx512bw, float*, const float*, float, const float*, size_t) const noexcept;
extern template void fmab_dispatch_kernel::operator()<xsimd::avx512bw, double>(xsimd::avx512bw, double*, const double*, double, const double*, size_t) const noexcept;
// x86-64-v3 (fma3<avx2>)
extern template void fmab_dispatch_kernel::operator()<xsimd::fma3<xsimd::avx2>, float>(xsimd::fma3<xsimd::avx2>, float*, const float*, float, const float*, size_t) const noexcept;
extern template void fmab_dispatch_kernel::operator()<xsimd::fma3<xsimd::avx2>, double>(xsimd::fma3<xsimd::avx2>, double*, const double*, double, const double*, size_t) const noexcept;
// x86-64-v2 (sse4_2)
extern template void fmab_dispatch_kernel::operator()<xsimd::sse4_2, float>(xsimd::sse4_2, float*, const float*, float, const float*, size_t) const noexcept;
extern template void fmab_dispatch_kernel::operator()<xsimd::sse4_2, double>(xsimd::sse4_2, double*, const double*, double, const double*, size_t) const noexcept;
// x86-64-v1 (sse2)
extern template void fmab_dispatch_kernel::operator()<xsimd::sse2, float>(xsimd::sse2, float*, const float*, float, const float*, size_t) const noexcept;
extern template void fmab_dispatch_kernel::operator()<xsimd::sse2, double>(xsimd::sse2, double*, const double*, double, const double*, size_t) const noexcept;

// ---------------------------------------------------------------------------
// fmab_dispatch — raw pointer interface (array base)
// ---------------------------------------------------------------------------

/**
 * @brief Compute out[i] = x[i] * slope + base[i]  (fused multiply-add, array base)
 *
 * Like fma_dispatch but the addend is a per-element array instead of a scalar.
 *
 * @tparam T  Floating-point element type (float or double).
 * @param out  Output array, must hold at least @p n elements.
 * @param x    Input array, must hold at least @p n elements.
 * @param slope  Scalar multiplier.
 * @param base   Per-element addend array, must hold at least @p n elements.
 * @param n      Number of elements to process.
 */
template<std::floating_point T>
void fmab_dispatch(T* out, const T* x, T slope, const T* base, size_t n);

// ---- Returning overloads (inline wrappers) --------------------------------

/**
 * @brief Returning variant: out = fma_dispatch(x, slope, base)
 */
template<std::floating_point T>
inline xt::xtensor<T, 1> fma_dispatch(const T* x, T slope, T base, size_t n)
{
    auto out = xt::xtensor<T, 1>::from_shape({n});
    fma_dispatch(out.data(), x, slope, base, n);
    return out;
}

/**
 * @brief Returning variant: out = fma_xtensor(x, slope, base)
 */
template<std::floating_point T>
inline xt::xtensor<T, 1> fma_xtensor(const T* x, T slope, T base, size_t n)
{
    auto out = xt::xtensor<T, 1>::from_shape({n});
    fma_xtensor(out.data(), x, slope, base, n);
    return out;
}

/**
 * @brief Returning variant: out = fmab_dispatch(x, slope, base_arr)
 */
template<std::floating_point T>
inline xt::xtensor<T, 1> fmab_dispatch(const T* x, T slope, const T* base, size_t n)
{
    auto out = xt::xtensor<T, 1>::from_shape({n});
    fmab_dispatch(out.data(), x, slope, base, n);
    return out;
}

// ---- View/expression overloads (write into existing container/view) -------

/**
 * @brief Write into an xtensor view/container: fma_dispatch(view, x, slope, base)
 *
 * Accepts any xtensor expression with contiguous .data() and .size(),
 * such as xt::view(tensor, row, xt::all()).
 */
template<typename t_xtensor_out, std::floating_point T>
inline void fma_dispatch(t_xtensor_out&& out, const T* x, T slope, T base)
{
    fma_dispatch(out.data() + out.data_offset(), x, slope, base, out.size());
}

/**
 * @brief Write into an xtensor view/container: fma_xtensor(view, x, slope, base)
 */
template<typename t_xtensor_out, std::floating_point T>
inline void fma_xtensor(t_xtensor_out&& out, const T* x, T slope, T base)
{
    fma_xtensor(out.data() + out.data_offset(), x, slope, base, out.size());
}

/**
 * @brief Write into an xtensor view/container: fmab_dispatch(view, x, slope, base_arr)
 */
template<typename t_xtensor_out, std::floating_point T>
inline void fmab_dispatch(t_xtensor_out&& out, const T* x, T slope, const T* base)
{
    fmab_dispatch(out.data() + out.data_offset(), x, slope, base, out.size());
}

} // namespace math
} // namespace tools
} // namespace themachinethatgoesping
