// SPDX-FileCopyrightText: 2024 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/classversion.doc.hpp"

#include <string_view>
#include <iostream>

namespace themachinethatgoesping::tools::classhelper {


inline void read_version(std::istream&   is,
                         std::string_view required_name,
                         std::string_view class_name)
{
    std::string name;
    name.resize(required_name.size());

    is.read(name.data(), required_name.size());

    if (name != required_name)
    {
        throw std::runtime_error(
            fmt::format("ERROR[{}::from_stream]: ClassName/Version mismatch: expected {}, got {}",
                        class_name,
                        required_name,
                        name));
    }
}

inline void write_version(std::ostream& os, std::string_view name)
{
    os.write(name.data(), name.size());
}

} // namespace themachinethatgoesping::tools::classhelper