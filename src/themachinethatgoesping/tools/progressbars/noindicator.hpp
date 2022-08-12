// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "i_progressbar.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

/* noIndicator observer
 * (uses start, update, end to print status to terminal (as a status bar */
class NoIndicator : public I_ProgressBar
{
  public:
    NoIndicator() = default;

    void init([[maybe_unused]] double             first,
              [[maybe_unused]] double             last,
              [[maybe_unused]] const std::string& name = "process") override
    {
    }

    void close([[maybe_unused]] const std::string& msg = "done") override {}

    void set_progress([[maybe_unused]] double new_progress) override { (void)new_progress; }
    void set_postfix([[maybe_unused]] const std::string& postfix) override{};

    void tick([[maybe_unused]] double increment = 1) override {}

    double current() const override { return 0; }
};

}
}
}
