#include <stdexcept>
#include <iostream>
#include <map>
#include <memory>
#include <iomanip>
#include <cstring>
#include "View.h"
#include "Object.h"
#include "Model.h"

View::View(size_t size, double zoom, double x, double y) : size(size), zoom(zoom), x(x), y(y) {
    this->setOrigin(x, y);
    this->setZoom(zoom);
    this->setSize(size);
    makeMatrix();
}
void View::setDefaultView() {
    this->setSize(defaultSize);
    this->setZoom(defaultZoom);
    this->setOrigin(defaultX, defaultY);
}
void View::setSize(size_t s) {
    if (s <= sizeBounds.first || sizeBounds.second <= s) throw std::invalid_argument("View setSize must be between " + std::to_string(sizeBounds.first) + " and " + std::to_string(sizeBounds.second) + ".");
    size = s;
    makeXAxis();
    makeYAxis();
}
void View::setZoom(double z) {
    zoom = z;
    makeXAxis();
    makeYAxis();
}
void View::setOrigin(double x0, double y0) {
    x = x0;
    y = y0;
    makeXAxis();
    makeYAxis();
}
void View::show() {
    std::cout << "Display setSize: " << size << ", scale: " << zoom << ", origin: (" << x / Model::scale << ", " << y / Model::scale << ")" << std::endl;
    makeMatrix();
    for (auto &site: Model::get().getSites()) {
        try {
            addToMap(site);
        } catch (const std::out_of_range &exception) {

        }
    }
    for (auto &spaceship: Model::get().getSpaceships()) {
        try {
            addToMap(spaceship);
        } catch (const std::out_of_range &exception) {

        }
    }
    for (auto &rocket: Model::get().getRockets()) {
        try {
            addToMap(rocket);
        } catch (const std::out_of_range &exception) {

        }
    }
    for (size_t i = 0; i < size; ++i) {
        printYAxis(size - i - 1);
        for (size_t j = 0; j < size; ++j) {
            if (map.find({size - i - 1, j}) == map.end()) {
                std::cout << space;
            } else {
                std::string toPrint = map.at({size - i - 1, j})->getName().substr(0, strlen(space));
                std::cout << toPrint;
            }
        }
        std::cout << std::endl;
    }
    printXAxis();
    std::cout << std::endl;
}

size_t View::getAxisXIndex(double x0) {
    if (x0 < xAxis[0]) throw std::out_of_range("x too small.");
    for (size_t i = 0; i < size; ++i) {
        if (x0 < xAxis[i + 1]) {
            return i;
        }
    }
    throw std::out_of_range("x too big.");
}

size_t View::getAxisYIndex(double y0) {
    if (y0 < yAxis[0]) throw std::out_of_range("y too small.");
    for (size_t i = 0; i < size; ++i) {
        if (y0 < yAxis[i + 1]) {
            return i;
        }
    }
    throw std::out_of_range("y too big.");
}

void View::addToMap(const std::shared_ptr<Object> &object) {
    size_t l = getAxisYIndex(object->getLocation()[1]);
    size_t l2 = getAxisXIndex(object->getLocation()[0]);
    std::pair<size_t, size_t> pair = {l, l2};
    if (map.find(pair) == map.end()) {
        map.insert({pair, object});
    }
}

void View::makeXAxis() {
    xAxis = {};
    for (size_t i = 0; i <= size; ++i) {
        xAxis.emplace_back(x + zoom * (double)i * Model::scale);
    }
}

void View::makeYAxis() {
    yAxis = {};
    for (size_t i = 0; i <= size; ++i) {
        yAxis.emplace_back(y + zoom * (double)i * Model::scale);
    }
}

void View::makeMatrix() {
    map = {};
}

void View::printYAxis(size_t line) {
    std::string z = std::to_string((long long) (yAxis[yAxis.size() - 1] / Model::scale));
    std::string z2 = std::to_string((long long) (yAxis[0] / Model::scale));
    size_t maxLength = std::max(z.length(), z2.length());
    if (line % spacing == (size - (size % spacing)) % spacing) {
        std::cout << std::setw((int)maxLength) << (long long)(yAxis[line] / Model::scale);
        std::cout << " ";
    } else {
        for (size_t i = 0; i <= maxLength; ++i) {
            std::cout << " ";
        }
    }

}

void View::printXAxis() {
    std::string z = std::to_string((long long) (yAxis[yAxis.size() - 1] / Model::scale));
    std::string z2 = std::to_string((long long) (yAxis[0] / Model::scale));
    size_t maxLength = std::max(z.length(), z2.length());
    std::cout << "  " << std::setw((int)maxLength) << (long long)(xAxis[0] / Model::scale);
    for (size_t i = spacing; i < size; i += spacing) {
        std::cout << std::setw((int)(spacing * strlen(space))) << (long long)(xAxis[i] / Model::scale);
    }
}


