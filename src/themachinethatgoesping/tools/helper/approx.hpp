#pragma once

/* generated doc strings */
#include ".docstrings/approx.doc.hpp"

#include <iostream>
#include <concepts>
#include <complex>
#include <ranges>

namespace themachinethatgoesping::tools::helper {

/**
 * @brief compare to floats using a relative difference factor
 *
 * @tparam t_float floating point type
 * @param f1 float/double 1
 * @param f2 float/double 1
 * @param relative_difference_factor relative factor by which the 2 numbers must be comparable
 * (default 0.01%)
 * @return true/false
 */
template<std::floating_point t_float>
bool approx(t_float f1, t_float f2, t_float relative_difference_factor = 0.0001 // 0.01%
)
{
    // if both are NAN return true
    if (std ::isnan(f1))
        if (std::isnan(f2))
            return true;

    // if both are inf (and same sign) return true
    if (std::isinf(f1))
        if (std::isinf(f2))
        {
            if (f1 < 0)
            {
                if (f2 < 0)
                    return true;
            }
            else
            {
                if (f2 > 0)
                    return true;
            }
        }

    if (f1 == f2)
        return true;

    // if the difference between both is smaller than the relative difference factor (compared to
    // the larger float) return true
    return std::abs(f1 - f2) <= relative_difference_factor * std::max(std::abs(f1), std::abs(f2));
}

template<std::floating_point t_float>
bool approx_complex(std::complex<t_float> f1,
                    std::complex<t_float> f2,
                    t_float               relative_difference_factor = 0.0001 /* 0.01% */)
{
    return approx(f1.real(), f2.real(), relative_difference_factor) &&
           approx(f1.imag(), f2.imag(), relative_difference_factor);
}

template<std::ranges::random_access_range t_container>
bool approx_container(const t_container&               c1,
                      const t_container&               c2,
                      typename t_container::value_type relative_difference_factor = 0.0001 // 0.01%
)
{
    if (c1.size() != c2.size())
        return false;

    for (size_t i = 0; i < c1.size(); i++)
        if (!approx(c1[i], c2[i], relative_difference_factor))
            return false;

    return true;
}

template<std::ranges::random_access_range t_container>
bool approx_container_complex(
    const t_container&                           c1,
    const t_container&                           c2,
    typename t_container::value_type::value_type relative_difference_factor = 0.0001f /* 0.01% */
)
{
    if (c1.size() != c2.size())
        return false;

    for (size_t i = 0; i < c1.size(); i++)
        if (!approx_complex(c1[i], c2[i], relative_difference_factor))
            return false;

    return true;
}
} // namespace themachinethatgoesping::tools::helper