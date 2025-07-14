# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- module name
module_name = 'tools_cppy'
        
# -- sources
sources = [
  'm_helper.cpp',
  'm_progressbars.cpp',
  'm_timeconv.cpp',
  'module.cpp',
  'classhelper/c_objectprinter.cpp',
  'classhelper/module.cpp',
  'vectorinterpolators/c_akimainterpolator.cpp',
  'vectorinterpolators/c_bivectorinterpolator.cpp',
  'vectorinterpolators/c_linearinterpolator.cpp',
  'vectorinterpolators/c_nearestinterpolator.cpp',
  'vectorinterpolators/c_slerpinterpolator.cpp',
  'vectorinterpolators/module.cpp',
  'rotationfunctions/c_quaternions.cpp',
  'rotationfunctions/module.cpp',
  'pyhelper/c_pyindexer.cpp',
  'pyhelper/module.cpp',
]

# define python module
py_tools = pymod.extension_module(
    module_name,
    sources: sources,
    dependencies: [
        tools_dep,
        tools_pybind_dep,
        pybind11_dep,
        python3_dep],
    #link_with : [tools],
    link_language: 'cpp',
    # cpp_pch : 'pch/pch.hpp',
    override_options: [
        #'cpp_rtti=true',
    ],
    cpp_args: ['-DMODULE_NAME='+module_name, '-DMODULE_VERSION=' + '"' + meson.project_version() + '"'],
    install: true,
    subdir: projectnamespace,
    install_tag: 'python-runtime',
    override_options: ['unity=off']
)



        
