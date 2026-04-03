// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// AArch64 NEON — baseline SIMD on all ARM64 / Apple Silicon.

#include "simd.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace math {

template void fma_dispatch_kernel::operator()<xsimd::neon64, float>(xsimd::neon64, float*, const float*, float, float, size_t) const noexcept;
template void fma_dispatch_kernel::operator()<xsimd::neon64, double>(xsimd::neon64, double*, const double*, double, double, size_t) const noexcept;

template void fmab_dispatch_kernel::operator()<xsimd::neon64, float>(xsimd::neon64, float*, const float*, float, const float*, size_t) const noexcept;
template void fmab_dispatch_kernel::operator()<xsimd::neon64, double>(xsimd::neon64, double*, const double*, double, const double*, size_t) const noexcept;

} // namespace math
} // namespace tools
} // namespace themachinethatgoesping
