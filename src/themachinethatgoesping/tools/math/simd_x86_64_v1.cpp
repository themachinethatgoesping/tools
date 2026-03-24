// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// No special flags — SSE2 is baseline on x86-64 (v1).

#include "simd.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace math {

template void fma_dispatch_kernel::operator()<xsimd::sse2, float>(xsimd::sse2, float*, const float*, float, float, size_t) const noexcept;
template void fma_dispatch_kernel::operator()<xsimd::sse2, double>(xsimd::sse2, double*, const double*, double, double, size_t) const noexcept;

} // namespace math
} // namespace tools
} // namespace themachinethatgoesping
