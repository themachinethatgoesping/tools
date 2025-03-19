//sourcehash: e84430c2e53dad0f9e45166f9e70dd867396c97d3cad782004c83e54f3deef90

/*
  This file contains docstrings for use in the Python bindings.
  Do not edit! They were automatically extracted by pybind11_mkdoc.

  This is a modified version which allows for more than 8 arguments and includes def-guard
 */

#pragma once

#ifndef __DOCSTRINGS_HPP__

#define __EXPAND(x)                                                  x
#define __COUNT(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, COUNT, ...) COUNT
#define __VA_SIZE(...)                                               __EXPAND(__COUNT(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1))
#define __CAT1(a, b)                                                 a##b
#define __CAT2(a, b)                                                 __CAT1(a, b)
#define __DOC1(n1)                                                   __doc_##n1
#define __DOC2(n1, n2)                                               __doc_##n1##_##n2
#define __DOC3(n1, n2, n3)                                           __doc_##n1##_##n2##_##n3
#define __DOC4(n1, n2, n3, n4)                                       __doc_##n1##_##n2##_##n3##_##n4
#define __DOC5(n1, n2, n3, n4, n5)                                   __doc_##n1##_##n2##_##n3##_##n4##_##n5
#define __DOC6(n1, n2, n3, n4, n5, n6)                               __doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6
#define __DOC7(n1, n2, n3, n4, n5, n6, n7)                           __doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7
#define __DOC8(n1, n2, n3, n4, n5, n6, n7, n8)                                                     \
    __doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7##_##n8
#define __DOC9(n1, n2, n3, n4, n5, n6, n7, n8, n9)                                                 \
    __doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7##_##n8##_##n9
#define __DOC10(n1, n2, n3, n4, n5, n6, n7, n8, n9, n10)                                           \
    __doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7##_##n8##_##n9##_##n10
#define DOC(...) __EXPAND(__EXPAND(__CAT2(__DOC, __VA_SIZE(__VA_ARGS__)))(__VA_ARGS__))

#endif // NEW_DOC_HEADER_HPP
#if defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif


static const char *__doc_formatter = R"doc()doc";

static const char *__doc_formatter_format = R"doc()doc";

static const char *__doc_formatter_parse = R"doc()doc";

static const char *__doc_formatter_specs = R"doc()doc";

static const char *__doc_formatter_style = R"doc()doc";

static const char *__doc_formatter_style_2 = R"doc()doc";

static const char *__doc_formatter_style_expr = R"doc()doc";

static const char *__doc_formatter_style_pair = R"doc()doc";

static const char *__doc_formatter_style_star = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter =
R"doc(Class that allows for easy pretty printing of class members usage: 1.
Implement a __printer__ function as public class member this function
should return a ObjectPrinter object. Register all, values,
containers, objects that are to be printed. 2. Add the
__CLASSHELPER_DEFAULT_PRINTING_FUNCTIONS__ macro to the public
functions. This macro implements std::string info_string() and
print(std::ostream) functions using the object printer 3. Add the
__PYCLASS_DEFAULT_PRINTING__ to the python module defintion. This
macro implements __str__(), __repr__(), info_string() and print() as
python functions)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_ObjectPrinter =
R"doc(Construct a new Object Printer object

Parameter ``float_precision``:
    default 2, set number of digits for floating point values)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_ObjectPrinter_2 =
R"doc(Construct a new Object Printer object

Parameter ``name``:
    name of the class that is to be printed)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_append =
R"doc(Append the fields of an existing object printer

Parameter ``printer``:
    printer to be appended)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_binary_hash =
R"doc(compute a 64 bit hash of the object using xxhash and the \ to_binary
function. This function is called binary because the \ to_binary
function of the object is used)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_class_name =
R"doc(Get the registered name of the object

Returns:
    std::string)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_create_str =
R"doc(Create an info_string from the registered values/sections

Returns:
    std::string)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_field_types = R"doc(< variable types)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_fields = R"doc(< variable names)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_float_precision = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_from_binary =
R"doc(convert object to vector of bytes \ \

Parameter ``check_buffer_is_read_completely``:
    variable for interface compatibility, does not do \ anything \ \

Returns:
    vector of bytes \)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_from_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_info_string =
R"doc(\ return an info string using the class __printer__ object \

Parameter ``float_precision``:
    number of digits for floating point values \

Parameter ``superscript_exponents``:
    print exponents in superscript \

