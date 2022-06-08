// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, Timm Schoening, GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

/**
 * @brief This is snipped that was once used for reaching a tri linear interpolation.
 * It is currently not used within the machinethatgoesping
 * 
 */

//source: http://www.siafoo.net/snippet/33
//source: https://web.archive.org/web/20200805072956/http://www.siafoo.net/snippet/33
//The snipped was fixed by Peter Urban and Timm Schoening

/*
    Linear interpolation
    target  - the target point, 0.0 - 1.0
    v       - a pointer to an array of size 2 containg the two values

*/

static double Linear_old(float target, double *v)
{
    return (double)(target*(v[1])+ (double(1.0f) - target)*(v[0]));
}


/*
    BiLinear interpolation, linear interpolation in 2D
    target  - a 2D point (X,Y)
    v       - an array of size 4 containg values
                1 3
                0 2
    target[x,y]: y pos 0 ->1 xpos 0 -> 2

    cost: performs 3 linear interpolations
*/
static double Bilinear(float *target, double *v)
{
    double v_prime[2] = {
        Linear_old(target[1], &(v[0])),
        Linear_old(target[1], &(v[2]))
    };

    return Linear_old(target[0], v_prime);

}

/*
    TriLinear interpolation, linear interpolation in 2D
    target  - a 3D point (X,Y,Z)
    v       - an array of size 8 containg the values of the 8 corners
                of a cube defined as two faces: 0-3 face one (front face)
                                                4-7 face two (back face)
            - 13 -> z positiv -> 5 7
                02                 4 6

    cost: 7 linear interpolations
*/

static double Trilinear(float *target, double *v)
{
    double v_prime[2] = {
        Bilinear(&(target[0]), &(v[0])),
        Bilinear(&(target[0]), &(v[4]))
    };

    return Linear_old(target[2], v_prime);
}