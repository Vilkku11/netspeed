#pragma once

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

void getInterfaces();
std::ifstream openFile();
void skipLines(std::ifstream& file, int lines);