Returns:
    std::string \)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_name = R"doc(< name of the class that is to be printed)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_print =
R"doc(\ print the object information to the given outpustream \ \

Parameter ``os``:
    output stream, e.g. file stream or std::out or std::cerr \

Parameter ``float_precision``:
    number of digits for floating point values \

Parameter ``superscript_exponents``:
    print exponents in superscript \)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_register_container =
R"doc(register a 1D container for printing

Template parameter ``t_value``:
    integer or floating point

Parameter ``name``:
    name of the container

Parameter ``value``:
    container values

Parameter ``value_info``:
    additional info (is printed in [] behind the variable)

Parameter ``pos``:
    position where the value is registers (if negative, the value is
    appended))doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_register_enum =
R"doc(register an enumeration for printing

Template parameter ``t_value``:
    enumerator

Parameter ``name``:
    name of the variable

Parameter ``value``:
    value of the variable

Parameter ``value_info``:
    additional info (is printed in [] behind the variable)

Parameter ``pos``:
    position where the value is registers (if negative, the value is
    appended))doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_register_optional_value =
R"doc(Registers an optional value with the given name and additional
information.

This function checks if the optional value has a value. If it does, it
registers the value using the provided name, value information, and
position. If the optional value does not have a value, it registers
the string "Not set" instead.

Template parameter ``t_value``:
    The type of the optional value.

Parameter ``name``:
    The name to register the value under.

Parameter ``value``:
    The optional value to register.

Parameter ``value_info``:
    Additional information about the value (default is an empty
    string).

Parameter ``pos``:
    The position to register the value at (default is -1).)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_register_section =
R"doc(register a section break for printing

Parameter ``name``:
    name of the following section

Parameter ``underliner``:
    character used to underline the section name

Parameter ``pos``:
    position where the value is registers (if negative, the value is
    appended))doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_register_string =
R"doc(register a formatted string field for printing

Parameter ``name``:
    name of the variable

Parameter ``value``:
    value of the variable

Parameter ``value_info``:
    additional info (is printed in [] behind the variable)

Parameter ``pos``:
    position where the value is registers (if negative, the value is
    appended)

Parameter ``max_visible_elements``:
    maximum of chars that are printed (if 0, all elements are printed))doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_register_string_with_delimiters =
R"doc(register a formatted string field for printing, with delimiters

Parameter ``name``:
    name of the variable

Parameter ``value``:
    value of the variable

Parameter ``delimiter_left``:
    left delimiter

Parameter ``delimiter_right``:
    right delimiter

Parameter ``value_info``:
    additional info (is printed in [] behind the variable)

Parameter ``pos``:
    position where the value is registers (if negative, the value is
    appended)

Parameter ``max_visible_elements``:
    maximum of chars that are printed (if 0, all elements are printed))doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_register_value =
R"doc(register a single integer of floating point value for printing

Template parameter ``t_value``:
    double or floating point

Parameter ``name``:
    name of the variable

Parameter ``value``:
    value of the variable

Parameter ``value_info``:
    additional info (is printed in [] behind the variable)

Parameter ``pos``:
    position where the value is registers (if negative, the value is
    appended))doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_register_value_bytes =
R"doc(register a single integer of floating point value for printing The
value is assumed to be in bytes. It will be converted to bytes, KB,
MB, GB

Parameter ``name``:
    name of the variable

Parameter ``value``:
    value of the variable in bytes

Parameter ``pos``:
    position where the value is registers (if negative, the value is
    appended))doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_remove_sections = R"doc(Remove all existing sections)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_section_underliner = R"doc(< additional info (printed in []))doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_superscript_exponents = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_t_field =
R"doc(internal, describe the value type for implementing different printing
strategies)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_t_field_tcontainer = R"doc(< 1D container (floating point or integer))doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_t_field_tenum = R"doc(< enumerator)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_t_field_tsection = R"doc(< section break)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_t_field_tstring = R"doc(< formatted string field)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_t_field_tvalue = R"doc(< double or integer)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_to_binary =
R"doc(convert object to vector of bytes \ \

Parameter ``resize_buffer``:
    variable for interface compatibility, does not do anything \ \

Returns:
    vector of bytes \)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_to_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_underline =
R"doc(add a line under a given line string

Parameter ``line``:
    input string

Returns:
    std::string)doc";

static const char *__doc_themachinethatgoesping_tools_classhelper_ObjectPrinter_value_infos = R"doc(< additional info (printed in []))doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif


