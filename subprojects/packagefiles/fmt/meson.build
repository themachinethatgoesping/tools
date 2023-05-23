# SPDX-FileCopyrightText: 2021 The Meson development team
# SPDX-FileCopyrightText: 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MIT

project('fmt', 'cpp', version: '10.0.0', license: 'BSD', default_options: ['cpp_std=c++14'])

fmt_private_cpp_args = ['-DFMT_USE_FULL_CACHE_DRAGONBOX=1']   # I don't know where this must go, so it is set for both
fmt_interface_cpp_args = ['-DFMT_USE_FULL_CACHE_DRAGONBOX=1'] # I don't know where this must go, so it is set for both
if get_option('default_library') == 'shared'
  fmt_private_cpp_args += ['-DFMT_EXPORT']
  fmt_interface_cpp_args += ['-DFMT_SHARED']
endif

fmt_lib = library(
  'fmt',
  'src/format.cc',
  'src/os.cc',
  cpp_args: fmt_private_cpp_args,
  include_directories: 'include',
)

fmt_dep = declare_dependency(
  include_directories: 'include',
  compile_args: fmt_interface_cpp_args,
  link_with: fmt_lib
)

if meson.version().version_compare('>=0.54.0')
  meson.override_dependency('fmt', fmt_dep)
endif

fmt_header_only_dep = declare_dependency(
  include_directories: 'include',
  compile_args: '-DFMT_HEADER_ONLY',
)
