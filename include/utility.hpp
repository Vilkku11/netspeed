#pragma once

#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <nlohmann/json.hpp>

#include "constants.hpp"

std::ifstream openFile();
void skipLines(std::ifstream& file, int lines);
void sleep(int time);

std::string validate_positive_integer(const std::string& value);