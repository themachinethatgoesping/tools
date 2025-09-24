# SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: CC0-1.0

#---------- general test case header --------------

testcomponent = 'tools'

sources = [
  'timeconv.test.cpp',
  'tutorial.test.cpp',
  'classhelper/option.test.cpp',
  'vectorinterpolators/akima.test.cpp',
  'vectorinterpolators/bivector.test.cpp',
  'vectorinterpolators/common.test.cpp',
  'vectorinterpolators/linear.test.cpp',
  'vectorinterpolators/nearest.test.cpp',
  'vectorinterpolators/slerp.test.cpp',
  'rotationfunctions/helper.test.cpp',
  'rotationfunctions/quaternions.test.cpp',
  'pyhelper/pyindexer.test.cpp',
  'helper/defaultsharedpointermap.test.cpp',
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








