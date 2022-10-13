# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

#---------- general test case header --------------

testcomponent = 'tools'

sources = [
    'tutorial.test.cpp',
    'timeconv.test.cpp',
    'helper/defaultsharedpointermap.test.cpp',
    'bitsery_helpers/custom_types.test.cpp',
    'rotationfunctions/helper.test.cpp',
    'rotationfunctions/quaternions.test.cpp',
    'vectorinterpolators/common.test.cpp',
    'vectorinterpolators/nearest.test.cpp',
    'vectorinterpolators/linear.test.cpp',
    'vectorinterpolators/akima.test.cpp',
    'vectorinterpolators/slerp.test.cpp'
]

foreach source : sources
    testname = projectnamespace + '._' + testcomponent + '.' + source.split('.')[0] + '_.test'
    testname = testname.replace('/', '.')

    testexe = executable(testname,
            sources: [source],
            dependencies : [catch2, tools_dep],
            link_language : 'cpp',
            override_options: [
            ],
            cpp_args : test_data_path
            #install : true
            )

    test(testname,testexe)
endforeach








