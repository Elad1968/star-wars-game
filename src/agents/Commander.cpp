#include "agents/Commander.hpp"

#include <iostream>

Commander::Commander(const std::string &name)
    : Agent(name) {
}
Commander::~Commander() = default;
void Commander::printType(std::ostream &stream) const {
    stream << "Commander";
}
