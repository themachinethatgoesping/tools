// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// SPDX-FileCopyrightText: (c)2019 Michael Tesch. tesch1@gmail.com (struct
// fmt::formatter<std::complex<T>,Char> : public fmt::formatter<T,Char>)
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief An object that allows for easy pretty printing of class members
 * usage:
 *  1. Implement a __printer__ function as public class member this function should return a
 *     ObjectPrinter object. Register all, values, containers, objects that are to be printed.
 *  2. Add the __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__ macro to the public functions.
 *     This macro implements std::string info_string() and print(std::ostream) functions using the
 * object printer
 *  3. Add the __PYCLASS_DEFAULT_PRINTING__ to the python module defintion. This macro implements
 *     __str__(), __repr__(), info_string() and print() as python functions
 *
 */

#pragma once

/* generated doc strings */
#include ".docstrings/objectprinter.doc.hpp"

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <iosfwd>
#include <magic_enum/magic_enum.hpp>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "stream.hpp"

// // Forward declarations
// namespace fmt {
// template<typename T, typename Char>
// struct formatter;
// }

// // source https://gitlab.com/tesch1/cppduals/blob/master/duals/dual#L1379-1452
// // and https://github.com/fmtlib/fmt/issues/1467#issuecomment-1595660866
// // This is a formatter that allows for using std::complex in fmt::format
// template<typename T, typename Char>
// struct fmt::formatter<std::complex<T>, Char> : public fmt::formatter<T, Char>
// {
//   private:
//     typedef fmt::formatter<T, Char> base;
//     enum style
//     {
//         expr,
//         star,
//         pair
//     } style_ = expr;

//     detail::dynamic_format_specs<Char> specs_;

//   public:
//     template<typename ParseContext>
//     FMT_CONSTEXPR auto parse(ParseContext& ctx) -> const Char*;

//     template<typename FormatContext>
//     FMT_CONSTEXPR auto format(const std::complex<T>& x,
//                               FormatContext&         ctx) const -> decltype(ctx.out());
// };

// --- print functions (need objectprinter __printer__ function that returns an ObjectPrinter) ---
#define __CLASSHELPER_PRINTER_INFO_STRING__                                                        \
    /**                                                                                            \
     * @brief return an info string using the class __printer__ object                             \
     * @param float_precision number of digits for floating point values                           \
     * @param superscript_exponents print exponents in superscript                                 \
     * @return std::string                                                                         \
     */                                                                                            \
    std::string info_string(unsigned int float_precision = 3, bool superscript_exponents = true)   \
        const                                                                                      \
    {                                                                                              \
        return this->__printer__(float_precision, superscript_exponents).create_str();             \
    }

#define __CLASSHELPER_PRINTER_PRINT__                                                              \
    /**                                                                                            \
     * @brief print the object information to the given outpustream                                \
     *                                                                                             \
     * @param os output stream, e.g. file stream or std::out or std::cerr                          \
     * @param float_precision number of digits for floating point values                           \
     * @param superscript_exponents print exponents in superscript                                 \
     */                                                                                            \
    void print(std::ostream& os,                                                                   \
               unsigned int  float_precision       = 3,                                            \
               bool          superscript_exponents = true) const                                            \
    {                                                                                              \
        os << this->__printer__(float_precision, superscript_exponents).create_str() << std::endl; \
    }

#define __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__                                                 \
    __CLASSHELPER_PRINTER_INFO_STRING__                                                            \
    __CLASSHELPER_PRINTER_PRINT__

namespace themachinethatgoesping {
namespace tools {
namespace classhelper {

/**
 * @brief Class that allows for easy pretty printing of class members
 * usage:
 *  1. Implement a __printer__ function as public class member this function should return a
 *     ObjectPrinter object. Register all, values, containers, objects that are to be printed.
 *  2. Add the __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__ macro to the public functions.
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
        tvalue,     ///< double or integer
        tenum,      ///< enumerator
        tcontainer, ///< 1D container (floating point or integer)
        tstring,    ///< formatted string field
        tsection    ///< section break
    };

    std::string                           _name;        ///< name of the class that is to be printed
    std::vector<std::string>              _fields;      ///< variable names
    std::vector<t_field>                  _field_types; ///< variable types
    std::vector<std::vector<std::string>> _lines;       ///< first line is typically the field value
    std::vector<std::string>              _value_infos; ///< additional info (printed in [])
    std::vector<char>                     _section_underliner; ///< additional info (printed in [])

    unsigned int _float_precision       = 3;
    bool         _superscript_exponents = true;

    /**
     * @brief Construct a new Object Printer object
     *
     * @param float_precision default 2, set number of digits for floating point values
     */
    ObjectPrinter() = default;

  public:
    // serialization support
    static ObjectPrinter from_stream(std::istream& is);
    void                 to_stream(std::ostream& os) const;

    ObjectPrinter __printer__(unsigned int float_precision, bool superscript_exponents) const;

    __STREAM_DEFAULT_TOFROM_BINARY_FUNCTIONS__(ObjectPrinter)
    __CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__

  public:
    /**
     * @brief Construct a new Object Printer object
     *
     * @param name name of the class that is to be printed
     */
    ObjectPrinter(std::string_view name, unsigned int float_precision, bool superscript_exponents);

