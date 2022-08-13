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

#include <atomic>
#include <fmt/core.h>

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {


// function that locks a mutex and waits for 10ms
void lock_mutex_for_x_ms(std::atomic_bool& skip, size_t x_ms = 100)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(x_ms));
    skip = false;
}

/* terminalPrint observer
 * (uses first, update, last to print status to terminal (as a status bar */
class I_ProgressBarTimed : public I_ProgressBar
{
    double             _first = 0.0;
    mutable std::mutex _mutex;
    const double       _x_ms = 100;
    std::atomic_bool   _skip = false;

    double      _skipped_increment = 0.0;
    std::string _skipped_postfix   = "";

  public:
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
        // lock mutex (no timing)
        std::unique_lock<std::mutex> lock(_mutex);

        _skip       = false;

        _skipped_increment = 0.0;
        _skipped_postfix   = "";
        callback_init(first, last, name);
    }

    void close(const std::string& msg = "done") final
    {
        // lock mutex (no timing)
        std::unique_lock<std::mutex> lock2(_mutex);

        _skip       = false;

        apply_skipped();
        callback_close(msg);
    }

    void set_progress(double new_progress) final
    {
        std::unique_lock<std::mutex> lock(_mutex);

        // try to unlock mutex.
        if (!_skip)
        {
            _skip = true;
            // start detached mutex timer thread
            std::thread t(lock_mutex_for_x_ms, std::ref(_skip), _x_ms);
            t.detach();

            // callback
            callback_set_progress(new_progress);
            _skipped_increment = 0.0;
            apply_skipped();
        }
    }

    void set_postfix(const std::string& postfix) final
    {
        std::unique_lock<std::mutex> lock(_mutex);

        // try to unlock mutex.
        if (!_skip)
        {
            _skip = true;
            // start detached mutex timer thread
            std::thread t(lock_mutex_for_x_ms, std::ref(_skip), _x_ms);
            t.detach();

            // callback
            callback_set_postfix(postfix);
            _skipped_postfix = "";
            apply_skipped();
        }
        else
        {
            _skipped_postfix = postfix;
        }
    }

    void tick(double increment = 1) final
    {
        std::unique_lock<std::mutex> lock(_mutex);

        // try to unlock mutex.
        if (!_skip)
        {
            _skip = true;
            // start detached mutex timer thread
            std::thread t(lock_mutex_for_x_ms, std::ref(_skip), _x_ms);
            t.detach();

            // callback
            callback_tick(increment + _skipped_increment);
            _skipped_increment = 0.0;
            apply_skipped();
        }
        else
        {
            _skipped_increment += increment;
        }
    }

    double current() const final
    {
        std::unique_lock<std::mutex> lock(_mutex);
        return callback_current() + _skipped_increment;
    }

  private:
    void apply_skipped()
    {
        if (!_skipped_postfix.empty())
        {
            callback_set_postfix(_skipped_postfix);
            _skipped_postfix = "";
        }

        if (_skipped_increment != 0.0)
        {
            callback_tick(_skipped_increment);
            _skipped_increment = 0.0;
        }
    }
    //
};

} // namespace progressbars
} // namespace tools
} // namespace themachinethatgoesping
