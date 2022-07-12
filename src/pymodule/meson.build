# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- module name
module_name = 'tools'
        
# -- sources
sources = [
    'module.cpp',
    'm_timeconv.cpp',
    'vectorinterpolators/module.cpp',
    'vectorinterpolators/subm_nearestinterpolator.cpp',
    'vectorinterpolators/subm_linearinterpolator.cpp',
    'vectorinterpolators/subm_akimainterpolator.cpp',
    'vectorinterpolators/subm_slerpinterpolator.cpp',
    'classhelpers/module.cpp',
    'classhelpers/subm_objectprinter.cpp'
]

# define python module
py_tools = pymod.extension_module(
    module_name,
    sources: sources,
    dependencies : [
        tools_dep,
        pybind11_dep,
        python3_dep],
    #link_with : [tools],
    link_language : 'cpp',
    override_options: [
        #'cpp_rtti=true',
    ],
    cpp_args : '-DPYTHON_LIB='+module_name,
    install : true,
    install_dir : pythoninstallpath,
    install_tag : 'python-runtime'
)



        
