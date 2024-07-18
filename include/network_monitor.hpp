#pragma once

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <nlohmann/json.hpp>

extern const std::string NET_PATH = "/proc/net/dev";

struct NetworkData {
    long long rx_bytes_prev;
    long long tx_bytes_prev;

    long long rx_bytes;
    long long tx_bytes;

    double rx_speed;
    double tx_speed;

    std::string interface;
    std::string unit;

    // CHECK IF NEEDED
    std::ostringstream rx_speed_str;
    std::ostringstream tx_speed_str;

    NetworkData();
};

void getInterfaces();
void readData(NetworkData* data);