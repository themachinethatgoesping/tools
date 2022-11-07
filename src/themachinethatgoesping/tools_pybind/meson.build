# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- library setup --
libname   = projectnamespace + '_tools_pybind'
headerdir = projectnamespace + '/tools_pybind'

# -- source files --
sources = [
]

headers = [
  'classhelpers.hpp',
  'enumhelpers.hpp',
]

# -- targets --
# for now force static linking on windows
if build_machine.system() != 'linux'
  tools_pybind_lib = static_library(libname,sources,
                        dependencies : [
                          tools_dep,
                          pybind11_dep,
                          python3_dep,
                          numpy_dep],
                        override_options: [
                          'b_lundef=false'
                      ],
                        install : true
                        )
else  
  tools_pybind_lib = library(libname,sources,
                        dependencies : [
                          tools_dep,
                          pybind11_dep,
                          python3_dep,
                          numpy_dep],
                        override_options: [
                          'b_lundef=false'
                      ],
                        install : true
                        )
endif
                      

# -- internal dependency --
tools_pybind_dep = declare_dependency(
  dependencies : [
                tools_dep,
                pybind11_dep,
                python3_dep,
                numpy_dep
  ],
  link_with : [tools_pybind_lib],
  compile_args : ['-D_USE_MATH_DEFINES'],
  include_directories : ['../../']
  )


# -- installation setup --

# install headers
if headers != ['']
    install_headers(headers, subdir: headerdir+'/', preserve_path: true)
endif

# create pkgconfig file
pkg = import('pkgconfig')
pkg.generate(tools_pybind_lib,
             requires : [tools_lib],#,'aglib','boost'],
             description : 'Shared functions and classes (C++) for pybind11 bindings',
             url : 'https://github.com/themachinethatgoesping/tools')

