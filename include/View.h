#ifndef HW03_VIEW_H
#define HW03_VIEW_H

#include <cstddef>
#include <map>
#include <memory>
#include <vector>
#include "Object.h"

class View {
public:
    explicit View(size_t size = defaultSize, double zoom = defaultZoom, double x = defaultX, double y = defaultY);
    void setDefaultView();
    void setSize(size_t s);
    void setZoom(double z);
    void setOrigin(double x, double y);
    void show();
private:
    static constexpr const char *space = ". ";
    static constexpr std::pair<size_t, size_t> sizeBounds = {6, 30};
    static constexpr size_t spacing = 3;
    static constexpr size_t defaultSize = 25;
    static constexpr double defaultZoom = 2.0;
    static constexpr double defaultX = 0;
    static constexpr double defaultY = 0;
    std::map<std::pair<size_t, size_t>, std::shared_ptr<Object>> map;
    std::vector<double> xAxis;
    std::vector<double> yAxis;
    size_t size;
    double zoom;
    double x;
    double y;
    void addToMap(const std::shared_ptr<Object> &object);
    void printXAxis();
    void printYAxis(size_t line);
    void makeMatrix();
    void makeXAxis();
    void makeYAxis();
    size_t getAxisXIndex(double x0);
    size_t getAxisYIndex(double y0);
};

#endif //HW03_VIEW_H
