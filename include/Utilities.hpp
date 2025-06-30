#pragma once

#include <iostream>
#include <vector>

namespace Utilities {
    std::vector<std::string> split(const std::string &string, char separator = ' ');
    std::string getLine(std::istream &stream);
}
