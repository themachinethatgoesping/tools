// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/progressindicator.doc.hpp"

#include "i_progressbartimed.hpp"

#include <memory>

// Include the concrete type to make it complete for unique_ptr destructor
#include <indicators/progress_spinner.hpp> // added

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

/**
 * @brief Text based ProgressBar that uses the indicators library.
 * (https://github.com/p-ranav/indicators)
 *
 * This class is based in I_ProgressBarTimed such that the callbacks are guarded by a timer.
 */
class ProgressIndicator : public I_ProgressBarTimed
{
    double _first = 0.0; // first value of the progressbar range

    std::unique_ptr<indicators::ProgressSpinner> _indicator; // indicator implementation

  public:
    ProgressIndicator() = default;
    ~ProgressIndicator(); // defined in .cpp

  private:
    // ----- I_ProgressBarTimed interface -----
    void   callback_init(double first, double last, const std::string& name = "process") override;
    void   callback_close(const std::string& msg = "done") override;
    void   callback_set_progress(double new_progress) override;
    void   callback_set_postfix(const std::string& postfix) override;
    void   callback_set_prefix(const std::string& prefix) override;
    void   callback_tick(double increment = 1) override;
    double callback_current() const override;
};

} // namespace progressbars
} // namespace tools
} // namespace themachinethatgoesping
