// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// Compile with -march=x86-64-v2 (SSE4.2 + SSSE3 + POPCNT)

#include "simd.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace math {

template void fma_dispatch_kernel::operator()<xsimd::sse4_2, float>(xsimd::sse4_2, float*, const float*, float, float, size_t) const noexcept;
template void fma_dispatch_kernel::operator()<xsimd::sse4_2, double>(xsimd::sse4_2, double*, const double*, double, double, size_t) const noexcept;

template void fmab_dispatch_kernel::operator()<xsimd::sse4_2, float>(xsimd::sse4_2, float*, const float*, float, const float*, size_t) const noexcept;
template void fmab_dispatch_kernel::operator()<xsimd::sse4_2, double>(xsimd::sse4_2, double*, const double*, double, const double*, size_t) const noexcept;

} // namespace math
} // namespace tools
} // namespace themachinethatgoesping
