# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MIT

project(
    'indicators', ['cpp'],
    default_options: ['cpp_std=c++17'],
    version: '2.2',
)

indicators_include = include_directories('include')

indicators_dep = declare_dependency(
    include_directories: indicators_include,
)

# list and install headers
subdir('include')
