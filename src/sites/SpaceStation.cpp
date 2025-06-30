#include "sites/SpaceStation.hpp"

SpaceStation::SpaceStation(const std::string &name, const Point &location, size_t count, size_t productionRate)
    : Site(name, count, location)
    , productionRate(productionRate) {
}

void SpaceStation::update() {
    addCrystals(productionRate);
}

void SpaceStation::print(std::ostream &stream) const {
    Site::print(stream);
    stream << " producing " << productionRate << " crystals.";
}

void SpaceStation::printType(std::ostream &stream) const {
    stream << "Space Station";
}
