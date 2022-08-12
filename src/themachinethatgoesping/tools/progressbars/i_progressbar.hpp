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
 *  - set_progress() - updates the status
 *  - close() - process is finished
 *
 * additional:
 *  - increment: increments the status by a given value
 *  -
 *
 **************************************************************************************************/
#pragma once
#include <memory>
#include <string>

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

class I_ProgressBar
{
  public:
    I_ProgressBar() = default;
    virtual ~I_ProgressBar() = default;

    virtual void init(double             first,
                      double             last,
                      const std::string& process_name = "process") = 0;
    virtual void close(const std::string& msg = "done") = 0;

    virtual void tick(double increment = 1) = 0; // increments current status
    virtual void set_progress(double new_progress) = 0;
    virtual void set_postfix(const std::string& postfix) = 0;

    virtual double current() const = 0;
};

}
}
}
