# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
# SPDX-FileCopyrightText: 2019 - 2022 Daniil Goncharov
#
# SPDX-License-Identifier: MIT

project(
    'sse2neon', ['cpp'],
    default_options: ['cpp_std=c++20'],
    version: 'v1.7.0',
)

sse2neon_include = include_directories('.')

# list and install headers
headers = [
    'sse2neon.h',
    ]

install_headers(headers, preserve_path: false)

sse2neon_dep = declare_dependency(
    include_directories: sse2neon_include,
)

