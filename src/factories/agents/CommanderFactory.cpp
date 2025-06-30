#include "factories/agents/CommanderFactory.hpp"

#include "agents/Commander.hpp"

std::shared_ptr<Agent> CommanderFactory::create(const std::string &name) const {
    return std::make_shared<Commander>(name);
}
CommanderFactory::~CommanderFactory() = default;
