# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MIT

project(
    'bitsery', ['cpp'],
    default_options: ['cpp_std=c++17'],
    version: '5.2.2',
)

bitsery_include = include_directories('include')

bitsery_dep = declare_dependency(
    include_directories: bitsery_include,
)

# list and install headers
subdir('include')
