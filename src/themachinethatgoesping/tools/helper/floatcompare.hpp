#pragma once

/* generated doc strings */
#include ".docstrings/floatcompare.doc.hpp"

/* generated doc strings */
#include ".docstrings/printing.doc.hpp"

#include <cmath>

namespace themachinethatgoesping::tools::helper {

template<std::floating_point t_float>
inline bool float_equals(t_float a, t_float b, t_float epsilon = t_float(0.0001))
{
    return std::abs(a - b) < epsilon || (std::isnan(a) && std::isnan(b)) ||
           (std::isinf(a) && std::isinf(b));
}

template<std::floating_point t_float>
inline bool optional_float_equals(std::optional<t_float> a,
                                  std::optional<t_float> b,
                                  t_float                epsilon = t_float(0.0001))
{
    if (a.has_value())
    {
        if (!b.has_value())
            return false;

        return float_equals(a.value(), b.value(), epsilon);
    }

    if (b.has_value())
        return false;

    return true;
}

template<std::floating_point t_float>
inline bool float_is_finite_and_not_zero(t_float a, t_float epsilon = t_float(0.0001))
{
    return std::isfinite(a) && std::abs(a) > epsilon;
}

} // namespace themachinethatgoesping::tools::helper