#pragma once
#include <string>

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
};

}