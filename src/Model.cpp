#include "Model.h"

std::shared_ptr<Model> Model::instance = nullptr;

void Model::update() {
    for (const auto &spaceship: spaceships) {
        spaceship->update();
    }
    for (const auto &site: sites) {
        site->update();
    }
    for (auto &rocket: rockets) {
        rocket->update();
    }
}

void Model::createShuttle(const std::string &name, const std::string &agentName, double x, double y) {
    try {
        findSpaceship(name);
        throw std::invalid_argument(name + " already exists.");
    } catch (const std::out_of_range &exception) {
        spaceships.emplace(std::make_shared<Shuttle>(name, agentName, Object::Point(x, y)));
    }
}

void Model::createBomber(const std::string &name, const std::string &agentName, const std::string &siteName) {
    try {
        findSpaceship(name);
        throw std::invalid_argument(name + " already exists.");
    } catch (const std::out_of_range &exception) {
        spaceships.emplace(std::make_shared<Bomber>(name, agentName, findSite(siteName)));
    }
}

void Model::createDestroyer(const std::string &name, const std::string &agentName, double x, double y) {
    try {
        findSpaceship(name);
        throw std::invalid_argument(name + " already exists.");
    } catch (const std::out_of_range &exception) {
        spaceships.emplace(std::make_shared<Destroyer>(name, agentName, Object::Point(x, y)));
    }
}

void Model::createFalcon(const std::string &name, double x, double y) {
    try {
        findSpaceship(name);
        throw std::invalid_argument(name + " already exists.");
    } catch (const std::out_of_range &exception) {
        spaceships.emplace(std::make_shared<Falcon>(name, Object::Point(x, y)));
    }
}

void Model::createShipman(const std::string &name) {
    createAgent(name, ShipmanFactory());
}

void Model::createCommander(const std::string &name) {
    createAgent(name, CommanderFactory());
}

void Model::createAdmiral(const std::string &name) {
    createAgent(name, AdmiralFactory());
}

void Model::course(const std::string &name, double angle) const {
    findSpaceship(name)->course(angle);
}

void Model::course(const std::string &name, double angle, double speed) const {
    findSpaceship(name)->course(angle, speed);
}

void Model::position(const std::string &name, double x, double y) const {
    findSpaceship(name)->go({x, y});
}

void Model::destination(const std::string &name, const std::string &destination) const {
    findSpaceship(name)->goTo(findSite(destination));
}

void Model::stop(const std::string &name) const {
    findSpaceship(name)->stop();
}

void Model::shoot(const std::string &name, double x, double y) const {
    std::shared_ptr<Spaceship> spaceship = findSpaceship(name);
    spaceship->shoot({x, y});
}

void Model::attack(const std::string &attackerName, const std::string &attackedName) const {
    std::shared_ptr<Spaceship> attackerSpaceship = findSpaceship(attackerName);
    std::shared_ptr<Spaceship> attackedSpaceship = findSpaceship(attackedName);
    attackerSpaceship->attack(attackedSpaceship);
}

void Model::createFortressStar(const std::string &name, double x, double y, size_t count) {
    try {
        findSite(name);
        throw std::invalid_argument(name + " already exists.");
    } catch (const std::out_of_range &exception) {
        sites.emplace(std::make_shared<FortressStar>(name, Object::Point(x, y), count));
    }
}

void Model::createSpaceStation(const std::string &name, double x, double y, size_t count, size_t productionRate) {
    try {
        findSite(name);
        throw std::invalid_argument(name + " already exists.");
    } catch (const std::out_of_range &exception) {
        sites.emplace(std::make_shared<SpaceStation>(name, Object::Point(x, y), count, productionRate));
    }
}

Model &Model::get() {
    if (instance == nullptr) {
        instance = std::shared_ptr<Model>(new Model());
    }
    return *instance;
}

void Model::transport(const std::string &spaceshipName, const std::string &stationName, const std::string &starName) const {
    std::shared_ptr<Spaceship> spaceship = findSpaceship(spaceshipName);
    std::shared_ptr<Site> fromSite = findSite(stationName);
    std::shared_ptr<Site> toSite = findSite(starName);
    std::shared_ptr<SpaceStation> station = std::dynamic_pointer_cast<SpaceStation>(fromSite);
    std::shared_ptr<FortressStar> star = std::dynamic_pointer_cast<FortressStar>(toSite);
    if (station == nullptr) throw std::invalid_argument(stationName + " is not a space station.");
    if (star == nullptr) throw std::invalid_argument(starName + " is not a star.");
    spaceship->transport(station, star);
}

