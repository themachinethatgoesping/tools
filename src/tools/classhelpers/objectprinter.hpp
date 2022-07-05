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
    enum class t_field
    {
        tvalue,
        tenum,
        tcontainer,
        tsection
    };

    const std::string                     _name;
    std::vector<std::string>              _fields;
    std::vector<std::vector<std::string>> _lines;
    std::vector<t_field>                  _field_types;

  public:
    ObjectPrinter(const std::string& name)
        : _name(name)
    {
    }

    // --- functions to register values for printing ----

    /**
     * @brief register a single integer of floating point value for printing
     *
     * @tparam t_value
     * @param name name of the variable
     * @param value value of the variable
     * @param value_info additional info (is printed in [] behind the variable)
     */
    template<typename t_value>
    void reg_value(const std::string& name, t_value value, std::string value_info = "")
    {
        std::string str;

        str = fmt::format("{}", value);

        if (value_info.size() > 0)
        {
            str += fmt::format(" [{}]", value_info);
        }

        _fields.push_back(name);
        _lines.push_back({ str });
        _field_types.push_back(t_field::tvalue);
    }

    /**
     * @brief register an enumeration for printing
     *
     * @tparam t_value
     * @param name name of the variable
     * @param value value of the variable
     * @param value_info additional info (is printed in [] behind the variable)
     */
    template<typename t_value>
    void reg_enum(const std::string& name, t_value value, std::string value_info = "")
    {
        std::string str;

        str = magic_enum::enum_name(value);

        constexpr auto enum_values = magic_enum::enum_names<t_value>();
        for (unsigned int i = 0; i < enum_values.size(); ++i)
        {
            if (i != 0)
                value_info += ", ";

            value_info += enum_values[i];
        }

        if (value_info.size() > 0)
        {
            str += fmt::format(" [{}]", value_info);
        }

        _fields.push_back(name);
        _lines.push_back({ str });
        _field_types.push_back(t_field::tenum);
    }

    /**
     * @brief register a 1D container for printing
     *
     * @tparam t_value
     * @param name name of the container
     * @param value container values
     * @param value_info additional info (is printed in [] behind the variable)
     */
    template<typename t_value>
    void reg_container(const std::string&   name,
                       std::vector<t_value> values,
                       std::string          value_info = "")
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

        _fields.push_back(name);
        _lines.push_back({ str });
        _field_types.push_back(t_field::tcontainer);
    }

    /**
     * @brief register a section break for printing
     *
     * @param name name of the section
     */
    void reg_section(const std::string& name)
    {
        _fields.push_back("- " + name + " -");
        _lines.push_back({ "" });
        _field_types.push_back(t_field::tsection);
    }

    std::string str() const
    {
        std::vector<size_t> max_len = { 0 };
        for (size_t i = 0; i < _fields.size(); ++i)
        {
            if (_field_types[i] == t_field::tsection)
            {
                max_len.back() += 1;
                max_len.push_back(0);
                continue;
            }

            if (_fields[i].size() > max_len.back())
                max_len.back() = _fields[i].size();
        }
        max_len.back() += 1;


        std::string str = underline(_name,'*');

        auto section_nr = 0;
        for (unsigned int i = 0; i < _fields.size(); ++i)
        {
            switch (_field_types[i])
            {
                case t_field::tsection:
                    section_nr += 1;
                    str += '\n' + underline(_fields[i],'-');
                    
                    break;
                case t_field::tvalue:
                    str += fmt::format("\n{:<{}} {}", _fields[i] + ':', max_len[section_nr], _lines[i][0]);
                    break;
                case t_field::tenum:
                    str += fmt::format("\n{:<{}} {}", _fields[i] + ':', max_len[section_nr], _lines[i][0]);
                    break;
                case t_field::tcontainer:
                    str += fmt::format("\n{:<{}} {}", _fields[i] + ':', max_len[section_nr], _lines[i][0]);
                    break;

                default:
                    throw(std::runtime_error("ObjectPrinter::str: unknown field type"));
            }

            // do value formating here
        }
        // do value ields[i] + ':', max_len, _lines[i][0]);

        return str;
    }

    static std::string underline(const std::string& line, char underliner = '-')
    {
        std::string str = line;
        for (unsigned int i = 0; i < line.size(); ++i)
        {
            if (i == 0)
                str += '\n';

            str += underliner;
        }

        return str;
    }
};

}
}
}
