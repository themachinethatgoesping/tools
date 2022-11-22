# SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

"""The object printer python interface is not yet ready for anything useful
"""

# import pytest
import numpy as np

from themachinethatgoesping.tools import pyhelper as ph


class Test_tools_pyhelper_pyindexerslice:
    def test_PyIndexerSlice_should_support_common_functions(self):
        sl = ph.PyIndexerSlice(0, 10, 2)

        # test if functions crash
        sl.print()
        print(sl)
        assert len(sl.info_string()) != 0

        # info_string should be the same if objects are the same

        assert sl.copy() == sl  # test copy
        assert (
            ph.PyIndexerSlice.from_binary(sl.to_binary()) == sl
        )  # test that info_string is the same after serialization
        assert (
            ph.PyIndexerSlice.from_binary(sl.to_binary()).to_binary() == sl.to_binary()
        )  # test that binary is the same after deserialization

    def test_PyIndexerSlice_should_support_implicit_conversion(self):

        sl1 = ph.PyIndexerSlice(0, 10, 2)
        sl2 = slice(0, 10, 2)

        # note the comparison works only because slice can be implicitly converted to PyIndexerSlice
        assert sl1 == sl2
