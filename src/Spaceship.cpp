#define _USE_MATH_DEFINES
#include "Spaceship.hpp"

#include <cmath>

Spaceship::Spaceship(
    const std::string &name, const std::shared_ptr<Agent> &agent, double speed, size_t health, const Point &location)
    : MovingObject(name, speed, location)
    , agent(agent)
    , health(health)
    , crystals(0) {
}
Spaceship::Status Spaceship::status() const {
    if (health == 0) return DEAD;
    if (getLocation() != getDestination()) return MOVING;
    if (site != nullptr && getLocation() == site->getLocation()) return DOCKED;
    return Spaceship::STOPPED;
}
void Spaceship::print(std::ostream &stream) const {
    MovingObject::print(stream);
    if (status() == DEAD) {
        stream << " is dead.";
    } else if (status() == MOVING && site != nullptr) {
        stream << " moving towards " << site->getName() << ".";
    } else if (status() == MOVING && angle != nullptr) {
        stream << " moving on course " << *angle * 180 / M_PI << ".";
    } else if (status() == DOCKED) {
        stream << " docked at " << site->getName() << ".";
    }
    if (agent != nullptr) {
        stream << " is driven by " << *agent << ".";
    }
}
void Spaceship::printType(std::ostream &stream) const {
    stream << "Spaceship";
}
size_t Spaceship::getHealth() const {
    return health;
}
size_t Spaceship::getCrystals() const {
    return crystals;
}
void Spaceship::go(const Object::Point &point) {
    if (status() == DEAD) throw std::runtime_error(getName() + " is dead and cannot operate.");
    site = nullptr;
    angle = nullptr;
    MovingObject::go(point);
}
void Spaceship::goTo(const std::shared_ptr<Site> &s) {
    site = s;
    angle = nullptr;
    MovingObject::go(site->getLocation());
}
void Spaceship::stop() {
    MovingObject::go(this->getLocation());
    site = nullptr;
    angle = nullptr;
}
void Spaceship::hurt() {
    if (health == 0) return;
    if (--health == 0) {
        die();
    }
}
void Spaceship::heal() {
    if (health >= maxHealth) return;
    ++health;
}
void Spaceship::die() {
    health = 0;
    stop();
}
void Spaceship::add() {
    if (crystals >= maxCrystals) return;
    ++crystals;
}
void Spaceship::remove() {
    if (crystals == 0) return;
    --crystals;
}
void Spaceship::course(double a) {
    a = fmod(a, 360);
    a *= M_PI / 180;
    angle = std::make_shared<double>(a);
    Point direction = {(getSpeed() + 1) * std::sin(*angle), (getSpeed() + 1) * std::cos(*angle)};
    MovingObject::go(direction + getLocation());
    site = nullptr;
}
void Spaceship::shoot(const Object::Point &point) {
    throw std::runtime_error(getName() + " is not a destroyer and cannot shoot a rocket to " + point.toString());
}
void Spaceship::transport(const std::shared_ptr<SpaceStation> &station, const std::shared_ptr<FortressStar> &star) {
    throw std::runtime_error(getName() + " is not a shuttle and cannot transport crystals from " + station->getName() +
                             " to " + star->getName());
}
void Spaceship::attack(const std::shared_ptr<Spaceship> &victim) {
    throw std::runtime_error(getName() + " is not a falcon and cannot attack " + victim->getName());
}
void Spaceship::beAttacked(const std::shared_ptr<Spaceship> &attacker) {
    throw std::runtime_error(getName() + " is not a shuttle and cannot be attacked by " + attacker->getName());
}
size_t Spaceship::crystalsToTake() const {
    return maxCrystals - crystals;
}
void Spaceship::course(double a, double speed) {
    throw std::runtime_error(getName() + " is not a falcon and cannot change angle to " + std::to_string(a) +
                             " speed to " + std::to_string(speed));
}
void Spaceship::go(const Object::Point &point, double speed) {
    throw std::invalid_argument(getName() + " is not a falcon and cannot go to " + point.toString() +
                                " change speed to " + std::to_string(speed));
}
void Spaceship::update() {
    if (angle != nullptr) {
        Point direction = {(getSpeed() + 1) * std::sin(*angle), (getSpeed() + 1) * std::cos(*angle)};
        MovingObject::go(direction + getLocation());
    }
    MovingObject::update();
}
const std::shared_ptr<Agent> &Spaceship::getAgent() const {
    return agent;
}
void Spaceship::interact(const std::shared_ptr<SpaceStation> &station) {
    std::cout << getName() + " docked at " + station->getName() << std::endl;
}
void Spaceship::interact(const std::shared_ptr<FortressStar> &star) {
    std::cout << getName() + " docked at " + star->getName() << std::endl;
}
