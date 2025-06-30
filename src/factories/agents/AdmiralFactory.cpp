#include "factories/agents/AdmiralFactory.hpp"

#include "agents/Admiral.hpp"

std::shared_ptr<Agent> AdmiralFactory::create(const std::string &name) const {
    return std::make_shared<Admiral>(name);
}
AdmiralFactory::~AdmiralFactory() = default;
