# SPDX-FileCopyrightText: 2022 Peter Urban, Sven Schorge, GEOMAR Helmholtz Centre for Ocean
# Research Kiel SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
#
# SPDX-License-Identifier: MPL-2.0

import math

import themachinethatgoesping.scripts.mbes as mbes

from pytest import approx

#def test_what_ever():
#    assert 1 == 2

#grouped tests
class TestMBES(object):

    def test_calc_footprint(self):
        m = mbes.MBES(120,1,2,seafloor_alpha=0)

        assert m.calc_footprint_along(100)    == 1.7453735581517578
        assert m.calc_footprint_across(100)   == 3.491012985643517
        assert m.calc_swathwidth(100)         == 346.41016151377534


    def test_calc_overlap_pingrate(self):
        m = mbes.MBES(120,1,2,seafloor_alpha=0)

        assert m.calc_along_overlap_pingrate(5,100) == 1.473724629313051

    def test_swath_xlimits(self):
        m = mbes.MBES(120,1,2,seafloor_alpha=0)

        assert m.get_swath_ymin_z(100) == (-173.20508075688767,-100)
        assert m.get_swath_ymax_z(100) == ( 173.20508075688767,-100)

        m.y=10
        assert m.get_swath_ymin_z(100) == (-163.20508075688767,-100)
        assert m.get_swath_ymax_z(100) == ( 183.20508075688767,-100)

        m.x =10
        m.z =10
        assert m.get_swath_ymin_z(110) == (-163.20508075688767,-110)
        assert m.get_swath_ymax_z(110) == ( 183.20508075688767,-110)


        m.seafloor_alpha = 15
        assert m.get_swath_ymin_z(110) == (-304.54482671904316,-191.6025403784438)
        assert m.get_swath_ymax_z(110) == ( 125.13139720814411,-76.47114317029974)

        m.seafloor_alpha = -15
        assert m.get_swath_ymin_z(110) == (-111.47114317029971,-80.13139720814414)
        assert m.get_swath_ymax_z(110) == ( 341.8653347947319, -201.6025403784438)

        m.seafloor_alpha = 45
        assert m.get_swath_ymin_z(110) == (-180.5255888325765,-120.00000000000003 )
        assert m.get_swath_ymax_z(110) == ( 67.05771365940052,-42.942286340599495)

        m.seafloor_alpha = -45
        assert m.get_swath_ymin_z(110) == (-59.737205583711756,-50.26279441628825)
        assert m.get_swath_ymax_z(110) == ( 200.5255888325765, -120.00000000000003)

    def test_calculations(self):
        m = mbes.MBES(120,7,2,seafloor_alpha=0)

        assert m.calc_along_overlap_pingrate(4,100)           == approx(0.1682203930224943)
        assert m.calc_along_overlap_depth_for_pingrate(4,0.5) == 33.644078604498866
        assert m.calc_along_overlap_depth(10)     == 81.74927738049836
        assert m.calc_along_pingdistance(4,1.25)  == 1.6462080000000001

    def test_linespacing(self):
        m = mbes.MBES(120,1,2,seafloor_alpha=0)

        assert m.calc_linespacing(100,10) == 43.58898943540674 * 2
        assert m.calc_linespacing(100,20) == 60 * 2
        assert m.calc_linespacing(100,2) == 19.8997487421324 * 2

        assert m.calc_linespacing(200, 40,
                                  min_minslant_visible_distance=50,
                                  max_flare_height=80) \
               == 210.71307505705477
        assert m.calc_linespacing(200, 40,
                                  min_minslant_visible_distance=50,
                                  max_flare_height=70) \
               == 174.35595774162695


    def test_seafloor_depth(self):
        m = mbes.MBES(120,1,2)
        m2 = mbes.MBES(120,1,2)

        assert m.get_seafloor_depth(100,y= 0, x=0 )     == 100
        assert m.get_seafloor_depth(100,y= 0, x=10)     == 100
        assert m.get_seafloor_depth(100,y= 10,x=0 )     == 100
        assert m.get_seafloor_depth(100,y= 10,x=10)     == 100
        assert m.get_seafloor_depth(100,y=-10,x=0 )     == 100


        for y in [0]:
            for x in [-10,0,10]:
                for seafloor_alpha in range(-85,85,5):
                    m.seafloor_alpha = seafloor_alpha
                    assert m.get_seafloor_depth(100,y=y, x=x) == 100


        for y in range(0,1000,10):
                for seafloor_alpha in range(0,85,5):
                    m.seafloor_alpha = seafloor_alpha
                    m2.seafloor_alpha = -seafloor_alpha

                    assert round(math.fabs(100-m.get_seafloor_depth(100,y=y, x=0)),10) == round(math.fabs(100-m.get_seafloor_depth(100,y=-y, x=0)),10)
                    assert round(math.fabs(100-m.get_seafloor_depth(100,y=y, x=0)),10) == round(math.fabs(100-m2.get_seafloor_depth(100,y=y, x=0)),10)
                    assert m.get_seafloor_depth(100,y=y, x=0) == m2.get_seafloor_depth(100,y=-y, x=0)




        m.seafloor_alpha = 5
        assert m.get_seafloor_depth(100,y= 10,x=0 )     == 99.12511336474076

        m.seafloor_alpha = 45
        assert m.get_seafloor_depth(100,y= 10,x=0 )     == 90


        m.seafloor_alpha = 70
        assert m.get_seafloor_depth(100,y=10, x=0 )     == 72.52522580545379

        m.seafloor_alpha = 80
        assert m.get_seafloor_depth(100,y=10, x=0 )     == approx(43.28718180382293)


    def test_seafloor_y_distace(self):

        m=mbes.MBES(120,1,2)
        m2=mbes.MBES(120,1,2,y=10,z=10)
        assert m.get_seafloor_y_distance(100,0) == 0
        assert m2.get_seafloor_y_distance(100,0) == 0

        for beamangle in range(-150,150,5):
            assert round(m.get_seafloor_y_distance(100,beamangle),10)  == round(m2.get_seafloor_y_distance(110,beamangle),10)

        for beamangle in range(-150,150,5):
            assert round(m.get_seafloor_y_distance(100,-beamangle),10) == -round(m.get_seafloor_y_distance(100, beamangle),10)

        assert m.get_seafloor_y_distance(100, 60) == 173.20508075688767


        m.seafloor_alpha = 5
        assert m.get_seafloor_y_distance(100, 60)  ==  150.41237069488048
        assert m.get_seafloor_y_distance(100, -60) == -204.13928922743875

        m.seafloor_alpha = -5
        assert m.get_seafloor_y_distance(100, 60)  ==  204.13928922743875
        assert m.get_seafloor_y_distance(100, -60) == -150.41237069488048

        m2.seafloor_alpha = 45
        assert m2.get_seafloor_y_distance(110, 60)  ==  57.05771365940052
        assert math.isnan(m2.get_seafloor_y_distance(110, -60))

        m2.seafloor_alpha = -45
        assert math.isnan(m2.get_seafloor_y_distance(110, 60))
        assert m2.get_seafloor_y_distance(110, -60) == -69.73720558371176

    def test_minslant_range(self):
        m=mbes.MBES(120,1,2)
        m2=mbes.MBES(120,1,2,z=10,y=10)

        assert m.get_minslant_range(100)  == 100
        assert m2.get_minslant_range(100) == 90

        m.seafloor_alpha = 10
        m2.seafloor_alpha = 10
        assert m.get_minslant_range(100)  == 98.4807753012208
        assert m2.get_minslant_range(100) == 86.89621599442941

        m.seafloor_alpha  = 45
        m2.seafloor_alpha = 45
        assert m.get_minslant_range(100)  == 70.71067811865476
        assert m2.get_minslant_range(100) == 56.568542494923804

        m.seafloor_alpha  = -45
        m2.seafloor_alpha = -45
        assert m.get_minslant_range(100)  == 70.71067811865476
        assert m2.get_minslant_range(100) == 70.71067811865476

        m.seafloor_alpha  = 60
        m2.seafloor_alpha = 60
        assert round(m.get_minslant_range(100),10)  == 50
        assert m2.get_minslant_range(100)           == 36.339745962155625

        m.seafloor_alpha  = -60
        m2.seafloor_alpha = -60
        assert round(m.get_minslant_range(100),10)  == 50
        assert m2.get_minslant_range(100)           == 53.660254037844396
