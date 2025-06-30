#pragma once

#include "Agent.hpp"

class Commander : public Agent {
public:
    ~Commander() override;
    explicit Commander(const std::string &name);
    void printType(std::ostream &stream) const override;
};
