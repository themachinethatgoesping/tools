// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief An object that allows for easy pretty printing of class members
 * usage:
 *  1. Implement a __printer__ function as public class member this function should return a
 *     ObjectPrinter object. Register all, values, containers, objects that are to be printerd.
 *  2. Add the __CLASSHELPERS_DEFUALT_PRINTING_FUNCTIONS__ macro to the public fucntions.
 *     This macro implements std::string info_string() and print(std::ostream) functions using the
 * object printer
 *  3. Add the __PYCLASS_DEFAULT_PRINTING__ to the python module defintion. This macro implements
 *     __str__(), __repr__(), info_string() and print() as python functions
 *
 */

#pragma once

#include <algorithm>
#include <fmt/core.h>
#include <limits>
#include <magic_enum.hpp>
#include <numeric>

#include "../bitsery_helpers/classhelpers.hpp"
#include "../bitsery_helpers/helpers.hpp"
#include <bitsery/traits/string.h>

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
        os << this->__printer__().create_str() << std::endl;                                       \
    }

#define __CLASSHELPERS_DEFUALT_PRINTING_FUNCTIONS__                                                \
    __CLASSHELPERS_PRINTER_INFO_STRING__                                                           \
    __CLASSHELPERS_PRINTER_PRINT__

namespace themachinethatgoesping {
namespace tools {
namespace classhelpers {

/**
 * @brief Class that allows for easy pretty printing of class members
 * usage:
 *  1. Implement a __printer__ function as public class member this function should return a
 *     ObjectPrinter object. Register all, values, containers, objects that are to be printerd.
 *  2. Add the __CLASSHELPERS_DEFUALT_PRINTING_FUNCTIONS__ macro to the public fucntions.
 *     This macro implements std::string info_string() and print(std::ostream) functions using the
 * object printer
 *  3. Add the __PYCLASS_DEFAULT_PRINTING__ to the python module defintion. This macro implements
 *     __str__(), __repr__(), info_string() and print() as python functions
 *
 */


class ObjectPrinter
{
    /**
     * @brief internal, describe the value type for implementing different printing strategies
     *
     */
    enum class t_field
    {
        tvalue,     /// < double or integer
        tenum,      /// < enumerator
        tcontainer, /// < 1D container (floating point or integer)
        tsection    /// < section break
    };

    std::string                           _name;   /// < name of the class that is to be printed
    std::vector<std::string>              _fields; /// < variable names
    std::vector<t_field>                  _field_types; /// < variable types
    std::vector<std::vector<std::string>> _lines;       /// frst line is typically the field value
    std::vector<std::string>              _value_infos; /// additional info (printed in [])

    // serialization support using bitsery
    ObjectPrinter() = default;
    friend bitsery::Access;

    template<typename S>
    void serialize(S& s)
    {
        s.text1b(_name, 100);
        s.container(_fields, 1000, [](S& s_, std::string& str) { s_.text1b(str,100); });
        s.container4b(_field_types, 1000);
        s.container(_lines, 1000, [](S& s_, std::vector<std::string>& str_vec) 
        { 
            s_.container(str_vec, 1000, [](S& s__, std::string& str) { s__.text1b(str,100); }); 
            });
        s.container(_value_infos, 1000, [](S& s_, std::string& str) { s_.text1b(str,100); });
        //s.container(_value_infos, 1000, &ser_txt);
    }

  public:
    __BITSERY_DEFAULT_TOFROM_BINARY_FUNCTIONS__(ObjectPrinter)
    __CLASSHELPERS_DEFUALT_PRINTING_FUNCTIONS__

    ObjectPrinter __printer__() const
    {
        ObjectPrinter printer("ObjectPrinter");

        printer.register_value("name", _name);
        printer.register_container("fields", _fields);
        printer.register_container("field_types", _field_types);

        // convert lines to string
        std::vector<std::string> lines;
        for (const auto& strl : _lines)
        {
            std::string str;
            for (const auto& s : strl)
            {
                if (str.size() != 0)
                    str += "; ";
                str += s;
            }
            lines.push_back(str);
        }
        printer.register_value("lines", fmt::format("... {} elements", _lines.size()));

        printer.register_container("value_infos", _value_infos);

        return printer;
    }

  public:
    /**
     * @brief Construct a new Object Printer object
     *
     * @param name name of the class that is to be printed
     */
    ObjectPrinter(const std::string& name)
        : _name(name)
    {
    }

    // --- functions to register values for printing ----

    /**
     * @brief register an enumeration for printing
     *
     * @tparam t_value enumerator
     * @param name name of the variable
     * @param value value of the variable
     * @param value_info additional info (is printed in [] behind the variable)
     */
    template<typename t_value>
    void register_enum(const std::string& name, t_value value, std::string value_info = "")
    {
        std::string str;

        // convert enum value to string using magic_enum library
        str = magic_enum::enum_name(value);

        // create string of all possible enum values
        constexpr auto enum_values = magic_enum::enum_names<t_value>();
        for (unsigned int i = 0; i < enum_values.size(); ++i)
        {
            if (i != 0)
                value_info += ", ";

            value_info += enum_values[i];
        }

        // attach all possible enum values as value_info
        if (value_info.size() > 0)
            _value_infos.push_back(fmt::format("[{}]", value_info));
        else
            _value_infos.push_back("");

        _fields.push_back(name);
        _lines.push_back({ str }); // only one line (value)
        _field_types.push_back(t_field::tenum);
    }

