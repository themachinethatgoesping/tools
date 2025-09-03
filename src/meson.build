# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- setup variables --
base_path = meson.current_source_dir()

# -- C++ projects --
subdir('themachinethatgoesping')

# -- python modules --
if get_option('build_pythonmodule').enabled()
    #put module folders here
    subdir('pymodule')
endif

# -- tests (catch2) --
if get_option('build_tests').enabled()
    # Suppress all warnings when building Catch2 subproject to avoid noise
    # during compilation. We set warning_level=0 to disable warnings and
    # werror=false to prevent warnings from being treated as errors.
    catch2 = subproject('catch2', default_options: [
        'tests=false', 
        'install=false',
        'warning_level=0',
        'werror=false'
    ])
    catch2 = catch2.get_variable('catch2_with_main_dep').as_system('system')

    subdir('tests')
endif
