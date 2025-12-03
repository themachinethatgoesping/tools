# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
# SPDX-FileCopyrightText: 2021 The Meson development team
#
# SPDX-License-Identifier: MIT

project('hinnant-date', ['cpp'],
        default_options: ['cpp_std=c++23'],
        version: '3.0.4',
        license: 'MIT')

pkg = import('pkgconfig')

thread_dep = dependency('threads')

header_files = files(
  'include/date/chrono_io.h',
  'include/date/date.h',
  'include/date/ios.h',
  'include/date/islamic.h',
  'include/date/iso_week.h',
  'include/date/julian.h',
  'include/date/ptz.h',
  'include/date/solar_hijri.h',
  'include/date/tz.h',
  'include/date/tz_private.h'
)
defines = []
date_public_defines = []

tz_public_defines = []
tz_deps = [thread_dep]

if get_option('only_c_locale')
  date_public_defines += ['-DONLY_C_LOCALE=1']
endif

if not get_option('string_view')
  date_public_defines += ['-DHAS_STRING_VIEW=0']
endif

i = include_directories('include')

if not get_option('header_only')
  if get_option('use_manual_tzdb')
    defines += ['-DAUTO_DOWNLOAD=0', '-DHAS_REMOTE_API=0']
  elif get_option('use_system_tzdb')
    defines += ['-DAUTO_DOWNLOAD=0', '-DHAS_REMOTE_API=0']
    tz_public_defines += ['-DUSE_OS_TZDB=1']
  else
    defines += ['-DAUTO_DOWNLOAD=1', '-DHAS_REMOTE_API=1']
    tz_public_defines += ['-DUSE_OS_TZDB=0']
    tz_deps += dependency('libcurl')
  endif

  if get_option('use_tzdb_in_dot')
    defines += ['-DINSTALL=.']
  endif

  tz_lib = library('tz', 'src/tz.cpp',
    include_directories: i,
    cpp_args: defines + date_public_defines + tz_public_defines,
    dependencies: tz_deps
  )
  tz_dep = declare_dependency(
    compile_args: date_public_defines + tz_public_defines,
    include_directories: i,
    link_with: tz_lib
  )
endif

date_dep = declare_dependency(
  compile_args: date_public_defines,
  include_directories: i
)

#install_headers(header_files, subdir: 'date', preserve_path: false)
