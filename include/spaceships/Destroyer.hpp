#pragma once

#include "Spaceship.hpp"
#include "factories/agents/AdmiralFactory.hpp"

#include <vector>

class Destroyer : public Spaceship {
public:
    class Rocket : public MovingObject {
    public:
        Rocket(const Point &start, const Point &finish);
        ~Rocket() override = default;
        void print(std::ostream &stream) const override;
        void update() override;
    };
    Destroyer(const std::string &name, const std::string &agentName, const Point &location);
    ~Destroyer() override = default;
    void print(std::ostream &stream) const override;
    void printType(std::ostream &stream) const override;
    void update() override;
    void shoot(const Point &point) override;
private:
    static const AdmiralFactory factory;
    static constexpr double speed = 2000;
    std::vector<Rocket> rockets;
};
