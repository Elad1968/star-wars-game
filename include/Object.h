#ifndef HW03_OBJECT_H
#define HW03_OBJECT_H

#include <cfloat>
#include <utility>
#include "Vector.h"

class Object {
public:
    using Point = Vector<double, 2>;
    virtual void update() = 0;
    virtual void print(std::ostream &stream) const;
    virtual void printType(std::ostream &stream) const;
    const std::string &getName() const;
    [[nodiscard]] const Point &getLocation() const;
    void setLocation(const Point &point);
protected:
    explicit Object(std::string name, Point location);
    virtual ~Object() = default;
private:
    std::string name;
    Point location;
};

std::ostream &operator<<(std::ostream &stream, const Object &object);

class MovingObject : public Object {
public:
    explicit MovingObject(const std::string &name, double speed, const Point &location);
    ~MovingObject() override = default;
    void update() override;
    [[nodiscard]] const Point &getDestination() const;
    virtual void go(const Point &point);
    void print(std::ostream &stream) const override;
    void printType(std::ostream &stream) const override;
    void setSpeed(double s);
    double getSpeed() const;
private:
    Point destination;
    double speed;
};

#endif //HW03_OBJECT_H
