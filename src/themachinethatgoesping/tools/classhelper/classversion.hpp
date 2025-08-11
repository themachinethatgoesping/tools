// SPDX-FileCopyrightText: 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/classversion.doc.hpp"

#include <string_view>
#include <iostream>

namespace themachinethatgoesping::tools::classhelper {

void read_version(std::istream&   is,
                  std::string_view required_name,
                  std::string_view class_name);

void write_version(std::ostream& os, std::string_view name);

} // namespace themachinethatgoesping::tools::classhelper