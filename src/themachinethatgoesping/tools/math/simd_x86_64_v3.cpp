// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// Compile with -march=x86-64-v3 (AVX2 + FMA)

#include "simd.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace math {

template void fma_dispatch_kernel::operator()<xsimd::fma3<xsimd::avx2>, float>(xsimd::fma3<xsimd::avx2>, float*, const float*, float, float, size_t) const noexcept;
template void fma_dispatch_kernel::operator()<xsimd::fma3<xsimd::avx2>, double>(xsimd::fma3<xsimd::avx2>, double*, const double*, double, double, size_t) const noexcept;

} // namespace math
} // namespace tools
} // namespace themachinethatgoesping
