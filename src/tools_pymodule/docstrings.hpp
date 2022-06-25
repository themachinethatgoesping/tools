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


static const char *__doc_themachinethatgoesping_tools_rotationfunctions_normalize_angles_degrees =
R"doc(Shift angles into specified angular range: yaw [0°,359.99°], pitch
[-90°, 90°], roll [-180¶, 179.99°]

Template parameter ``floattype``:
    double or gloat

Parameter ``ypr``:
    Matrix with yaw, pitch and roll value in °

Returns:
    std::array<floattype, 3> (Matrix with yaw, pitch and roll value in
    °))doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_normalize_angles_rad =
R"doc(Shift angles into specified angular range: yaw [0,2pi], pitch [-p/2°,
p/2°], roll [-pi, pi]

Template parameter ``floattype``:
    double or gloat

Parameter ``ypr``:
    Matrix with yaw, pitch and roll value in rad

Returns:
    std::array<floattype, 3> (Matrix with yaw, pitch and roll value in
    rad))doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_ypr =
R"doc(create an eigen quaternion by rotating yaw (z axis), pitch (y axis)
and roll (x axis)

Template parameter ``floattype``:
    $Parameter ``ypr``:

array that contains yaw, pitch and roll value

Parameter ``input_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad

Returns:
    Eigen::Quaternion<floattype>)doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_quaternion_from_ypr_2 =
R"doc(create an eigen quaternion by rotating yaw (z axis), pitch (y axis)
and roll (x axis)

Template parameter ``floattype``:
    floating point value

Parameter ``yaw``:
    rotation arround z axis [° or rad]

Parameter ``pitch``:
    rotation arround y axis [° or rad]

Parameter ``roll``:
    rotation arround x axis [° or rad]

Parameter ``input_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad

Returns:
    Eigen::Quaternion<floattype>)doc";

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

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator =
R"doc(Interpolator class to perform a (modified) akima interpolation. Uses
boost makima interpolator.)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_AkimaInterpolator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_AkimaInterpolator_2 =
R"doc(Construct a new Akima Spline Interpolator object from a vector of
pairs This class uses the modified akima interpolation of boost c++ ht
tps://www.boost.org/doc/libs/1_79_0/libs/math/doc/html/math_toolkit/ma
kima.html usage: interpolated_y_value = interpolator(x_value)

Parameter ``XY``:
    vector of x,y pairs. X must be unique and sorted in ascending
    order

Parameter ``extrapolation_mode``:
    :py:class:`t_extr_mode
    <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>`
    object that describes the extrapolation mode)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_AkimaInterpolator_3 =
R"doc(Construct a new Akima Spline Interpolator object from a vector of
pairs This class uses the modified akima interpolation of boost c++ ht
tps://www.boost.org/doc/libs/1_79_0/libs/math/doc/html/math_toolkit/ma
kima.html usage: interpolated_y_value = interpolator(x_value)

Parameter ``X``:
    X vector; must be unique and sorted in ascending order. same size
    as Y!

Parameter ``Y``:
    Y vector; must be unique and sorted in ascending order. same size
    as X!

Parameter ``extrapolation_mode``:
    :py:class:`t_extr_mode
    <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>`
    object that describes the extrapolation mode)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_akima_spline = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_append = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_append_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_extend = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_extend_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_init_linearextrapolators =
R"doc(internal function to initialize the linear extrapolation objects
_min_x, _min_x1, _max_x, _max_x_1, _min_y, _max_y and the
_akima_spline must be set/initialized before calling this function)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_max_linearextrapolator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_max_x = R"doc(< min/max x and y values)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_max_x_1 = R"doc(< one value above min and max x)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_max_y = R"doc(< min/max x and y values)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_min_linearextrapolator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_min_x = R"doc(< min/max x and y values)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_min_x_1 = R"doc(< one value above min and max x)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_min_y = R"doc(< min/max x and y values)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_operator_call =
R"doc(get the interolated y value for given x target

Parameter ``target_x``:
    find the corresponding y value for this x value

Returns:
    corresponding y value)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_operator_call_2 =
R"doc(get nearest y values for given x targets (vectorized call)

Parameter ``targets_x``:
    vector of x values. For each of these values find the corrspondig
    y value

Returns:
    corresponding y value)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_set_data_XY =
R"doc(change the input data to these X and Y vectors

Parameter ``X:``:
    x vector (must be same size)

Parameter ``Y:``:
    y vector (must be same size))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_set_data_XY_2 =
R"doc(change the input data to this vector of XY pairs

Parameter ``XY:``:
    input data vector given as vector<pair<X,Y>>)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator =
