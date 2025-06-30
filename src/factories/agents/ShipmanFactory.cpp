#include "factories/agents/ShipmanFactory.hpp"

#include "agents/Shipman.hpp"

std::shared_ptr<Agent> ShipmanFactory::create(const std::string &name) const {
    return std::make_shared<Shipman>(name);
}
ShipmanFactory::~ShipmanFactory() = default;