    /**
     * @brief register a single integer of floating point value for printing
     *
     * @tparam t_value double or floating point
     * @param name name of the variable
     * @param value value of the variable
     * @param value_info additional info (is printed in [] behind the variable)
     */
    template<typename t_value>
    void register_value(const std::string& name, t_value value, std::string value_info = "")
    {
        std::string str;

        // convert value to string
        if constexpr (std::is_floating_point<t_value>())
            str = fmt::format("{:.2f}", value);
        else
            str = fmt::format("{}", value);

        // add value information
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
     * @tparam t_value integer or floating point
     * @param name name of the container
     * @param value container values
     * @param value_info additional info (is printed in [] behind the variable)
     */
    template<typename t_value>
    void register_container(const std::string&          name,
                            const std::vector<t_value>& values,
                            std::string                 value_info = "")
    {
        static const size_t max_visible_elements = 9; // maximum values to display for a vector
        std::string         str, format;

        // define value to string format
        if constexpr (std::is_floating_point<t_value>())
            format = "{:.6g}"; // 6 characters, automatic scientific noation depending on magnitude
        else if constexpr (std::is_base_of<t_value, std::string>())
            format = "\"{}\"";
        else
            format = "{}";

        // add values to {} list
        str = "{";
        for (unsigned int i = 0; i < values.size(); ++i)
        {
            if (i != 0)
                str += ", ";

            // don't print entire list of > max_visible_elements in vector
            if (values.size() > max_visible_elements)
                if (i == size_t(max_visible_elements / 2) - 1)
                {
                    str += "..., ..., ...";
                    i = values.size() - size_t(max_visible_elements / 2);
                    continue;
                }
            if constexpr (std::is_enum<t_value>())
                str += magic_enum::enum_name(values[i]);
            else
                str += fmt::format(format, values[i]);
        }
        str += "}";

        // add value info
        if (value_info.size() > 0)
            _value_infos.push_back(fmt::format("[{}]", value_info));
        else
            _value_infos.push_back("");

        _fields.push_back(name);
        _lines.push_back({ str });
        _field_types.push_back(t_field::tcontainer);

        // add vector statistics if not all elements are displayed
        if (values.size() > max_visible_elements)
        {
            // begin statistics for numbers
            if constexpr (std::is_floating_point<t_value>() || std::is_integral<t_value>())
            {

                {
                    // copy vector once to modify it
                    std::vector<t_value> v;
                    size_t               cnt_nan   = 0; ///< number of nan values
                    size_t               cnt_inf   = 0; ///< number of positive infinity values
                    size_t               cnt_inf_n = 0; ///< number of negative infinity values

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

                    // get statistics from nan/inf cleaned lists
                    auto minmax = std::minmax_element(std::begin(v), std::end(v));
                    auto mean   = std::reduce(std::begin(v), std::end(v)) / v.size();

                    // compute median
                    size_t n_2 = v.size() / 2;
                    std::nth_element(v.begin(), v.begin() + n_2, v.end());

                    // -- print statistics 1 --
                    std::string line_format =
                        fmt::format("... Min:  {} | Max: {} | Mean: {}", format, format, format);
                    _lines.back().push_back(
                        fmt::format(line_format, *(minmax.first), *(minmax.second), mean));

                    // print meadian (special case for even numbers)
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

                    // -- print statistics 2 --
                    // value count
                    _lines.back().push_back(fmt::format("... {} elements", values.size()));

                    // for floating point vectors, add number of nan/inf elements to info
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
            else // end number statistics
            {
                // statistics also for not number containers
                _lines.back().push_back(fmt::format("... {} elements", values.size()));
            }
        }
    }

    /**
     * @brief register a section break for printing
     *
     * @param name name of the following section
     */
    void register_section(const std::string& name)
    {
        _fields.push_back(name);
        _lines.push_back({ "" });
        _value_infos.push_back({ "" });
        _field_types.push_back(t_field::tsection);
    }

    /**
     * @brief Create an info_string from the registered values/sections
     *
     * @return std::string
     */
    std::string create_str() const
    {
        std::vector<std::string> str_lines; // individual lines

        std::vector<size_t> max_len_field = { 0 }; // max string len of field name
        std::vector<size_t> max_len_value = { 0 }; // max string len of field + value

        // get max_len_field for each section
        // this is used for alligning the values for each section
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

    /**
     * @brief add a line under a given line string
     *
     * @param line input string
     * @param underliner line character
     * @return std::string
     */
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
