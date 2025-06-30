#pragma once

#include "Spaceship.hpp"

class Falcon : public Spaceship {
public:
    Falcon(const std::string &name, const Point &location);
    ~Falcon() override = default;
    void attack(const std::shared_ptr<Spaceship> &spaceship) override;
    void course(double angle, double speed) override;
    void goTo(const std::shared_ptr<Site> &site) override;
    void go(const Object::Point &point, double speed) override;
    void update() override;
    void print(std::ostream &stream) const override;
    void printType(std::ostream &stream) const override;
private:
    void interact(const std::shared_ptr<SpaceStation> &station) override;
    void interact(const std::shared_ptr<FortressStar> &star) override;
    static constexpr double startHealth = 5;
    static constexpr double startSpeed = 3000;
    std::shared_ptr<Spaceship> victim;
};
