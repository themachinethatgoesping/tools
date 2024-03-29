# SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
# Research Kiel SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

import themachinethatgoesping.scripts.sbes as sbes

from pytest import approx

#grouped tests
class TestSBES(object):

    def test_calc_footprint(self):
        s = sbes.SBES(7)

        assert s.calc_footprint(100)    == approx(12.232524030096862)
        assert s.calc_footprint(100,10) == approx(17.497732705184802)

    def test_calc_overlap_pingrate(self):
        s = sbes.SBES(1)

        assert s.calc_overlap_pingrate(5,100) == approx(1.473724629313051)

    def test_beam_xlimits(self):
        s = sbes.SBES(7)

        assert s.get_beam_xmin(100) == approx(-6.116262015048431)
        assert s.get_beam_xmax(100) ==  approx(6.116262015048431)

        s.x=10
        assert s.get_beam_xmin(100) ==  approx(3.883737984951569)
        assert s.get_beam_xmax(100) == approx(16.116262015048431)

        s.x =10
        s.z =10
        assert s.get_beam_xmin(110) ==  approx(3.883737984951569)
        assert s.get_beam_xmax(110) == approx(16.116262015048431)

    def test_calculations(self):
        s = sbes.SBES(7)

        assert s.calc_overlap_pingrate(4,100)           == approx(0.1682203930224943)
        assert s.calc_overlap_depth_for_pingrate(4,0.5) == approx(33.644078604498866)
        assert s.calc_overlap_depth(10)                 == approx(81.74927738049836)
        assert s.calc_pingdistance(4,1.25)              == approx(1.6462080000000001)


        s = sbes.SBES(7,z=5)

        assert s.calc_overlap_pingrate(4,100)           == approx(0.1682203930224943)
        assert s.calc_overlap_depth_for_pingrate(4,0.5) == approx(38.644078604498866)
        assert s.calc_overlap_depth(10)                 == approx(86.74927738049836)
        assert s.calc_pingdistance(4,1.25)              == approx(1.6462080000000001)