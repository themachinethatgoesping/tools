// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// SPDX-FileCopyrightText: (c)2019 Michael Tesch. tesch1@gmail.com (struct
// fmt::formatter<std::complex<T>,Char> : public fmt::formatter<T,Char>)
//
// SPDX-License-Identifier: MPL-2.0

#include "objectprinter.hpp"

// All the heavy headers moved here
#include "../helper/xtensor.hpp"
#include <algorithm>
#include <cmath>
#include <complex>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <iostream>
#include <limits>
#include <numeric>

// Add proper xtensor includes for the types you're instantiating
#include <xtensor/containers/xtensor.hpp>

#include "../helper/printing.hpp"

// // fmt::formatter implementations
// template<typename T, typename Char>
// template<typename ParseContext>
// FMT_CONSTEXPR auto fmt::formatter<std::complex<T>, Char>::parse(ParseContext& ctx) -> const Char*
// {
//     auto it = ctx.begin();
//     if (it != ctx.end())
//     {
//         switch (*it)
//         {
//             case '$':
//                 style_ = style::expr;
//                 ctx.advance_to(++it);
//                 break;
//             case '*':
//                 style_ = style::star;
//                 ctx.advance_to(++it);
//                 break;
//             case ',':
//                 style_ = style::pair;
//                 ctx.advance_to(++it);
//                 break;
//             default:
//                 break;
//         }
//     }

//     auto type = detail::type_constant<T, Char>::value;
//     auto end  = detail::parse_format_specs(ctx.begin(), ctx.end(), specs_, ctx, type);
//     if (type == detail::type::char_type)
//         detail::check_char_specs(specs_);
//     return end;
// }

// template<typename T, typename Char>
// template<typename FormatContext>
// FMT_CONSTEXPR auto fmt::formatter<std::complex<T>, Char>::format(const std::complex<T>& x,
//                           FormatContext&         ctx) const -> decltype(ctx.out())
// {
//     format_to(ctx.out(), "(");
//     if (style_ == style::pair)
//     {
//         base::format(x.real(), ctx);
//         format_to(ctx.out(), ",");
//         base::format(x.imag(), ctx);
//         return format_to(ctx.out(), ")");
//     }
//     if (x.real() || !x.imag())
//         base::format(x.real(), ctx);
//     if (x.imag())
//     {
//         if (x.real() && x.imag() >= 0 && specs_.sign != sign::plus)
//             format_to(ctx.out(), "+");
//         base::format(x.imag(), ctx);
//         if (style_ == style::star)
//             format_to(ctx.out(), "*i");
//         else
//             format_to(ctx.out(), "i");
//         if (std::is_same<typename std::decay<T>::type, float>::value)
//             format_to(ctx.out(), "f");
//         if (std::is_same<typename std::decay<T>::type, long double>::value)
//             format_to(ctx.out(), "l");
//     }
//     return format_to(ctx.out(), ")");
// }

