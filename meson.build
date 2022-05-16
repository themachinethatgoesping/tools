# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# --- Project ---
# Define project meta data
project(
  'tools',
  'cpp',
version : '0.0.1',
default_options : ['warning_level=3', 'buildtype=release', 'cpp_std=c++20']
)


# --- dependencies ---
# system
omp    = dependency('openmp')

# boost
boost_modules  = dependency('boost', modules : ['filesystem'])
boost  = dependency('boost')

# eigen 3
eigen3 = dependency('eigen3', required : false)

if not eigen3.found()
    eigen3 = subproject('eigen')
    eigen3 = eigen3.get_variable('eigen_dep')
endif


# add src
subdir('src')
 
# add tests
#subdir('tests')
 
