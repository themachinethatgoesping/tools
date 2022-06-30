# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

#---------- general test case header --------------

testcomponent = 'tools'

sources = [
    'tutorial.test.cpp',
    'timeconv.test.cpp',
    'bitsery_helpers/custom_types.test.cpp',
    'rotationfunctions/quaternions.test.cpp',
    'vectorinterpolators/common.test.cpp',
    'vectorinterpolators/nearest.test.cpp',
    'vectorinterpolators/linear.test.cpp',
    'vectorinterpolators/akima.test.cpp',
    'vectorinterpolators/slerp.test.cpp'
]

foreach source : sources
    testname = projectnamespace + '._' + testcomponent + '.' + source.split('.')[0] + '_.test'
    testname = testname.replace('/','.')

    testexe = executable(testname,
            sources: [source, 'test_main.cpp'],
            dependencies : [catch2, tools_dep],
            link_language : 'cpp',
            override_options: [
            ],
            cpp_args : '-D__PROJECT_TESTDATADIR__="' + meson.current_source_dir() + '/testdata"'
            #install : true
            )

    test(testname,testexe)
endforeach








