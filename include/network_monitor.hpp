#pragma once

#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>

struct NetworkData {
    unsigned long long rx_bytes_prev;
    unsigned long long tx_bytes_prev;

    unsigned long long rx_bytes;
    unsigned long long tx_bytes;

    double rx_speed;
    double tx_speed;

    std::string interface;
    std::string unit;
    bool initialized;

    NetworkData();
};


void readData(NetworkData& data);
void calculateSpeed(NetworkData& data);
void returnData(NetworkData& data, const std::unique_ptr<std::ostringstream>& output_string);
void returnDataJson(NetworkData& data, const std::unique_ptr<nlohmann::json>& output_json);

