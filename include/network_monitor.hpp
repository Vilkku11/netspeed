#pragma once

#include <fstream>
#include <iostream>
#include <unistd.h>
#include <nlohmann/json.hpp>


struct NetworkData {
    long long rx_bytes_prev;
    long long tx_bytes_prev;

    long long rx_bytes;
    long long tx_bytes;

    double rx_speed;
    double tx_speed;

    std::string interface;
    std::string unit;
    bool initialized;

    NetworkData();
};

void getInterfaces();
void readData(NetworkData& data);
void calculateSpeed(NetworkData& data);
std::ifstream openFile();
void skipLines(std::ifstream& file, int lines);