// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "i_progressbar.hpp"

#include <iostream>
#include <memory>

#include <indicators/block_progress_bar.hpp>
#include <indicators/progress_spinner.hpp>

#include <atomic>
#include <fmt/core.h>

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

// function that locks a mutex and waits for 10ms
void lock_mutex_for_x_ms(std::shared_ptr<std::atomic_bool> skip, size_t x_ms = 100)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(x_ms));
    *skip = false;
}

/**
 * @brief This is a generic (abstract) class for progress bars.
 * Usage: call init() and close() to initialize and finalize the progress bar.
 * Then call set_progress() or tick() to update the progress bar.
 * set_postfix() can be used to set a postfix message. *
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
 *
 */
class I_ProgressBarTimed : public I_ProgressBar
{
    std::shared_ptr<std::atomic_bool> _skip = std::make_shared<std::atomic_bool>(
        false);              ///< atomic (thread safe) boolean to skip the progressbar update
    const size_t _x_ms = 50; ///< time to wait for a new progress update (100ms)

    double      _state_progress  = 0.0; ///< internal state for the skipped progress
    double      _state_increment = 0.0; ///< internal counter for the skipped increments
    std::string _state_postfix   = "";  ///< internal state for the skipped postfix

    bool _initialized = false;

  public:
    // ----- callbacks -----
    /**
     * @brief Initialize a new progressbar within the given range
     *
     * @param first lowest number in the range (typically 0.0)
     * @param last highest number in the range (typically 100.0)
     * @param process_name Name of the progress
     */
    virtual void callback_init(double             first,
                               double             last,
                               const std::string& process_name = "process") = 0;

    /**
     * @brief Finalize the progressbar
     *
     * @param msg A message that can be appended as postfix
     */
    virtual void callback_close(const std::string& msg = "done") = 0;

    /**
     * @brief Increment the progress state by the given amount
     * This callback is guarded a timer (100ms).
     *
     * If skipped, the increment is added to the internal counter and will be applied with the next
     * unskipped call to tick().
     *
     * @param increment Number of steps to increment the progress by
     */
    virtual void callback_tick(double increment = 1) = 0;

    /**
     * @brief Set the progress state to the given value.
     * Note some implementations may require the new_progress to be higher than the current
     * progress!
     *
     * This callback is guarded by a timer (100ms). If skipped, the progress is stored
     * to the internal state and will be applied with the next successful call to set_progress(),
     * tick() or set_postfix().
     *
     * @param new_progress New progress state (within the given first/last range)
     */
    virtual void callback_set_progress(double new_progress) = 0;

    /**
     * @brief Append a postfix message to the progressbar
     *
     * This callback is guarded by a timer (100ms). If skipped, the postfix is stored to
     * the internal state and will be applied with the next successful call to set_progress(),
     * tick() or set_postfix().
     *
     * @param postfix postfix message
     */
    virtual void callback_set_postfix(const std::string& postfix) = 0;

    /**
     * @brief Get the current progress state
     *
     * @return progress state
     */
    virtual double callback_current() const = 0;

  public:
    I_ProgressBarTimed()          = default;
    virtual ~I_ProgressBarTimed() = default;

    bool is_initialized() const override { return _initialized; }

    /**
     * @brief Initialize a new progressbar within the given range
     *
     * @param first lowest number in the range (typically 0.0)
     * @param last highest number in the range (typically 100.0)
     * @param process_name Name of the progress
     */
    void init(double first, double last, const std::string& name = "process") final
    {
        *_skip = false;

        _state_increment = 0.0;
        _state_postfix   = "";
        callback_init(first, last, name);
        _initialized = true;
    }

    /**
     * @brief Finalize the progressbar
     *
     * @param msg A message that can be appended as postfix
     */
    void close(const std::string& msg = "done") final
    {
        // reset state flag (to force apply_state to update)
        *_skip                  = false;
        _check_timer_every_step = 1;
        apply_state();

        callback_close(msg);

        // reset state flags
        *_skip                  = false;
        _check_timer_every_step = 1;
        _initialized            = false;
    }

    /**
     * @brief Increment the progress state by the given amount
     *
     * This function is guarded by a timer. Calls that happen more
     * frequent than 100ms are added to the internal state, but not to the progressbar.
     *
     * @param increment Number of steps to increment the progress by
     */
    void tick(double increment = 1) final
    {
        _state_increment += increment;

        apply_state();
    }

    /**
     * @brief Set the progress state to the given value.
     * Note some implementations may require the new_progress to be higher than the current
     * progress!
     *
     * This function is guarded by a timer. Calls that happen more
     * frequent than 100ms are added to the internal state, but not to the progressbar.
     *
     * @param new_progress New progress state (within the given first/last range)
     */
    void set_progress(double new_progress) final
    {
        _state_increment = 0.0; // call to set_progress always resets previously skipped increments
        _state_progress  = new_progress;

        apply_state();
    }

    /**
     * @brief Append a postfix message to the progressbar
     *
     * This function is guarded a timer. Calls that happen more
     * frequent than 100ms are added to the internal state, but not to the progressbar.
     *
     * @param postfix postfix message
     */
    void set_postfix(const std::string& postfix) final
    {
        _state_postfix = postfix;
        apply_state();
    }

    /**
     * @brief Get the current progress state
     *
     * @return progress state
     */
    double current() const final
    {
        // add skipped increments to the current state of the progressbar
        return callback_current() + _state_increment;
    }

    int _skips                  = 0;
    int _check_timer_every_step = 1;

    /**
     * @brief Apply (call appropriate callback) and reset the internal states to the progress bar
     *
     */
    void apply_state()
    {        
        // heuristics to skip the atomic boolean (next operation)
        // we only check the atomic boolean _check_timer_every_step
        _skips += 1;
        if (_skips % _check_timer_every_step != 0)
            return;

        // this atomic shared boolean is slow, but ensures that the progressbar is updated only once
        // per 100ms
        if (*_skip == true)
            return;

        if (!_initialized)
            throw(std::runtime_error("ERROR: Progressbar was not initialized!"));

        // compute check_every_step as number of steps counted in the last 100ms divided by 20 (~approx every 5 ms)
        _check_timer_every_step = ceil(double(_skips) / 10.0);
        _skips                  = 0;
        // _state_postfix = std::to_string(_check_timer_every_step);

        // reset skip flag
        *_skip = true;
        // start detached mutex timer thread
        std::thread t(lock_mutex_for_x_ms, _skip, _x_ms);
        t.detach();

        if (_state_progress != 0.0)
        {
            callback_set_progress(_state_progress);
            _state_progress = 0.0;
        }

        if (_state_increment != 0.0)
        {
            callback_tick(_state_increment);
            _state_increment = 0.0;
        }

        if (!_state_postfix.empty())
        {
            callback_set_postfix(_state_postfix);
            _state_postfix = "";
        }
    }
    //
};

} // namespace progressbars
} // namespace tools
} // namespace themachinethatgoesping
