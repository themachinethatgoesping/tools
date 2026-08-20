// SPDX-FileCopyrightText: 2022 - 2026 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include "rotation.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace rotationfunctions {

// explicit template instantiation definitions (declarations are in rotation.hpp).
// Provide float and double; any other type will fail to link (by design).
template class Rotation<float>;
template class Rotation<double>;

} // namespace rotationfunctions
} // namespace tools
} // namespace themachinethatgoesping
