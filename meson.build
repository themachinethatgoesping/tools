# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# --- Project ---
# Define project meta data
project(
  'themachinethatgoesping_tools',
  'cpp',
  license: 'MPL-2.0',

  version: '0.31.0',
  default_options: ['warning_level=0', 'buildtype=release', 'cpp_std=c++23'],
  meson_version: '>=1.8.1' #there is a problem with meson 1.8.0 so just use a higher version,
)

projectnamespace = 'themachinethatgoesping'

# --- dependencies ---

# openmp (not used in clang-cl / windows)
omp_dep = declare_dependency()
if meson.get_compiler('cpp').get_id() != 'clang-cl' or get_option('force_openmp').enabled()
  omp_dep = dependency('openmp')
endif

# extra compiler args when for the tools target
tools_compile_args = ['-D_USE_MATH_DEFINES', 
#'-march=x86-64-v3',
#'-mtune=generic',
#'-funroll-loops'
]

if meson.get_compiler('cpp').get_id() == 'gcc'
  # require minimum gcc version 14
  gcc_version = meson.get_compiler('cpp').version()
  if not gcc_version.version_compare('>=14.0')
    error(
      'GCC version 14.0 or newer is required for building the tools module. Found version '
      + gcc_version,
    )
  endif

  # TODO: find a way to include these warnings again
  # these are generated in xtensor and I don't know how to deal with them ...
  tools_compile_args += '-Wno-array-bounds'
  tools_compile_args += '-Wno-maybe-uninitialized'
  tools_compile_args += '-Wno-stringop-overflow'
  tools_compile_args += '-Wno-stringop-overread'
  # Suppress unused function warnings from third-party libraries like Catch2
  tools_compile_args += '-Wno-unused-function'
  
elif meson.get_compiler('cpp').get_id() == 'clang'
  # Clang-specific warning suppressions (different from GCC)
  tools_compile_args += '-Wno-array-bounds'
  # Suppress warnings from third-party headers like SSE2NEON
  tools_compile_args += '-Wno-#warnings'
  # Suppress unused function warnings from third-party libraries like Catch2
  tools_compile_args += '-Wno-unused-function'
  # Note: -Wno-maybe-uninitialized and -Wno-stringop-overflow are GCC-specific
  # and not recognized by Clang, so we don't include them here

endif

# # boost
boost_version = '>=1.73'
boost_modules = dependency(
  'boost',
  modules: ['iostreams'],
  static: get_option('dynamic_boost').disabled(),
  version: boost_version,
  include_type: 'system'
)
boost_dep = dependency('boost', version: boost_version, include_type: 'system')

# eigen 3
eigen3_dep = dependency('eigen3', version: '>=3.4', include_type: 'system')

# fmt for pretty printing
#fmt_dep = dependency('fmt', static: true, version: 10.0)
fmt_dep = subproject('fmt', default_options: ['default_library=static']).get_variable('fmt_dep')

# frozen constexpr containers
#fmt_dep = dependency('fmt', static: true, version: 10.0)
frozen_dep = subproject('frozen', default_options: 'default_library=static').get_variable('frozen_dep')

# indicators for pretty progress bars
indicators_dep = dependency('indicators', static: true)

#date (to be replaced with c++23 features)
#hinnant_date_dep = subproject('hinnant-date', default_options: 'header_only=true').get_variable('date_dep')

#magic_enum (for enum reflection)
magic_enum_dep = dependency('magic_enum')
tools_compile_args += '-DMAGIC_ENUM_ENABLE_HASH' #reduce complexity of enum_name and enum_switch at the price of increased memory and compilation time

#xtensor (for numpy array support)
xtensor_dep = dependency('xtensor', static: true, default_options: ['xsimd=enabled']).as_system('system')

#fast_float (for fast locale independent float parsing)
fast_float_dep = dependency('fast_float')

#xxhash_cpp (for fast hashing of classes/buffers)
xxhash_cpp_dep = dependency('xxhash_cpp')

# -- python modules --
if get_option('build_pythonmodule').enabled()

  pymod = import('python').find_installation(get_option('python_path'), pure: false)

  python3_dep = pymod.dependency()
  pybind11_dep = dependency('pybind11',  version : '>=3.0.1')
  nanobind_dep = dependency('nanobind', static: true, version: '>=2.9.2') 
  xtensor_python_dep = dependency('xtensor-python', static: true).as_system('system')

  # -- numpy (necessary for xtensor_python) --
  #numpy (copied from https://github.com/mesonbuild/meson/issues/9598)
  # NumPy include directory - needed in all submodules
  py3 = find_program('python3', 'python')
  incdir_numpy = run_command(
    py3,
    [
      '-c', 'import os; os.chdir(".."); import numpy; print(numpy.get_include())',
    ],
    check: true,
  ).stdout().strip()

  inc_np = include_directories(incdir_numpy)
  numpy_dep = declare_dependency(include_directories: inc_np)

  # set path where to install sources (pythonpath/site-packages/projectnamespace)
  message(
    'python module install directory:',
    pymod.get_install_dir(subdir: projectnamespace),
  )
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
