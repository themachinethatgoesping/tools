// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/noindicator.doc.hpp"

#include "i_progressbar.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

/**
 * @brief A progress bar that does not show any progress and has nearly no overhead.
 *
 */
class NoIndicator : public I_ProgressBar
{
    bool _is_initialized = false;

  public:
    NoIndicator() = default;

    // ----- I_ProgressBar interface -----
    // (all functions simply do nothing)
    bool is_initialized() const override { return _is_initialized; }

    void init([[maybe_unused]] double             first,
              [[maybe_unused]] double             last,
              [[maybe_unused]] const std::string& name = "process") override
    {
        _is_initialized = true;
    }

    void close([[maybe_unused]] const std::string& msg = "done") override { _is_initialized = false; }

    void set_progress([[maybe_unused]] double new_progress) override {}
    void set_postfix([[maybe_unused]] const std::string& postfix) override{};
    void set_prefix([[maybe_unused]] const std::string& prefix) override{};

    void tick([[maybe_unused]] double increment = 1) override {}

    double current() const override { return 0; }
};

}
}
}
