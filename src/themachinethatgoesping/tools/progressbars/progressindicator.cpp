// SPDX-License-Identifier: MPL-2.0

#include "progressindicator.hpp"

#include <cmath>
#include <string>
#include <vector>

#include <indicators/block_progress_bar.hpp>
#include <indicators/progress_spinner.hpp>

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

ProgressIndicator::~ProgressIndicator() = default;

void ProgressIndicator::callback_init(double first, double last, const std::string& name)
{
    _first = first;

    _indicator = std::make_unique<indicators::ProgressSpinner>();
    // _indicator = std::make_unique<indicators::BlockProgressBar>();

    _indicator->set_option(indicators::option::SpinnerStates{
        std::vector<std::string>{ "⠈", "⠐", "⠠", "⢀", "⡀", "⠄", "⠂", "⠁" } });

    _indicator->set_option(indicators::option::ForegroundColor{ indicators::Color::yellow });
    _indicator->set_option(indicators::option::FontStyles{
        std::vector<indicators::FontStyle>{ indicators::FontStyle::bold } });

    _indicator->set_option(indicators::option::ShowPercentage{ true });
    _indicator->set_option(indicators::option::ShowElapsedTime{ true });
    _indicator->set_option(indicators::option::ShowRemainingTime{ true });

    _indicator->set_option(indicators::option::PrefixText{ name + " " });
    _indicator->set_option(indicators::option::MaxProgress{
        static_cast<size_t>(std::ceil(last - first)) });
}

void ProgressIndicator::callback_close(const std::string& msg)
{
    _indicator->set_option(indicators::option::PostfixText{ "[" + msg + "]" });
    _indicator->mark_as_completed();
}

void ProgressIndicator::callback_set_progress(double new_progress)
{
    _indicator->set_progress(static_cast<size_t>(new_progress - _first));
}

void ProgressIndicator::callback_set_postfix(const std::string& postfix)
{
    _indicator->set_option(indicators::option::PostfixText{ "[" + postfix + "]" });
    _indicator->set_progress(_indicator->current());
}

void ProgressIndicator::callback_set_prefix(const std::string& prefix)
{
    _indicator->set_option(indicators::option::PrefixText{ prefix + " " });
    _indicator->set_progress(_indicator->current());
}

void ProgressIndicator::callback_tick(double increment)
{
    callback_set_progress(static_cast<double>(_indicator->current()) + increment);
}

double ProgressIndicator::callback_current() const
{
    return static_cast<double>(_indicator->current());
}

} // namespace progressbars
} // namespace tools
} // namespace themachinethatgoesping
