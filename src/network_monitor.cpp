#include "network_monitor.hpp"
#include "utility.hpp"

/*#include <fstream>
#include <iostream>
#include <unistd.h>
#include <nlohmann/json.hpp>
*/

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

        if (!interface.empty() && interface.back() == ':') {
            interface.pop_back();
        }

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

void returnData(NetworkData& data, const std::unique_ptr<std::ostringstream>& output_string) {

    output_string->str("");
    *output_string << std::fixed << std::setprecision(2) << data.rx_speed << " " <<data.unit
     << "|" << std::fixed << std::setprecision(2) << data.tx_speed << " " << data.unit;
    std::cout << output_string->str() << std::endl;
    return;
}

void returnDataJson(NetworkData& data, const std::unique_ptr<nlohmann::json>& output_json) {
    (*output_json)["D"] = (std::ostringstream() << std::fixed << std::setprecision(2) << data.rx_speed << " " << data.unit).str();
    (*output_json)["U"] = (std::ostringstream() << std::fixed << std::setprecision(2) << data.tx_speed << " " << data.unit).str();
    std::cout << (*output_json).dump() << std::endl;
}