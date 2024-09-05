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
    unsigned int update_interval;
    std::string unit;
    bool initialized;

    NetworkData();
};

void getInterfaces();
void readData(NetworkData& data);
void calculateSpeed(NetworkData& data);

class OutputHandler {
    public:
    
    virtual void returnData(const NetworkData& data) = 0;
    virtual ~OutputHandler() = default;
};

class StringOutputHandler : public OutputHandler {
    std::unique_ptr<std::ostringstream> output;
    public:
        StringOutputHandler();
        void returnData(const NetworkData& data) override;

};

class JsonOutputHandler : public OutputHandler {
    std::unique_ptr<nlohmann::json> output;
    public:
        JsonOutputHandler();
        void returnData(const NetworkData& data) override;
};