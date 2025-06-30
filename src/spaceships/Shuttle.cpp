#include "spaceships/Shuttle.hpp"

#include "Model.hpp"
#include "agents/Shipman.hpp"

Shuttle::Shuttle(const std::string &name, const std::string &agentName, const Point &location)
    : Spaceship(name, Model::get().findAgent(agentName), speed, startHealth, location)
    , jobs() {
    if (!std::dynamic_pointer_cast<Shipman>(getAgent()))
        throw std::runtime_error(getName() + " is a shuttle and can only have a midshipman as an agent");
    Model::get().takeAgent(agentName);
}
void Shuttle::update() {
    if (!jobs.empty()) {
        Job &job = jobs.front();
        std::shared_ptr<SpaceStation> &from = job.first;
        std::shared_ptr<FortressStar> &to = job.second;
        if (from != nullptr && from->getLocation() == getLocation()) {
            interact(from);
            from = nullptr;
        } else if (from != nullptr) {
            Spaceship::goTo(from);
        } else if (to->getLocation() == getLocation()) {
            interact(to);
            jobs.pop();
        } else {
            Spaceship::goTo(to);
        }
    }
    Spaceship::update();
}
void Shuttle::transport(const std::shared_ptr<SpaceStation> &station, const std::shared_ptr<FortressStar> &star) {
    if (status() == DEAD) throw std::runtime_error(getName() + " is dead and cannot operate.");
    jobs.emplace(station, star);
}
void Shuttle::interact(const std::shared_ptr<SpaceStation> &station) {
    while (crystalsToTake() != 0 && station->removeCrystals(1)) {
        add();
    }
}
void Shuttle::interact(const std::shared_ptr<FortressStar> &star) {
    while (getCrystals() != 0) {
        remove();
        star->addCrystals(1);
    }
    heal();
}
void Shuttle::stop() {
    Spaceship::stop();
    jobs = {};
}
void Shuttle::course(double angle) {
    throw std::runtime_error("Shuttle cannot change angle to " + std::to_string(angle));
}
void Shuttle::print(std::ostream &stream) const {
    Spaceship::print(stream);
    stream << " holding " << getCrystals() << " crystals with " << getHealth() << " health.";
}
void Shuttle::printType(std::ostream &stream) const {
    stream << "Shuttle";
}
void Shuttle::go(const Object::Point &point) {
    throw std::runtime_error(getName() + " is a shuttle and cannot go to " + point.toString());
}
void Shuttle::goTo(const std::shared_ptr<Site> &site) {
    throw std::runtime_error(getName() + " is a shuttle and cannot go to " + site->getName());
}
void Shuttle::beAttacked(const std::shared_ptr<Spaceship> &attacker) {
    hurt();
    if (attacker->getLocation().distance(getLocation()) <= 100 && getHealth() < attacker->getHealth() &&
        !Model::get().isBomberNearby(getLocation())) {
        attacker->heal();
        while (getCrystals() != 0) {
            remove();
            attacker->add();
        }
        stop();
    } else {
        attacker->hurt();
    }
}
