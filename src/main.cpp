#include "network_monitor.hpp"
#include "utility.hpp"

#include "CLI/CLI.hpp"

int main(int argc, char * argv[]) {

    CLI::App app{"Netspeed"};

    bool list_interfaces = false;
    std::string output_format;
    std::string interface;
    int update_interval = 1;

    app.add_flag("-l,--list", list_interfaces, "List network interfaces");
    
    app.add_option("-f,--format", output_format, "Output format (string or JSON)")
    ->default_val("string")
    ->check(CLI::IsMember({"json", "string"}));

    app.add_option("-i,--interface", interface, "Network interface to monitor");

    app.add_option("-t, --timeout", update_interval, "Update interval in seconds")
    ->check(validate_positive_integer);

    CLI11_PARSE(app, argc, argv);

    if(argc == 1) {
     std::cout << app.help() << std::endl;
     return 0; 
    }

    if(list_interfaces) {
        getInterfaces();
        return 0;
    }

    //Init data
    NetworkData data;
    data.interface = interface;
    data.update_interval = update_interval;
    data.interface += ":";
    std::unique_ptr<std::ostringstream> output_string;
    std::unique_ptr<nlohmann::json> output_json;


    if(output_format == "string") {
        output_string = std::make_unique<std::ostringstream>();
    }else {
        output_json = std::make_unique<nlohmann::json>(nlohmann::json{{"D", ""}, {"U", ""}});
    }

    while (true) {
        readData(data);
        calculateSpeed(data);

        if(output_format == "string") {
            returnData(data, output_string);
        }else {
            returnDataJson(data, output_json);
        }

        data.rx_bytes_prev = data.rx_bytes;
        data.tx_bytes_prev = data.tx_bytes;
        sleep(update_interval);
    }

    return 0;
}