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
  'pybind11/classhelpers.hpp',
  'timeconv.hpp',
  'rotationfunctions/quaternions.hpp',
  'vectorinterpolators.hpp',
  'vectorinterpolators/i_interpolator.hpp',
  'vectorinterpolators/linearinterpolator.hpp',
  'vectorinterpolators/nearestinterpolator.hpp',
  'vectorinterpolators/akimainterpolator.hpp',
  'vectorinterpolators/slerpinterpolator.hpp'
]

# -- targets --
# for now force static linking on windows
if build_machine.system() != 'linux'
  tools_lib = static_library(libname,sources,
                        dependencies : [
                          boost_dep, 
                          eigen3_dep, 
                          omp_dep,
                          hinnant_date_dep],
                        override_options: [
                          'b_lundef=false'
                      ],
                        install : true
                        )
else  
  tools_lib = library(libname,sources,
                        dependencies : [
                          boost_dep, 
                          eigen3_dep, 
                          omp_dep,
                          hinnant_date_dep],
                        override_options: [
                          'b_lundef=false'
                      ],
                        install : true
                        )
endif
                      

# -- internal dependency --
tools_dep = declare_dependency(
  dependencies : [
    boost_dep,
    eigen3_dep,
    omp_dep,
    hinnant_date_dep
  ],
  link_with : [tools_lib],
  compile_args : ['-D_USE_MATH_DEFINES']
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
