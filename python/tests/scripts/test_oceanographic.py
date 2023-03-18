# SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
# Research Kiel SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

try:
    from oceanographic import knots_to_ms
except:
    from themachinethatgoesping.scripts.oceanographic import knots_to_ms

class TestSBES(object):
    def test_knots_to_ms(self):
        assert knots_to_ms(3) == 1.54332
