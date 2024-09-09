#ifndef HW03_SITE_H
#define HW03_SITE_H

#include <cstddef>
#include <memory>
#include "Object.h"
#include "Utilities.h"

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

class SpaceStation : public Site {
public:
    explicit SpaceStation(const std::string &name, const Point &location, size_t count, size_t productionRate);
    void update() override;
    void print(std::ostream &stream) const override;
    void printType(std::ostream &stream) const override;
private:
    size_t productionRate;
};

class FortressStar : public Site {
public:
    explicit FortressStar(const std::string &name, const Point &location, size_t count);
    void update() override;
    void print(std::ostream &stream) const override;
    void printType(std::ostream &stream) const override;
};

#endif //HW03_SITE_H