namespace themachinethatgoesping {
namespace tools {
namespace classhelper {

// Constructor
ObjectPrinter::ObjectPrinter(std::string_view name,
                             unsigned int     float_precision,
                             bool             superscript_exponents)
    : _name(std::string(name))
    , _float_precision(float_precision)
    , _superscript_exponents(superscript_exponents)
{
}

// Serialization
ObjectPrinter ObjectPrinter::from_stream(std::istream& is)
{
    using namespace stream;

    ObjectPrinter printer;
    printer._name        = container_from_stream<decltype(printer._name)>(is);
    printer._fields      = container_container_from_stream<1, decltype(printer._fields)>(is);
    printer._field_types = container_from_stream<decltype(printer._field_types)>(is);
    printer._lines       = container_container_from_stream<2, decltype(printer._lines)>(is);
    printer._value_infos = container_container_from_stream<1, decltype(printer._value_infos)>(is);
    printer._section_underliner = container_from_stream<decltype(printer._section_underliner)>(is);

    is.read(reinterpret_cast<char*>(&printer._float_precision), sizeof(printer._float_precision));

    is.read(reinterpret_cast<char*>(&printer._superscript_exponents),
            sizeof(printer._superscript_exponents));

    return printer;
}

void ObjectPrinter::to_stream(std::ostream& os) const
{
    using namespace stream;

    container_to_stream(os, _name);
    container_container_to_stream<1>(os, _fields);
    container_to_stream(os, _field_types);
    container_container_to_stream<2>(os, _lines);
    container_container_to_stream<1>(os, _value_infos);
    container_to_stream(os, _section_underliner);

    os.write(reinterpret_cast<const char*>(&_float_precision), sizeof(_float_precision));
    os.write(reinterpret_cast<const char*>(&_superscript_exponents),
             sizeof(_superscript_exponents));
}

ObjectPrinter ObjectPrinter::__printer__(unsigned int float_precision,
                                         bool         superscript_exponents) const
{
    ObjectPrinter printer("ObjectPrinter", float_precision, superscript_exponents);

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
    printer.register_container("section_underliner", _section_underliner);
    printer.register_value("float_precision", _float_precision);
    printer.register_value("superscript_exponents", _superscript_exponents);

    return printer;
}

// Remove sections
void ObjectPrinter::remove_sections()
{
    for (size_t i = 0; i < _field_types.size(); i++)
    {
        if (_field_types[i] == t_field::tsection)
        {
            _fields.erase(_fields.begin() + i);
            _field_types.erase(_field_types.begin() + i);
            _lines.erase(_lines.begin() + i);
            _value_infos.erase(_value_infos.begin() + i);
            _section_underliner.erase(_section_underliner.begin() + i);
            i--;
        }
    }
}

// Append
void ObjectPrinter::append(ObjectPrinter printer, char remove_sections, char section_underliner)
{
    if (remove_sections)
        printer.remove_sections();

    _fields.insert(_fields.end(), printer._fields.begin(), printer._fields.end());
    _field_types.insert(
        _field_types.end(), printer._field_types.begin(), printer._field_types.end());
    _lines.insert(_lines.end(), printer._lines.begin(), printer._lines.end());
    _value_infos.insert(
        _value_infos.end(), printer._value_infos.begin(), printer._value_infos.end());

    if (!section_underliner)
        _section_underliner.insert(_section_underliner.end(),
                                   printer._section_underliner.begin(),
                                   printer._section_underliner.end());
    else
        for ([[maybe_unused]] const auto& c : printer._section_underliner)
            _section_underliner.push_back(section_underliner);
}

template<typename t_value>
void ObjectPrinter::register_optional_value(const std::string&     name,
                                            std::optional<t_value> value,
                                            std::string_view       value_info,
                                            std::string_view       optional_value,
                                            int                    pos)
{
    if (value.has_value())
        register_value(name, value.value(), value_info, pos);
    else
        register_string(name, std::string(optional_value), std::string(value_info), pos);
}

template<typename t_value>
void ObjectPrinter::register_value(const std::string& name,
                                   t_value            value,
                                   std::string_view   value_info,
                                   int                pos)
{
    std::string str;

    // convert value to string
    if constexpr (std::is_floating_point<t_value>())
    {
        // make sure small values are displayed in a more readable format
        int  exponent  = 0;
        auto abs_value = std::fabs(value);

        if (value != t_value(0) && abs_value != t_value(0))
        {
            if (abs_value < 0.1)
                exponent = std::floor((std::log10(abs_value) + t_value(1)) / t_value(3)) * 3;
            else if (abs_value > 1000)
                exponent = std::floor((std::log10(abs_value) - t_value(1)) / t_value(3)) * 3;
        }

        if (exponent != 0)
        {
            value *= std::pow(10, t_value(-exponent));
            if (_superscript_exponents)
                str = fmt::format(
                    "{:.{}f}e{}", value, _float_precision, tools::helper::superscript(exponent));
            else
                str = fmt::format("{:.{}f}e{}", value, _float_precision, exponent);
        }
        else
            str = fmt::format("{:.{}f}", value, _float_precision);
    }
    else
        str = fmt::format("{}", value);

    // add value information
    std::string value_info_str = "";
    if (value_info.size() > 0)
        value_info_str = fmt::format("[{}]", value_info);

    if (pos < 0 || pos >= int(_fields.size()))
    {
        _fields.push_back(name);
        _lines.push_back({ str });
        _field_types.push_back(t_field::tvalue);
        _value_infos.push_back(value_info_str);
        _section_underliner.push_back(' ');
    }
    else
    {
        _fields.insert(_fields.begin() + pos, name);
        _lines.insert(_lines.begin() + pos, { str });
        _field_types.insert(_field_types.begin() + pos, t_field::tvalue);
        _value_infos.insert(_value_infos.begin() + pos, value_info_str);
        _section_underliner.insert(_section_underliner.begin() + pos, ' ');
    }
}

void ObjectPrinter::_register_enum_string(const std::string& name,
                                          const std::string& value_str,
                                          std::string        value_info,
                                          int                pos)
{
    // attach all possible enum values as value_info
    std::string value_info_str = "";
    if (value_info.size() > 0)
        value_info_str = fmt::format("[{}]", value_info);

    if (pos < 0 || pos >= int(_fields.size()))
    {
        _fields.push_back(name);
        _lines.push_back({ value_str }); // only one line (value)
        _field_types.push_back(t_field::tenum);
        _value_infos.push_back(value_info_str);
        _section_underliner.push_back(' ');
    }
    else
    {
        _fields.insert(_fields.begin() + pos, name);
        _lines.insert(_lines.begin() + pos, { value_str }); // only one line (value)
        _field_types.insert(_field_types.begin() + pos, t_field::tenum);
        _value_infos.insert(_value_infos.begin() + pos, value_info_str);
        _section_underliner.insert(_section_underliner.begin() + pos, ' ');
    }
}

void ObjectPrinter::register_value_bytes(const std::string& name, size_t value, int pos)
{
    if (value < 1024)
        register_value(name, value, "bytes", pos);
    else if (value < 1024 * 1024)
        register_value(name, double(value) / 1024., "KB", pos);
    else if (value < 1024 * 1024 * 1024)
        register_value(name, double(value) / 1024. / 1024., "MB", pos);
    else
        register_value(name, double(value) / 1024. / 1024. / 1024., "GB", pos);
}

template<typename t_container>
void ObjectPrinter::register_container(const std::string& name,
                                       const t_container& values,
                                       std::string_view   value_info,
                                       int                pos)
{
    static const size_t max_visible_elements = 7; // maximum values to display for a vector
    std::string         str, format;
    using t_value = typename t_container::value_type;

    // define value to string format
    if constexpr (std::is_floating_point<typename t_container::value_type>())
        format = "{:.6g}"; // 6 characters, automatic scientific notation depending on magnitude
    else if constexpr (std::is_base_of<t_value, std::string>())
        format = "\"{}\"";
    else
        format = "{}";

    // add values to {} list
    str       = "{";
    int64_t i = -1;
    for (auto value_it = values.begin(); value_it != values.end(); ++value_it)
    {
        ++i;
        if (i != 0)
            str += ", ";

        // don't print entire list of > max_visible_elements in vector
        if (values.size() > max_visible_elements)
            if (i == int64_t(max_visible_elements / 2))
            {
                str += "...";
                std::advance(value_it, values.size() - int64_t(max_visible_elements / 2) - i - 1);
                i = values.size() - int64_t(max_visible_elements / 2);
                continue;
            }
        if constexpr (std::is_enum<t_value>())
            str += magic_enum::enum_name(*value_it);
        else
            str += fmt::vformat(format, fmt::make_format_args(*value_it));
    }
    str += "}";

    // add value information
    std::string value_info_str = "";
    if (value_info.size() > 0)
        value_info_str = fmt::format("[{}]", value_info);

    if (pos < 0 || pos >= int(_fields.size()))
    {
        _fields.push_back(name);
        _lines.push_back({ str });
        _field_types.push_back(t_field::tcontainer);
        _value_infos.push_back(value_info_str);
        _section_underliner.push_back(' ');
    }
    else
    {
        _fields.insert(_fields.begin() + pos, name);
        _lines.insert(_lines.begin() + pos, { str });
        _field_types.insert(_field_types.begin() + pos, t_field::tcontainer);
        _value_infos.insert(_value_infos.begin() + pos, value_info_str);
        _section_underliner.insert(_section_underliner.begin() + pos, ' ');
    }

    auto& line_ref = _lines.back();
    if (pos >= 0 || pos >= int(_fields.size()))
        line_ref = _lines.at(pos);

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
                // copy all values to v
                {
                    v.resize(values.size());
                    std::copy(values.begin(), values.end(), v.begin());
                }

                // get statistics from nan/inf cleaned lists
                auto minmax = std::minmax_element(std::begin(v), std::end(v));
                auto mean   = std::reduce(std::begin(v), std::end(v)) / v.size();

                // compute median
                size_t n_2 = v.size() / 2;
                std::nth_element(v.begin(), v.begin() + n_2, v.end());

                // -- print statistics 1 --
                std::string line_format =
                    fmt::format("... Min:  {} | Max: {} | Mean: {}", format, format, format);
                line_ref.push_back(fmt::vformat(
                    line_format, fmt::make_format_args(*(minmax.first), *(minmax.second), mean)));

                // print median (special case for even numbers)
                if (v.size() % 2)
                {
                    std::nth_element(v.begin(), v.begin() + n_2 + 1, v.end());
                    auto median = (v[n_2] + v[n_2 + 1]) / 2;
                    line_ref.back() +=
                        fmt::vformat("| Median: " + format, fmt::make_format_args(median));
                }
                else
                {
                    line_ref.back() +=
                        fmt::vformat(" | Median: " + format, fmt::make_format_args(v[n_2]));
                }

                // -- print statistics 2 --
                // value count
                line_ref.push_back(fmt::format("... {} elements", values.size()));

                // for floating point vectors, add number of nan/inf elements to info
                if constexpr (std::is_floating_point<t_value>())
                {
                    if (cnt_nan || cnt_inf || cnt_inf_n)
                    {
                        line_ref.back() += fmt::format(" ! NAN elements: ");

                        if (cnt_nan)
                        {
                            line_ref.back() += fmt::format("nan({})", cnt_nan);
                            if (cnt_inf || cnt_inf_n)
                                line_ref.back() += ", ";
                        }
                        if (cnt_inf_n)
                        {
                            line_ref.back() += fmt::format("-inf({})", cnt_inf_n);
                            if (cnt_inf)
                                line_ref.back() += ", ";
                        }
                        if (cnt_inf)
                        {
                            line_ref.back() += fmt::format("+inf({})", cnt_inf);
                        }
                    }
                }
            }
        }
        else // end number statistics
        {
            // statistics also for not number containers
            line_ref.push_back(fmt::format("... {} elements", values.size()));
        }
    }
}

