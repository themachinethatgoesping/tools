#pragma once

/* generated doc strings */
#include ".docstrings/integermath.doc.hpp"

namespace themachinethatgoesping::tools::helper {
template<typename t_out, typename t_in1, typename t_in2>
inline t_out substract_set_zero_if_negative(t_in1 a, t_in2 b)
{
    return a > b ? a - b : 0;
}

} // namespace themachinethatgoesping::tools::helper