#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/string_view.h>
#include <nanobind/stl/chrono.h>

#include "datetime.hpp"
#include <themachinethatgoesping/tools/timeconv.hpp>

namespace nb = nanobind;

namespace themachinethatgoesping {
namespace tools {
namespace nanobind_helper {

nb::object unixtime_to_datetime(double timestamp, double timezone_offset_hours)
{
    nb::module_ datetimeModule = nb::module_::import_("datetime");
    nb::object datetimeClass  = datetimeModule.attr("datetime");
    nb::object timezoneClass  = datetimeModule.attr("timezone");
    nb::object timedeltaClass = datetimeModule.attr("timedelta");

    nb::object timezoneObject = timezoneClass(timedeltaClass(nb::arg("hours") = timezone_offset_hours));
    nb::object datetimeObject = datetimeClass.attr("fromtimestamp")(timestamp, timezoneObject);

    return datetimeObject;
}

nb::object datestring_to_datetime(std::string_view datestring, const std::string& format, double timezone_offset_hours)
{
    return unixtime_to_datetime(timeconv::datestring_to_unixtime(datestring, format), timezone_offset_hours);
}

double datetime_to_unixtime(const nb::handle& datetimeObject)
{
    return nb::cast<double>(datetimeObject.attr("timestamp")());
}

std::string datetime_to_datestring(const nb::handle& datetimeObject, unsigned int fractionalSecondsDigits, const std::string& format)
{
    // Convert the datetime object to unixtime first, then use timeconv to format it
    double unixtime = datetime_to_unixtime(datetimeObject);
    return timeconv::unixtime_to_datestring(unixtime, fractionalSecondsDigits, format);
}

} // namespace nanobind_helper
} // namespace tools
} // namespace themachinethatgoesping