Model::Model() :
    spaceships(),
    sites(),
    agents(),
    rockets()
{
    createFortressStar("DS", 40 * scale, 10 * scale, 100000);
}

const std::shared_ptr<Spaceship> &Model::findSpaceship(const std::string &name) const {
    auto iterator = std::find_if(spaceships.begin(), spaceships.end(), [&name](const std::shared_ptr<Spaceship> &spaceship) -> bool {
        if (spaceship->getName() == name) return true;
        return false;
    });
    if (iterator != spaceships.end()) return *iterator;
    throw std::out_of_range("Did not find a spaceship named " + name + ".");
}

const std::shared_ptr<Site> &Model::findSite(const std::string &name) const {
    auto iterator = std::find_if(sites.begin(), sites.end(), [&name](const decltype(sites)::value_type &pair) -> bool {
        if (pair->getName() == name) return true;
        return false;
    });
    if (iterator != sites.end()) return *iterator;
    throw std::out_of_range("Did not find a site named " + name + ".");
}

void Model::explode(const Destroyer::Rocket &rocket) {
    for (const std::shared_ptr<Spaceship> &spaceship: spaceships) {
        if (spaceship->getLocation() == rocket.getLocation() && std::dynamic_pointer_cast<Falcon>(spaceship) != nullptr) {
            spaceship->die();
        }
    }
    auto it = std::remove_if(rockets.begin(), rockets.end(), [&rocket](const decltype(rockets)::value_type &rocket2) -> bool {
        return &rocket == &*rocket2;
    });
    rockets.erase(it, rockets.end());
}

void Model::addRocket(const Destroyer::Rocket &rocket) {
    rockets.push_back(std::make_shared<Destroyer::Rocket>(rocket));
}

const std::shared_ptr<Agent> &Model::findAgent(const std::string &name) const {
    auto iterator = std::find_if(agents.begin(), agents.end(), [&name](const decltype(agents)::value_type &pair) -> bool {
        if (pair->getName() == name) return true;
        return false;
    });
    if (iterator != agents.end()) return *iterator;
    auto it = std::find_if(spaceships.begin(), spaceships.end(), [&name](const decltype(spaceships)::value_type &spaceship) -> bool {
        if (spaceship->getAgent() == nullptr) return false;
        return spaceship->getAgent()->getName() == name;
    });
    if (it != spaceships.end()) return (*it)->getAgent();
    throw std::out_of_range("Did not find an agent named " + name + ".");
}

void Model::position(const std::string &name, double x, double y, double speed) const {
    findSpaceship(name)->go({x, y}, speed);
}

void Model::takeAgent(const std::string &name) {
    auto it = std::find_if(agents.begin(), agents.end(), [&name](const decltype(agents)::value_type &agent) -> bool {
        return agent->getName() == name;
    });
    if (it == agents.end()) throw std::out_of_range("The agent is already assigned");
    agents.erase(findAgent(name));
}

const std::set<std::shared_ptr<Spaceship>, Model::ObjectComparator> &Model::getSpaceships() const {
    return spaceships;
}

const std::set<std::shared_ptr<Site>, Model::ObjectComparator> &Model::getSites() const {
    return sites;
}

const std::set<std::shared_ptr<Agent>, Model::AgentComparator> &Model::getAgents() const {
    return agents;
}

const std::vector<std::shared_ptr<Destroyer::Rocket>> &Model::getRockets() const {
    return rockets;
}

void Model::createAgent(const std::string &name, const AgentFactory &factory) {
    try {
        findAgent(name);
        throw std::invalid_argument(name + " already exists.");
    } catch (const std::out_of_range &exception) {
        agents.emplace(factory.create(name));
    }
}

bool Model::isBomberNearby(const Object::Point &point) {
    return std::any_of(spaceships.begin(), spaceships.end(), [&point](const decltype(spaceships)::value_type &spaceship) -> bool {
        return point.distance(spaceship->getLocation()) <= 250 && std::dynamic_pointer_cast<Bomber>(spaceship);
    });
}
