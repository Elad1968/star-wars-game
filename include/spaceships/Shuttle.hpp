#pragma once

#include "Spaceship.hpp"
#include "factories/agents/ShipmanFactory.hpp"

#include <queue>

class Shuttle : public Spaceship {
public:
    Shuttle(const std::string &name, const std::string &agentName, const Point &location);
    ~Shuttle() override = default;
    void print(std::ostream &stream) const override;
    void printType(std::ostream &stream) const override;
    void update() override;
    void go(const Point &point) override;
    void goTo(const std::shared_ptr<Site> &site) override;
    void stop() override;
    void course(double angle) override;
    void transport(const std::shared_ptr<SpaceStation> &station, const std::shared_ptr<FortressStar> &star) override;
    void beAttacked(const std::shared_ptr<Spaceship> &attacker) override;
private:
    using Job = std::pair<std::shared_ptr<SpaceStation>, std::shared_ptr<FortressStar>>;
    void interact(const std::shared_ptr<SpaceStation> &station) override;
    void interact(const std::shared_ptr<FortressStar> &star) override;
    std::queue<Job> jobs;
    static const ShipmanFactory factory;
    static constexpr double speed = 300;
    static constexpr size_t startHealth = 10;
};
