#include "Object.h"

void Object::print(std::ostream &stream) const {
    printType(stream);
    stream << " " << name << " at position " << location / 1000 << ".";
}

const std::string &Object::getName() const  {
    return name;
}

const Object::Point &Object::getLocation() const {
    return location;
}

void Object::setLocation(const Object::Point &point) {
    location = point;
}

Object::Object(std::string name, Object::Point location) :
    name(std::move(name)),
    location(std::move(location))
{

}

void Object::printType(std::ostream &stream) const {
    stream << "Object";
}

std::ostream &operator<<(std::ostream &stream, const Object &object) {
    object.print(stream);
    return stream;
}

MovingObject::MovingObject(const std::string &name, double speed, const Object::Point &location) :
    Object(name, location),
    destination(location),
    speed(speed)
{

}

void MovingObject::update() {
    if (getLocation() == destination) return;
    Point difference = destination - getLocation();
    double distance = std::min(speed, difference.norm());
    difference.normalize();
    difference *= distance;
    difference += getLocation();
    setLocation(difference);
    if ((destination - getLocation()).norm() < Point::epsilon) {
        setLocation(destination);
    }
}

const Object::Point &MovingObject::getDestination() const {
    return destination;
}

void MovingObject::go(const Object::Point &point) {
    destination = point;
}

void MovingObject::print(std::ostream &stream) const {
    Object::print(stream);
    if (getLocation() == getDestination()) {
        stream << " not moving.";
    } else {
        stream << " moving to " << destination / 1000 << " flying " << speed << " km/h.";
    }
}

void MovingObject::printType(std::ostream &stream) const {
    stream << "Moving Object";
}

void MovingObject::setSpeed(double s) {
    speed = s;
}

double MovingObject::getSpeed() const {
    return speed;
}
