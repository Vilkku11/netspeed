#include "network_monitor.hpp"

NetworkData::NetworkData() :
    rx_bytes_prev(0),
    tx_bytes_prev(0),

    rx_bytes(0),
    tx_bytes(0),

    rx_speed(0),
    tx_speed(0),

    interface(""),
    unit(""),

    rx_speed_str(""),
    tx_speed_str("") {}


void getInterfaces() {
    std::ifstream file(NET_PATH);

    if (!file.is_open()) {
        std::cerr << "Failed to open " << NET_PATH << std::endl;
    }

    std::string line;
    std::string interface;
    nlohmann::json json;

    std::getline(file, line);
    std::getline(file, line);

    while(std::getline(file, line)) {
        std::istringstream iss(line); 
        iss >> interface;
        json.push_back(interface);
        
    }
    std::cout << json.dump() << std::endl;
    return;
}

void readData(NetworkData* data) {
    return;
}
