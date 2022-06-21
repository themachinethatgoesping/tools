// SPDX-FileCopyrightText: 2022 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#include "timeconv.hpp"

#include <date/date.h>

#include <boost/algorithm/string.hpp>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;
namespace themachinethatgoesping {

namespace tools {

namespace timeconv {

chrono::system_clock::time_point unixtime_to_timepoint(double UnixTime)
{

    chrono::duration<double> time_since_epoch(UnixTime);

    return (chrono::system_clock::time_point(
        chrono::duration_cast<chrono::microseconds>(time_since_epoch)));
}

double timepoint_to_unixtime(chrono::system_clock::time_point TimePoint)
{

    chrono::microseconds us =
        chrono::duration_cast<chrono::microseconds>(TimePoint.time_since_epoch());

    auto timeUSec = static_cast<unsigned long long>(us.count());
    return ((double)timeUSec) / 1000000.0;
}

double datestring_to_unixtime(const string& DateString, const string& format)
{
    date::sys_time<chrono::microseconds> timePoint;

    stringstream(DateString) >> date::parse(format, timePoint);

    return timepoint_to_unixtime(timePoint);
}

string unixtime_to_datestring(double        UnixTime,
                              unsigned int  fractionalSecondsDigits,
                              const string& format)
{
    // microsecond precision is the max
    if (fractionalSecondsDigits > 6)
        fractionalSecondsDigits = 6;

    double digits = pow(10, fractionalSecondsDigits);

    UnixTime = std::round(UnixTime * digits);
    UnixTime /= digits;

    auto time = unixtime_to_timepoint(UnixTime);

    auto datestring = date::format(format, time);

    /* remove fractional seconds digits */
    if (auto pos = datestring.find_last_of('.'); pos != string::npos)
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