void ObjectPrinter::register_string_with_delimiters(const std::string& name,
                                                    std::string        value,
                                                    std::string        value_info,
                                                    std::string        delimiter_left,
                                                    std::string        delimiter_right,
                                                    int                pos,
                                                    size_t             max_visible_elements)
{
    value = delimiter_left + value + delimiter_right;
    register_string(name, value, value_info, pos, max_visible_elements);
}

void ObjectPrinter::register_string(const std::string& name,
                                    std::string        value,
                                    std::string        value_info,
                                    int                pos,
                                    size_t             max_visible_elements)
{
    if (value_info.size() > 0)
        value_info = fmt::format("[{}]", value_info);

    if (max_visible_elements > 0 && value.size() > max_visible_elements)
    {
        value = value.substr(0, max_visible_elements) + "...";
    }

    std::vector<std::string> lines;

    // split string into lines
    std::string::size_type start = 0;
    std::string::size_type end   = 0;
    while ((end = value.find('\n', start)) != std::string::npos)
    {
        lines.push_back(value.substr(start, end - start));
        start = end + 1;
    }
    lines.push_back(value.substr(start));

    if (pos < 0 || pos >= int(_fields.size()))
    {
        _fields.push_back(name);
        _lines.push_back(lines);
        _field_types.push_back(t_field::tstring);
        _value_infos.push_back(value_info);
        _section_underliner.push_back(' ');
    }
    else
    {
        _fields.insert(_fields.begin() + pos, name);
        _lines.insert(_lines.begin() + pos, lines);
        _field_types.insert(_field_types.begin() + pos, t_field::tstring);
        _value_infos.insert(_value_infos.begin() + pos, value_info);
        _section_underliner.insert(_section_underliner.begin() + pos, ' ');
    }
}

