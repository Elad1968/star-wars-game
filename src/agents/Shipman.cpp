#include "agents/Shipman.hpp"

#include <iostream>

Shipman::Shipman(const std::string &name)
    : Agent(name) {
}
Shipman::~Shipman() = default;
void Shipman::printType(std::ostream &stream) const {
    stream << "Midshipman";
}
