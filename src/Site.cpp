#include "Site.h"

Site::Site(const std::string &name, size_t count, const Point &location) : Object(name, location), crystals(count) {

}

void Site::addCrystals(size_t count) {
    crystals += count;
}

size_t Site::removeCrystals(size_t count) {
    size_t temp = crystals;
    if (crystals <= count) {
        crystals = 0;
        return temp;
    } else {
        crystals -= count;
        return count;
    }
}

void Site::print(std::ostream &stream) const {
    Object::print(stream);
    stream << " containing " << crystals << " crystals.";
}

size_t Site::getCrystals() const {
    return crystals;
}

void Site::printType(std::ostream &stream) const {
    stream << "Site";
}

Site::~Site() = default;

SpaceStation::SpaceStation(const std::string &name, const Point &location, size_t count, size_t productionRate) :
    Site(name, count, location),
    productionRate(productionRate)
{

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

FortressStar::FortressStar(const std::string &name, const Point &location, size_t count) :
    Site(name, count, location)
{

}

void FortressStar::update() {

}

void FortressStar::print(std::ostream &stream) const {
    Site::print(stream);
}

void FortressStar::printType(std::ostream &stream) const {
    stream << "Fortress Star";
}
