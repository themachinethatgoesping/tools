# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# --- Project ---
# Define project meta data
project(
  'themachinethatgoesping_tools',
  'cpp',
  license: 'MPL-2.0',

  version: '0.6.2',
  default_options: ['warning_level=3', 'buildtype=release', 'cpp_std=c++17'],
  meson_version: '>=0.63' #0.63 added preserve_path for install headers option
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
boost_modules = dependency('boost', modules: ['iostreams'], static: true, version: boost_version)
boost_dep     = dependency('boost', version: boost_version)

# eigen 3
eigen3_dep = dependency('eigen3')

# fmt for pretty printing
#fmt_dep = dependency('fmt', static: true)
fmt_dep = subproject('fmt', default_options: 'default_library=static').get_variable('fmt_dep')

# indicators for pretty progress bars
indicators_dep = dependency('indicators')

#date (to be replaced with c++20 features)
hinnant_date_dep = subproject('hinnant-date', default_options: 'header_only=true').get_variable('date_dep')

#bitsery (for object serialization)
bitsery_dep = dependency('bitsery')

#magic_enum (for enum reflection)
magic_enum_dep = dependency('magic_enum')

#xtensor (for numpy array support)
xtensor_dep = dependency('xtensor')

#fast_float (for fast locale independent float parsing)
fast_float_dep = dependency('fast_float')


#themachinethatgoesping meta info
meta_dep = dependency('themachinethatgoesping_meta')

#setup test_data_path
test_data_path = '-D__PROJECT_TESTDATADIR__="' + meson.current_source_dir() + '/test_data"'

# add c++ src
subdir('src')
 
# add python src
subdir('python')

