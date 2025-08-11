// SPDX-License-Identifier: MPL-2.0

#include "i_progressbartimed.hpp"

#include <chrono>
#include <cmath>
#include <stdexcept>
#include <thread>

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

namespace {
// internal helper: waits x_ms and clears the skip flag
inline void lock_mutex_for_x_ms(const std::shared_ptr<std::atomic_bool>& skip, size_t x_ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(x_ms));
    *skip = false;
}
} // namespace

bool I_ProgressBarTimed::is_initialized() const
{
    return _is_initialized;
}

void I_ProgressBarTimed::init(double first, double last, const std::string& name)
{
    *_skip = false;

    _max_skips = static_cast<int>((last - first) / 1000.0);
    if (_max_skips < 1)
        _max_skips = 1;

    _state_increment = 0.0;
    _state_postfix   = "";
    _state_prefix    = "";
    callback_init(first, last, name);
    _is_initialized = true;
}

void I_ProgressBarTimed::close(const std::string& msg)
{
    // force last apply
    *_skip                  = false;
    _check_timer_every_step = 1;
    apply_state();

    callback_close(msg);

    // reset state flags
    *_skip                  = false;
    _check_timer_every_step = 1;
    _is_initialized         = false;
}

void I_ProgressBarTimed::tick(double increment)
{
    _state_increment += increment;
    apply_state();
}

void I_ProgressBarTimed::set_progress(double new_progress)
{
    // call to set_progress always resets previously skipped increments
    _state_increment = 0.0;
    _state_progress  = new_progress;
    apply_state();
}

void I_ProgressBarTimed::set_postfix(const std::string& postfix)
{
    _state_postfix = postfix;
    apply_state();
}

void I_ProgressBarTimed::set_prefix(const std::string& prefix)
{
    _state_prefix = prefix;
    apply_state();
}

double I_ProgressBarTimed::current() const
{
    // add skipped increments to the current state of the progressbar
    return callback_current() + _state_increment;
}

void I_ProgressBarTimed::apply_state()
{
    // heuristics to skip the atomic boolean check: only check every n-th call
    _skips += 1;
    if (_skips % _check_timer_every_step != 0)
        return;

    // single update per time slice
    if (*_skip)
        return;

    if (!_is_initialized)
        throw std::runtime_error("ERROR: Progressbar was not initialized!");

    // compute check_every_step as number of steps counted in the last 100ms divided by ~10
    _check_timer_every_step = static_cast<int>(std::ceil(double(_skips) / 10.0));
    if (_check_timer_every_step > _max_skips)
        _check_timer_every_step = _max_skips;
    _skips = 0;

    // set skip and arm timer
    *_skip = true;
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

    if (!_state_prefix.empty())
    {
        callback_set_prefix(_state_prefix);
        _state_prefix = "";
    }
}

} // namespace progressbars
} // namespace tools
} // namespace themachinethatgoesping