#include <algorithm>
#include <iostream>
#include "club.h"

namespace club {

Club::Club(const int &tableCount, const int &costPerHour, const helpers::Time &openTime, const helpers::Time &closeTime, const std::set<client::Client> &clients)
    : m_costPerHour(costPerHour),
      m_openTime(openTime),
      m_closeTime(closeTime)
{
    m_tables.reserve(tableCount);
    for (auto i = 1; i <= tableCount; ++i)
        m_tables.emplace_back(i, m_costPerHour);

    for (const auto &client : clients)
        m_clients.insert(std::make_pair(client.name(), client));
}

void Club::log(const std::string &message)
{
    m_log.push_back(message);
}

void Club::processEvent(const helpers::Event &event) {
    std::string logMessage = event.m_time.toString() + " " + std::to_string(event.m_id) + " " + event.m_name;

    if (event.m_id == 2 && event.m_tableId.has_value())
        logMessage += " " + std::to_string(event.m_tableId.value());

    log(logMessage);
    switch (event.m_id) {
        case 1: handleClientEnter(event);
            break;
        case 2: handleClientSit(event);
            break;
        case 3: handleWaiting(event);
            break;
        case 4: handleClientLeave(event);
            break;
        default:
            log(event.m_time.toString() + " 13 UnknownEvent");
    }
}


void Club::handleClientEnter(const helpers::Event &event)
{
    if (!helpers::Time::isOpen(event.m_time, m_openTime, m_closeTime)) {
        log(event.m_time.toString() + " 13 NotOpenYet");
        return;
    }
    auto it = m_clients.find(event.m_name);

    if (it != m_clients.end() && it->second.atClub()) {
        log(event.m_time.toString() + " 13 YouShallNotPass");
        return;
    }
    m_clients.emplace(event.m_name, client::Client(event.m_time, event.m_name));
    m_clients.at(event.m_name).setArrivalTime(event.m_time);
    m_clients.at(event.m_name).setAtClub(true);
}

void Club::handleClientSit(const helpers::Event &event)
{
    auto &client = m_clients.at(event.m_name);
    if (!client.atClub()) {
        log(event.m_time.toString() + " 13 ClientUnknown");
        return;
    }

    const auto tableId = event.m_tableId.value();
    if (tableId <= 0 || tableId > m_tables.size()) {
        //log(event.m_time.toString() + " 13 TableDoesNotExist");
        return;
    }
    auto &table = m_tables[tableId - 1];
    if (table.isOccupied()) {
        log(event.m_time.toString() + " 13 PlaceIsBusy");
        return;
    }

    if (client.occupiedTable() != -1)
        m_tables[client.occupiedTable() - 1].release(event.m_time);
    table.occupy(client.name(), event.m_time);
    client.setOccupiedTable(tableId);
}

void Club::handleWaiting(const helpers::Event &event)
{
    if (m_waitingQueue.size() > m_tables.size()) {
        log(event.m_time.toString() + " 11 " + event.m_name + "left from table " + "" + std::to_string(event.m_tableId.value()));
        return;
    }

    for (const auto &table : m_tables) {
        if (!table.isOccupied()) {
            log(event.m_time.toString() + " 13 ICanWaitNoLonger!");
            return;
        }
    }
    m_waitingQueue.push_back(event.m_name);
    m_clients.at(event.m_name).setInQueue(true);
}

void Club::handleClientLeave(const helpers::Event &event)
{
    auto &client = m_clients.at(event.m_name);
    if (!client.atClub()) {
        log(event.m_time.toString() + " 13 ClientUnknown");
        return;
    }
    if (client.occupiedTable() != -1) {
        const int oldTableId = client.occupiedTable();
        if (oldTableId <= 0 || oldTableId > m_tables.size()) {
            return;
        }
        m_tables[oldTableId - 1].release(event.m_time);
        serveClientFromQueue(oldTableId - 1, event.m_time);
    } else if (client.inQueue()) {
        m_waitingQueue.erase(std::find(m_waitingQueue.begin(), m_waitingQueue.end(), event.m_name));
    }
    client.setAtClub(false);
    client.setOccupiedTable(-1);
}

const std::vector<std::string> &Club::getLogs()
{
    return m_log;
}

void Club::serveClientFromQueue(const int &tableId, const helpers::Time &time)
{
    if (m_waitingQueue.empty())
        return;
    const std::string name = m_waitingQueue.front();
    m_waitingQueue.pop_front();
    m_tables.at(tableId).occupy(name, time);
    m_clients.at(name).setOccupiedTable(tableId + 1);
    m_clients.at(name).setInQueue(false);
    log(time.toString() + " 12 " + name + " " + std::to_string(tableId + 1));
}

void Club::closeClubAndLogEverything()
{
    std::cout << m_openTime.toString() << "\n";
    for (auto& l : m_log)
        std::cout << l << "\n";
    std::cout << m_closeTime.toString() << "\n";
    std::vector<std::string> remaining;

    for (auto& [name, client] : m_clients) {
        if (client.atClub()) {
            const int tableId = client.occupiedTable();
            if (tableId > 0 && tableId <= m_tables.size())
                m_tables[tableId - 1].release(m_closeTime);
            remaining.push_back(name);
        }
    }
    std::sort(remaining.begin(), remaining.end());
    for (auto& name : remaining)
        std::cout << m_closeTime.toString() << " 11 " << name << "\n";

    for (auto& tbl : m_tables)
        std::cout << tbl.id() << " " << tbl.moneyEarned() << " " << tbl.spentTime().toString() << "\n";
}

}
