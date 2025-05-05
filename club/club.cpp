#include "club.h"

namespace club {

Club::Club(const int &tableCount, const int &costPerHour, const Time &openTime, const Time &closeTime)
    : m_costPerHour(costPerHour),
      m_openTime(openTime),
      m_closeTime(closeTime)
{
    m_tables.reserve(tableCount);
    for (auto i = 0; i < tableCount; ++i) {
        m_tables.emplace_back(i + 1, m_costPerHour);
    }
}


void Club::addClient(const client::Client &client)
{

}

void Club::assignTable(const client::Client &client, const int &tableId)
{

}


}