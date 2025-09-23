# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- library setup --
libname   = projectnamespace + '_tools_nanobind'
headerdir = projectnamespace + '/tools_nanobind'

# -- source files --
sources = [
  'datetime.cpp',
]

headers = [
  'classhelper.hpp',
  'datetime.hpp',
  'enumhelper.hpp',
  '.docstrings/classhelper.doc.hpp',
  '.docstrings/datetime.doc.hpp',
  '.docstrings/enumhelper.doc.hpp',
]

# -- targets --
# Build as shared library when building python modules to avoid duplicate symbols
# from nanobind in the static lib and the extension module
tools_nanobind_lib = library(libname,sources,
                      dependencies : [
                        tools_dep,
                        nanobind_dep,
                        python3_dep,
                        xtensor_python_dep,
                        numpy_dep],
                      override_options: [
                        'b_lundef=false',
                        'unity=off'  # Disable unity builds for nanobind
                    ],
                      # cpp_pch : 'pch/pch.hpp',
                      install : true
                      )
                      

# -- internal dependency --
tools_nanobind_dep = declare_dependency(
  dependencies : [
                tools_dep,
                nanobind_dep,
                python3_dep,
                xtensor_python_dep,
                numpy_dep
  ],
  link_with : [tools_nanobind_lib],
  compile_args : ['-D_USE_MATH_DEFINES'],
  include_directories : ['../../']
  )


# -- installation setup --

# install headers
if headers != ['']
    install_headers(headers, subdir: headerdir+'/', preserve_path: true)
endif

# create pkgconfig file
# pkg = import('pkgconfig')
# pkg.generate(tools_nanobind_lib,
#              requires : [tools_lib],#,'aglib','boost'],
#              description : 'Shared functions and classes (C++) for nanobind bindings',
#              url : 'https://github.com/themachinethatgoesping/tools')
