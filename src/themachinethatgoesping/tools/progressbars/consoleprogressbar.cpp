// SPDX-License-Identifier: MPL-2.0

#include "consoleprogressbar.hpp"

#include <cmath>
#include <stdexcept>
#include <string>

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

ConsoleProgressBar::ConsoleProgressBar(std::ostream& os)
    : _os(os)
{
}

void ConsoleProgressBar::callback_init(double first, double last, const std::string& name)
{
    // check if initialized already
    if (_is_initialized)
        I_ProgressBarTimed::close();

    // check conditions
    if (first > last)
        throw std::runtime_error("ERROR[ConsoleProgressBar]: last !> first! [" +
                                 std::to_string(last) + " !> " + std::to_string(first) + "]");

    _first         = first;
    _last          = last;
    _current       = first;
    _is_initialized = true;
    _currentStep   = 0;

    std::string out;
    std::string prc          = "... " + name + " ... ";
    std::string prc_progress = "                                             100%|";
    std::string progress     = "\n0%                    50%                    100%|";

    if (prc.size() < 45)
        out = prc_progress.replace(0, prc.size(), prc);
    else
        out = prc + progress;

    _os << out << "\n" << std::flush;
}

void ConsoleProgressBar::callback_close(const std::string& msg)
{
    if (!_is_initialized)
        throw std::runtime_error(
            "ERROR[DSMToolsLib::Status::ConsoleProgressBar::last))]: Can't stop StatusBar! "
            "StatusBar is not _is_initialized yet!");

    for (unsigned int i = 1; i < _numOf_steps - _currentStep; i++)
        _os << "\\" << std::flush;

    _os << "| [ " << msg << " ]" << std::endl;

    _is_initialized = false;
}

void ConsoleProgressBar::callback_set_progress(double new_progress)
{
    if (!_is_initialized)
        throw std::runtime_error(
            "ERROR[DSMToolsLib::Status::ConsoleProgressBar::update))]: Not possible to call "
            "update! StatusBar is not _is_initialized yet!");

    if (new_progress < _current)
        std::cerr << "WARNING[DSMToolsLib::Status::ConsoleProgressBar::update]: new status is less "
                     "than old status! [" +
                         std::to_string(new_progress) + " < " + std::to_string(_current) + "]"
                  << std::endl;

    if (new_progress > _last)
        std::cerr << "ERROR[DSMToolsLib::Status::ConsoleProgressBar::update]: statusOverflow! "
                     "\n\t- current status :" +
                         std::to_string(new_progress) + "\n\t- last status: " +
                         std::to_string(_last) + "]"
                  << std::endl;

    _current = new_progress;

    unsigned int status_steps = static_cast<unsigned int>(std::round(
        (static_cast<double>(_numOf_steps) - 1.0) * (_current - _first) / (_last - _first)));

    while (_currentStep < status_steps)
    {
        _currentStep++;
        _os << "/" << std::flush;
    }
}

void ConsoleProgressBar::callback_set_postfix([[maybe_unused]] const std::string& postfix) {}

void ConsoleProgressBar::callback_set_prefix([[maybe_unused]] const std::string& prefix) {}

void ConsoleProgressBar::callback_tick(double increment)
{
    callback_set_progress(_current + increment);
}

double ConsoleProgressBar::callback_current() const
{
    return _current;
}

} // namespace progressbars
} // namespace tools
} // namespace themachinethatgoesping