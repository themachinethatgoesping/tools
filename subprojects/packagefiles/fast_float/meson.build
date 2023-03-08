# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
# SPDX-FileCopyrightText: 2019 - 2022 Daniil Goncharov
#
# SPDX-License-Identifier: MIT

project(
    'fast_float', ['cpp'],
    default_options: ['cpp_std=c++17'],
    version: '3.10.1',
)

fast_float_include = include_directories('include')

fast_float_dep = declare_dependency(
    include_directories: fast_float_include,
)

# list and install headers
headers = [
    'include/fast_float/ascii_number.h',
    'include/fast_float/bigint.h',
    'include/fast_float/decimal_to_binary.h',
    'include/fast_float/digit_comparison.h',
    'include/fast_float/fast_float.h',
    'include/fast_float/fast_table.h',
    'include/fast_float/float_common.h',
    'include/fast_float/parse_number.h',
    'include/fast_float/simple_decimal_conversion.h',
    'tests/build_tests/issue72/test.h'
    ]

#install_headers(headers, preserve_path: false)
