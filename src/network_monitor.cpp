#include "network_monitor.hpp"
#include "utility.hpp"

NetworkData::NetworkData() :
    rx_bytes_prev(0),
    tx_bytes_prev(0),

    rx_bytes(0),
    tx_bytes(0),

    rx_speed(0),
    tx_speed(0),

    interface(""),
    update_interval(1),
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

    if (json.empty()) {
        std::cout << "No interfaces found" << std::endl;
        return;
    }

    std::cout << "Interfaces:" << std::endl;
    for (const auto& item: json) {
        std::cout << item.get<std::string>() << std::endl;
    }

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

    if(data.update_interval != 1) {
        data.rx_speed = data.rx_speed / data.update_interval;
        data.tx_speed = data.tx_speed / data.update_interval;
    }

    if(data.rx_speed > 1000 || data.tx_speed > 1000) {
        data.rx_speed /= 1000;
        data.tx_speed /= 1000;
        data.unit = "Mbit/s";
    }else {
        data.unit = "Kbit/s";
    }
}

StringOutputHandler::StringOutputHandler()
    : output(std::make_unique<std::ostringstream>()) {}

void StringOutputHandler::returnData(const NetworkData& data) {
    output->str("");
    *output << std::fixed << std::setprecision(2) << data.rx_speed << " " <<data.unit
     << "|" << std::fixed << std::setprecision(2) << data.tx_speed << " " << data.unit;
    std::cout << output->str() << std::endl;
}

JsonOutputHandler::JsonOutputHandler()
    : output(std::make_unique<nlohmann::json>()) {
        *output = {{"D", ""}, {"U", ""}};
    }

void JsonOutputHandler::returnData(const NetworkData& data) {
    (*output)["D"] = (std::ostringstream() << std::fixed << std::setprecision(2) << data.rx_speed << " " << data.unit).str();
    (*output)["U"] = (std::ostringstream() << std::fixed << std::setprecision(2) << data.tx_speed << " " << data.unit).str();
    std::cout << (*output).dump() << std::endl;
}