    /**
     * @brief Remove all existing sections
     *
     */
    void remove_sections();

    /**
     * @brief Append the fields of an existing object printer
     *
     * @param printer printer to be appended
     */
    void append(ObjectPrinter printer, char remove_sections = false, char section_underliner = 0);

    // --- functions to register values for printing ----
    void _register_enum_string(std::string_view name,
                               std::string_view value_str,
                               std::string_view value_info = "",
                               int              pos        = -1);
    /**
     * @brief register an enumeration for printing
     *
     * @tparam t_value enumerator
     * @param name name of the variable
     * @param value value of the variable
     * @param value_info additional info (is printed in [] behind the variable)
     * @param pos position where the value is registers (if negative, the value is appended)
     */
    // Template implementations
    template<typename t_value>
    void register_enum(std::string_view name,
                       t_value          value,
                       std::string_view value_info = "",
                       int              pos        = -1)
    {
        std::string str;

        // convert enum value to string using magic_enum library
        str = magic_enum::enum_name(value);

        _register_enum_string(
            name,
            str,
            fmt::format("{}{}", value_info, fmt::join(magic_enum::enum_names<t_value>(), ", ")),
            pos);
    }

    /**
     * @brief Registers an optional value with the given name and additional information.
     *
     * This function checks if the optional value has a value. If it does, it registers the value
     * using the provided name, value information, and position. If the optional value does not
     * have a value, it registers the string "Not set" instead.
     *
     * @tparam t_value The type of the optional value.
     * @param name The name to register the value under.
     * @param value The optional value to register.
     * @param value_info Additional information about the value (default is an empty string).
     * @param pos The position to register the value at (default is -1).
     */
    template<typename t_value>
    void register_optional_value(std::string_view       name,
                                 std::optional<t_value> value,
                                 std::string_view       value_info     = "",
                                 std::string_view       optional_value = "Not set",
                                 int                    pos            = -1);

    /**
     * @brief register a single integer of floating point value for printing
     *
     * @tparam t_value double or floating point
     * @param name name of the variable
     * @param value value of the variable
     * @param value_info additional info (is printed in [] behind the variable)
     * @param pos position where the value is registers (if negative, the value is appended)
     */
    template<typename t_value>
    void register_value(std::string_view name,
                        t_value          value,
                        std::string_view value_info = "",
                        int              pos        = -1);

    /**
     * @brief register a single integer of floating point value for printing
     * The value is assumed to be in bytes. It will be converted to bytes, KB, MB, GB
     *
     * @param name name of the variable
     * @param value value of the variable in bytes
     * @param pos position where the value is registers (if negative, the value is appended)
     */
    void register_value_bytes(std::string_view name, size_t value, int pos = -1);

    /**
     * @brief register a 1D container for printing
     *
     * @tparam t_value integer or floating point
     * @param name name of the container
     * @param value container values
     * @param value_info additional info (is printed in [] behind the variable)
     * @param pos position where the value is registers (if negative, the value is appended)
     */
    template<typename t_container>
    void register_container(std::string_view   name,
                            const t_container& values,
                            std::string_view   value_info = "",
                            int                pos        = -1);

    /**
     * @brief register a formatted string field for printing, with delimiters
     *
     * @param name name of the variable
     * @param value value of the variable
     * @param delimiter_left left delimiter
     * @param delimiter_right right delimiter
     * @param value_info additional info (is printed in [] behind the variable)
     * @param pos position where the value is registers (if negative, the value is appended)
     * @param max_visible_elements maximum of chars that are printed (if 0, all elements are
     * printed)
     */
    void register_string_with_delimiters(std::string_view name,
                                         std::string_view value,
                                         std::string_view value_info           = "",
                                         std::string_view delimiter_left       = "\"",
                                         std::string_view delimiter_right      = "\"",
                                         int              pos                  = -1,
                                         size_t           max_visible_elements = 0);

    /**
     * @brief register a formatted string field for printing
     *
     * @param name name of the variable
     * @param value value of the variable
     * @param value_info additional info (is printed in [] behind the variable)
     * @param pos position where the value is registers (if negative, the value is appended)
     * @param max_visible_elements maximum of chars that are printed (if 0, all elements are
     * printed)
     */
    void register_string(std::string_view name,
                         std::string_view value_str,
                         std::string_view value_info           = "",
                         int              pos                  = -1,
                         size_t           max_visible_elements = 0);

    /**
     * @brief register a section break for printing
     *
     * @param name name of the following section
     * @param underliner character used to underline the section name
     * @param pos position where the value is registers (if negative, the value is appended)
     */
    void register_section(std::string_view name, char underliner = '-', int pos = -1);

    /**
     * @brief Get the registered name of the object
     *
     * @return std::string
     */
    std::string class_name() const;

    /**
     * @brief Create an info_string from the registered values/sections
     *
     * @return std::string
     */
    std::string create_str() const;

    /**
     * @brief add a line under a given line string
     *
     * @param line input string
     * @return std::string
     */
    static std::string underline(std::string_view line, char underliner);
};

}
}
}
