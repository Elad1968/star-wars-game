#include "Agent.hpp"

#include <iostream>

const std::string &Agent::getName() const {
    return name;
}
Agent::Agent(std::string name)
    : name(std::move(name)) {
}
Agent::~Agent() = default;
void Agent::print(std::ostream &stream) const {
    printType(stream);
    stream << " " << name;
}
std::ostream &operator<<(std::ostream &stream, const Agent &agent) {
    agent.print(stream);
    return stream;
}
