#pragma once

#include "View.hpp"

#include <functional>
#include <map>

class Controller {
public:
    Controller();
    void run(int argc, char *argv[]);
private:
    using Commands = std::map<std::string, std::function<void(const std::vector<std::string> &)>>;
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
