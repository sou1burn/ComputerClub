#include <sstream>
#include <iomanip>
#include "client.h"

namespace client
{
Client::Client(const helpers::Time &arrivalTime, std::string name)
    : m_name(std::move(name)), m_arrivalTime(arrivalTime)
{
}
const std::string &Client::name() const
{
    return m_name;
}

const int &Client::occupiedTable() const
{
    return m_occupiedTable;
}

const bool &Client::atClub() const
{
    return m_atClub;
}

const bool &Client::inQueue() const
{
    return m_inQueue;
}

void Client::setOccupiedTable(const int &table)
{
    m_occupiedTable = table;
}

void Client::setAtClub(const bool &atClub)
{
    m_atClub = atClub;
}

void Client::setInQueue(const bool &inQueue)
{
    m_inQueue = inQueue;
}

void Client::setArrivalTime(const helpers::Time &arrivalTime)
{
    m_arrivalTime = arrivalTime;
}

bool Client::operator<(const client::Client &other) const
{
    return this->name() < other.name();
}

}




