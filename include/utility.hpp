#pragma once

#include <fstream>
#include <iostream>
//#include <unistd.h>
#include <nlohmann/json.hpp>

void getInterfaces();
std::ifstream openFile();
void skipLines(std::ifstream& file, int lines);