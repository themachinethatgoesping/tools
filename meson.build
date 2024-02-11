# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# --- Project ---
# Define project meta data
project(
  'themachinethatgoesping_tools',
  'cpp',
  license: 'MPL-2.0',

  version: '0.22.1',
  default_options: ['warning_level=2', 'buildtype=release', 'cpp_std=c++20'],
  meson_version: '>=1.1' #last meson version that was tested
)

projectnamespace = 'themachinethatgoesping'

# --- dependencies ---

# system
if meson.get_compiler('cpp').get_id() == 'clang-cl'
  libomp = meson.get_compiler('cpp').find_library('libomp')
  omp_dep = declare_dependency(
  compile_args : ['-fopenmp'],
  dependencies : [libomp]
  )
elif  meson.get_compiler('cpp').get_id() == 'clang'
  # libomp = meson.get_compiler('cpp').find_library('libomp5')
  # omp_dep = declare_dependency(
  # compile_args : ['-fopenmp'],
  # dependencies : [libomp]
  # )
  omp_dep = dependency('openmp')
else
  omp_dep = dependency('openmp')
endif

# extra compiler args when for the tools target
tools_compile_args = ['-D_USE_MATH_DEFINES', '-fPIC']

# # boost
boost_version = '>=1.73'
boost_modules = dependency('boost', modules: ['iostreams'], static: get_option('dynamic_boost').disabled(), version: boost_version)
boost_dep     = dependency('boost', version: boost_version)

# eigen 3
eigen3_dep = dependency('eigen3')

# fmt for pretty printing
#fmt_dep = dependency('fmt', static: true, version: 10.0)
fmt_dep = subproject('fmt', default_options: 'default_library=static').get_variable('fmt_dep')

# frozen constexpr containers
#fmt_dep = dependency('fmt', static: true, version: 10.0)
frozen_dep = subproject('frozen', default_options: 'default_library=static').get_variable('frozen_dep')

# indicators for pretty progress bars
indicators_dep = dependency('indicators', static: true)

#date (to be replaced with c++20 features)
hinnant_date_dep = subproject('hinnant-date', default_options: 'header_only=true').get_variable('date_dep')

#magic_enum (for enum reflection)
magic_enum_dep = dependency('magic_enum')
tools_compile_args += '-DMAGIC_ENUM_ENABLE_HASH' #reduce complexity of enum_name and enum_switch at the price of increased memory and compilation time

#xtensor (for numpy array support)
xtensor_dep = dependency('xtensor', static: true, default_options: ['xsimd=enabled'])

#fast_float (for fast locale independent float parsing)
fast_float_dep = dependency('fast_float')

#xxhash_cpp (for fast hashing of classes/buffers)
xxhash_cpp_dep = dependency('xxhash_cpp')

# -- python modules --
if get_option('build_pythonmodule').enabled()

  pymod = import('python').find_installation(get_option('python_path'), pure: false)

  python3_dep = pymod.dependency()
  pybind11_dep = dependency('pybind11')
  xtensor_python_dep = dependency('xtensor-python', static: true)

  # -- numpy (necessary for xtensor_python) --
  #numpy (copied from https://github.com/mesonbuild/meson/issues/9598)
  # NumPy include directory - needed in all submodules
  py3 = find_program('python3', 'python')
  incdir_numpy = run_command(py3,
  [
      '-c',
      'import os; os.chdir(".."); import numpy; print(numpy.get_include())'
  ],
  check: true
  ).stdout().strip()

  inc_np = include_directories(incdir_numpy)
  numpy_dep = declare_dependency(include_directories: inc_np)

  # set path where to install sources (pythonpath/site-packages/projectnamespace)
  message('python module install directory:', pymod.get_install_dir(subdir: projectnamespace))
endif

#themachinethatgoesping meta info
meta_dep = dependency('themachinethatgoesping_meta')

#setup test_data_path
test_data_path = '-D__PROJECT_TESTDATADIR__="' + meson.current_source_dir() + '/test_data"'

# add c++ src
subdir('src')
 
# add python src
subdir('python')

