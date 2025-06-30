#pragma once

#include "Object.hpp"

#include <cstddef>

class Site : public Object {
public:
    void addCrystals(size_t count);
    [[nodiscard]] size_t removeCrystals(size_t count);
    void print(std::ostream &stream) const override;
    void printType(std::ostream &stream) const override;
    size_t getCrystals() const;
protected:
    explicit Site(const std::string &name, size_t count, const Point &location);
    virtual ~Site();
private:
    size_t crystals;
};
