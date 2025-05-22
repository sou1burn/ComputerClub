#include <sstream>
#include <iomanip>
#include "utils.h"

namespace helpers
{
Time Time::fromString(const std::string &value)
{
    Time t;
    char sep;

    std::istringstream ss(value);
    ss >> t.hour >> sep >> t.minute;

    if (ss.fail() || sep != ':' || t.hour < 0 || t.hour >= 24 || t.minute < 0 || t.minute >= 60) {
        throw std::invalid_argument("Invalid time format: " + value);
    }

    return t;
}

std::string Time::toString() const
{
    std::stringstream ss;

    ss << std::setw(2) << std::setfill('0') << hour << ":" << std::setw(2) << std::setfill('0') << minute;
    return ss.str();
}

bool Time::operator<(const Time &other) const
{
    return (hour < other.hour) || (hour == other.hour && minute < other.minute);
}

bool Time::operator>(const Time &other) const
{
    return (hour > other.hour) || (hour == other.hour && minute > other.minute);
}

Time Time::operator-(const Time& other) const
{
    const int total = this->toMinutes() - other.toMinutes();
    return Time::fromMinutes(total);
}

bool Time::operator==(const Time& other) const
{
    return hour == other.hour && minute == other.minute;
}

Time Time::roundUp() const
{
    return {minute > 0 ? hour + 1 : hour, 0};
}

inline int Time::toMinutes() const
{
    return hour * 60 + minute;
}

inline Time Time::fromMinutes(const int &minutes)
{
    if (minutes < 0)
        throw std::invalid_argument("Negative minutes in fromMinutes()");

    return {minutes / 60, minutes % 60};
}

bool Time::operator>=(const Time &other) const
{
    return !(*this < other);
}

bool Time::isOpen(const Time &now, const Time &open, const Time &close)
{
    if (open == close)
        return true;
    if (open < close)
        return (now >= open && now < close);

    return (now >= open || now < close);
}

} // namespace club