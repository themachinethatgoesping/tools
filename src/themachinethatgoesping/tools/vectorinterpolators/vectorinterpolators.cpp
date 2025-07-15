// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
// Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

// This file provides explicit instantiations of common interpolators
// The instantiations are marked extern in the interpolator headers to avoid instantiation with header inclusion for these types

#include "akimainterpolator.hpp"
#include "linearinterpolator.hpp"
#include "nearestinterpolator.hpp"
#include "slerpinterpolator.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace vectorinterpolators {

// Explicit template instantiations for AkimaInterpolator
template class AkimaInterpolator<float>;
template class AkimaInterpolator<double>;

// Explicit template instantiations for LinearInterpolator
template class LinearInterpolator<float, float>;
template class LinearInterpolator<double, double>;
template class LinearInterpolator<float, double>;
template class LinearInterpolator<double, float>;

// Explicit template instantiations for NearestInterpolator
template class NearestInterpolator<float, float>;
template class NearestInterpolator<double, double>;
template class NearestInterpolator<float, double>;
template class NearestInterpolator<double, float>;

template class NearestInterpolator<float, uint8_t>;
template class NearestInterpolator<float, int8_t>;
template class NearestInterpolator<double, uint8_t>;
template class NearestInterpolator<double, int8_t>;
template class NearestInterpolator<float, uint16_t>;
template class NearestInterpolator<float, int16_t>;
template class NearestInterpolator<double, uint16_t>;
template class NearestInterpolator<double, int16_t>;
template class NearestInterpolator<float, uint32_t>;
template class NearestInterpolator<float, int32_t>;
template class NearestInterpolator<double, uint32_t>;
template class NearestInterpolator<double, int32_t>;
template class NearestInterpolator<float, uint64_t>;
template class NearestInterpolator<float, int64_t>;
template class NearestInterpolator<double, uint64_t>;
template class NearestInterpolator<double, int64_t>;

template class SlerpInterpolator<float, float>;
template class SlerpInterpolator<double, double>;
template class SlerpInterpolator<float, double>;
template class SlerpInterpolator<double, float>;
}
}
}