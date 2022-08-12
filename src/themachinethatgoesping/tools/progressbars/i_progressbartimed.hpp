// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "i_progressbar.hpp"

#include <iostream>
#include <memory>
#include <mutex>

#include <indicators/block_progress_bar.hpp>
#include <indicators/progress_spinner.hpp>

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

/* terminalPrint observer
 * (uses first, update, last to print status to terminal (as a status bar */
class I_ProgressBarTimed : public I_ProgressBar
{
    double     _first = 0.0;
    std::mutex timer_mutex;

  protected:
    virtual void callback_init(double             first,
                               double             last,
                               const std::string& process_name = "process") = 0;
    virtual void callback_close(const std::string& msg = "done")            = 0;

    virtual void callback_tick(double increment = 1)              = 0; // increments current status
    virtual void callback_set_progress(double new_progress)       = 0;
    virtual void callback_set_postfix(const std::string& postfix) = 0;

    virtual double callback_current() const = 0;

  public:
    I_ProgressBarTimed()          = default;
    virtual ~I_ProgressBarTimed() = default;

    void init(double first, double last, const std::string& name = "process") final
    {
        callback_init(first, last, name);
    }

    void close(const std::string& msg = "done") final { callback_close(msg); }

    void set_progress(double new_progress) final
    {
        std::lock_guard<std::mutex> timer_lock(timer_mutex);
        callback_set_progress(new_progress);
    }
    void set_postfix(const std::string& postfix) final { callback_set_postfix(postfix); }

    void tick(double increment = 1) override { callback_tick(increment); }

    double current() const override { return callback_current(); }

    private:
    static void lock_timer(std::lock_guard<std::mutex>&& timer_mutex)
    {
    }
};

}
}
}
