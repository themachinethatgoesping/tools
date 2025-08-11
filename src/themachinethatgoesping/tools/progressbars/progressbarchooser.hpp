// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/progressbarchooser.doc.hpp"

#include <variant>

#include "consoleprogressbar.hpp"
#include "noindicator.hpp"
#include "progressindicator.hpp"

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

enum class t_BuiltInProgressBar { pbar_NoIndicator, pbar_Indicator, pbar_Classic };

using v_BuiltInProgressBar = std::variant<NoIndicator, ProgressIndicator, ConsoleProgressBar>;

/**
 * @brief This class allows choosing between different progress bars
 * It will be extended in the future to allow setting the default progressbar using a configuration
 * file
 */
class ProgressBarChooser
{
    // I would prefer to derive from std::variant, but this is not supported by g++-11
    v_BuiltInProgressBar builtin_progress_bar;

  public:
    ProgressBarChooser();
    explicit ProgressBarChooser(bool show_progress);
    ~ProgressBarChooser();

    /**
     * @brief This is the visitor function that implicitly converts t_ProgressBar to I_ProgressBar
     * (the common interface)
     */
    template<typename t_ProgressBar>
    I_ProgressBar& operator()(t_ProgressBar& progress_bar) const
    {
        return progress_bar;
    }

    /**
     * @brief get the ProgressBarInterface
     */
    I_ProgressBar& get();
};

} // namespace progressbars
} // namespace tools
} // namespace themachinethatgoesping
