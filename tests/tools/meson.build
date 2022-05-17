# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

#---------- general test case header --------------

testcomponent = 'tools'

sources = [
    'tutorial.test.cpp',
    'datetime.test.cpp'
]

foreach source : sources
    testname = parentprojectname + '-' + testcomponent + '-' + source.split('.')[0] + '-tests'

    testexe = executable(testname,
            sources: [source, 'test_main.cpp'],
            dependencies : [catch2, tools_lib_dep],
            link_language : 'cpp',
            override_options: [
            ],
            )

    test(testname,testexe)
endforeach








