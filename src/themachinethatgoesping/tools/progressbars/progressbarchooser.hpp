// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <variant>

#include "consoleprogressbar.hpp"
#include "noindicator.hpp"
#include "progressindicator.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

enum class t_BuiltInProgressBar
{
  pbar_NoIndicator,
  pbar_Indicator,
  pbar_Classic
} DefaultProgressBarType = t_BuiltInProgressBar::pbar_Indicator;

/**
 * @brief This class allows choosing between different progress bars
 * It will be extended in the future to allow setting the default progressbar using a configuration file
 */
struct ProgressBarChooser : std::variant<NoIndicator, ProgressIndicator, ConsoleProgressBar>
{
    ProgressBarChooser()  = default;
    ProgressBarChooser(bool show_progress)
        : std::variant<NoIndicator, ProgressIndicator, ConsoleProgressBar>()
    {
        if (show_progress)
        {
            switch (DefaultProgressBarType)
            {
                case t_BuiltInProgressBar::pbar_Indicator:
                    this->emplace<ProgressIndicator>();
                    break;
                case t_BuiltInProgressBar::pbar_Classic:
                    this->emplace<ConsoleProgressBar>();
                    break;
                case t_BuiltInProgressBar::pbar_NoIndicator:
                    this->emplace<NoIndicator>();
                    break;
            }
        }
        // else //(variants default is NoIndicator )
        // {
        //     this->emplace<NoIndicator>();
        // }
    }
    ProgressBarChooser(t_BuiltInProgressBar progress_bar_type)
        : std::variant<NoIndicator, ProgressIndicator, ConsoleProgressBar>()
    {
            switch (progress_bar_type)
            {
                case t_BuiltInProgressBar::pbar_Indicator:
                    this->emplace<ProgressIndicator>();
                    break;
                case t_BuiltInProgressBar::pbar_Classic:
                    this->emplace<ConsoleProgressBar>();
                    break;
                case t_BuiltInProgressBar::pbar_NoIndicator:
                    this->emplace<NoIndicator>();
                    break;
            }
    }

    ~ProgressBarChooser() = default;

    /**
     * @brief This is the visitor function that implicitly converts t_ProgressBar to I_ProgressBar (the common interface)
     * 
     * @tparam t_ProgressBar 
     * @param progress_bar ProgressBar class that is derived from I_ProgressBar
     * @return I_ProgressBar& 
     */
    template<typename t_ProgressBar>
    I_ProgressBar& operator()(t_ProgressBar& progress_bar) const
    {
        return progress_bar;
    }

    /**
     * @brief get the ProgressBarInterface
     * 
     * @return I_ProgressBar& 
     */
    I_ProgressBar& get() { return std::visit(ProgressBarChooser{}, *this); }
};

// I_ProgressBar& get(ProgressBar& progress_bar)
// {
//     return std::visit(ProgressBarVisitor{}, progress_bar);
// }

} // namespace progressbars
} // namespace tools
} // namespace themachinethatgoesping
