
// hash functions for xtensor

// #if defined(__x86_64__) || defined(_M_X64)
// #else
// #define _MM_PERM_ENUM int
// #endif
#include <xxhash.hpp>
#include "xtensor.hpp"

namespace xt {

/**
 * @brief Boost hash function for xt tensors
 *
 * @tparam T
 * @param array
 * @return std::size_t
 */
template<themachinethatgoesping::tools::helper::c_xtensor t_xtensor>
std::size_t hash_value(const t_xtensor& array)
{
    return xxh::xxhash3<64>(
        array.data(),
        array.size() *
            sizeof(
                typename themachinethatgoesping::tools::helper::xtensor_datatype<t_xtensor>::type));
}


}