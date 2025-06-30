#include "sites/FortressStar.hpp"

FortressStar::FortressStar(const std::string &name, const Point &location, size_t count)
    : Site(name, count, location) {
}

void FortressStar::update() {
}

void FortressStar::print(std::ostream &stream) const {
    Site::print(stream);
}

void FortressStar::printType(std::ostream &stream) const {
    stream << "Fortress Star";
}
