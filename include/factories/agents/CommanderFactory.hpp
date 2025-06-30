#pragma once

#include "AgentFactory.hpp"

class CommanderFactory : public AgentFactory {
public:
    ~CommanderFactory() override;
    std::shared_ptr<Agent> create(const std::string &name) const override;
};
