#pragma once
#include <string>
#include <optional>

namespace helpers {
struct Time {
    int hour {};
    int minute {};
    static Time fromString(const std::string& value);
    std::string toString() const;
    Time roundUp() const;
    int toMinutes() const;
    static Time fromMinutes(const int &minutes);

    bool operator<(const Time& other) const;
    bool operator>(const Time& other) const;
    Time operator-(const Time& other) const;
    bool operator==(const Time& other) const;
    static bool isOpen(const Time &now, const Time &open, const Time &close);
    bool operator>=(const Time &other) const;
};

struct Event
{
    Time m_time;
    int m_id;
    std::string m_name;
    std::optional<int> m_tableId;
};

}