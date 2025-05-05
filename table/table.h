#pragma once
#include <string>
#include "club.h"

namespace table
{
class Table {
public:
    explicit Table(const int &id, const int &cost);
    ~Table() = default;
    void occupy(const std::string& clientName, const club::Time& startTime);
    void release(const club::Time& endTime);
    void reset();
    std::string status() const;

    const int &id() const;
    const bool &isOccupied() const;
    const std::string& clientName() const;
    const club::Time& spentTime() const;
    const int &moneyEarned() const;

private:
    int m_id {};
    bool m_occupied {false};
    std::string m_clientName {};
    club::Time m_spentTime {};
    club::Time m_startTime {};
    int m_money {};
    int m_cost {};
};

}