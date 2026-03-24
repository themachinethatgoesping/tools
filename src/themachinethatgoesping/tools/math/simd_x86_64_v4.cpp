// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

// Compile with -march=x86-64-v4 (AVX-512F/BW/CD/DQ/VL)

#include "simd.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace math {

template void fma_dispatch_kernel::operator()<xsimd::avx512bw, float>(xsimd::avx512bw, float*, const float*, float, float, size_t) const noexcept;
template void fma_dispatch_kernel::operator()<xsimd::avx512bw, double>(xsimd::avx512bw, double*, const double*, double, double, size_t) const noexcept;

} // namespace math
} // namespace tools
} // namespace themachinethatgoesping