R"doc(Interface class for interpolator classes Create an interpolator object
by provding vectors for x and y (same size). X must be sorted and no
duplicates are allowed. then call interpolator(new x value) to get a
corresponding y value at this x position.

Template parameter ``YType:``:
    type of the y values (typically double, but will be a vector for
    the slerp interpolator class))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_I_Interpolator =
R"doc(Construct a new Interpolator object from two vectors usage:
interpolated_y_value = interpolator.interpolate(x_value)

Parameter ``extrapolation_mode``:
    extrapolation mode (nearest or fail))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_append =
R"doc(append an x- and the corresponding y value to the interpolator data.

Parameter ``x``:
    value, must be > than all existing x values

Parameter ``y``:
    corresponding y value)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_append_2 =
R"doc(append a x and y value pair to the interpolator data

Parameter ``xy``:
    x and y value pair. x must be > than all existing x values)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_check_XY = R"doc(check if input data is valid (e.g. sorted, no duplicated x values))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_check_XY_2 = R"doc(check if input data is valid (e.g. sorted, no duplicated x values))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_extend =
R"doc(append x and y value lists to the interplator data (vectorized call)

Parameter ``X``:
    list of x values. Must be sorted in ascending order. All x values
    must be larger than the largest x value in the interpolator data.

Parameter ``Y``:
    list of corresponding Y values. Must be same size as X)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_extend_2 =
R"doc(append a list of x and y value pairs to the interplator data
(vectorized call)

Parameter ``XY``:
    list of x,y value pairs. X Must be sorted in ascending order. All
    x values must be larger than the largest x value in the
    interpolator data.)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_extr_mode = R"doc(extrapolation mode type.)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_get_extrapolation_mode =
R"doc(Get the currently set extrapolation mode

Returns:
    :py:class:`t_extr_mode
    <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>`
    object (enumerator) that describes the extrapolation mode)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_operator_call =
R"doc(get the interolated y value for given x target

Parameter ``target_x``:
    find the corresponding y value for this x value

Returns:
    corresponding y value)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_operator_call_2 =
R"doc(get nearest y values for given x targets (vectorized call)

Parameter ``targets_x``:
    vector of x values. For each of these values find the corrspondig
    y value

Returns:
    corresponding y value)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_set_data_XY =
R"doc(change the input data to these X and Y vectors

Parameter ``X:``:
    x vector (must be same size, must be sorted in ascending order)

Parameter ``Y:``:
    y vector (must be same size))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_set_data_XY_2 =
R"doc(change the input data to this vector of XY pairs

Parameter ``XY:``:
    input data vector given as vector<pair<X,Y>>)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_set_extrapolation_mode =
R"doc(Set the extrapolation mode

Parameter ``extrapolation_mode``:
    :py:class:`t_extr_mode
    <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>`
    object (enumerator) that describes the extrapolation mode)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator =
R"doc(Interface class for interpolator classes This template clas implements
base functions interpolators that interpolate between two values
(pairs). This interface implements the search for the x position
within this vector (closest 2 x/y value pair) and computes an x
interpolation value (target_x) Then it call the __call__ functions of
the implementation classes that use this interface to interpolate
between these pairs.

Template parameter ``YType:``:
    type of the y values (typically double, but will be a vector for
    the slerp interpolator class))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_I_PairInterpolator =
R"doc(Construct a new Interpolator object from a vector of pairs usage:
interpolated_y_value = interpolator.interpolate(x_value)

Parameter ``XY``:
    vector of x,y pairs. X must be unique and sorted

Parameter ``extrapolation_mode``:
    :py:class:`t_extr_mode
    <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>`
    object that describes the extrapolation mode)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_I_PairInterpolator_2 =
R"doc(Construct a new Interpolator object from a vector of pairs usage:
interpolated_y_value = interpolator.interpolate(x_value)

Parameter ``X``:
    X vector; must be unique and sorted in ascending order. same size
    as Y!

Parameter ``Y``:
    Y vector; must be unique and sorted in ascending order. same size
    as X!

Parameter ``extrapolation_mode``:
    :py:class:`t_extr_mode
    <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>`
    object that describes the extrapolation mode)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_XY =
R"doc(< main data vector containing pairs of corresponding x and y
datapoitns)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_append = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_append_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_extend = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_extend_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_get_data_X =
R"doc(return the x component of the internal data vector

Returns:
    std::vector<double>)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_get_data_XY =
R"doc(return the internal data vector

Returns:
    const std::vector<std::pair<double,YType>>&)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_get_data_Y =
R"doc(return the y component of the itnernal data vector

Returns:
    std::vector<YType>)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_get_extrapolation_mode = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_interpolate_pair =
