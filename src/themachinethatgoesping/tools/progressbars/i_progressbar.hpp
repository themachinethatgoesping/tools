// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**************************************************************************************************
 *
 * ProcessStatus interface class
 *
 * interface to status bars using three simple functions
 *  - start() - starts the status bar
 *  - update() - updates the status
 *  - end() - process is finished
 *
 * additional:
 *  - increment: increments the status by a given value
 *  -
 *
**************************************************************************************************/
#pragma once
#include <string>
#include <memory>

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

class I_ProgressBar
{
public:
    I_ProgressBar(){}
    virtual ~I_ProgressBar(){}

    virtual void update(double newStatus) = 0;
    virtual void increment(double increment = 1) = 0;   //increments current status

    virtual void start(double start, double end, const std::string& process_name = "process") = 0;
    virtual void end(const std::string& msg = "done") = 0;

    virtual double get_currentStatus() = 0;
};


typedef std::shared_ptr<I_ProgressBar> I_ProgressBar_ptr;

}
}
}
