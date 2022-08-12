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


static const char *__doc_Eigen_serialize = R"doc()doc";

static const char *__doc_Eigen_serialize_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_bitsery_helpers_is_input = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_bitsery_helpers_is_input_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter =
R"doc(Class that allows for easy pretty printing of class members usage: 1.
Implement a __printer__ function as public class member this function
should return a ObjectPrinter object. Register all, values,
containers, objects that are to be printed. 2. Add the
__CLASSHELPERS_DEFAULT_PRINTING_FUNCTIONS__ macro to the public
functions. This macro implements std::string info_string() and
print(std::ostream) functions using the object printer 3. Add the
__PYCLASS_DEFAULT_PRINTING__ to the python module defintion. This
macro implements __str__(), __repr__(), info_string() and print() as
python functions)doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_ObjectPrinter =
R"doc(Construct a new Object Printer object

Parameter ``float_precision``:
    default 2, set number of digits for floating point values)doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_ObjectPrinter_2 =
R"doc(Construct a new Object Printer object

Parameter ``name``:
    name of the class that is to be printed)doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_append =
R"doc(Append the fields of an existing object printer

Parameter ``printer``:
    printer to be appended)doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_create_str =
R"doc(Create an info_string from the registered values/sections

Returns:
    std::string)doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_field_types = R"doc(< variable types)doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_fields = R"doc(< variable names)doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_float_precision = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_from_binary = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_from_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_info_string = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_name = R"doc(< name of the class that is to be printed)doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_print = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_register_container =
R"doc(register a 1D container for printing

Template parameter ``t_value``:
    integer or floating point

Parameter ``name``:
    name of the container

Parameter ``value``:
    container values

Parameter ``value_info``:
    additional info (is printed in [] behind the variable)

Parameter ``pos``:
    position where the value is registers (if negative, the value is
    appended))doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_register_enum =
R"doc(register an enumeration for printing

Template parameter ``t_value``:
    enumerator

Parameter ``name``:
    name of the variable

Parameter ``value``:
    value of the variable

Parameter ``value_info``:
    additional info (is printed in [] behind the variable)

Parameter ``pos``:
    position where the value is registers (if negative, the value is
    appended))doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_register_section =
R"doc(register a section break for printing

Parameter ``name``:
    name of the following section

Parameter ``underliner``:
    character used to underline the section name

Parameter ``pos``:
    position where the value is registers (if negative, the value is
    appended))doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_register_string =
R"doc(register a formatted string field for printing

Parameter ``name``:
    name of the variable

Parameter ``value``:
    value of the variable

Parameter ``value_info``:
    additional info (is printed in [] behind the variable)

Parameter ``pos``:
    position where the value is registers (if negative, the value is
    appended))doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_register_value =
R"doc(register a single integer of floating point value for printing

Template parameter ``t_value``:
    double or floating point

Parameter ``name``:
    name of the variable

Parameter ``value``:
    value of the variable

Parameter ``value_info``:
    additional info (is printed in [] behind the variable)

Parameter ``pos``:
    position where the value is registers (if negative, the value is
    appended))doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_remove_sections = R"doc(Remove all existing sections)doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_section_underliner = R"doc(< additional info (printed in []))doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_t_field =
R"doc(internal, describe the value type for implementing different printing
strategies)doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_t_field_tcontainer = R"doc(< 1D container (floating point or integer))doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_t_field_tenum = R"doc(< enumerator)doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_t_field_tsection = R"doc(< section break)doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_t_field_tstring = R"doc(< formatted string field)doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_t_field_tvalue = R"doc(< double or integer)doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_to_binary = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_to_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_underline =
R"doc(add a line under a given line string

Parameter ``line``:
    input string

Returns:
    std::string)doc";

static const char *__doc_themachinethatgoesping_tools_classhelpers_ObjectPrinter_value_infos = R"doc(< additional info (printed in []))doc";

static const char *__doc_themachinethatgoesping_tools_helper_approx =
R"doc(compare to floats using a relative difference factor

Template parameter ``t_float``:
    floating point type

Parameter ``f1``:
    float/double 1

Parameter ``f2``:
    float/double 1

Parameter ``relative_difference_factor``:
    relative factor by which the 2 numbers must be comparable (default
    0.01%)

