#pragma once

#include "AgentFactory.hpp"

class ShipmanFactory : public AgentFactory {
public:
    ~ShipmanFactory() override;
    std::shared_ptr<Agent> create(const std::string &name) const override;
};
