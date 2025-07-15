
// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

#pragma once

/* generated doc strings */
#include ".docstrings/defaultmap.doc.hpp"

#include <map>
#include <memory>

namespace themachinethatgoesping {
namespace tools {
namespace helper {

    

template<typename t_key, typename t_value>
class DefaultMap : public std::map<t_key, t_value>
{
    const t_value _default_value;

  public:
    // use all constructors of the base class
    DefaultMap(t_value default_value = t_value())
        : _default_value(std::move(default_value))
    {
    }

    t_value& at(const t_key& key)
    {
        auto it = this->find(key);

        if (it == this->end())
        {
            this->operator[](key) = _default_value;

            return this->operator[](key);
        }
        return it->second;
    }

    t_value at_const(
        const t_key& key) const // TODO: this function is lying about constness. While the map is
                                // const, the return pointer and return value are not.
    {
        auto it = this->find(key);

        if (it == this->end())
        {
            return _default_value;
        }
        return it->second;
    }

    // get all keys
    std::vector<t_key> keys() const
    {
        std::vector<t_key> keys;
        for (const auto& [key, value] : *this)
        {
            keys.push_back(key);
        }
        return keys;
    }
};

}
}
}