#pragma once
#include <string>
#include <utility>
#include "club.h"

namespace client {

class Client
{
public:
    explicit Client(const club::Time &arrivalTime, std::string name)
        : m_name(std::move(name)), m_arrivalTime(arrivalTime) {};

    ~Client() = default;

    const std::string &name() const { return m_name; }
    const club::Time &arrivalTime() const { return m_arrivalTime; }
    const int &occupiedTable() const { return m_occupiedTable; }
    void setOccupiedTable(const int &table) { m_occupiedTable = table; }
    void setArrivalTime(const club::Time &arrivalTime) { m_arrivalTime = arrivalTime; }
    void setAtClub(const bool &atClub) { m_atClub = atClub; }
    void setInQueue(const bool &inQueue) { m_inQueue = inQueue; }
    const bool &atClub() const { return m_atClub; }
    const bool &inQueue() const { return m_inQueue; }

private:
    std::string m_name;
    int m_occupiedTable {-1};
    club::Time m_arrivalTime;
    bool m_atClub {false};
    bool m_inQueue {false};
};

} // namespace client