R"doc(Interface for implementing an interpolation between two y values using
a given interpolation factor

Parameter ``target_x``:
    interpolation factor. 0 means return smaller y value, 1 means
    return larger y value

Parameter ``y1``:
    smaller y value

Parameter ``y1``:
    larger y value

Returns:
    interpolated y value)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_last_x_pair = R"doc(< last pair (for faster consequtive searches))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_operator_call =
R"doc(get the interolated y value for given x target

Parameter ``target_x``:
    find the corresponding y value for this x value

Returns:
    corresponding y value)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_operator_call_2 =
R"doc(get nearest y values for given x targets (vectorized call)

Parameter ``targets_x``:
    vector of x values. For each of these values find the corrspondig
    y value

Returns:
    corresponding y value)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_set_data_XY =
R"doc(change the input data to this vector of XY pairs

Parameter ``XY:``:
    input data vector given as vector<pair<X,Y>>)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_set_data_XY_2 =
R"doc(change the input data to these X and Y vectors

Parameter ``X:``:
    x vector (must be same size, must be sorted in ascending order)

Parameter ``Y:``:
    y vector (must be same size))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_set_extrapolation_mode = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_calc_target_x =
R"doc(compute the interpolation factor between xmin and xmax

Parameter ``target_x``:
    x value for which we want to know the interpolation factor

Returns:
    interpolation factor)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_t_x_pair = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_xfactor = R"doc(< 1/(xmax-xmin))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_xmax = R"doc(< larger xvalue)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_xmax_index = R"doc(< index of the larger x value (in the internal vector))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_xmin = R"doc(< smaller xvalue)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_xmin_index = R"doc(< index of the smaller x value (in the internal vector))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator = R"doc(Find linear interpolated values within vector data)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_LinearInterpolator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_LinearInterpolator_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_LinearInterpolator_3 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_interpolate_pair =
R"doc(Interpolate: Interpolate interpolation between two values

Parameter ``target_x:``:
    the target point [0.0 - 1.0]

Parameter ``y1``:
    : first y value (target_x = 0)

Parameter ``y2``:
    : second value (target_x = 01) inbetween)

Returns:
    Interpolated value for target position)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator = R"doc(Interpolator class to find nearest neighbors within vector data)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_NearestInterpolator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_NearestInterpolator_2 =
R"doc(Construct a new Nearest Interpolator object from a vector of pairs
usage: interpolated_y_value = interpolator.interpolate(x_value)

Parameter ``XY``:
    vector of x,y pairs. X must be unique and sorted in ascending
    order.

Parameter ``extrapolation_mode``:
    extrapolation mode (nearest or fail))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_NearestInterpolator_3 =
R"doc(Construct a new Nearest Interpolator object from a vector of pairs
usage: interpolated_y_value = interpolator.interpolate(x_value)

Parameter ``X``:
    X vector; must be unique and sorted in ascending order. same size
    as Y!

Parameter ``Y``:
    Y vector; must be unique and sorted in ascending order. same size
    as X!

Parameter ``extrapolation_mode``:
    extrapolation mode (nearest or fail))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_interpolate_pair =
R"doc(Interpolate interpolation between two values

Parameter ``target_x:``:
    the target point [0.0 - 1.0]

Parameter ``y1``:
    : first y value (target_x = 0)

Parameter ``y2``:
    : second value (target_x = 01) inbetween)

Returns:
    Interpolated value for target position)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator =
R"doc(Class that implements a slerp interpolation for vectors. Data is
internaly represented in quaternions using libeigen. Interfaces to
represent the data in yaw, pitch, roll angles are provided. the
__call__ equivalent to get interpolated yaw pitch roll is the ypr
function)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_SlerpInterpolator = R"doc(Constructor to make default initialization possible (neccessary?))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_SlerpInterpolator_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_SlerpInterpolator_3 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_SlerpInterpolator_4 =
R"doc(Construct a new Slerp Interpolator object using vectors of x, yaw,
pitch and roll

Parameter ``X``:
    vector; must be unique and sorted in ascending order

Parameter ``yaw``:
    vector with yaw data (rotation arround z axis). Must be same size
    as X!

Parameter ``pitch``:
    vector with pitch data (rotation arround y axis). Must be same
    size as X!

Parameter ``roll``:
    vector with roll data (rotation arround x axis). Must be same size
    as X!

Parameter ``input_in_degrees``:
    if true (default) yaw,pitch and roll are in °, otherwise [rad]

Parameter ``extrapolation_mode``:
    :py:class:`t_extr_mode
    <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>`
    object that describes the extrapolation mode)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_SlerpInterpolator_5 =
