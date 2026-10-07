# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- library setup --
libname   = projectnamespace + '_tools_nanobind'
headerdir = projectnamespace + '/tools_nanobind'

# -- source files --
sources = [
]

headers = [
  'classhelper.hpp',
  'datetime.hpp',
  'enumhelper.hpp',
  'nanobind_xtensor.hpp',
  'ostream_redirect.hpp',
  'pytensor_nanobind.hpp',
  'scoped_ostream_redirect.hpp',
  '.docstrings/classhelper.doc.hpp',
  '.docstrings/datetime.doc.hpp',
  '.docstrings/enumhelper.doc.hpp',
  '.docstrings/nanobind_xtensor.doc.hpp',
  '.docstrings/ostream_redirect.doc.hpp',
  '.docstrings/pytensor_nanobind.doc.hpp',
  '.docstrings/scoped_ostream_redirect.doc.hpp',
]

# -- targets --
# for now force static linking on windows
# if build_machine.system() != 'linux'
#   tools_nanobind_lib = static_library(libname,sources,
#                         dependencies : [
#                           tools_dep,
#                           nanobind_dep,
#                           python3_dep,
#                           xtensor_python_dep,
#                           numpy_dep],
#                         override_options: [
#                           'b_lundef=false'
#                       ],
#                         # cpp_pch : 'pch/pch.hpp',
#                         install : true
#                         )
# else  
#   tools_nanobind_lib = library(libname,sources,
#                         dependencies : [
#                           tools_dep,
#                           nanobind_dep,
#                           python3_dep,
#                           xtensor_python_dep,
#                           numpy_dep],
#                         override_options: [
#                           'b_lundef=false'
#                       ],
#                         # cpp_pch : 'pch/pch.hpp',
#                         install : true
#                         )
# endif
                      

# -- internal dependency --
# NOTE: python3_dep is taken as a partial dependency (include dirs + compile
# args only, NOT the link library). The Python library is linked by each
# consuming extension_module via its own top-level python dependency, which in
# split mode Meson swaps to the stable python3.lib (limited_api). Linking the
# full version-specific python3XX.lib here would leak a python3XX.dll
# dependency into the abi3 modules and break loading on other Python versions
# (Windows). See the nanobind frontend dependency for the same reasoning.
tools_nanobind_dep = declare_dependency(
  dependencies : [
                tools_dep,
                nanobind_dep,
                python3_dep.partial_dependency(compile_args : true, includes : true),
                xtensor_python_dep, 
                xtensor_dep,
                numpy_dep
  ],
  #link_with : [tools_nanobind_lib],
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