Returns:
    true/false)doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_ConsoleProgressBar = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_callback_close = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_callback_current = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_callback_init = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_callback_set_postfix = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_callback_set_progress = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_callback_tick = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_current = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_currentStep = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_first = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_last = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_numOf_steps = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_os = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ConsoleProgressBar_started = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBar = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_I_ProgressBarTimed = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_callback_close = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_callback_current = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_callback_init = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_callback_set_postfix = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_callback_set_progress = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_callback_tick = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_close = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_current = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_first = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_init = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_lock_timer = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_set_postfix = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_set_progress = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_tick = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBarTimed_timer_mutex = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_I_ProgressBar = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_close = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_current = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_init = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_set_postfix = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_set_progress = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_I_ProgressBar_tick = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_NoIndicator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_NoIndicator_NoIndicator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_NoIndicator_close = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_NoIndicator_current = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_NoIndicator_init = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_NoIndicator_set_postfix = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_NoIndicator_set_progress = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_NoIndicator_tick = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ProgressIndicator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ProgressIndicator_ProgressIndicator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ProgressIndicator_callback_close = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ProgressIndicator_callback_current = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ProgressIndicator_callback_init = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ProgressIndicator_callback_set_postfix = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ProgressIndicator_callback_set_progress = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ProgressIndicator_callback_tick = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ProgressIndicator_first = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ProgressIndicator_indicator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ProgressIndicator_last = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_progressbars_ProgressIndicator_name = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_rotationfunctions_compute_heading =
R"doc(compute heading from northing and easting north 0°/360°, east 90°,
south 180°, west 270

Parameter ``northing``:
    northing in m

Parameter ``easting``:
    easting in m

Parameter ``radians``:
    return as rad, otherwise as degrees

Returns:
    heading in rad or degrees)doc";

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
    rotation around z axis [° or rad]

Parameter ``pitch``:
    rotation around y axis [° or rad]

Parameter ``roll``:
    rotation around x axis [° or rad]

Parameter ``input_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad

Returns:
    Eigen::Quaternion<floattype>)doc";

static const char *__doc_themachinethatgoesping_tools_timeconv_datestring_to_unixtime =
R"doc(Converting between date strings and UnixTime stamps (ref 1970)

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
R"doc(Converting between date strings and UnixTime stamps (ref 1970)

Parameter ``UnixTime:``:
    seconds since 01.01.1970 as double

Parameter ``fractionalSecondsDigits:``:
    How many digits to use for the split seconds. Minimum is 0 (second
    resolution) Maximum is 6 (microsecond resolution)

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
boost makima interpolator. Note: this interpolator acts as linear
interpolator if less than 4 values are stored.)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_AkimaInterpolator = R"doc(Construct a new (uninitialized) Akima Interpolator object)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_AkimaInterpolator_2 =
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

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_X = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_Y = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_akima_spline = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_append = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_empty = R"doc(check if the interpolator contains data)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_extend = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_from_binary = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_from_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_get_data_X =
R"doc(return the x component of the internal data vector

Returns:
    std::vector<double>)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_get_data_Y =
R"doc(return the y component of the internal data vector

Returns:
    std::vector<YType>)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_info_string = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_init_linearextrapolators =
R"doc(internal function to initialize the linear extrapolation objects _X,
_Y and the _akima_spline must be set/initialized before calling this
function)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_max_linearextrapolator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_min_linearextrapolator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_operator_call =
R"doc(get the interpolated y value for given x target

Parameter ``target_x``:
    find the corresponding y value for this x value

Returns:
    corresponding y value)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_operator_call_2 =
R"doc(get nearest y values for given x targets (vectorized call)

Parameter ``targets_x``:
    vector of x values. For each of these values find the corrsponding
    y value

Returns:
    corresponding y value)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_print = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_set_data_XY =
R"doc(change the input data to these X and Y vectors

Parameter ``X:``:
    x vector (must be same size)

Parameter ``Y:``:
    y vector (must be same size))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_to_binary = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_to_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_AkimaInterpolator_type_to_string = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator =
R"doc(Interface class for interpolator classes Create an interpolator object
by providing vectors for x and y (same size). X must be sorted and no
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

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_check_XY = R"doc(check if input data is valid (e.g. sorted, no duplicated x values))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_extend =
R"doc(append x and y value lists to the interpolator data (vectorized call)

Parameter ``X``:
    list of x values. Must be sorted in ascending order. All x values
    must be larger than the largest x value in the interpolator data.

