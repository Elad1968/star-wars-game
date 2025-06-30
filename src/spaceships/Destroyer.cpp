#include "spaceships/Destroyer.hpp"

#include "Model.hpp"
#include "agents/Admiral.hpp"

Destroyer::Destroyer(const std::string &name, const std::string &agentName, const Object::Point &location)
    : Spaceship(name, Model::get().findAgent(agentName), speed, 1, location) {
    if (!std::dynamic_pointer_cast<Admiral>(getAgent()))
        throw std::runtime_error(getName() + " is a destroyer and can only have an admiral as an agent");
    Model::get().takeAgent(agentName);
}
void Destroyer::shoot(const Object::Point &point) {
    Model::get().addRocket({getLocation(), point});
}
void Destroyer::update() {
    Spaceship::update();
}
void Destroyer::print(std::ostream &stream) const {
    Spaceship::print(stream);
}
void Destroyer::printType(std::ostream &stream) const {
    stream << "Destroyer";
}

Destroyer::Rocket::Rocket(const Point &start, const Point &finish)
    : MovingObject("* ", 3000, start) {
    MovingObject::go(finish);
}
void Destroyer::Rocket::update() {
    MovingObject::update();
    if (getLocation() == getDestination()) {
        Model::get().explode(*this);
    }
}
void Destroyer::Rocket::print(std::ostream &stream) const {
    stream << "Rocket at position " << getLocation() << ". moving to " << getDestination() << " flying " << getSpeed()
           << " km/h.";
}
