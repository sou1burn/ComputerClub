#include "table.h"

namespace table {

Table::Table(const int &id, const int &cost) : m_id(id), m_cost(cost)
{
}

const int &Table::id() const
{
    return m_id;
}

bool Table::isOccupied() const
{
    return m_occupied;
}

helpers::Time Table::spentTime() const
{
    return helpers::Time::fromMinutes(m_totalMinutes);
}

const int &Table::moneyEarned() const
{
    return m_money;
}

void Table::occupy(const std::string &clientName, const helpers::Time &startTime)
{
    m_occupied = true;
    m_clientName = clientName;
    m_startTime = startTime;
}

void Table::release(const helpers::Time &endTime)
{
    const int sessionMinutes = (endTime - m_startTime).toMinutes();
    const int hoursToPay = (sessionMinutes + 59)/ 60;
    m_money += hoursToPay * m_cost;
    m_totalMinutes += sessionMinutes;
    m_occupied = false;
    m_clientName.clear();
}

void Table::reset()
{
    m_occupied = false;
    m_money = 0;
    m_clientName.clear();
    m_spentTime = helpers::Time();
    m_startTime = helpers::Time();
}

}
