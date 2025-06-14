#include <iostream>
#include <fstream>
#include <optional>
#include <sstream>
#include <set>
#include "club.h"
#include "utils.h"

int main(int argc, char** argv) {
    if (argc != 2)
        throw std::invalid_argument("Usage: " + std::string(argv[0]) + " <file>");

    std::ifstream file(argv[1]);

    if (!file.is_open()) {
        std::cout << std::string(argv[0]) + " is not a valid file." << std::endl;
        return 1;
    }
    int tableCount, costPerHour;
    std::string openTime, closeTime;
    std::string tableIdStr;

    file >> tableCount;
    file >> openTime >> closeTime;

    file >> costPerHour;

    std::vector<helpers::Event> events;
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        helpers::Event event;
        std::string time;
        iss >> time >> event.m_id >> event.m_name >> tableIdStr;
        if (!tableIdStr.empty()) {
            std::istringstream(tableIdStr) >> std::ws;
            if (std::isdigit(tableIdStr[0]))
                event.m_tableId = std::stoi(tableIdStr);
            else
                event.m_tableId = std::nullopt;
        } else
            event.m_tableId = std::nullopt;

        event.m_time = helpers::Time::fromString(time);
        events.push_back(event);
    }

    // for (const auto& [m_time, m_id, m_name, m_tableId] : events) {
    //     std::cout << m_time.toString() << " | " << m_id << " | " << m_name << " | ";
    //     if (m_tableId.has_value())
    //         std::cout << m_tableId.value();
    //     else
    //         std::cout << " ";
    //     std::cout << "\n";
    // }

    std::set<client::Client> clients;

    for (const auto& event : events)
        clients.insert(client::Client(event.m_time, event.m_name));

    club::Club club(tableCount, costPerHour, helpers::Time::fromString(openTime), helpers::Time::fromString(closeTime), clients);

    for (const auto &event : events)
        club.processEvent(event);

    club.closeClubAndLogEverything();

    return 0;
}

