# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- library setup --
libname = 'tools'

# -- source files --
sources = [
  "datetime.cpp"
]

headers = [
  "datetime.h"
]

# -- targets --
tools = library(libname,sources,
                      dependencies : [boost, eigen3, omp],
                      override_options: [
                        'b_lundef=false'
                    ],
                      install : true)
                      

# -- installation setup --
#tools_dep = declare_dependency(tools)

# install headers
if headers != ['']
    install_headers(headers, subdir : libname+'/'+dir)
endif

# create pkgconfig file
pkg = import('pkgconfig')
pkg.generate(dsmtoolslib,
             #requires : [eigen3],#,'aglib','boost'],
             description : 'Shared functions (C++) and small tool functionality (python) for themachinethatgoesping projects',
             url : 'https://github.com/themachinethatgoesping/tools')

