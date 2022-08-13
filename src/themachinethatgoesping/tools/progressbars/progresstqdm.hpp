// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "i_progressbartimed.hpp"

#include <iostream>
#include <memory>
#include <thread>

#include <pybind11/pybind11.h>

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

/* terminalPrint observer
 * (uses first, update, last to print status to terminal (as a status bar */
class ProgressTqdm : public I_ProgressBarTimed, public pybind11::object
{
    double _first = 0;

  public:
    ProgressTqdm(pybind11::object& tqdm)
    : pybind11::object(tqdm)
    {
    }
    ~ProgressTqdm() = default;

  private:
    void callback_init(double first, double last, const std::string& name = "process") override
    {
        _first = first;
        attr("set_description")(name);
        attr("reset")(last-first);
    }

    void callback_close(const std::string& msg = "done") override
    {
        attr("set_postfix_str")("[" + msg + "]");
        attr("close")();
    }

    void callback_set_progress(double new_progress) override
    {
        double increment = new_progress - _first - pybind11::cast<double>(attr("n")());
        attr("update")(increment);
    }
    void callback_set_postfix(const std::string& postfix) override
    {
        attr("set_postfix_str")("[" + postfix + "]");
    }

    void callback_tick(double increment = 1) override
    {
        attr("update")(increment);
    }

    double callback_current() const override { return pybind11::cast<double>(attr("n")()); }
};

}
}
}
