#include "utility.hpp"

std::ifstream openFile() {
    std::ifstream file(Constants::NET_PATH);

    if(!file.is_open()) {
        std::cerr << "Failed to open \"" << Constants::NET_PATH << "\"" << std::endl;
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

void sleep(int time) {
    std::this_thread::sleep_for(std::chrono::seconds(time));
}

std::string validate_positive_integer(const std::string& value) {
    try {
        int val = std::stoi(value);
        if (val <= 0) {
            return "Value must be positive integer";
        }
        return "";
    } catch (...){
        return "Invalid input";
    }
}