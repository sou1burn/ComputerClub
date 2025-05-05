#include "table.h"

namespace table {
Table::Table(const int &id) : m_id(id)
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



}
