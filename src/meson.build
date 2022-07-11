# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- setup variables --
base_path = meson.current_source_dir()

# -- C++ projects --
subdir('themachinethatgoesping')

# -- tests (catch2) --
if get_option('build_tests').enabled()
    catch2 = dependency('catch2', required : false)

    if not catch2.found()
        catch2 = subproject('catch2')
        catch2 = catch2.get_variable('catch2_dep')
    endif

    subdir('tests')
endif
