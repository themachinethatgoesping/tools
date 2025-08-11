// SPDX-License-Identifier: MPL-2.0

#include "progressbarchooser.hpp"

#include <stdexcept>
#include <memory>

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

ProgressBarChooser::ProgressBarChooser() = default;

ProgressBarChooser::ProgressBarChooser(bool show_progress)
{
    static const auto DefaultProgressBarType = t_BuiltInProgressBar::pbar_Indicator;

    if (show_progress)
    {
        switch (DefaultProgressBarType)
        {
            case t_BuiltInProgressBar::pbar_Indicator:
                builtin_progress_bar.emplace<ProgressIndicator>();
                break;
            case t_BuiltInProgressBar::pbar_Classic:
                builtin_progress_bar.emplace<ConsoleProgressBar>();
                break;
            case t_BuiltInProgressBar::pbar_NoIndicator:
                builtin_progress_bar.emplace<NoIndicator>();
                break;
            default:
                throw std::runtime_error("Unknown progress bar type");
        }
    }
    // else: variant remains default-constructed
}

ProgressBarChooser::~ProgressBarChooser() = default;

I_ProgressBar& ProgressBarChooser::get()
{
    return std::visit(ProgressBarChooser{}, builtin_progress_bar);
}

} // namespace progressbars
} // namespace tools
} // namespace themachinethatgoesping