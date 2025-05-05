#pragma once
#include <string>
#include "utils.h"

namespace client {

class Client
{
public:
    explicit Client(const helpers::Time &arrivalTime, std::string name);

    ~Client() = default;
    Client& operator=(const Client& other) = default;

    const std::string &name() const;
    const helpers::Time &arrivalTime() const;
    const int &occupiedTable() const;
    void setOccupiedTable(const int &table);
    void setArrivalTime(const helpers::Time &arrivalTime);
    void setAtClub(const bool &atClub);
    void setInQueue(const bool &inQueue);
    const bool &atClub() const;
    const bool &inQueue() const;

    bool operator<(const client::Client& other) const;

private:
    std::string m_name;
    int m_occupiedTable {-1};
    helpers::Time m_arrivalTime;
    bool m_atClub {false};
    bool m_inQueue {false};
};

} // namespace client
