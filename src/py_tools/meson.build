# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- module name
module_name = 'tools'
        
# -- sources
sources = [
    'module.cpp',
    'm_timeconv.cpp'
]

# define python module
py_tools = pymod.extension_module(
    module_name,
    sources: sources,
    dependencies : [
        tools_lib_dep,
        pybind11,
        python3],
    #link_with : [tools],
    link_language : 'cpp',
    override_options: [
        #'cpp_rtti=true',
    ],
    cpp_args : '-DPYTHON_LIB='+module_name,
    install : true,
    install_dir : pythoninstallpath
)



        
