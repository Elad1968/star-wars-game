#define _USE_MATH_DEFINES
#include <cmath>
#include "Model.h"
#include "Spaceship.h"

Spaceship::Spaceship(const std::string &name, const std::shared_ptr<Agent> &agent, double speed, size_t health, const Point &location) :
    MovingObject(name, speed, location),
    agent(agent),
    health(health),
    crystals(0)
{

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
    throw std::runtime_error(getName() + " is not a shuttle and cannot transport crystals from " + station->getName() + " to " + star->getName());
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
    throw std::runtime_error(getName() + " is not a falcon and cannot change angle to " + std::to_string(a) + " speed to " + std::to_string(speed));
}
void Spaceship::go(const Object::Point &point, double speed) {
    throw std::invalid_argument(getName() + " is not a falcon and cannot go to " + point.toString() + " change speed to " + std::to_string(speed));
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

Shuttle::Shuttle(const std::string &name, const std::string &agentName, const Point &location) :
    Spaceship(name, Model::get().findAgent(agentName), speed, startHealth, location),
    jobs()
{
    if (!std::dynamic_pointer_cast<Shipman>(getAgent())) throw std::runtime_error(getName() + " is a shuttle and can only have a midshipman as an agent");
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
    if (attacker->getLocation().distance(getLocation()) <= 100 && getHealth() < attacker->getHealth() && !Model::get().isBomberNearby(getLocation())) {
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

Bomber::Bomber(const std::string &name, const std::string &agentName, const std::shared_ptr<Site> &start) :
    Spaceship(name, Model::get().findAgent(agentName), speed, 1, start->getLocation()),
    start(start),
    sites()
{
    std::copy_if(Model::get().getSites().begin(), Model::get().getSites().end(), std::inserter(sites, sites.begin()), [&start](const std::shared_ptr<Site> &site) -> bool {
        return site != start;
    });
    if (!std::dynamic_pointer_cast<Commander>(getAgent())) throw std::runtime_error(getName() + " is a bomber and can only have a commander as an agent");
    Model::get().takeAgent(agentName);
}
void Bomber::print(std::ostream &stream) const {
    Spaceship::print(stream);
}
void Bomber::printType(std::ostream &stream) const {
    stream << "Bomber";
}
void Bomber::update() {
    Spaceship::update();
    for (const auto &site: sites) {
        if (site->getLocation() == getLocation()) {
            sites.erase(site);
            goTo(next());
            return;
        }
    }
    if (start->getLocation() == getLocation()) {
        goTo(next());
    }
}
const std::shared_ptr<Site> &Bomber::next() const {
    if (sites.empty()) return start;
    auto closest = sites.begin();
    for (auto site = sites.begin(); site != sites.end(); ++site) {
        if (((*site)->getLocation() - getLocation()).norm() < ((*closest)->getLocation() - getLocation()).norm()) {
            closest = site;
        }
    }
    return *closest;
}

Destroyer::Destroyer(const std::string &name, const std::string &agentName, const Object::Point &location) :
    Spaceship(name, Model::get().findAgent(agentName), speed, 1, location)
{
    if (!std::dynamic_pointer_cast<Admiral>(getAgent())) throw std::runtime_error(getName() + " is a destroyer and can only have an admiral as an agent");
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

Destroyer::Rocket::Rocket(const Point &start, const Point &finish) : MovingObject("* ", 3000, start) {
    MovingObject::go(finish);
}
void Destroyer::Rocket::update() {
    MovingObject::update();
    if (getLocation() == getDestination()) {
        Model::get().explode(*this);
    }
}
void Destroyer::Rocket::print(std::ostream &stream) const {
    stream << "Rocket at position " << getLocation() << ". moving to " << getDestination() << " flying " << getSpeed() << " km/h.";
}

void Falcon::interact(const std::shared_ptr<SpaceStation> &station) {
    throw std::runtime_error("Falcon cannot interact with the station " + station->getName());
}
void Falcon::interact(const std::shared_ptr<FortressStar> &star) {
    throw std::runtime_error("Falcon cannot interact with the star " + star->getName());
}
Falcon::Falcon(const std::string &name, const Object::Point &location) :
    Spaceship(name, nullptr, startSpeed, startHealth, location),
    victim(nullptr)
{

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
    if (std::dynamic_pointer_cast<Shuttle>(spaceship) == nullptr) throw std::runtime_error(spaceship->getName() + " is not a shuttle and cannot be attacked.");
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
