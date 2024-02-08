#pragma once

/* generated doc strings */
#include ".docstrings/version_error.doc.hpp"

#include <stdexcept>

namespace themachinethatgoesping {
namespace tools {
namespace exceptions {

class version_error : public std::runtime_error
{
  public:
    using std::runtime_error::runtime_error;
};

} // namespace classhelper
} // namespace tools
} // namespace themachinethatgoesping