#include "network_monitor.hpp"

const std::string NET_PATH = "/proc/net/dev";

NetworkData::NetworkData() :
    rx_bytes_prev(0),
    tx_bytes_prev(0),

    rx_bytes(0),
    tx_bytes(0),

    rx_speed(0),
    tx_speed(0),

    interface(""),
    unit(""),
    initialized(false){}


void getInterfaces() {
    std::ifstream file = openFile();

    std::string line;
    std::string interface;
    nlohmann::json json;

    skipLines(file, 2);

    while(std::getline(file, line)) {
        std::istringstream iss(line); 
        iss >> interface;
        json.push_back(interface);
        
    }
    std::cout << json.dump() << std::endl;
    return;
}

void readData(NetworkData& data) {
    std::ifstream file = openFile();

    std::string line;
    std::string iface;

    skipLines(file, 2);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> iface;
        if(iface == data.interface) {
            iss >> data.rx_bytes;

            for (int i = 0; i < 7; i++) {
                // Using dummy for now
                iss >> line;
            }
            iss >> data.tx_bytes;
            return;
        }
    }
    std::cerr << "Could not find interface " << data.interface << std::endl;
    exit(EXIT_FAILURE);
}

void calculateSpeed(NetworkData& data) {

    if(!data.initialized) {
        data.rx_bytes_prev = data.rx_bytes;
        data.tx_bytes_prev = data.tx_bytes;
        data.initialized = true;
    }

    data.rx_speed = (data.rx_bytes - data.rx_bytes_prev)* 8 / 1000;
    data.tx_speed = (data.tx_bytes - data.tx_bytes_prev)*8 / 1000;

    if(data.rx_speed > 1000 || data.tx_speed > 1000) {
        data.rx_speed /= 1000;
        data.tx_speed /= 1000;
        data.unit = "Mbit/s";
    }else {
        data.unit = "Kbit/s";
    }
}

std::ifstream openFile() {
    std::ifstream file(NET_PATH);

    if(!file.is_open()) {
        std::cerr << "Failed to open " << NET_PATH << std::endl;
        exit(EXIT_FAILURE);
    }
    return file;
}

void skipLines(std::ifstream& file, int lines) {
    for (int i = 0; i < lines; i++) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return;
}