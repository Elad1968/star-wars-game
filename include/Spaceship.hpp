#pragma once

#include "Agent.hpp"
#include "Site.hpp"
#include "sites/FortressStar.hpp"
#include "sites/SpaceStation.hpp"

#include <memory>

class Spaceship : public MovingObject {
public:
    enum Status { STOPPED, MOVING, DOCKED, DEAD };
    virtual Status status() const;
    void print(std::ostream &stream) const override;
    void printType(std::ostream &stream) const override;
    size_t getHealth() const;
    size_t getCrystals() const;
    const std::shared_ptr<Agent> &getAgent() const;
    void update() override;
    void go(const Point &point) override;
    virtual void go(const Point &point, double speed);
    virtual void goTo(const std::shared_ptr<Site> &site);
    virtual void stop();
    virtual void hurt();
    virtual void heal();
    virtual void die();
    virtual void add();
    virtual void remove();
    virtual void course(double angle);
    virtual void course(double angle, double speed);
    virtual void shoot(const Point &point);
    virtual void transport(const std::shared_ptr<SpaceStation> &station, const std::shared_ptr<FortressStar> &star);
    virtual void attack(const std::shared_ptr<Spaceship> &victim);
    virtual void beAttacked(const std::shared_ptr<Spaceship> &attacker);
protected:
    Spaceship(const std::string &name,
              const std::shared_ptr<Agent> &agent,
              double speed,
              size_t health,
              const Point &location);
    ~Spaceship() override = default;
    virtual void interact(const std::shared_ptr<SpaceStation> &station);
    virtual void interact(const std::shared_ptr<FortressStar> &star);
    size_t crystalsToTake() const;
private:
    static constexpr size_t maxHealth = 20;
    static constexpr size_t maxCrystals = 5;
    std::shared_ptr<Agent> agent;
    std::shared_ptr<Site> site;
    std::shared_ptr<double> angle;
    size_t health;
    size_t crystals;
};