Parameter ``Y``:
    list of corresponding Y values. Must be same size as X)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_extr_mode = R"doc(extrapolation mode type.)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_get_data_X =
R"doc(return the x component of the internal data vector

Returns:
    std::vector<double>)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_get_data_Y =
R"doc(return the y component of the internal data vector

Returns:
    std::vector<YType>)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_get_extrapolation_mode =
R"doc(Get the currently set extrapolation mode

Returns:
    :py:class:`t_extr_mode
    <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>`
    object (enumerator) that describes the extrapolation mode)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_operator_call =
R"doc(get the interpolated y value for given x target

Parameter ``target_x``:
    find the corresponding y value for this x value

Returns:
    corresponding y value)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_operator_call_2 =
R"doc(get nearest y values for given x targets (vectorized call)

Parameter ``targets_x``:
    vector of x values. For each of these values find the corrsponding
    y value

Returns:
    corresponding y value)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_set_data_XY =
R"doc(change the input data to these X and Y vectors

Parameter ``X:``:
    x vector (must be same size, must be sorted in ascending order)

Parameter ``Y:``:
    y vector (must be same size))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_Interpolator_set_extrapolation_mode =
R"doc(Set the extrapolation mode

Parameter ``extrapolation_mode``:
    :py:class:`t_extr_mode
    <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>`
    object (enumerator) that describes the extrapolation mode)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator =
R"doc(Interface class for interpolator classes This template class
implements base functions interpolators that interpolate between two
values (pairs). This interface implements the search for the x
position within this vector (closest 2 x/y value pair) and computes an
x interpolation value (target_x) Then it call the __call__ functions
of the implementation classes that use this interface to interpolate
between these pairs.

Template parameter ``YType:``:
    type of the y values (typically double, but will be a vector for
    the slerp interpolator class))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_I_PairInterpolator =
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

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_I_PairInterpolator_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_X = R"doc(< main data vector containing pairs of corresponding x datapoints)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_Y = R"doc(< main data vector containing pairs of corresponding y datapoints)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_append = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_empty = R"doc(check if the interpolator contains data)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_extend = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_get_data_X =
R"doc(return the x component of the internal data vector

Returns:
    std::vector<double>)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_get_data_Y =
R"doc(return the y component of the internal data vector

Returns:
    std::vector<YType>)doc";

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
R"doc(get the interpolated y value for given x target

Parameter ``target_x``:
    find the corresponding y value for this x value

Returns:
    corresponding y value)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_operator_call_2 =
R"doc(get nearest y values for given x targets (vectorized call)

Parameter ``targets_x``:
    vector of x values. For each of these values find the corrsponding
    y value

Returns:
    corresponding y value)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_set_data_XY =
R"doc(change the input data to these X and Y vectors

Parameter ``X:``:
    x vector (must be same size, must be sorted in ascending order)

Parameter ``Y:``:
    y vector (must be same size))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_calc_target_x =
R"doc(compute the interpolation factor between xmin and xmax

Parameter ``target_x``:
    x value for which we want to know the interpolation factor

Returns:
    interpolation factor)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_t_x_pair = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_t_x_pair_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_xfactor = R"doc(< 1/(xmax-xmin))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_xmax = R"doc(< larger xvalue)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_xmax_index = R"doc(< index of the larger x value (in the internal vector))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_xmin = R"doc(< smaller xvalue)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_I_PairInterpolator_t_x_pair_xmin_index = R"doc(< index of the smaller x value (in the internal vector))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator = R"doc(Find linear interpolated values within vector data)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_LinearInterpolator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_LinearInterpolator_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_from_binary = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_from_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_info_string = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_interpolate_pair =
R"doc(Interpolate: Interpolate interpolation between two values

Parameter ``target_x:``:
    the target point [0.0 - 1.0]

Parameter ``y1``:
    : first y value (target_x = 0)

Parameter ``y2``:
    : second value (target_x = 01) between)

Returns:
    Interpolated value for target position)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_print = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_to_binary = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_to_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_LinearInterpolator_type_to_string = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator = R"doc(Interpolator class to find nearest neighbors within vector data)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_NearestInterpolator = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_NearestInterpolator_2 =
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

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_from_binary = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_from_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_info_string = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_interpolate_pair =
R"doc(Interpolate interpolation between two values

