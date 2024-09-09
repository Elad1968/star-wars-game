#ifndef HW03_CONTROLLER_H
#define HW03_CONTROLLER_H

#include <functional>
#include <map>
#include "Spaceship.h"
#include "Vector.h"
#include "View.h"

class Controller {
public:
    Controller();
    void run(int argc, char *argv[]);
private:
    using Commands = std::map<std::string, std::function<void(const std::vector<std::string>&)>>;
    static void open(const std::string &path);
    static double parseXY(const std::string &arg);
    static double parseSpeed(const std::string &arg);
    static void sanitize(std::string &line);
    void run();
    Commands modelViewCommands;
    Commands spaceshipCommands;
    Commands creatorCommand;
    View view;
    size_t time;
};

#endif //HW03_CONTROLLER_H
