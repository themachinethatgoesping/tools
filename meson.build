# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# --- Project ---
# Define project meta data
project(
  'themachinethatgoesping_tools',
  'cpp',
  license: 'MPL-2.0',

  version: '0.0.1.6-1',
  default_options: ['warning_level=3', 'buildtype=release', 'cpp_std=c++17'],
  meson_version: '>=0.62' #force new meson version to limit necessary testing
)

projectnamespace = 'themachinethatgoesping'

# --- dependencies ---
# system
if meson.get_compiler('cpp').get_id() == 'clang'
  omp_dep = declare_dependency(
    compile_args: ['-Xpreprocessor', '-fopenmp']
  )
else
  omp_dep = dependency('openmp')
endif

# # boost
boost_version = '>=1.73'
boost_modules = dependency('boost', modules: ['filesystem'], static: true, version: boost_version)
boost_dep     = dependency('boost', version: boost_version)

# eigen 3
eigen3_dep = dependency('eigen3', required: false)

if not eigen3_dep.found()
    eigen3_dep = subproject('eigen').get_variable('eigen_dep')
endif

# fmt for pretty printing
fmt_dep = dependency('fmt', required: false)

if not fmt_dep.found()
    fmt_dep = subproject('fmt', default_options: 'default_library=static').get_variable('fmt_dep')
endif

#date (to be replaced with c++20 features)
hinnant_date_project = subproject('hinnant-date', default_options: 'use_manual_tzdb=true')
hinnant_date_incl = hinnant_date_project.get_variable('i')

hinnant_date_dep = declare_dependency(
 include_directories : hinnant_date_incl
 )

#bitsery (for object serialization)
bitsert_dep = declare_dependency(
  include_directories : ['extern/bitsery/include/']
)

#magic_enum (for enum reflection)
magic_enum_dep = declare_dependency(
  include_directories : ['extern/magic_enum/include/']
)

#setup test_data_path
test_data_path = '-D__PROJECT_TESTDATADIR__="' + meson.current_source_dir() + '/test_data"'

# add c++ src
subdir('src')
 
# add python src
subdir('python')

