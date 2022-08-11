// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "i_progressbar.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

/* noStatus observer
 * (uses start, update, end to print status to terminal (as a status bar */
class NoStatus : public I_ProgressBar
{
    public:
    noStatus() = default;

    void start(double start, double end, const std::string& name = "process")
    {
        (void)start;
        (void)end;
        (void)name;
    }

    void end(const std::string& msg = "done") { (void)msg; }

    void update(double newStatus) { (void)newStatus; }

    void increment(double increment = 1)
    {
        (void)increment;
    }

    double get_currentStatus() { return 0; }
};

}
}
}