Parameter ``target_x:``:
    the target point [0.0 - 1.0]

Parameter ``y1``:
    : first y value (target_x = 0)

Parameter ``y2``:
    : second value (target_x = 01) between)

Returns:
    Interpolated value for target position)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_print = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_to_binary = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_to_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_NearestInterpolator_type_to_string = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator =
R"doc(Class that implements a slerp interpolation for vectors. Data is
internally represented in quaternions using lib eigen. Interfaces to
represent the data in yaw, pitch, roll angles are provided. the
__call__ equivalent to get interpolated yaw pitch roll is the ypr
function)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_SlerpInterpolator = R"doc(Constructor to make default initialization possible (necessary?))doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_SlerpInterpolator_2 = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_SlerpInterpolator_3 =
R"doc(Construct a new Slerp Interpolator object using vectors of x, yaw,
pitch and roll

Parameter ``X``:
    vector; must be unique and sorted in ascending order

Parameter ``yaw``:
    vector with yaw data (rotation around z axis). Must be same size
    as X!

Parameter ``pitch``:
    vector with pitch data (rotation around y axis). Must be same size
    as X!

Parameter ``roll``:
    vector with roll data (rotation around x axis). Must be same size
    as X!

Parameter ``input_in_degrees``:
    if true (default) yaw,pitch and roll are in °, otherwise [rad]

Parameter ``extrapolation_mode``:
    :py:class:`t_extr_mode
    <themachinethatgoesping.tools.vectorinterpolators.t_extr_mode>`
    object that describes the extrapolation mode)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_SlerpInterpolator_4 =
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
    rotation around z axis

Parameter ``pitch``:
    rotation around y axis

Parameter ``roll``:
    rotation around x axis

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
    vector with yaw data (rotation around z axis). Must be same size
    as X!

Parameter ``pitch``:
    vector with pitch data (rotation around y axis). Must be same size
    as X!

Parameter ``roll``:
    vector with roll data (rotation around x axis). Must be same size
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

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_from_binary = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_from_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_get_data_YPR =
R"doc(return the internal yrp data vector

Parameter ``output_in_degrees``:
    convert yaw, pitch and roll to degrees (default = True)

Returns:
    std::vector<std::array<3, double>> YPR)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_info_string = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_interpolate_pair =
R"doc(Interpolate: Slerp interpolation between two values

Parameter ``target_x:``:
    the target point [0.0 - 1.0]

Parameter ``y1``:
    : first quaternion (target_x = 0)

Parameter ``y2``:
    : second quaternion (target_x = 01)

Returns:
    Interpolated value for target position)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_operator_eq = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_operator_ne = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_print = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_printer = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_serialize = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_set_data_XYPR =
R"doc(change the input data to these X, yaw, pitch, roll vectors (will be
converted to quaternion)

Parameter ``X``:
    vector; must be unique and sorted in ascending order

Parameter ``yaw``:
    vector with yaw data (rotation around z axis). Must be same size
    as X!

Parameter ``pitch``:
    vector with pitch data (rotation around y axis). Must be same size
    as X!

Parameter ``roll``:
    vector with roll data (rotation around x axis). Must be same size
    as X!

Parameter ``input_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_set_data_XYPR_2 =
R"doc(change the input data to these X, yaw, pitch, roll vectors (will be
converted to quaternion)

Parameter ``X``:
    vector; must be unique and sorted in ascending order

Parameter ``yaw``:
    vector with yaw data (rotation around z axis). Must be same size
    as X!

Parameter ``pitch``:
    vector with pitch data (rotation around y axis). Must be same size
    as X!

Parameter ``roll``:
    vector with roll data (rotation around x axis). Must be same size
    as X!

Parameter ``input_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_to_binary = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_to_stream = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_type_to_string = R"doc()doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_ypr =
R"doc(get the interpolated yaw, pitch and roll values for given x target

Parameter ``target_x``:
    find the corresponding y value for this x value

Parameter ``output_in_degrees``:
    if true, yaw pitch and roll input values are in ° otherwise rad

Returns:
    corresponding y value)doc";

static const char *__doc_themachinethatgoesping_tools_vectorinterpolators_SlerpInterpolator_ypr_2 =
R"doc(get the interpolated yaw, pitch and roll values for given x target
(vectorized call)

Parameter ``targets_x``:
    vector of x values. For each of these values find the corrsponding
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

