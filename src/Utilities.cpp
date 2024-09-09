#include "Utilities.h"

std::vector<std::string> Utilities::split(const std::string &string, char separator) {
    std::vector<std::string> strings = {""};
    size_t index = 0;
    bool wasSeparator = false;
    for (char c: string) {
        if (c == separator && !wasSeparator) {
            wasSeparator = true;
            strings.emplace_back("");
            strings[++index] = "";
        } else if (c != separator) {
            wasSeparator = false;
            strings[index] += c;
        }
    }
    if (strings[strings.size() - 1].empty()) {
        strings.erase(--strings.end());
    }
    return strings;
}
std::string Utilities::getLine(std::istream &stream) {
    std::string line;
    std::getline(stream, line);
    return line;
}