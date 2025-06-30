#include "Site.hpp"

Site::Site(const std::string &name, size_t count, const Point &location)
    : Object(name, location)
    , crystals(count) {
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
