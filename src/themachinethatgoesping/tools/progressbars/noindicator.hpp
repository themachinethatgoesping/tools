// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/noindicator.doc.hpp"

#include "i_progressbar.hpp"
#include <string>

namespace themachinethatgoesping {
namespace tools {
namespace progressbars {

/**
 * @brief A progress bar that does not show any progress and has nearly no overhead.
 */
class NoIndicator : public I_ProgressBar
{
    bool _is_initialized = false;

  public:
    NoIndicator();

    // ----- I_ProgressBar interface -----
    bool is_initialized() const override;

    void init(double first, double last, const std::string& name = "process") override;
    void close(const std::string& msg = "done") override;

    void set_progress(double new_progress) override;
    void set_postfix(const std::string& postfix) override;
    void set_prefix(const std::string& prefix) override;

    void tick(double increment = 1) override;

    double current() const override;
};

} // namespace progressbars
} // namespace tools
} // namespace themachinethatgoesping
