// SPDX-FileCopyrightText: Peter Urban, 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/consoleprogressbar.doc.hpp"

#include "i_progressbartimed.hpp"
#include <iostream>
#include <string>

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

/**
 * @brief Old-school progress bar that prints to terminal. For reference only, might be removed in
 * the future.
 *
 * This class is based in I_ProgressBarTimed such that the callbacks are guarded by a timer.
 */
class ConsoleProgressBar : public I_ProgressBarTimed
{
    std::ostream& _os; ///< output stream

    // internal state
    double       _first;       ///< starting value
    double       _last;        ///< ending value
    double       _current;     ///< current value
    unsigned int _currentStep; ///< step (step "/" of _numOf_steps)

    const unsigned int _numOf_steps = 50; ///< steps till 100% (equals linesize)

    bool _is_initialized = false; ///< flag to control if the progressbar is is_initialized

  public:
    explicit ConsoleProgressBar(std::ostream& os = std::cout);

  private:
    // ----- I_ProgressBarTimed interface -----
    void callback_init(double first, double last, const std::string& name = "process") override;
    void callback_close(const std::string& msg = "done") override;
    void callback_set_progress(double new_progress) override;
    void callback_set_postfix([[maybe_unused]] const std::string& postfix) override;
    void callback_set_prefix([[maybe_unused]] const std::string& prefix) override;
    void callback_tick(double increment = 1) override;
    double callback_current() const override;
};

} // namespace progressbars
} // namespace tools
} // namespace themachinethatgoesping
