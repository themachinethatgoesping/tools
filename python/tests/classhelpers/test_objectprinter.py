# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

"""The object printer python interface is not yet ready for anything usefull
"""

import pytest
import numpy as np

from themachinethatgoesping.tools import classhelpers as ch


class Test_tools_classhelpers_objectprinter:
    def test_ObjectPrinter_should_not_crash_for_basic_operations(self):
        a = ch.ObjectPrinter("ObjectPrinterTester",2)

        a.register_value("test1", 0, "int")
        a.register_value("test1", 0, "int")
        a.register_value("test1", 0, "int")
        a.register_value("test1", 0, "int")
        a.register_value("test1", 0, "int")
        a.register_value("test1", 0, "int")
        a.register_value("te1", 100, "int")
        a.register_value("te1", 100.0021, "float")
        a.register_value("te1", "I am a string", "string")

        a.register_section("lists")
        a.register_container("5 elements", np.random.random(5))
        a.register_container("50 elements", np.random.random(50))
        a.register_container("90 elements", np.random.randint(0, 100, 90))

        #test if functions crash
        a.print()
        print(a)
        assert len(a.info_string()) != 0
        assert len(a.create_str()) != 0

        # info_string should be the same if objects are the same

        assert a.copy().info_string() == a.info_string()  # test copy
        assert a.copy().create_str() == a.create_str()  # test copy
        assert (
            ch.ObjectPrinter.from_binary(a.to_binary()).info_string() == a.info_string()
        )  # test that info_string is the same after serialization
        assert (
            ch.ObjectPrinter.from_binary(a.to_binary()).to_binary() == a.to_binary()
        )  # test that binary is the same after deserialization
        assert (
            ch.ObjectPrinter.from_binary(a.to_binary()).create_str() == a.create_str()
        )  # test that create_str is the same after deserialization
