#pragma once

#include "Agent.hpp"

#include <memory>

class AgentFactory {
public:
    virtual ~AgentFactory();
    virtual std::shared_ptr<Agent> create(const std::string &name) const = 0;
};
