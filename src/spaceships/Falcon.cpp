#include "spaceships/Falcon.hpp"

#include "Model.hpp"
#include "spaceships/Shuttle.hpp"

void Falcon::interact(const std::shared_ptr<SpaceStation> &station) {
    throw std::runtime_error("Falcon cannot interact with the station " + station->getName());
}
void Falcon::interact(const std::shared_ptr<FortressStar> &star) {
    throw std::runtime_error("Falcon cannot interact with the star " + star->getName());
}
Falcon::Falcon(const std::string &name, const Object::Point &location)
    : Spaceship(name, nullptr, startSpeed, startHealth, location)
    , victim(nullptr) {
}
void Falcon::update() {
    if (victim != nullptr) {
        Spaceship::go(victim->getLocation());
    }
    Spaceship::update();
    if (victim != nullptr) {
        victim->beAttacked(Model::get().findSpaceship(getName()));
        victim = nullptr;
        stop();
    }
}
void Falcon::print(std::ostream &stream) const {
    Spaceship::print(stream);
    stream << " holding " << getCrystals() << " crystals with " << getHealth() << " health.";
}
void Falcon::printType(std::ostream &stream) const {
    stream << "Falcon";
}
void Falcon::attack(const std::shared_ptr<Spaceship> &spaceship) {
    if (std::dynamic_pointer_cast<Shuttle>(spaceship) == nullptr)
        throw std::runtime_error(spaceship->getName() + " is not a shuttle and cannot be attacked.");
    victim = spaceship;
}
void Falcon::course(double angle, double speed) {
    Spaceship::course(angle);
    setSpeed(speed);
}
void Falcon::go(const Object::Point &point, double speed) {
    Spaceship::go(point);
    setSpeed(speed);
}
void Falcon::goTo(const std::shared_ptr<Site> &site) {
    throw std::runtime_error(getName() + " is a falcon and cannot dock at " + site->getName());
}
