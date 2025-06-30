#pragma once

#include "Site.hpp"

class SpaceStation : public Site {
public:
    explicit SpaceStation(const std::string &name, const Point &location, size_t count, size_t productionRate);
    void update() override;
    void print(std::ostream &stream) const override;
    void printType(std::ostream &stream) const override;
private:
    size_t productionRate;
};
