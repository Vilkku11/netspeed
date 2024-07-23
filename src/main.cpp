#include "network_monitor.hpp"
#include "utility.hpp"

int main(int argc, char * argv[]) {

    if(argc == 1) {
        getInterfaces();
        return 0;
    }else if (argc == 2) {
        NetworkData data;
        data.interface = argv[1];
        data.interface += ":";
    }

    NetworkData data;
    data.interface = argv[1];
    data.interface += ":";
    nlohmann::json json_obj = {
        {"D", ""},
        {"U", ""}
    };


    while (true) {
        readData(data);
        calculateSpeed(data);

        json_obj["D"] = (std::ostringstream() << std::fixed << std::setprecision(2) << data.rx_speed << " " << data.unit).str();
        json_obj["U"] = (std::ostringstream() << std::fixed << std::setprecision(2) << data.tx_speed << " " << data.unit).str();

        std::cout << json_obj.dump() << std::endl;
        returnData(data);

        data.rx_bytes_prev = data.rx_bytes;
        data.tx_bytes_prev = data.tx_bytes;
        sleep(1);
    }

    return 0;
}