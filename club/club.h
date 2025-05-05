#pragma once
#include <deque>
#include <map>
#include <string>
#include <vector>

#include "utils.h"
#include "../client/client.h"
#include "../table/table.h"


namespace club {

class Club
{
public:
    explicit Club(const int &tableCount, const int &costPerHour, const helpers::Time &openTime, const helpers::Time &closeTime);
    ~Club() = default;
    void addClient(const client::Client &client);
    void assignTable(const client::Client &client, const int &tableId);
    void processEvent();
    void freeAllTables();
    void freeTable(const int &tableId);

private:
    std::vector<table::Table> m_tables {};
    std::deque<std::string> m_clientsQueue {};
    std::map<table::Table, client::Client> m_clients {};
    std::vector<std::string> m_log {};
    int m_costPerHour {};
    helpers::Time m_openTime {};
    helpers::Time m_closeTime {};

    void log(const std::string &message);
    void handleClientEnter();
    void handleClientSit();
    void handleClientLeave();
    void hanleWaiting();
    void handleQueue();

};

} // namespace club