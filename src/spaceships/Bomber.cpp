#include "spaceships/Bomber.hpp"

#include "Model.hpp"
#include "agents/Commander.hpp"

Bomber::Bomber(const std::string &name, const std::string &agentName, const std::shared_ptr<Site> &start)
    : Spaceship(name, Model::get().findAgent(agentName), speed, 1, start->getLocation())
    , start(start)
    , sites() {
    std::copy_if(Model::get().getSites().begin(),
                 Model::get().getSites().end(),
                 std::inserter(sites, sites.begin()),
                 [&start](const std::shared_ptr<Site> &site) -> bool {
                     return site != start;
                 });
    if (!std::dynamic_pointer_cast<Commander>(getAgent()))
        throw std::runtime_error(getName() + " is a bomber and can only have a commander as an agent");
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
    for (const auto &site : sites) {
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
