#pragma once
#include <string>
#include "utils.h"

namespace table
{
class Table {
public:
    explicit Table(const int &id, const int &cost);
    ~Table() = default;
    void occupy(const std::string& clientName, const helpers::Time& startTime);
    void release(const helpers::Time& endTime);
    void reset();
    std::string status() const;

    const int &id() const;
    bool isOccupied() const;
    const std::string& clientName() const;
    helpers::Time spentTime() const;
    const int &moneyEarned() const;

private:
    int m_id {};
    bool m_occupied {false};
    std::string m_clientName {};
    helpers::Time m_spentTime {};
    helpers::Time m_startTime {};
    int m_money {};
    int m_cost {};
    int m_totalMinutes {};
};

}