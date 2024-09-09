#ifndef HW03_SPACESHIP_H
#define HW03_SPACESHIP_H

#include <memory>
#include <queue>
#include <set>
#include "Agent.h"
#include "Site.h"

class Spaceship : public MovingObject {
public:
    enum Status {STOPPED, MOVING, DOCKED, DEAD};
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
    Spaceship(const std::string &name, const std::shared_ptr<Agent> &agent, double speed, size_t health, const Point &location);
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

class Shuttle : public Spaceship {
public:
    Shuttle(const std::string &name, const std::string &agentName, const Point &location);
    ~Shuttle() override = default;
    void print(std::ostream &stream) const override;
    void printType(std::ostream &stream) const override;
    void update() override;
    void go(const Point &point) override;
    void goTo(const std::shared_ptr<Site> &site) override;
    void stop() override;
    void course(double angle) override;
    void transport(const std::shared_ptr<SpaceStation> &station, const std::shared_ptr<FortressStar> &star) override;
    void beAttacked(const std::shared_ptr<Spaceship> &attacker) override;
private:
    using Job = std::pair<std::shared_ptr<SpaceStation>, std::shared_ptr<FortressStar>>;
    void interact(const std::shared_ptr<SpaceStation> &station) override;
    void interact(const std::shared_ptr<FortressStar> &star) override;
    std::queue<Job> jobs;
    static const ShipmanFactory factory;
    static constexpr double speed = 300;
    static constexpr size_t startHealth = 10;
};

class Bomber : public Spaceship {
public:
    Bomber(const std::string &name, const std::string &agentName, const std::shared_ptr<Site> &start);
    ~Bomber() override = default;
    void print(std::ostream &stream) const override;
    void printType(std::ostream &stream) const override;
    void update() override;
private:
    const std::shared_ptr<Site> &next() const;
    static const CommanderFactory factory;
    static constexpr double speed = 1000;
    std::shared_ptr<Site> start;
    std::set<std::shared_ptr<Site>> sites;
};

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


#endif //HW03_SPACESHIP_H
