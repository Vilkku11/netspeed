#include "utility.hpp"

const std::string NET_PATH = "/proc/net/dev";

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