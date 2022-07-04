// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief an object that allows for easy pretty printing of class members
 *
 */

#pragma once

#include <fmt/core.h>
#include <magic_enum.hpp>

namespace themachinethatgoesping {
namespace tools {
namespace classhelpers {

class ObjectPrinter
{
    const std::string                                _name;
    std::vector<std::pair<std::string, std::string>> _data;

  public:
    ObjectPrinter(const std::string& name)
        : _name(name)
    {
    }

    template<typename t_value>
    void value(const std::string& name, t_value value, std::string value_info = "")
    {
        std::string str;

        if constexpr (std::is_enum<t_value>())
        {
            str = magic_enum::enum_name(value);

            constexpr auto enum_values = magic_enum::enum_names<t_value>();
            for (unsigned int i = 0; i < enum_values.size(); ++i)
            {
                if (i != 0)
                    value_info += ", ";

                value_info += enum_values[i];
            }
        }
        else
        {
            str = fmt::format("{}", value);
        }

        if (value_info.size() > 0)
        {
            str += fmt::format(" [{}]", value_info);
        }

        _data.push_back(std::make_pair(name, str));
    }

    // for vector: add '\n' before value
    template<typename t_value>
    void container(const std::string& name, std::vector<t_value> values, std::string value_info = "")
    {
        std::string str;

        str = "{";
        for (unsigned int i = 0; i < values.size(); ++i)
        {
            if (i != 0)
                str += " ,";
            str += fmt::format("{}", values[i]);
        }
        str += "}";

        if (value_info.size() > 0)
        {
            str += fmt::format(" [{}]", value_info);
        }

        _data.push_back(std::make_pair(name, str));
    }

    std::string str() const
    {
        size_t max_len = 0;
        // find leng of string(till ':')
        for (const auto& n_s : _data)
        {
            if (n_s.first.size() > max_len)
                max_len = n_s.first.size();
        }
        max_len += 1;

        std::string str = _name;

        for (unsigned int i = 0; i < _name.size(); ++i)
        {
            if (i == 0)
                str += '\n';

            str += '-';
        }

        for (const auto& n_s : _data)
        {
            // do value formating here
            str += fmt::format("\n{:<{}} {}", n_s.first + ':', max_len, n_s.second);
        }

        return str;
    }
};

}
}
}