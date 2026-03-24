// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "m_simd.hpp"

#include <themachinethatgoesping/tools/math/simd.hpp>

#include <nanobind/nanobind.h>
#include <xtensor-python/nanobind/pytensor.hpp>

namespace nb        = nanobind;
namespace pingtools = themachinethatgoesping::tools;

template <typename T>
void bind_fma(nb::module_& m)
{
    // fma_dispatch — runtime SIMD dispatch, in-place
    m.def(
        "fma_dispatch",
        [](xt::nanobind::pytensor<T, 1>& x,
           T slope,
           T base) {
            pingtools::math::fma_dispatch(x.data(), x.data(), slope, base, x.shape(0));
        },
        "Compute x[:] = x * slope + base in-place using runtime SIMD dispatch",
        nb::arg("x"),
        nb::arg("slope"),
        nb::arg("base"));

    // fma_xtensor — xt::fma, in-place
    m.def(
        "fma_xtensor",
        [](xt::nanobind::pytensor<T, 1>& x,
           T slope,
           T base) {
            pingtools::math::fma_xtensor(x.data(), x.data(), slope, base, x.shape(0));
        },
        "Compute x[:] = x * slope + base in-place using xt::fma (compile-time SIMD)",
        nb::arg("x"),
        nb::arg("slope"),
        nb::arg("base"));
}

void init_m_simd(nb::module_& m)
{
    auto m_math = m.def_submodule("math", "SIMD math functions for performance testing");

    // architecture diagnostic
    m_math.def("fma_dispatch_arch", &pingtools::math::fma_dispatch_arch,
               "Return the SIMD architecture name selected by fma_dispatch (e.g. 'avx2', 'sse2')");

    bind_fma<float>(m_math);
    bind_fma<double>(m_math);
}
