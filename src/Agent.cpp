#include "Agent.h"
#include <iostream>

const std::string &Agent::getName() const {
    return name;
}
Agent::Agent(std::string name) : name(std::move(name)) {

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

Shipman::Shipman(const std::string &name) : Agent(name) {

}
Shipman::~Shipman() = default;
void Shipman::printType(std::ostream &stream) const {
    stream << "Midshipman";
}

Commander::Commander(const std::string &name) : Agent(name) {

}
Commander::~Commander() = default;
void Commander::printType(std::ostream &stream) const {
    stream << "Commander";
}

Admiral::Admiral(const std::string &name) : Agent(name) {

}
Admiral::~Admiral() = default;
void Admiral::printType(std::ostream &stream) const {
    stream << "Admiral";
}

AgentFactory::~AgentFactory() = default;

std::shared_ptr<Agent> ShipmanFactory::create(const std::string &name) const {
    return std::make_shared<Shipman>(name);
}
ShipmanFactory::~ShipmanFactory() = default;

std::shared_ptr<Agent> CommanderFactory::create(const std::string &name) const {
    return std::make_shared<Commander>(name);
}
CommanderFactory::~CommanderFactory() = default;

std::shared_ptr<Agent> AdmiralFactory::create(const std::string &name) const {
    return std::make_shared<Admiral>(name);
}
AdmiralFactory::~AdmiralFactory() = default;
