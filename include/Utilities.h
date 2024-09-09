#ifndef HW01_UTILITIES_HPP
#define HW01_UTILITIES_HPP

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <memory>

namespace Utilities {
    std::vector<std::string> split(const std::string &string, char separator = ' ');
    std::string getLine(std::istream &stream);
}

#endif //HW01_UTILITIES_HPP
