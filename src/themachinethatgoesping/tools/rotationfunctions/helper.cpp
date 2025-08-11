#include "rotationfunctions/helper.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace rotationfunctions {

// explicit instantiation definitions
template std::array<float, 3>  normalize_angles_rad<float>(std::array<float, 3>);
template std::array<double, 3> normalize_angles_rad<double>(std::array<double, 3>);

template std::array<float, 3>  normalize_angles_degrees<float>(std::array<float, 3>);
template std::array<double, 3> normalize_angles_degrees<double>(std::array<double, 3>);

template float  compute_heading<float>(float, float, bool);
template double compute_heading<double>(double, double, bool);

} // namespace rotationfunctions
} // namespace tools
} // namespace themachinethatgoesping