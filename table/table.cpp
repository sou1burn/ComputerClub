#include "table.h"

namespace table {
Table::Table(const int &id, const int &cost) : m_id(id), m_cost(cost)
{
}

const int &Table::id() const
{
    return m_id;
}

const bool &Table::isOccupied() const
{
    return m_occupied;
}

const std::string &Table::clientName() const
{
    return m_clientName;
}

const club::Time &Table::spentTime() const
{
    return m_spentTime;
}

const int &Table::moneyEarned() const
{
    return m_money;
}

void Table::occupy(const std::string &clientName, const club::Time &startTime)
{
    m_occupied = true;
    m_clientName = clientName;
    m_startTime = startTime;
}

void Table::release(const club::Time &endTime)
{
    m_occupied = false;
    m_spentTime = endTime - m_startTime;
    m_money = m_spentTime.toMinutes() * m_cost / 60;
}

void Table::reset()
{
    m_occupied = false;
    m_money = 0;
    m_clientName.clear();
    m_spentTime = club::Time();
    m_startTime = club::Time();
}

std::string Table::status() const
{
    if (m_occupied)
        return "Table " + std::to_string(m_id) + " is occupied by " + m_clientName;
    else
        return "Table " + std::to_string(m_id) + " is free";
}
}
