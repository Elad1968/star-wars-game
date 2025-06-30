#pragma once

#include "Spaceship.hpp"
#include "factories/agents/CommanderFactory.hpp"

#include <set>

class Bomber : public Spaceship {
public:
    Bomber(const std::string &name, const std::string &agentName, const std::shared_ptr<Site> &start);
    ~Bomber() override = default;
    void print(std::ostream &stream) const override;
    void printType(std::ostream &stream) const override;
    void update() override;
private:
    const std::shared_ptr<Site> &next() const;
    static const CommanderFactory factory;
    static constexpr double speed = 1000;
    std::shared_ptr<Site> start;
    std::set<std::shared_ptr<Site>> sites;
};
