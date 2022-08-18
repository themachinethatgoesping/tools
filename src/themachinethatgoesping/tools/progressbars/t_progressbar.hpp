// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <variant>

#include "noindicator.hpp"
#include "progressindicator.hpp"
#include "consoleprogressbar.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

using ProgressBar = std::variant<NoIndicator, ProgressIndicator, ConsoleProgressBar>;

struct ProgressBarVisitor
{
    template<typename t_ProgressBar>
    I_ProgressBar& operator()(t_ProgressBar& progress_bar) const
    {
        return progress_bar;
    }
};

I_ProgressBar& get_progress_bar(ProgressBar& progress_bar)
{
    return std::visit(ProgressBarVisitor{}, progress_bar);
}


} // namespace progressbars
} // namespace tools
} // namespace themachinethatgoesping
