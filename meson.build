# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# --- Project ---
# Define project meta data
project(
  'themachinethatgoesping_tools',
  'cpp',
  license : 'MPL-2.0'

  version : '0.0.1.6-1',
  default_options : ['warning_level=3', 'buildtype=release', 'cpp_std=c++17']
)
)

projectnamespace = 'themachinethatgoesping'

# --- dependencies ---
# system
omp_dep    = dependency('openmp')

# boost
boost_modules = dependency('boost', modules : ['filesystem'])
boost_dep     = dependency('boost')

# eigen 3
eigen3_dep = dependency('eigen3', required : false)

if not eigen3_dep.found()
    eigen3_project = subproject('eigen')
    eigen3_dep = eigen3_project.get_variable('eigen_dep')
endif

# date (to be replaced with c++20 features)
hinnant_date_project = subproject('hinnant-date', default_options : 'use_manual_tzdb=true')
#hinnant_date_dep = hinnant_date_project.get_variable('date_dep')
hinnant_date_incl = hinnant_date_project.get_variable('i')

hinnant_date_dep = declare_dependency(
  include_directories : hinnant_date_incl
  )


# add src
subdir('src')
 
 # add python files
subdir('py_ext')

# add tests
subdir('tests')
 
