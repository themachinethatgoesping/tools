// SPDX-FileCopyrightText: Peter Urban, 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "i_progressbar.hpp"
#include <iostream>

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

/* terminalPrint observer
 * (uses start, update, end to print status to terminal (as a status bar */
class ConsoleStatusBar : public I_ProgressBar
{
    std::ostream& _os;

    double       _start;       // starting value
    double       _end;         // ending value
    double       _current;     // current value
    unsigned int _currentStep; // step (step "/" of _numOf_steps)

    const unsigned int _numOf_steps = 50; // steps till 100% (equals linesize)

    bool _started = false; // is status actively running or not flag

  public:
    ConsoleStatusBar(std::ostream& os = std::cerr)
        : _os(os)
    {
    }

    void start(double start, double end, const std::string& name = "process")
    {
        /* check if _started already */
        if (_started)
            throw(std::runtime_error("ERROR[ConsoleStatusBar]: Can't start StatusBar! StatusBar is already _started!"));

        /* check conditions */
        if (start > end)
            throw(std::runtime_error(
                "ERROR[ConsoleStatusBar]: end !> start! [" +
                std::to_string(end) + " !> " + std::to_string(start) + "]"));

        _start       = start;
        _end         = end;
        _current     = start;
        _started      = true;
        _currentStep = 0;

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

    void end(const std::string& msg = "done")
    {
        /* check if _started already */
        if (!_started)
            throw(std::runtime_error("ERROR[DSMToolsLib::Status::ConsoleStatusBar::end))]: Can't "
                                     "stop StatusBar! StatusBar is not _started yet!"));

        for (unsigned int i = 1; i < _numOf_steps - _currentStep; i++)
            _os << "\\" << std::flush;

        _os << "| [ " << msg << " ]" << std::endl;

        _started = false;
    }

    void update(double newStatus)
    {
        /* check if _started already */
        if (!_started)
            throw(std::runtime_error("ERROR[DSMToolsLib::Status::ConsoleStatusBar::update))]: Not "
                                     "possible to call update! StatusBar is not _started yet!"));

        if (newStatus < _current)
            // throw(std::runtime_error("ERROR[DSMToolsLib::Status::ConsoleStatusBar::update]: new
            // status is less than old status! [" + std::to_string(newStatus) + " < " +
            // std::to_string(_current) + "]"));
            std::cerr << "WARNING[DSMToolsLib::Status::ConsoleStatusBar::update]: new status is less "
                    "than old status! [" +
                        std::to_string(newStatus) + " < " + std::to_string(_current) + "]"
                 << std::endl;

        if (newStatus > _end)
            // throw(std::runtime_error("ERROR[DSMToolsLib::Status::ConsoleStatusBar::update]:
            // statusOverflow! \n\t- current status :" + std::to_string(newStatus) + "\n\t- end
            // status: " + std::to_string(_end) + "]"));
            std::cerr << "ERROR[DSMToolsLib::Status::ConsoleStatusBar::update]: statusOverflow! \n\t- "
                    "current status :" +
                        std::to_string(newStatus) + "\n\t- end status: " + std::to_string(_end) +
                        "]"
                 << std::endl;

        _current = newStatus;

        unsigned int status_steps = (unsigned int)std::round(((double)_numOf_steps - 1) *
                                                             (_current - _start) / (_end - _start));

        while (_currentStep < status_steps)
        {
            _currentStep++;
            _os << "/" << std::flush;
        }
    }

    void increment(double increment = 1) { update(_current + increment_); }

    double get_currentStatus() { return _current; }
};

}
}
}
