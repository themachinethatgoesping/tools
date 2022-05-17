# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

#---------- general test case header --------------

test_name = 'themachinethatgoesping-tools-tests'

sources = [
    'tutorial.test.cpp',
    'datetime.test.cpp',
    'test_main.cpp'
]

themachinethatgoesping_tools_tests = executable(test_name,
        sources: sources,
        dependencies : [catch2, tools_dep],
        link_language : 'cpp',
        override_options: [
        ],
        )

test(test_name,themachinethatgoesping_tools_tests)








