// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "simd.hpp"

#include <xtensor/containers/xadapt.hpp>
#include <xtensor/core/xmath.hpp>
#include <xtensor/core/xnoalias.hpp>

namespace themachinethatgoesping {
namespace tools {
namespace math {

// ---------------------------------------------------------------------------
// Architecture diagnostic — reports what arch fma_dispatch actually uses
// ---------------------------------------------------------------------------
namespace {
struct arch_name_kernel
{
    template <class Arch>
    std::string operator()(Arch) const noexcept
    {
        return Arch::name();
    }
};
} // anonymous namespace

std::string fma_dispatch_arch()
{
    return xsimd::dispatch<dispatch_arch_list>(arch_name_kernel{})();
}

// ---------------------------------------------------------------------------
// fma_dispatch — the dispatch call itself needs NO architecture-specific flags.
// The per-arch template instantiations live in simd_x86_64_v{1..4}.cpp,
// each compiled with -march=x86-64-vN.
// ---------------------------------------------------------------------------

template <std::floating_point T>
void fma_dispatch(T* out, const T* x, T slope, T base, size_t n)
{
    xsimd::dispatch<dispatch_arch_list>(fma_dispatch_kernel{})(out, x, slope, base, n);
}

// Explicit instantiations
template void fma_dispatch<float>(float*, const float*, float, float, size_t);
template void fma_dispatch<double>(double*, const double*, double, double, size_t);

// ---------------------------------------------------------------------------
// fma_xtensor — xt::fma, uses compile-time SIMD
// ---------------------------------------------------------------------------
template <std::floating_point T>
void fma_xtensor(T* out, const T* x, T slope, T base, size_t n)
{
    auto x_view   = xt::adapt(x, n, xt::no_ownership(), std::array<size_t, 1>{n});
    auto out_view = xt::adapt(out, n, xt::no_ownership(), std::array<size_t, 1>{n});

    xt::noalias(out_view) = xt::fma(x_view, slope, base);
}

// Explicit instantiations
template void fma_xtensor<float>(float*, const float*, float, float, size_t);
template void fma_xtensor<double>(double*, const double*, double, double, size_t);

} // namespace math
} // namespace tools
} // namespace themachinethatgoesping
