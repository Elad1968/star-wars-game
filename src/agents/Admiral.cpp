#include "agents/Admiral.hpp"

#include <iostream>

Admiral::Admiral(const std::string &name)
    : Agent(name) {
}
Admiral::~Admiral() = default;
void Admiral::printType(std::ostream &stream) const {
    stream << "Admiral";
}
