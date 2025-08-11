// SPDX-License-Identifier: MPL-2.0

#include "noindicator.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

NoIndicator::NoIndicator() = default;

bool NoIndicator::is_initialized() const
{
    return _is_initialized;
}

void NoIndicator::init([[maybe_unused]] double first,
                       [[maybe_unused]] double last,
                       [[maybe_unused]] const std::string& name)
{
    _is_initialized = true;
}

void NoIndicator::close([[maybe_unused]] const std::string& msg)
{
    _is_initialized = false;
}

void NoIndicator::set_progress([[maybe_unused]] double new_progress) {}

void NoIndicator::set_postfix([[maybe_unused]] const std::string& postfix) {}

void NoIndicator::set_prefix([[maybe_unused]] const std::string& prefix) {}

void NoIndicator::tick([[maybe_unused]] double increment) {}

double NoIndicator::current() const
{
    return 0.0;
}

} // namespace progressbars
} // namespace tools
} // namespace themachinethatgoesping
