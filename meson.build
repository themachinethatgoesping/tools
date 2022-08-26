# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# --- Project ---
# Define project meta data
project(
  'themachinethatgoesping_tools',
  'cpp',
  license: 'MPL-2.0',

  version: '0.5.1',
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

# indicators for pretty progress bars
indicators_dep = dependency('indicators', required: false)
if not indicators_dep.found()
    indicators_dep = subproject('indicators').get_variable('indicators_dep')
endif

#date (to be replaced with c++20 features)
hinnant_date_dep = subproject('hinnant-date', default_options: 'header_only=true').get_variable('date_dep')

#bitsery (for object serialization)
bitsery_dep = dependency('bitsery', required: false)
if not bitsery_dep.found()
  bitsery_dep = subproject('bitsery').get_variable('bitsery_dep')
endif

#magic_enum (for enum reflection)
magic_enum_dep = dependency('magic_enum', required: false)

if not magic_enum_dep.found()
  magic_enum_dep = subproject('magic_enum').get_variable('magic_enum_dep')
endif

#xtensor (for numpy array support)
xtensor_dep = dependency('xtensor', required: false)

if not xtensor_dep.found()
  xtensor_dep = subproject('xtensor').get_variable('xtensor_dep')
endif

#themachinethatgoesping meta info
meta_dep = dependency('themachinethatgoesping_meta', required: false)
if not meta_dep.found()
    meta_dep = subproject('meta').get_variable('meta_dep')
endif

#setup test_data_path
test_data_path = '-D__PROJECT_TESTDATADIR__="' + meson.current_source_dir() + '/test_data"'

# add c++ src
subdir('src')
 
# add python src
subdir('python')

