/*
  This file contains docstrings for use in the Python bindings.
  Do not edit! They were automatically extracted by pybind11_mkdoc.
 */

#define __EXPAND(x)                                      x
#define __COUNT(_1, _2, _3, _4, _5, _6, _7, COUNT, ...)  COUNT
#define __VA_SIZE(...)                                   __EXPAND(__COUNT(__VA_ARGS__, 7, 6, 5, 4, 3, 2, 1))
#define __CAT1(a, b)                                     a ## b
#define __CAT2(a, b)                                     __CAT1(a, b)
#define __DOC1(n1)                                       __doc_##n1
#define __DOC2(n1, n2)                                   __doc_##n1##_##n2
#define __DOC3(n1, n2, n3)                               __doc_##n1##_##n2##_##n3
#define __DOC4(n1, n2, n3, n4)                           __doc_##n1##_##n2##_##n3##_##n4
#define __DOC5(n1, n2, n3, n4, n5)                       __doc_##n1##_##n2##_##n3##_##n4##_##n5
#define __DOC6(n1, n2, n3, n4, n5, n6)                   __doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6
#define __DOC7(n1, n2, n3, n4, n5, n6, n7)               __doc_##n1##_##n2##_##n3##_##n4##_##n5##_##n6##_##n7
#define DOC(...)                                         __EXPAND(__EXPAND(__CAT2(__DOC, __VA_SIZE(__VA_ARGS__)))(__VA_ARGS__))

#if defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#endif


static const char *__doc_Bilinear = R"doc()doc";

static const char *__doc_Linear_old =
R"doc(This is snipped that was once used for reaching a tri linear
interpolation. It is currently not used within the machinethatgoesping)doc";

static const char *__doc_Trilinear = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator =
R"doc(Interface class for interpolator classes Create an interpolator object
by provding vectors for x and y (same size). X must be sorted and no
duplicates are allowed. then call class.Interpolate(new x value) to
get a corresponding y value at this x position. This interface
implements the search for the x position within this vector (closest 2
x/y value pair) and computes an x interpolation value (targetX) Then
it call the Interpolate functions of the implementation classes that
use this interface to interpolate between these pairs.

Template parameter ``YType:``:
    type of the y values (typically double, but will be a vector for
    the slerp interpolator class))doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_I_Interpolator =
R"doc(Construct a new i interpolator object from a vector of x,y pairs

Parameter ``XY:``:
    input data vector given as vector<pair<X,Y>>

Parameter ``sortX:``:
    sort the input data vector after interpolator construction
    (necessary if the vector was not sorted before)

Parameter ``checkX:``:
    check if the inptur data vector is valid)doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_I_Interpolator_2 =
R"doc(Construct a new i interpolator object from two (x and y) data vectors
(of same size)

Parameter ``X:``:
    x vector (must be same size)

Parameter ``Y:``:
    y vector (must be same size)

Parameter ``sortX:``:
    sort the input data vector after interpolator construction
    (necessary if the vector was not sorted before)

Parameter ``checkX:``:
    check if the inptur data vector is valid)doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_XY =
R"doc(< main data vector containing pairs of corresponding x and y
datapoitns)doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_checkX = R"doc(check if input data is valid (e.g. sorted, no duplicated x values))doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_extr_mode = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_get_X =
R"doc(return the x component of the internal data vector

Returns:
    std::vector<double>)doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_get_XY =
R"doc(return the internal data vector

Returns:
    const std::vector<std::pair<double,YType>>&)doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_get_Y =
R"doc(return the y component of the itnernal data vector

Returns:
    std::vector<YType>)doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_get_extrapolation_mode = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_interpolate =
R"doc(Search for the closest x values in the internal data and then
interpolate between the coressponding y functions.

Parameter ``targetX``:
    x value where for which the corresponding y value is to be
    interpolated

Returns:
    interpolated y value)doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_interpolate_2 =
R"doc(Interpolat multiple vector values in a loop

Parameter ``targetsX``:
    x values to interpolate

Returns:
    std::vector of interpolated y values)doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_interpolate_pair =
R"doc(Interface for implementing an interpolation between two y values using
a given interpolation factor

Parameter ``targetX``:
    interpolation factor. 0 means return smaller y value, 1 means
    return larger y value

Parameter ``y1``:
    smaller y value

Parameter ``y1``:
    larger y value

Returns:
    interpolated y value)doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_lastXPair = R"doc(< last pair (for faster consequtive searches))doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_set_XY =
R"doc(change the input data to this vector of XY pairs

Parameter ``XY:``:
    input data vector given as vector<pair<X,Y>>

Parameter ``sortX:``:
    sort the input data vector after interpolator construction
    (necessary if the vector was not sorted before)

Parameter ``checkX:``:
    check if the inptur data vector is valid)doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_set_XY_2 =
R"doc(change the input data to these X and Y vectors

Parameter ``X:``:
    x vector (must be same size)

