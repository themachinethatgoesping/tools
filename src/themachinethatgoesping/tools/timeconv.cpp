// SPDX-FileCopyrightText: 2022 - 2025 Peter Urban, Ghent University
// SPDX-FileCopyrightText: 2022 Peter Urban, GEOMAR Helmholtz Centre for Ocean Research Kiel
//
// SPDX-License-Identifier: MPL-2.0

#include "timeconv.hpp"

#include <chrono>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string_view>
#include <utility>

#include <fmt/chrono.h>

#include "helper/isviewstream.hpp"

namespace themachinethatgoesping {

namespace tools {

namespace timeconv {

std::chrono::system_clock::time_point unixtime_to_timepoint(double unixtime)
{
    std::chrono::duration<double> time_since_epoch(unixtime);
    return std::chrono::system_clock::time_point(
        std::chrono::duration_cast<std::chrono::microseconds>(time_since_epoch));
}

double timepoint_to_unixtime(std::chrono::system_clock::time_point TimePoint)
{
    std::chrono::microseconds us =
        std::chrono::duration_cast<std::chrono::microseconds>(TimePoint.time_since_epoch());
    auto timeUSec = static_cast<uint64_t>(us.count());
    return static_cast<double>(timeUSec) / 1000000.0;
}

double year_month_day_to_unixtime(int year, int month, int day, uint64_t micro_seconds)
{
    auto ymd = std::chrono::year{ year } / std::chrono::month{ static_cast<unsigned>(month) } /
               std::chrono::day{ static_cast<unsigned>(day) };
    auto tp = std::chrono::sys_days{ ymd } + std::chrono::microseconds{ micro_seconds };
    return timepoint_to_unixtime(tp);
}

double datestring_to_unixtime(std::string_view DateString, const std::string& format)
{
    std::chrono::sys_time<std::chrono::microseconds> tp;
    helper::isviewstream                             is(DateString);
    is >> std::chrono::parse(format, tp);

    return std::chrono::duration<double>(tp.time_since_epoch()).count();
}

std::string unixtime_to_datestring(double             unixtime,
                                   unsigned int       fractionalSecondsDigits,
                                   const std::string& format)
{
    if (!std::isfinite(unixtime))
        return "NaN_time_string";

    if (fractionalSecondsDigits > 6)
        fractionalSecondsDigits = 6;

    double digits = std::pow(10, fractionalSecondsDigits);

    unixtime = std::round(unixtime * digits);
    unixtime /= digits;

    auto time       = unixtime_to_timepoint(unixtime);
    auto fmt_spec   = std::string("{:") + format + "}";
    auto datestring = fmt::format(fmt::runtime(fmt_spec), time);

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

double windows_filetime_to_unixtime(uint32_t highDateTime, uint32_t lowDateTime)
{
    uint64_t              date     = (static_cast<int64_t>(highDateTime) << 32) + lowDateTime;
    static const uint64_t adjust   = 11644473600000ULL * 10000ULL;
    double                unixtime = static_cast<double>(date - adjust) / 10000000.0;
    return unixtime;
}

std::pair<uint32_t, uint32_t> unixtime_to_windows_filetime(double unixtime)
{
    static const int64_t adjust = int64_t(11644473600000. * 10000.);
    unixtime *= 10000000.;
    uint64_t date         = static_cast<uint64_t>(std::llround(unixtime)) + adjust;
    uint32_t lowDateTime  = static_cast<uint32_t>(date & 0xFFFFFFFF);
    uint32_t highDateTime = static_cast<uint32_t>(date >> 32);
    return std::make_pair(highDateTime, lowDateTime);
}

} // namespace timeconv

} // namespace tools

} // namespace themachinethatgoesping
