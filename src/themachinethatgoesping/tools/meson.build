# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- library setup --
libname   = projectnamespace + '_tools'
headerdir = projectnamespace + '/tools'

# -- source files --
sources = [
  'timeconv.cpp',
  'classhelper/classversion.cpp',
  'classhelper/objectprinter.cpp',
  'vectorinterpolators/i_interpolator.cpp',
  'vectorinterpolators/vectorinterpolators.cpp',
  'rotationfunctions/helper.cpp',
  'rotationfunctions/quaternions.cpp',
  'pyhelper/pyindexer.cpp',
  'progressbars/consoleprogressbar.cpp',
  'progressbars/i_progressbartimed.cpp',
  'progressbars/noindicator.cpp',
  'progressbars/progressbarchooser.cpp',
  'progressbars/progressindicator.cpp',
  'helper/container_intersection.cpp',
  'helper/downsampling.cpp',
]

headers = [
  'timeconv.hpp',
  'exceptions/version_error.hpp',
  'exceptions/.docstrings/version_error.doc.hpp',
  'classhelper/classversion.hpp',
  'classhelper/objectprinter.hpp',
  'classhelper/option.hpp',
  'classhelper/option_frozen.hpp',
  'classhelper/stream.hpp',
  'classhelper/xxhashhelper.hpp',
  'classhelper/.docstrings/classversion.doc.hpp',
  'classhelper/.docstrings/objectprinter.doc.hpp',
  'classhelper/.docstrings/option.doc.hpp',
  'classhelper/.docstrings/option_frozen.doc.hpp',
  'classhelper/.docstrings/stream.doc.hpp',
  'classhelper/.docstrings/xxhashhelper.doc.hpp',
  'vectorinterpolators/akimainterpolator.hpp',
  'vectorinterpolators/bivectorinterpolator.hpp',
  'vectorinterpolators/i_interpolator.hpp',
  'vectorinterpolators/i_pairinterpolator.hpp',
  'vectorinterpolators/linearinterpolator.hpp',
  'vectorinterpolators/nearestinterpolator.hpp',
  'vectorinterpolators/slerpinterpolator.hpp',
  'vectorinterpolators/.docstrings/akimainterpolator.doc.hpp',
  'vectorinterpolators/.docstrings/bivectorinterpolator.doc.hpp',
  'vectorinterpolators/.docstrings/i_interpolator.doc.hpp',
  'vectorinterpolators/.docstrings/i_pairinterpolator.doc.hpp',
  'vectorinterpolators/.docstrings/linearinterpolator.doc.hpp',
  'vectorinterpolators/.docstrings/nearestinterpolator.doc.hpp',
  'vectorinterpolators/.docstrings/slerpinterpolator.doc.hpp',
  '.docstrings/timeconv.doc.hpp',
  'rotationfunctions/helper.hpp',
  'rotationfunctions/quaternions.hpp',
  'rotationfunctions/.docstrings/helper.doc.hpp',
  'rotationfunctions/.docstrings/quaternions.doc.hpp',
  'pyhelper/pyindexer.hpp',
  'pyhelper/.docstrings/pyindexer.doc.hpp',
  'progressbars/consoleprogressbar.hpp',
  'progressbars/i_progressbar.hpp',
  'progressbars/i_progressbartimed.hpp',
  'progressbars/noindicator.hpp',
  'progressbars/progressbarchooser.hpp',
  'progressbars/progressindicator.hpp',
  'progressbars/progresstqdm.hpp',
  'progressbars/progresstqdm_nano.hpp',
  'progressbars/.docstrings/consoleprogressbar.doc.hpp',
  'progressbars/.docstrings/i_progressbar.doc.hpp',
  'progressbars/.docstrings/i_progressbartimed.doc.hpp',
  'progressbars/.docstrings/noindicator.doc.hpp',
  'progressbars/.docstrings/progressbarchooser.doc.hpp',
  'progressbars/.docstrings/progressindicator.doc.hpp',
  'progressbars/.docstrings/progresstqdm.doc.hpp',
  'progressbars/.docstrings/progresstqdm_nano.doc.hpp',
  'helper/approx.hpp',
  'helper/container_intersection.hpp',
  'helper/defaultmap.hpp',
  'helper/defaultsharedpointermap.hpp',
  'helper/downsampling.hpp',
  'helper/floatcompare.hpp',
  'helper/integermath.hpp',
  'helper/isviewstream.hpp',
  'helper/map_tools.hpp',
  'helper/omp_helper.hpp',
  'helper/printing.hpp',
  'helper/stringconversion.hpp',
  'helper/variant.hpp',
  'helper/xtensor.hpp',
  'helper/xtensor_hash.hpp',
  'helper/.docstrings/approx.doc.hpp',
  'helper/.docstrings/container_intersection.doc.hpp',
  'helper/.docstrings/defaultmap.doc.hpp',
  'helper/.docstrings/defaultsharedpointermap.doc.hpp',
  'helper/.docstrings/downsampling.doc.hpp',
  'helper/.docstrings/floatcompare.doc.hpp',
  'helper/.docstrings/integermath.doc.hpp',
  'helper/.docstrings/isviewstream.doc.hpp',
  'helper/.docstrings/map_tools.doc.hpp',
  'helper/.docstrings/omp_helper.doc.hpp',
  'helper/.docstrings/printing.doc.hpp',
  'helper/.docstrings/stringconversion.doc.hpp',
  'helper/.docstrings/variant.doc.hpp',
  'helper/.docstrings/xtensor.doc.hpp',
  'helper/.docstrings/xtensor_hash.doc.hpp',
]

# -- targets --
# for now force static linking on windows
if build_machine.system() != 'linux'
  tools_lib = static_library(libname,sources,
                        dependencies : [
                          boost_dep, 
                          eigen3_dep, 
                          omp_dep,
                          hinnant_date_dep,
                          fmt_dep,
                          indicators_dep,
                          magic_enum_dep,
                          xtensor_dep,
                          fast_float_dep,
                          frozen_dep,
                          xxhash_cpp_dep],
                        override_options: [
                          'b_lundef=false'
                      ],
                        cpp_pch : '../../pch/tools_themachinethatgoesping_tools.hpp',
                        install : true
                        )
else  
  tools_lib = library(libname,sources,
                        dependencies : [
                          boost_dep, 
                          eigen3_dep, 
                          omp_dep,
                          hinnant_date_dep,
                          fmt_dep,
                          indicators_dep,
                          magic_enum_dep,
                          xtensor_dep,
                          fast_float_dep,
                          frozen_dep,
                          xxhash_cpp_dep],
                        override_options: [
                          'b_lundef=false'
                      ],
                        cpp_pch : '../../pch/tools_themachinethatgoesping_tools.hpp',
                        install : true
                        )
endif
                      

# -- internal dependency --
tools_dep = declare_dependency(
  dependencies : [
    boost_dep,
    eigen3_dep,
    omp_dep,
    hinnant_date_dep,
    fmt_dep,
    indicators_dep,
    magic_enum_dep,
    xtensor_dep,
    fast_float_dep,
    frozen_dep,
    xxhash_cpp_dep
  ],
  link_with : [tools_lib],
  compile_args : tools_compile_args,
  include_directories : ['../../']
  )


# -- installation setup --

# install headers
if headers != ['']
    install_headers(headers, subdir: headerdir+'/', preserve_path: true)
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
