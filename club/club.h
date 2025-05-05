#pragma once
#include <deque>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "client.h"
#include "table.h"
#include "utils.h"


namespace club {

class Club
{
public:
    explicit Club(const int &tableCount, const int &costPerHour, const helpers::Time &openTime, const helpers::Time &closeTime, const std::set<client::Client> &clients);
    ~Club() = default;
    void processEvent(const helpers::Event &event);
    void closeClubAndLogEverything();
    const std::vector<std::string> &getLogs();

private:
    std::vector<table::Table> m_tables {};
    std::deque<std::string> m_waitingQueue {};
    std::map<std::string, client::Client> m_clients {};
    std::vector<std::string> m_log {};
    int m_costPerHour {};
    helpers::Time m_openTime {};
    helpers::Time m_closeTime {};

    void log(const std::string &message);
    void handleClientEnter(const helpers::Event &event);
    void handleClientSit(const helpers::Event &event);
    void handleClientLeave(const helpers::Event &event);
    void handleWaiting(const helpers::Event &event);
    void serveClientFromQueue(const int &tableId, const helpers::Time &time);

};

} // namespace club