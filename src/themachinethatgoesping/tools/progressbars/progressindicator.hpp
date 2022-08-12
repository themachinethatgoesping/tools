// SPDX-FileCopyrightText: Peter Urban, 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "i_progressbar.hpp"

#include <iostream>

#include <indicators/progress_spinner.hpp>

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

/* terminalPrint observer
 * (uses first, update, last to print status to terminal (as a status bar */
class ProgressIndicator : public I_ProgressBar
{
    indicators::ProgressSpinner _spinner{ indicators::option::PostfixText{ "peter" },
              indicators::option::ForegroundColor{ indicators::Color::yellow },
              indicators::option::SpinnerStates{
                  std::vector<std::string>{ "⠈", "⠐", "⠠", "⢀", "⡀", "⠄", "⠂", "⠁" } },
              indicators::option::FontStyles{ std::vector<indicators::FontStyle>{ indicators::FontStyle::bold } } };

  public:
    ProgressIndicator() {}

    void init([[maybe_unused]] double first, [[maybe_unused]] double last, const std::string& name = "process") override
    {
        // _spinner = indicators::ProgressSpinner(
        //     { indicators::option::PostfixText{ name },
        //       indicators::option::ForegroundColor{ indicators::Color::yellow },
        //       indicators::option::SpinnerStates{
        //           std::vector<std::string>{ "⠈", "⠐", "⠠", "⢀", "⡀", "⠄", "⠂", "⠁" } },
        //       indicators::option::FontStyles{ std::vector<indicators::FontStyle>{ indicators::FontStyle::bold } } };
    }

    void close([[maybe_unused]] const std::string& msg = "done") override { _spinner.mark_as_completed(); }

    void set_progress(double new_progress) override { _spinner.set_progress(new_progress); }
    void set_postfix(const std::string& postfix) override
    {
        _spinner.set_option(indicators::option::PostfixText{postfix});
    }

    void tick([[maybe_unused]] double increment = 1) override { _spinner.tick(); }

    double get_current_progress() const override { return 0; }
};

}
}
}
