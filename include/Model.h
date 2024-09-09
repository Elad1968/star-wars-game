#ifndef HW03_MODEL_H
#define HW03_MODEL_H

#include <memory>
#include <vector>
#include <set>
#include <map>
#include "Spaceship.h"
#include "Site.h"

class Model {
private:
    class ObjectComparator {
    public:
        bool operator()(const std::shared_ptr<Object> &a, const std::shared_ptr<Object> &b) {
            return a->getName() < b->getName();
        }
    };
    class AgentComparator {
    public:
        bool operator()(const std::shared_ptr<Agent> &a, const std::shared_ptr<Agent> &b) {
            return a->getName() < b->getName();
        }
    };
public:
    static constexpr double scale = 1000;
    static Model &get();
    Model(const Model &model) = delete;
    Model &operator=(const Model &model) = delete;
    const std::set<std::shared_ptr<Spaceship>, ObjectComparator> &getSpaceships() const;
    const std::set<std::shared_ptr<Site>, ObjectComparator> &getSites() const;
    const std::set<std::shared_ptr<Agent>, AgentComparator> &getAgents() const;
    const std::vector<std::shared_ptr<Destroyer::Rocket>> &getRockets() const;
    void update();
    void createShuttle(const std::string &name, const std::string &agentName, double x, double y);
    void createBomber(const std::string &name, const std::string &agentName, const std::string &siteName);
    void createDestroyer(const std::string &name, const std::string &agentName, double x, double y);
    void createFalcon(const std::string &name, double x, double y);
    void createAgent(const std::string &name, const AgentFactory &factory);
    void createShipman(const std::string &name);
    void createCommander(const std::string &name);
    void createAdmiral(const std::string &name);
    void createFortressStar(const std::string &name, double x, double y, size_t count);
    void createSpaceStation(const std::string &name, double x, double y, size_t count, size_t productionRate);
    void course(const std::string &name, double angle) const;
    void course(const std::string &name, double angle, double speed) const;
    void position(const std::string &name, double x, double y) const;
    void position(const std::string &name, double x, double y, double speed) const;
    void destination(const std::string &name, const std::string &destination) const;
    void stop(const std::string &name) const;
    void attack(const std::string &attackerName, const std::string &attackedName) const;
    void shoot(const std::string &name, double x, double y) const;
    void transport(const std::string &spaceshipName, const std::string &stationName, const std::string &starName) const;
    const std::shared_ptr<Spaceship> &findSpaceship(const std::string &name) const;
    const std::shared_ptr<Site> &findSite(const std::string &name) const;
    const std::shared_ptr<Agent> &findAgent(const std::string &name) const;
    void explode(const Destroyer::Rocket &rocket);
    void addRocket(const Destroyer::Rocket &rocket);
    void takeAgent(const std::string &name);
    bool isBomberNearby(const Object::Point &point);
private:
    Model();
    static std::shared_ptr<Model> instance;
    std::set<std::shared_ptr<Spaceship>, ObjectComparator> spaceships;
    std::set<std::shared_ptr<Site>, ObjectComparator> sites;
    std::set<std::shared_ptr<Agent>, AgentComparator> agents;
    std::vector<std::shared_ptr<Destroyer::Rocket>> rockets;
};

#endif //HW03_MODEL_H
