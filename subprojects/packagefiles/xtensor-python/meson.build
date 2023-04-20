# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MIT

project(
    'xtensor-python', ['cpp'],
    default_options: ['cpp_std=c++17'],
    version: '0.26.1',
)

xtensor_python_include = include_directories('include')

xtensor_python_dep = declare_dependency(
    include_directories: xtensor_python_include,
)

# list and install headers
subdir('include')
