// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/i_progressbartimed.doc.hpp"

#include "i_progressbar.hpp"

#include <atomic>
#include <memory>
#include <string>
// Optional heavy includes moved to cpp to keep header light
// #include <iostream>
// #include <indicators/block_progress_bar.hpp>
// #include <indicators/progress_spinner.hpp>
// #include <fmt/core.h>

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

/**
 * @brief This is a generic (abstract) class for progress bars.
 * Usage: call init() and close() to initialize and finalize the progress bar.
 * Then call set_progress() or tick() to update the progress bar.
 * set_postfix() can be used to set a postfix message.
 *
 * The above name functions are guarded by a timer (100ms).
 * The timer is started when calling set_progress() or tick().
 * Repetitively calling of these functions (in a loop) will update the internal state but not
 * update the progress bar until the timer (100ms) expires.
 *
 * This ensures a low overhead even for slow progressbar implementations.
 *
 * All functions are thread-safe.
 *
 * To implement this interface the abstract callback_ functions must be implemented.
 */
class I_ProgressBarTimed : public I_ProgressBar
{
    std::shared_ptr<std::atomic_bool> _skip = std::make_shared<std::atomic_bool>(false);
    const size_t _x_ms = 50; // time to wait for a new progress update (ms)

    double      _state_progress  = 0.0;
    double      _state_increment = 0.0;
    std::string _state_postfix   = "";
    std::string _state_prefix    = "";

    int _skips                  = 0;
    int _check_timer_every_step = 1;
    int _max_skips              = 100; // set to ~0.1% of total progress in init()

    bool _is_initialized = false;

  public:
    // ----- callbacks to be implemented by concrete progress bars -----
    virtual void callback_init(double first, double last, const std::string& process_name = "process") = 0;
    virtual void callback_close(const std::string& msg = "done") = 0;
    virtual void callback_tick(double increment = 1) = 0;
    virtual void callback_set_progress(double new_progress) = 0;
    virtual void callback_set_prefix(const std::string& prefix) = 0;
    virtual void callback_set_postfix(const std::string& postfix) = 0;
    virtual double callback_current() const = 0;

  public:
    I_ProgressBarTimed() = default;
    virtual ~I_ProgressBarTimed() = default;

    // ----- I_ProgressBar interface (definitions moved to .cpp) -----
    bool is_initialized() const override;

    void init(double first, double last, const std::string& name = "process") final;
    void close(const std::string& msg = "done") final;

    void tick(double increment = 1) final;
    void set_progress(double new_progress) final;

    void set_postfix(const std::string& postfix) final;
    void set_prefix(const std::string& prefix) final;

    double current() const final;

    // Apply internal buffered state to the underlying progress bar (definition moved to .cpp)
    void apply_state();
};

} // namespace progressbars
} // namespace tools
} // namespace themachinethatgoesping
