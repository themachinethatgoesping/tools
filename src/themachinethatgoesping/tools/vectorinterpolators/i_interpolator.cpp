// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief Template instantiations for i_interpolator
 *
 * @authors Peter Urban
 */

#include "i_interpolator.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace vectorinterpolators {


} // namespace vectorinterpolators
} // namespace tools
} // namespace themachinethatgoesping

// Explicit template instantiation for Option<t_extr_mode>
template class themachinethatgoesping::tools::classhelper::Option<
    themachinethatgoesping::tools::vectorinterpolators::t_extr_mode>;