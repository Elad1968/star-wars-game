#pragma once

#include "Site.hpp"

class FortressStar : public Site {
public:
    explicit FortressStar(const std::string &name, const Point &location, size_t count);
    void update() override;
    void print(std::ostream &stream) const override;
    void printType(std::ostream &stream) const override;
};
