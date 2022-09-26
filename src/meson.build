# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- setup variables --
base_path = meson.current_source_dir()

# -- C++ projects --
subdir('themachinethatgoesping')

# -- python modules --
pymod = import('python').find_installation(get_option('python_path'), required : get_option('build_pythonmodule'))

if get_option('build_pythonmodule').enabled()

    if pymod.found()
        python3_dep = pymod.dependency()

        pybind11_dep = dependency('pybind11', required : false)

        if not pybind11_dep.found()
            pybind11_project = subproject('pybind11')
            pybind11_dep     = pybind11_project.get_variable('pybind11_dep')
        endif


        # -- put python module stuff here --

        # set path where to install sources (pythonpath/site-packages/projectnamespace)
        pythoninstallpath = pymod.get_install_dir() + projectnamespace + '/'
        message('python module install directory:', pythoninstallpath)


        #put module folders here
        subdir('pymodule')

    endif
endif

# -- tests (catch2) --
if get_option('build_tests').enabled()
    catch2 = subproject('catch2')
    catch2 = catch2.get_variable('catch2_with_main_dep')

    subdir('tests')
endif
