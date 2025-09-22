# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

# -- setup variables --
base_path = meson.current_source_dir()

# -- C++ projects --
subdir('tools')


# -- tools_pybind --
if get_option('build_pythonmodule').enabled()
    #put module folders here
    subdir('tools_pybind')
    subdir('tools_nanobind')
endif
