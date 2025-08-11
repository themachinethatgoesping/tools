// SPDX-License-Identifier: MPL-2.0

#include "classversion.hpp"

#include <stdexcept>
#include <fmt/format.h>

namespace themachinethatgoesping::tools::classhelper {

void read_version(std::istream&   is,
                  std::string_view required_name,
                  std::string_view class_name)
{
    std::string name;
    name.resize(required_name.size());

    is.read(name.data(), static_cast<std::streamsize>(required_name.size()));

    if (name != required_name)
    {
        throw std::runtime_error(
            fmt::format("ERROR[{}::from_stream]: ClassName/Version mismatch: expected {}, got {}",
                        class_name,
                        required_name,
                        name));
    }
}

void write_version(std::ostream& os, std::string_view name)
{
    os.write(name.data(), static_cast<std::streamsize>(name.size()));
}

} // namespace themachinethatgoesping::tools::classhelper