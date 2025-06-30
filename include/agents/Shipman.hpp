#pragma once

#include "Agent.hpp"

class Shipman : public Agent {
public:
    ~Shipman() override;
    explicit Shipman(const std::string &name);
    void printType(std::ostream &stream) const override;
};
