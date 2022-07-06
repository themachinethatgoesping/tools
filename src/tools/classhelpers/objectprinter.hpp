// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief an object that allows for easy pretty printing of class members
 *
 */

#pragma once

#include <algorithm>
#include <fmt/core.h>
#include <limits>
#include <magic_enum.hpp>
#include <numeric>

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
    std::vector<t_field>                  _field_types;
    std::vector<std::vector<std::string>> _lines;
    std::vector<std::string>              _value_infos;

  public:
    ObjectPrinter(const std::string& name)
        : _name(name)
    {
    }

    // --- functions to register values for printing ----

    /**
     * @brief register an enumeration for printing
     *
     * @tparam t_value
     * @param name name of the variable
     * @param value value of the variable
     * @param value_info additional info (is printed in [] behind the variable)
     */
    template<typename t_value>
    void add_enum(const std::string& name, t_value value, std::string value_info = "")
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
            _value_infos.push_back(fmt::format("[{}]", value_info));
        else
            _value_infos.push_back("");

        _fields.push_back(name);
        _lines.push_back({ str });
        _field_types.push_back(t_field::tenum);
    }

    /**
     * @brief register a single integer of floating point value for printing
     *
     * @tparam t_value
     * @param name name of the variable
     * @param value value of the variable
     * @param value_info additional info (is printed in [] behind the variable)
     */
    template<typename t_value>
    void add_value(const std::string& name, t_value value, std::string value_info = "")
    {
        std::string str;

        if constexpr (std::is_floating_point<t_value>())
            str = fmt::format("{:.2f}", value);
        else
            str = fmt::format("{}", value);

        if (value_info.size() > 0)
            _value_infos.push_back(fmt::format("[{}]", value_info));
        else
            _value_infos.push_back("");

        _fields.push_back(name);
        _lines.push_back({ str });
        _field_types.push_back(t_field::tvalue);
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
    void add_container(const std::string&          name,
                       const std::vector<t_value>& values,
                       std::string                 value_info           = "",
                       size_t                      max_visible_elements = 9)
    {
        std::string str, format;

        if constexpr (std::is_floating_point<t_value>())
            format = "{:.6g}";
        else
            format = "{}";

        str = "{";
        for (unsigned int i = 0; i < values.size(); ++i)
        {
            if (i != 0)
                str += ", ";

            if (values.size() > max_visible_elements)
                if (i == size_t(max_visible_elements / 2) - 1)
                {
                    str += "..., ..., ...";
                    i = values.size() - size_t(max_visible_elements / 2);
                    continue;
                }
            str += fmt::format(format, values[i]);
        }
        str += "}";

        if (value_info.size() > 0)
            _value_infos.push_back(fmt::format("[{}]", value_info));
        else
            _value_infos.push_back("");

        _fields.push_back(name);
        _lines.push_back({ str });
        _field_types.push_back(t_field::tcontainer);

        // add vector information if not all elements are displayed
        if (values.size() > max_visible_elements)
        {
            // copy vector once to modify it
            std::vector<t_value> v;
            size_t               cnt_nan   = 0;
            size_t               cnt_inf   = 0;
            size_t               cnt_inf_n = 0;

            // count nans and infs and copy normal values to v

            if constexpr (std::is_floating_point<t_value>())
            {
                for (const auto& value : values)
                {
                    if (std::isnan(value))
                    {
                        ++cnt_nan;
                        continue;
                    }

                    if (std::isinf(value))
                    {
                        if (value < 0)
                            ++cnt_inf_n;
                        else
                            ++cnt_inf;
                        continue;
                    }

                    v.push_back(value);
                }
            }
            else
                v = values;

            auto minmax = std::minmax_element(std::begin(v), std::end(v));
            auto mean   = std::reduce(std::begin(v), std::end(v)) / v.size();

            size_t n_2 = v.size() / 2;
            std::nth_element(v.begin(), v.begin() + n_2, v.end());

            // std::string line_format = fmt::format("Min:  {} | Max: {}", format, format);
            // _lines.back().push_back(
            //     fmt::format(line_format, *(minmax.first), *(minmax.second), mean));

            // _lines.back().push_back(fmt::format("Mean: " + format, mean));

            std::string line_format =
                fmt::format("... Min:  {} | Max: {} | Mean: {}", format, format, format);
            _lines.back().push_back(
                fmt::format(line_format, *(minmax.first), *(minmax.second), mean));

            // special case for even numbers
            if (v.size() % 2)
            {
                std::nth_element(v.begin(), v.begin() + n_2 + 1, v.end());
                _lines.back().back() +=
                    fmt::format("| Median: " + format, (v[n_2] + v[n_2 + 1]) / 2);
            }
            else
            {
                _lines.back().back() += fmt::format(" | Median: " + format, v[n_2]);
            }

            // value count
            _lines.back().push_back(fmt::format("... {} elements", values.size()));

            // special signs for floating point lists and value count
            if constexpr (std::is_floating_point<t_value>())
            {
                if (cnt_nan || cnt_inf || cnt_inf_n)
                {
                    _lines.back().back() += fmt::format(" ! NAN elements: ");

                    if (cnt_nan)
                    {
                        _lines.back().back() += fmt::format("nan({})", cnt_nan);
                        if (cnt_inf || cnt_inf_n)
                            _lines.back().back() += ", ";
                    }
                    if (cnt_inf_n)
                    {
                        _lines.back().back() += fmt::format("-inf({})", cnt_inf_n);
                        if (cnt_inf)
                            _lines.back().back() += ", ";
                    }
                    if (cnt_inf)
                    {
                        _lines.back().back() += fmt::format("+inf({})", cnt_inf);
                    }
                }
            }
        }
    }

    /**
     * @brief register a section break for printing
     *
     * @param name name of the section
     */
    void add_section(const std::string& name)
    {
        _fields.push_back(name);
        _lines.push_back({ "" });
        _value_infos.push_back({ "" });
        _field_types.push_back(t_field::tsection);
    }

    std::string create_str() const
    {
        std::vector<std::string> str_lines;

        std::vector<size_t> max_len_field = { 0 }; // max string len of field name
        std::vector<size_t> max_len_value = { 0 }; // max string len of field + value

        // get max_len_field for each section
        for (size_t i = 0; i < _fields.size(); ++i)
        {
            if (_field_types[i] == t_field::tsection)
            {
                max_len_field.back() += 1;
                max_len_field.push_back(0);
                continue;
            }

            if (_fields[i].size() > max_len_field.back())
                max_len_field.back() = _fields[i].size();
        }
        max_len_field.back() += 1;

        // create string depending on field type
        auto section_nr = 0;
        for (unsigned int i = 0; i < _fields.size(); ++i)
        {
            std::string prefix = "";
            if (i > 0)
            {
                // add \n if previous element had multiple str_lines
                if (_field_types[i - 1] != t_field::tsection)
                    if (_lines[i - 1].size() > 1)
                        prefix = "\n";
            }
            switch (_field_types[i])
            {

                case t_field::tsection:
                    section_nr += 1;

                    max_len_value.push_back(0);
                    // str += '\n' + underline(_fields[i], '-');
                    str_lines.push_back("\n" + underline(" " + _fields[i] + " ", '-'));

                    continue;
                case t_field::tvalue:
                    str_lines.push_back(fmt::format(prefix + "- {:<{}} {}",
                                                    _fields[i] + ':',
                                                    max_len_field[section_nr],
                                                    _lines[i][0]));
                    break;
                case t_field::tenum:
                    str_lines.push_back(fmt::format(prefix + "- {:<{}} {}",
                                                    _fields[i] + ':',
                                                    max_len_field[section_nr],
                                                    _lines[i][0]));
                    break;
                case t_field::tcontainer:
                    str_lines.push_back(fmt::format(prefix + "- {:<{}} {}",
                                                    _fields[i] + ':',
                                                    max_len_field[section_nr],
                                                    _lines[i][0]));
                    break;

                default:
                    throw(std::runtime_error("ObjectPrinter::str: unknown field type"));
            }

            if (str_lines.back().size() > max_len_value.back())
                max_len_value.back() = str_lines.back().size();
        }

        std::string str = underline(_name, '*');
        section_nr      = 0;
        for (size_t i = 0; i < str_lines.size(); ++i)
        {
            if (_field_types[i] == t_field::tsection)
            {
                section_nr += 1;
            }

            str += fmt::format(
                "\n{:<{}} {}", str_lines[i], max_len_value[section_nr], _value_infos[i]);

            for (size_t j = 1; j < _lines[i].size(); ++j)
                // str += fmt::format("\n  {}", _lines[i][j]);
                str += fmt::format("\n{:<{}}  {}", "", max_len_field[section_nr], _lines[i][j]);
        }

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

// --- print functions (need objectprinter __printer__ function that returns an ObjectPrinter) ---
#define __CLASSHELPERS_PRINTER_INFO_STRING__                                                       \
    /**                                                                                            \
     * @brief return an info string using the class __printer__ object                             \
     *                                                                                             \
     * @return std::string                                                                         \
     */                                                                                            \
    std::string info_string() const                                                                \
    {                                                                                              \
        return this->__printer__().create_str();                                                   \
    }

#define __CLASSHELPERS_PRINTER_PRINT__                                                             \
    /**                                                                                            \
     * @brief print the object information to the given outpustream                                \
     *                                                                                             \
     * @param os output stream, e.g. file stream or std::out or std::cerr                          \
     */                                                                                            \
    void print(std::ostream& os) const                                                             \
    {                                                                                              \
        os << this->__printer__().create_str() << std::flush;                                      \
    }

#define __CLASSHELPERS_DEFUALT_PRINTING_FUNCTIONS__                                                \
    __CLASSHELPERS_PRINTER_INFO_STRING__                                                           \
    __CLASSHELPERS_PRINTER_PRINT__

}
}
}
