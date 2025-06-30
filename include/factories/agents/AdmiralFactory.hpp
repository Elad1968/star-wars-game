#pragma once

#include "AgentFactory.hpp"

class AdmiralFactory : public AgentFactory {
public:
    ~AdmiralFactory() override;
    std::shared_ptr<Agent> create(const std::string &name) const override;
};
