// SPDX-FileCopyrightText: 2022 - 2023 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#include "timeconv.hpp"

#include <date/date.h>

#include <boost/algorithm/string.hpp>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

// using namespace std;
namespace themachinethatgoesping {

namespace tools {

namespace timeconv {

std::chrono::system_clock::time_point unixtime_to_timepoint(double unixtime)
{

    std::chrono::duration<double> time_since_epoch(unixtime);

    return (std::chrono::system_clock::time_point(
        std::chrono::duration_cast<std::chrono::microseconds>(time_since_epoch)));
}

double timepoint_to_unixtime(std::chrono::system_clock::time_point TimePoint)
{

    std::chrono::microseconds us =
        std::chrono::duration_cast<std::chrono::microseconds>(TimePoint.time_since_epoch());

    auto timeUSec = static_cast<uint64_t>(us.count());
    return ((double)timeUSec) / 1000000.0;
}

double year_month_day_to_unixtime(int year, int month, int day, uint64_t micro_seconds)
{
    auto X  = date::year{ year } / month / day;
    auto tp = date::sys_days{ X } + std::chrono::microseconds{ micro_seconds };
    return tools::timeconv::timepoint_to_unixtime(tp);
}

double datestring_to_unixtime(const std::string& DateString, const std::string& format)
{
    date::sys_time<std::chrono::microseconds> timePoint;

    std::stringstream(DateString) >> date::parse(format, timePoint);

    return timepoint_to_unixtime(timePoint);
}

std::string unixtime_to_datestring(double             unixtime,
                                   unsigned int       fractionalSecondsDigits,
                                   const std::string& format)
{
    if (!std::isfinite(unixtime))
        return "NaN_time_string";

    // microsecond precision is the max
    if (fractionalSecondsDigits > 6)
        fractionalSecondsDigits = 6;

    double digits = pow(10, fractionalSecondsDigits);

    unixtime = std::round(unixtime * digits);
    unixtime /= digits;

    auto time = unixtime_to_timepoint(unixtime);

    auto datestring = date::format(format, time);

    /* remove fractional seconds digits */
    if (auto pos = datestring.find_last_of('.'); pos != std::string::npos)
    {
        if (fractionalSecondsDigits == 0)
        {
            datestring.replace(pos, datestring.size(), "");
        }
        else
        {
            if (pos + fractionalSecondsDigits > datestring.size())
                fractionalSecondsDigits = static_cast<unsigned int>(datestring.size() - pos);

            datestring.replace(pos + fractionalSecondsDigits + 1, datestring.size(), "");
        }
    }

    return datestring;
}

} // namespace timeconv

} // namespace tools

} // namespace themachinethatgoesping
