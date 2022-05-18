# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- library setup --
libname   = projectnamespace + '_tools'
headerdir = projectnamespace + '/tools'

# -- source files --
sources = [
  'timeconv.cpp'
]

headers = [
  'timeconv.h'
]

# -- targets --
tools_lib = library(libname,sources,
                      #include_directories : [hinnant_date]
                      dependencies : [
                        boost, 
                        eigen3, 
                        omp,
                        hinnant_date],
                      override_options: [
                        'b_lundef=false'
                    ],
                      install : true)
                      

# -- internal dependency --
tools_lib_dep = declare_dependency(
  dependencies : [
    boost,
    eigen3,
    omp,
    hinnant_date
  ],
  link_with : [tools_lib],
  #include_directories : ['../']
  )


# -- installation setup --

# install headers
if headers != ['']
    install_headers(headers, subdir : headerdir+'/')
endif

# create pkgconfig file
pkg = import('pkgconfig')
pkg.generate(tools_lib,
             #requires : [eigen3],#,'aglib','boost'],
             description : 'Shared functions (C++) and small tool functionality (python) for themachinethatgoesping projects',
             url : 'https://github.com/themachinethatgoesping/tools')



#         conf = configuration_data()
#         conf.set('prefix', prefix)
#         conf.set('VERSION', meson.project_version())
#         conf.set('includedir', includedir)
#
#         pkg = configure_file(configuration: conf,
#                             input: 'gsettings-desktop-schemas.pc.in',
#                             install: true,
#                             install_dir: join_paths(datadir, 'pkgconfig'),
#                             output: 'gsettings-desktop-schemas.pc')