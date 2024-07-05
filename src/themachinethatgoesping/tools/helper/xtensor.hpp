
// SPDX-FileCopyrightText: 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#include <xtensor/xcontainer.hpp>

namespace themachinethatgoesping {
    namespace tools {
        namespace helper {

// define a xcontainer concept that works for both xtensor and pytensor
template <typename T>
concept XContainerConcept = std::is_base_of<xt::xcontainer<T>, T>::value;
        }
    }
}