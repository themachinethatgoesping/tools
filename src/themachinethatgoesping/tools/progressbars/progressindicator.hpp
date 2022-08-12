// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "i_progressbartimed.hpp"

#include <iostream>
#include <memory>
#include <thread>

#include <indicators/block_progress_bar.hpp>
#include <indicators/progress_spinner.hpp>

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

/* terminalPrint observer
 * (uses first, update, last to print status to terminal (as a status bar */
class ProgressIndicator : public I_ProgressBarTimed
{
    std::string _name;
    double      _first = 0.0;
    double      _last  = 0.0;

    std::unique_ptr<indicators::ProgressSpinner> _indicator;
    // std::unique_ptr<indicators::BlockProgressBar> _indicator;

  public:
    ProgressIndicator()  = default;
    ~ProgressIndicator() = default;

  private:
    void callback_init(double first, double last, const std::string& name = "process") override
    {
        _name  = name;
        _first = _first;
        _last  = _last;

        _indicator = std::make_unique<indicators::ProgressSpinner>();
        //_indicator = std::make_unique<indicators::BlockProgressBar>();

        //_indicator->set_option(indicators::option::BarWidth{ 20 });
        _indicator->set_option(indicators::option::SpinnerStates{
            std::vector<std::string>{"⠈", "⠐", "⠠", "⢀", "⡀", "⠄", "⠂", "⠁"}
        });

        _indicator->set_option(indicators::option::ForegroundColor{ indicators::Color::yellow });

        _indicator->set_option(indicators::option::FontStyles{
            std::vector<indicators::FontStyle>{ indicators::FontStyle::bold } });

        _indicator->set_option(indicators::option::ShowPercentage{ true });
        _indicator->set_option(indicators::option::ShowElapsedTime{ true });
        _indicator->set_option(indicators::option::ShowRemainingTime{ true });

        _indicator->set_option(indicators::option::PrefixText{ name + " " });
        //_indicator->set_option(indicators::option::PostfixText{ name });
        _indicator->set_option(indicators::option::MaxProgress{ last - first });
    }

    void callback_close(const std::string& msg = "done") override
    {
        _indicator->set_option(indicators::option::PostfixText{ "[" + msg + "]" });
        _indicator->mark_as_completed();
    }

    void callback_set_progress(double new_progress) override
    {
        _indicator->set_progress(new_progress - _first);
    }
    void callback_set_postfix(const std::string& postfix) override
    {
        _indicator->set_option(indicators::option::PostfixText{ "[" + postfix + "]" });
    }

    void callback_tick(double increment = 1) override
    {
        callback_set_progress(_indicator->current() + increment);
    }

    double callback_current() const override { return _indicator->current(); }
};

}
}
}
