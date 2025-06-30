#pragma once

#include "Agent.hpp"

class Admiral : public Agent {
public:
    ~Admiral() override;
    explicit Admiral(const std::string &name);
    void printType(std::ostream &stream) const override;
};
