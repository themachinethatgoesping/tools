# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
# SPDX-FileCopyrightText: 2019 - 2022 Daniil Goncharov
#
# SPDX-License-Identifier: MIT

project(
    'magic_enum', ['cpp'],
    default_options: ['cpp_std=c++17'],
    version: '0.8.0',
)

magic_enum_include = include_directories('include')

magic_enum_dep = declare_dependency(
    include_directories: magic_enum_include,
)

# list and install headers
headers = [
    'include/magic_enum.hpp',
    'include/magic_enum_fuse.hpp',
]

install_headers(headers, preserve_path: false)
