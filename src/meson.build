# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- setup variables --
base_path = meson.current_source_dir()

# -- C++ projects --
subdir('tools')


# -- python modules --
pymod = import('python').find_installation(get_option('python_path'), required : get_option('build_pythonmodule'))

if get_option('build_pythonmodule').enabled()
    
    if pymod.found()
        python3 = pymod.dependency()
        
        pybind11 = dependency('pybind11', required : false)

        if not pybind11.found()
            pybind11 = subproject('pybind11')
            pybind11 = pybind11.get_variable('pybind11_dep')
        endif

    #put module folders here
    subdir('py_tools')

    endif
endif