void ObjectPrinter::register_section(const std::string& name, char underliner, int pos)
{
    if (pos < 0 || pos >= int(_fields.size()))
    {
        _fields.push_back(name);
        _lines.push_back({ "" });
        _value_infos.push_back({ "" });
        _field_types.push_back(t_field::tsection);
        _section_underliner.push_back(underliner);
    }
    else
    {
        _fields.insert(_fields.begin() + pos, name);
        _lines.insert(_lines.begin() + pos, { "" });
        _value_infos.insert(_value_infos.begin() + pos, { "" });
        _field_types.insert(_field_types.begin() + pos, t_field::tsection);
        _section_underliner.insert(_section_underliner.begin() + pos, underliner);
    }
}

std::string ObjectPrinter::class_name() const
{
    return _name;
}

std::string ObjectPrinter::create_str() const
{
    std::vector<std::string> str_lines; // individual lines

    std::vector<size_t> max_len_field = { 0 }; // max string len of field name
    std::vector<size_t> max_len_value = { 0 }; // max string len of field + value

    // get max_len_field for each section
    // this is used for aligning the values for each section
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
                if (i == 0)
                    str_lines.push_back(
                        underline("-\n" + _fields[i] + " ", _section_underliner[i]));
                else
                    str_lines.push_back("\n" +
                                        underline(" " + _fields[i] + " ", _section_underliner[i]));

                continue;
            case t_field::tvalue:
                str_lines.push_back(prefix + fmt::format("- {:<{}} {}",
                                                         _fields[i] + ':',
                                                         max_len_field[section_nr],
                                                         _lines[i][0]));
                break;
            case t_field::tstring:
                str_lines.push_back(prefix + fmt::format("- {:<{}} {}",
                                                         _fields[i] + ':',
                                                         max_len_field[section_nr],
                                                         _lines[i][0]));
                break;
            case t_field::tenum:
                str_lines.push_back(prefix + fmt::format("- {:<{}} {}",
                                                         _fields[i] + ':',
                                                         max_len_field[section_nr],
                                                         _lines[i][0]));
                break;
            case t_field::tcontainer:
                str_lines.push_back(prefix + fmt::format("- {:<{}} {}",
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

    // If no variables are added, do not underline the object name
    if (str_lines.size() == 0)
        return _name;

    std::string str = underline(_name, '#');
    section_nr      = 0;
    for (size_t i = 0; i < str_lines.size(); ++i)
    {
        if (_field_types[i] == t_field::tsection)
        {
            section_nr += 1;
        }

        if ((_value_infos[i].empty()) ||
            (max_len_value[section_nr] + _value_infos[i].size() <= 150))
        {
            str += fmt::format(
                "\n{:<{}} {}", str_lines[i], max_len_value[section_nr], _value_infos[i]);
        }
        else
        {
            // put value info in the next line if line with value info is > 150 characters
            str += fmt::format("\n{:<{}}", str_lines[i], max_len_value[section_nr]);
            str += fmt::format("\n{:<{}}   {}", "", max_len_field[section_nr], _value_infos[i]);
        }

        for (size_t j = 1; j < _lines[i].size(); ++j)
            // str += fmt::format("\n  {}", _lines[i][j]);
            str += fmt::format("\n{:<{}}  {}", "", max_len_field[section_nr], _lines[i][j]);
    }

    return str;
}

std::string ObjectPrinter::underline(const std::string& line, char underliner)
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

// Explicit template instantiations for common types
template void ObjectPrinter::register_value<bool>(const std::string&, bool, std::string_view, int);
template void ObjectPrinter::register_value<std::string_view>(const std::string&,
                                                              std::string_view,
                                                              std::string_view,
                                                              int);
template void ObjectPrinter::register_value<uint8_t>(const std::string&,
                                                     uint8_t,
                                                     std::string_view,
                                                     int);
template void ObjectPrinter::register_value<uint16_t>(const std::string&,
                                                      uint16_t,
                                                      std::string_view,
                                                      int);
template void ObjectPrinter::register_value<uint32_t>(const std::string&,
                                                      uint32_t,
                                                      std::string_view,
                                                      int);
template void ObjectPrinter::register_value<uint64_t>(const std::string&,
                                                      uint64_t,
                                                      std::string_view,
                                                      int);
template void ObjectPrinter::register_value<int8_t>(const std::string&,
                                                    int8_t,
                                                    std::string_view,
                                                    int);
template void ObjectPrinter::register_value<int16_t>(const std::string&,
                                                     int16_t,
                                                     std::string_view,
                                                     int);
template void ObjectPrinter::register_value<int32_t>(const std::string&,
                                                     int32_t,
                                                     std::string_view,
                                                     int);
template void ObjectPrinter::register_value<int64_t>(const std::string&,
                                                     int64_t,
                                                     std::string_view,
                                                     int);
template void ObjectPrinter::register_value<float>(const std::string&,
                                                   float,
                                                   std::string_view,
                                                   int);
template void ObjectPrinter::register_value<double>(const std::string&,
                                                    double,
                                                    std::string_view,
                                                    int);

// Add missing char instantiation
template void ObjectPrinter::register_value<char>(const std::string&, char, std::string_view, int);

// Add missing std::string instantiation
template void ObjectPrinter::register_value<std::string>(const std::string&,
                                                         std::string,
                                                         std::string_view,
                                                         int);
// Standard containers
template void ObjectPrinter::register_container<std::vector<int>>(const std::string&,
                                                                  const std::vector<int>&,
                                                                  std::string_view,
                                                                  int);
template void ObjectPrinter::register_container<std::vector<float>>(const std::string&,
                                                                    const std::vector<float>&,
                                                                    std::string_view,
                                                                    int);
template void ObjectPrinter::register_container<std::vector<double>>(const std::string&,
                                                                     const std::vector<double>&,
                                                                     std::string_view,
                                                                     int);
template void ObjectPrinter::register_container<std::vector<std::string>>(
    const std::string&,
    const std::vector<std::string>&,
    std::string_view,
    int);
template void ObjectPrinter::register_container<std::vector<uint16_t>>(const std::string&,
                                                                       const std::vector<uint16_t>&,
                                                                       std::string_view,
                                                                       int);
template void ObjectPrinter::register_container<std::array<float, 3>>(const std::string&,
                                                                      const std::array<float, 3>&,
                                                                      std::string_view,
                                                                      int);

// 1D xtensor containers
template void ObjectPrinter::register_container<
    xt::xtensor_container<xt::uvector<float, xsimd::aligned_allocator<float, 16ul>>,
                          1ul,
                          xt::layout_type::row_major,
                          xt::xtensor_expression_tag>>(
    const std::string&,
    const xt::xtensor_container<xt::uvector<float, xsimd::aligned_allocator<float, 16ul>>,
                                1ul,
                                xt::layout_type::row_major,
                                xt::xtensor_expression_tag>&,
    std::string_view,
    int);

template void ObjectPrinter::register_container<
    xt::xtensor_container<xt::uvector<double, xsimd::aligned_allocator<double, 16ul>>,
                          1ul,
                          xt::layout_type::row_major,
                          xt::xtensor_expression_tag>>(
    const std::string&,
    const xt::xtensor_container<xt::uvector<double, xsimd::aligned_allocator<double, 16ul>>,
                                1ul,
                                xt::layout_type::row_major,
                                xt::xtensor_expression_tag>&,
    std::string_view,
    int);

template void ObjectPrinter::register_container<
    xt::xtensor_container<xt::uvector<unsigned int, xsimd::aligned_allocator<unsigned int, 16ul>>,
                          1ul,
                          xt::layout_type::row_major,
                          xt::xtensor_expression_tag>>(
    const std::string&,
    const xt::xtensor_container<
        xt::uvector<unsigned int, xsimd::aligned_allocator<unsigned int, 16ul>>,
        1ul,
        xt::layout_type::row_major,
        xt::xtensor_expression_tag>&,
    std::string_view,
    int);

// 2D xtensor containers
template void ObjectPrinter::register_container<
    xt::xtensor_container<xt::uvector<float, xsimd::aligned_allocator<float, 16ul>>,
                          2ul,
                          xt::layout_type::row_major,
                          xt::xtensor_expression_tag>>(
    const std::string&,
    const xt::xtensor_container<xt::uvector<float, xsimd::aligned_allocator<float, 16ul>>,
                                2ul,
                                xt::layout_type::row_major,
                                xt::xtensor_expression_tag>&,
    std::string_view,
    int);

template void ObjectPrinter::register_container<
    xt::xtensor_container<xt::uvector<uint16_t, xsimd::aligned_allocator<uint16_t, 16ul>>,
                          2ul,
                          xt::layout_type::row_major,
                          xt::xtensor_expression_tag>>(
    const std::string&,
    const xt::xtensor_container<xt::uvector<uint16_t, xsimd::aligned_allocator<uint16_t, 16ul>>,
                                2ul,
                                xt::layout_type::row_major,
                                xt::xtensor_expression_tag>&,
    std::string_view,
    int);

template void ObjectPrinter::register_container<
    xt::xtensor_container<xt::uvector<unsigned int, xsimd::aligned_allocator<unsigned int, 16ul>>,
                          2ul,
                          xt::layout_type::row_major,
                          xt::xtensor_expression_tag>>(
    const std::string&,
    const xt::xtensor_container<
        xt::uvector<unsigned int, xsimd::aligned_allocator<unsigned int, 16ul>>,
        2ul,
        xt::layout_type::row_major,
        xt::xtensor_expression_tag>&,
    std::string_view,
    int);

// Add missing std::array instantiations
template void ObjectPrinter::register_container<std::array<unsigned char, 4>>(
    const std::string&,
    const std::array<unsigned char, 4>&,
    std::string_view,
    int);

template void ObjectPrinter::register_container<std::array<unsigned char, 7>>(
    const std::string&,
    const std::array<unsigned char, 7>&,
    std::string_view,
    int);

// Add missing std::vector<uint64_t> instantiation
template void ObjectPrinter::register_container<std::vector<uint64_t>>(const std::string&,
                                                                       const std::vector<uint64_t>&,
                                                                       std::string_view,
                                                                       int);

// Add missing std::vector<unsigned int> instantiation
template void ObjectPrinter::register_container<std::vector<unsigned int>>(
    const std::string&,
    const std::vector<unsigned int>&,
    std::string_view,
    int);

// Add missing std::vector<int64_t> instantiation
template void ObjectPrinter::register_container<std::vector<int64_t>>(const std::string&,
                                                                      const std::vector<int64_t>&,
                                                                      std::string_view,
                                                                      int);

// Add missing char vector instantiations
template void ObjectPrinter::register_container<std::vector<unsigned char>>(
    const std::string&,
    const std::vector<unsigned char>&,
    std::string_view,
    int);

template void ObjectPrinter::register_container<std::vector<signed char>>(
    const std::string&,
    const std::vector<signed char>&,
    std::string_view,
    int);

template void ObjectPrinter::register_container<std::vector<int16_t>>(const std::string&,
                                                                      const std::vector<int16_t>&,
                                                                      std::string_view,
                                                                      int);

// Add missing optional value instantiations
template void ObjectPrinter::register_optional_value<unsigned char>(const std::string&,
                                                                    std::optional<unsigned char>,
                                                                    std::string_view,
                                                                    std::string_view,
                                                                    int);
// Add missing optional value instantiations
template void ObjectPrinter::register_optional_value<std::string>(const std::string&,
                                                                  std::optional<std::string>,
                                                                  std::string_view,
                                                                  std::string_view,
                                                                  int);

template void ObjectPrinter::register_optional_value<float>(const std::string&,
                                                            std::optional<float>,
                                                            std::string_view,
                                                            std::string_view,
                                                            int);
template void ObjectPrinter::register_optional_value<double>(const std::string&,
                                                             std::optional<double>,
                                                             std::string_view,
                                                             std::string_view,
                                                             int);

// template void ObjectPrinter::register_optional_value<uint8_t>(const std::string&,
//                                                               std::optional<uint8_t>,
//                                                               std::string_view,
//                                                               std::string_view,
//                                                               int);
template void ObjectPrinter::register_optional_value<uint16_t>(const std::string&,
                                                               std::optional<uint16_t>,
                                                               std::string_view,
                                                               std::string_view,
                                                               int);
template void ObjectPrinter::register_optional_value<uint32_t>(const std::string&,
                                                               std::optional<uint32_t>,
                                                               std::string_view,
                                                               std::string_view,
                                                               int);
template void ObjectPrinter::register_optional_value<uint64_t>(const std::string&,
                                                               std::optional<uint64_t>,
                                                               std::string_view,
                                                               std::string_view,
                                                               int);

// template void ObjectPrinter::register_optional_value<int8_t>(const std::string&,
//                                                              std::optional<int8_t>,
//                                                              std::string_view,
//                                                              std::string_view,
//                                                              int);
template void ObjectPrinter::register_optional_value<int16_t>(const std::string&,
                                                              std::optional<int16_t>,
                                                              std::string_view,
                                                              std::string_view,
                                                              int);
template void ObjectPrinter::register_optional_value<int32_t>(const std::string&,
                                                              std::optional<int32_t>,
                                                              std::string_view,
                                                              std::string_view,
                                                              int);
template void ObjectPrinter::register_optional_value<int64_t>(const std::string&,
                                                              std::optional<int64_t>,
                                                              std::string_view,
                                                              std::string_view,
                                                              int);

// Add missing 1D xtensor container for signed char
template void ObjectPrinter::register_container<
    xt::xtensor_container<xt::uvector<signed char, xsimd::aligned_allocator<signed char, 16ul>>,
                          1ul,
                          xt::layout_type::row_major,
                          xt::xtensor_expression_tag>>(
    const std::string&,
    const xt::xtensor_container<
        xt::uvector<signed char, xsimd::aligned_allocator<signed char, 16ul>>,
        1ul,
        xt::layout_type::row_major,
        xt::xtensor_expression_tag>&,
    std::string_view,
    int);

// Add missing 1D xtensor container for uint16_t
template void ObjectPrinter::register_container<
    xt::xtensor_container<xt::uvector<uint16_t, xsimd::aligned_allocator<uint16_t, 16ul>>,
                          1ul,
                          xt::layout_type::row_major,
                          xt::xtensor_expression_tag>>(
    const std::string&,
    const xt::xtensor_container<xt::uvector<uint16_t, xsimd::aligned_allocator<uint16_t, 16ul>>,
                                1ul,
                                xt::layout_type::row_major,
                                xt::xtensor_expression_tag>&,
    std::string_view,
    int);

// Add missing 3D xtensor container for float
template void ObjectPrinter::register_container<
    xt::xtensor_container<xt::uvector<float, xsimd::aligned_allocator<float, 16ul>>,
                          3ul,
                          xt::layout_type::row_major,
                          xt::xtensor_expression_tag>>(
    const std::string&,
    const xt::xtensor_container<xt::uvector<float, xsimd::aligned_allocator<float, 16ul>>,
                                3ul,
                                xt::layout_type::row_major,
                                xt::xtensor_expression_tag>&,
    std::string_view,
    int);

// Add missing 3D xtensor container for uint16_t
template void ObjectPrinter::register_container<
    xt::xtensor_container<xt::uvector<uint16_t, xsimd::aligned_allocator<uint16_t, 16ul>>,
                          3ul,
                          xt::layout_type::row_major,
                          xt::xtensor_expression_tag>>(
    const std::string&,
    const xt::xtensor_container<xt::uvector<uint16_t, xsimd::aligned_allocator<uint16_t, 16ul>>,
                                3ul,
                                xt::layout_type::row_major,
                                xt::xtensor_expression_tag>&,
    std::string_view,
    int);

}
}
}