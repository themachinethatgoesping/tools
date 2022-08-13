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
class ProgressTqdm : public I_ProgressBarTimed
{
    pybind11::module_ m = pybind11::module_::import("tqdm.auto");  // like 'import os.path as path'
    pybind11::object  _tqdm;

    double _first = 0;

  public:
    ProgressTqdm()
    {
        _tqdm = m.attr("tqdm")(pybind11::arg("leave") = false);
    }
    ~ProgressTqdm() = default;

  private:
    void callback_init(double first, double last, const std::string& name = "process") override
    {
        _first = first;
        _tqdm.attr("set_description")(name);
        _tqdm.attr("set_total")(last-first);
    }

    void callback_close(const std::string& msg = "done") override
    {
        _tqdm.attr("close")();
    }

    void callback_set_progress(double new_progress) override
    {
    }
    void callback_set_postfix(const std::string& postfix) override
    {
    }

    void callback_tick(double increment = 1) override
    {
    }

    double callback_current() const override { return 0; }
};

}
}
}