R"doc(Construct a new Slerp Interpolator object using vectors of x, yaw,
pitch and roll

Parameter ``X``:
    vector; must be unique and sorted in ascending order

Parameter ``YPR``:
    vector with yaw, pitch and roll data points. Must be same size as
    X!

Parameter ``input_in_degrees``:
    if true (default) yaw,pitch and roll are in °, otherwise [rad]

Parameter ``extrapolation_mode``:
    :py:class:`t_extr_mode
    <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>`
    object that describes the extrapolation mode)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_append =
R"doc(append an x, yaw, pitch, roll data point

Parameter ``X``:
    must be larger than all internal data points

Parameter ``yaw``:
    rotation arround z axis

Parameter ``pitch``:
    rotation arround y axis

Parameter ``roll``:
    rotation arround x axis

Parameter ``input_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_append_2 =
R"doc(append an x, yaw, pitch, roll data point

Parameter ``X``:
    must be larger than all internal data points

Parameter ``ypr``:
    array with one yaw, pitch and roll data point

Parameter ``input_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_extend =
R"doc(append data with lists of x, yaw, pitch, roll data (vectorized call)

Parameter ``X``:
    vector; must be unique and sorted in ascending order

Parameter ``yaw``:
    vector with yaw data (rotation arround z axis). Must be same size
    as X!

Parameter ``pitch``:
    vector with pitch data (rotation arround y axis). Must be same
    size as X!

Parameter ``roll``:
    vector with roll data (rotation arround x axis). Must be same size
    as X!

Parameter ``input_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_extend_2 =
R"doc(append data with list of x, yaw, pitch, roll data (vectorized call)

Parameter ``X``:
    vector; must be unique and sorted in ascending order

Parameter ``ypr``:
    vector with yaw, pitch and roll data points. Must be same size as
    X!

Parameter ``input_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_get_data_XYPR =
R"doc(return the internal x and yrp data vector

Parameter ``output_in_degrees``:
    convert yaw, pitch and roll to degrees (default = True)

Returns:
    std::vector<std::array<4, double>> XYPR)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_get_data_YPR =
R"doc(return the internal yrp data vector

Parameter ``output_in_degrees``:
    convert yaw, pitch and roll to degrees (default = True)

Returns:
    std::vector<std::array<3, double>> YPR)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_interpolate_pair =
R"doc(Interpolate: Slerp interpolation between two values

Parameter ``target_x:``:
    the target point [0.0 - 1.0]

Parameter ``y1``:
    : first quaternion (target_x = 0)

Parameter ``y2``:
    : second quaternion (target_x = 01) inbetween)

Returns:
    Interpolated value for target position)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_set_data_XYPR =
R"doc(change the input data to thes X, yaw, pitch, roll vectors (will be
converted to queternion)

Parameter ``X``:
    vector; must be unique and sorted in ascending order

Parameter ``yaw``:
    vector with yaw data (rotation arround z axis). Must be same size
    as X!

Parameter ``pitch``:
    vector with pitch data (rotation arround y axis). Must be same
    size as X!

Parameter ``roll``:
    vector with roll data (rotation arround x axis). Must be same size
    as X!

Parameter ``input_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_set_data_XYPR_2 =
R"doc(change the input data to thes X, yaw, pitch, roll vectors (will be
converted to queternion)

Parameter ``X``:
    vector; must be unique and sorted in ascending order

Parameter ``yaw``:
    vector with yaw data (rotation arround z axis). Must be same size
    as X!

Parameter ``pitch``:
    vector with pitch data (rotation arround y axis). Must be same
    size as X!

Parameter ``roll``:
    vector with roll data (rotation arround x axis). Must be same size
    as X!

Parameter ``input_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_ypr =
R"doc(get the interolated yaw, pitch and roll values for given x target

Parameter ``target_x``:
    find the corresponding y value for this x value

Parameter ``output_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad

Returns:
    corresponding y value)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_ypr_2 =
R"doc(get the interolated yaw, pitch and roll values for given x target
(vectorized call)

Parameter ``targets_x``:
    vector of x values. For each of these values find the corrspondig
    yaw, pitch and roll value

Parameter ``output_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad

Returns:
    corresponding y value)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_t_extr_mode = R"doc(extrapolation mode type.)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_t_extr_mode_extrapolate = R"doc(< interpolate using the closest value pair in the internal x vector)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_t_extr_mode_fail =
R"doc(< throw out_of_range exception if x value exceeds boundaries of
internal vector)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_t_extr_mode_nearest = R"doc(< return nearest value in the vector.)doc";

#if defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