Parameter ``Y:``:
    y vector (must be same size)

Parameter ``sortX:``:
    sort the input data vector after interpolator construction
    (necessary if the vector was not sorted before)

Parameter ``checkX:``:
    check if the inptur data vector is valid)doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_set_extrapolation_mode = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_sortX =
R"doc(sort internal vectors by X. This is necessary if the input data was
not sorted by X so far! TODO: provide function to deal with x value
duplicates)doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_t_XPair = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_t_XPair_calc_targetX =
R"doc(compute the interpolation factor between xmin and xmax

Parameter ``targetX``:
    x value for which we want to know the interpolation factor

Returns:
    interpolation factor)doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_t_XPair_t_XPair = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_t_XPair_xfactor = R"doc(< 1/(xmax-xmin))doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_t_XPair_xmax = R"doc(< larger xvalue)doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_t_XPair_xmax_index = R"doc(< index of the larger x value (in the internal vector))doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_t_XPair_xmin = R"doc(< smaller xvalue)doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_t_XPair_xmin_index = R"doc(< index of the smaller x value (in the internal vector))doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_t_extr_mode = R"doc(extrapolation mode type.)doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_t_extr_mode_extrapolate = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_t_extr_mode_fail = R"doc(< return nearest value in the vector.)doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_I_Interpolator_t_extr_mode_nearest =
R"doc(< throw out_of_range exception if given x value exceeds < boundaries
of internal vector)doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_LinearInterpolator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_LinearInterpolator_LinearInterpolator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_LinearInterpolator_LinearInterpolator_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_LinearInterpolator_LinearInterpolator_3 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_LinearInterpolator_interpolate_pair = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_LinearInterpolator_linear =
R"doc(Interpolate: Interpolate interpolation between two values

Parameter ``target:``:
    the target point [0.0 - 1.0]

Parameter ``v``:
    : An array of size 2 containing 2 values (to interpolate
    inbetween)

Returns:
    Interpolated value for target position)doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_NearestInterpolator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_NearestInterpolator_NearestInterpolator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_NearestInterpolator_NearestInterpolator_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_NearestInterpolator_average_halves = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_NearestInterpolator_get_average_halves = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_NearestInterpolator_interpolate_pair = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_NearestInterpolator_nearest =
R"doc(Nearest: Nearest neighbor interpolation between two values

Parameter ``target:``:
    the x position of the target point

Parameter ``p1``:
    : An array of size 2 containing the x and y position of the first
    point (x,y)

Parameter ``p2``:
    : An array of size 2 containing the x and y position of the second
    point (x,y)

Parameter ``average_halves:``:
    if true, the average_halves of both will be used when target is
    0.5, if False v[1] is used

Returns:
    p1[1],p2[1] or average_halves of the 2)doc";

static const char *__doc_themachinethatgoesping_tools_interpolation_NearestInterpolator_set_average_halves = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_timeconv_datestring_to_unixtime =
R"doc(Converting between date strings and UnixTime stampes (ref 1970)

Parameter ``DateString:``:
    DateString to be converted. Must fit format string.

Parameter ``format:``:
    Format string to convert Date string. Default Format:
    "%z__%d-%m-%Y__%H:%M:%S" see
    https://m.cplusplus.com/reference/ctime/strftime/ * https://themac
    hinethatgoesping.readthedocs.io/en/latest/modules/tools/timeconv.h
    tml#format-string

Returns:
    UnixTime as double (seconds since 01.01.1970))doc";

static const char *__doc_themachinethatgoesping_tools_timeconv_timepoint_to_unixtime =
R"doc(timepoint_to_unixtime IMPORTANT: Conversion does only have
microseconds precision!

Parameter ``TimePoint:``:
    chrono::system_clock::time_point

Returns:
    Unix time stamp (seconds since 01.01.1970) as double)doc";

static const char *__doc_themachinethatgoesping_tools_timeconv_unixtime_to_datestring =
R"doc(Converting between date strings and UnixTime stampes (ref 1970)

Parameter ``UnixTime:``:
    seconds since 01.01.1970 as double

Parameter ``fractionalSecondsDigits:``:
    How many digits to use for the split seconds. Minimum is 0 (second
    resolution) Maximum is 6 (microsecond resolutiuon)

Parameter ``format:``:
    Format string to convert Date string. Default Format:
    "%z__%d-%m-%Y__%H:%M:%S" see:
    https://m.cplusplus.com/reference/ctime/strftime/ * https://themac
    hinethatgoesping.readthedocs.io/en/latest/modules/tools/timeconv.h
    tml#format-string

Returns:
    DateString that fits to the specified format)doc";

static const char *__doc_themachinethatgoesping_tools_timeconv_unixtime_to_timepoint =
R"doc(unixtime_to_timepoint IMPORTANT: return value will only have
microseconds precision!

Parameter ``UnixTime:``:
    Unix time stamp (seconds since 01.01.1970) as double

Returns:
    chrono::system_clock::time_point)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

