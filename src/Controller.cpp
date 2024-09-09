#include "Controller.h"
#include <fstream>
#include "Model.h"

Controller::Controller() : view(), time(0) {
    Model &model = Model::get();
    creatorCommand = {
        {"shuttle", [&model](const std::vector<std::string> &args) -> void {
            if (args.size() != 6) throw std::invalid_argument("Usage: create shuttle <name> <agent_name> (<x>, <y>)");
            model.createShuttle(args[2], args[3], Controller::parseXY(args[4]), Controller::parseXY(args[5]));
        }},
        {"bomber", [&model](const std::vector<std::string> &args) -> void {
            if (args.size() != 5) throw std::invalid_argument("Usage: create bomber <name> <agent_name> <site_name>");
            model.createBomber(args[2], args[3], args[4]);
        }},
        {"destroyer", [&model](const std::vector<std::string> &args) -> void {
            if (args.size() != 6) throw std::invalid_argument("Usage: create destroyer <name> <agent_name> (<x>, <y>)");
            model.createDestroyer(args[2], args[3], Controller::parseXY(args[4]), Controller::parseXY(args[5]));
        }},
        {"falcon", [&model](const std::vector<std::string> &args) -> void {
            if (args.size() != 5) throw std::invalid_argument("Usage: create falcon <name> (<x>, <y>)");
            model.createFalcon(args[2], Controller::parseXY(args[3]), Controller::parseXY(args[4]));
        }},
        {"midshipman", [&model](const std::vector<std::string> &args) -> void {
            if (args.size() != 3) throw std::invalid_argument("Usage: create midshipman <name>");
            model.createShipman(args[2]);
        }},
        {"commander", [&model](const std::vector<std::string> &args) -> void {
            if (args.size() != 3) throw std::invalid_argument("Usage: create commander <name>");
            model.createCommander(args[2]);
        }},
        {"admiral", [&model](const std::vector<std::string> &args) -> void {
            if (args.size() != 3) throw std::invalid_argument("Usage: create admiral <name>");
            model.createAdmiral(args[2]);
        }},
    };
    modelViewCommands = {
        {"status", [&model](const std::vector<std::string> &args) -> void {
            if (args.size() != 1) throw std::invalid_argument("Usage: status");
            for (const auto &spaceship: model.getSpaceships()) {
                std::cout << *spaceship << std::endl;
            }
            for (const auto &site: model.getSites()) {
                std::cout << *site << std::endl;
            }
            for (const auto &agent: model.getAgents()) {
                std::cout << *agent << std::endl;
            }
            for (const auto &rocket: model.getRockets()) {
                std::cout << rocket << std::endl;
            }
        }},
        {"go", [this, &model](const std::vector<std::string> &args) -> void {
            if (args.size() != 1) throw std::invalid_argument("Usage: go");
            model.update();
            ++time;
        }},
        {"create", [this](const std::vector<std::string> &args) -> void {
            if (args.size() < 2) throw std::invalid_argument("Usage: create <type> <args...>");
            creatorCommand.at(args[1])(args);
        }},
        {"default", [this](const std::vector<std::string> &args) -> void {
            if (args.size() != 1) throw std::invalid_argument("Usage: default");
            view.setDefaultView();
        }},
        {"size", [this](const std::vector<std::string> &args) -> void {
            if (args.size() != 2) throw std::invalid_argument("Usage: size <size>");
            view.setSize(std::stoull(args[1]));
        }},
        {"zoom", [this](const std::vector<std::string> &args) -> void {
            if (args.size() != 2) throw std::invalid_argument("Usage: zoom <scale>");
            view.setZoom(std::stod(args[1]));
        }},
        {"pan", [this](const std::vector<std::string> &args) -> void {
            if (args.size() != 3) throw std::invalid_argument("Usage: pan (<x>, <y>)");
            view.setOrigin(parseXY(args[1]), parseXY(args[2]));
        }},
        {"show", [this](const std::vector<std::string> &args) -> void {
            if (args.size() != 1) throw std::invalid_argument("Usage: show");
            view.show();
        }},
    };
    spaceshipCommands = {
        {"course", [&model](const std::vector<std::string> &args) -> void {
            if (args.size() == 3) {
                model.course(args[0], parseSpeed(args[2]));
            } else if (args.size() == 4) {
                model.course(args[0], std::stod(args[2]), parseSpeed(args[3]));
            } else {
                throw std::invalid_argument("Usage: <spaceship_name> course <angle> [speed]");
            }
        }},
        {"position", [&model](const std::vector<std::string> &args) -> void {
            if (args.size() == 4) {
                model.position(args[0], parseXY(args[2]), parseXY(args[3]));
            } else if (args.size() == 5) {
                model.position(args[0], parseXY(args[2]), parseXY(args[3]), parseSpeed(args[4]));
            }
            if (args.size() != 4) throw std::invalid_argument("Usage: <spaceship_name> position (<x>, <y>) [speed]");
        }},
        {"destination", [&model](const std::vector<std::string> &args) -> void {
            if (args.size() != 3) throw std::invalid_argument("Usage: <spaceship_name> destination <site_name>");
            model.destination(args[0], args[2]);
        }},
        {"stop", [&model](const std::vector<std::string> &args) -> void {
            if (args.size() != 2) throw std::invalid_argument("Usage: <spaceship_name> stop");
            model.stop(args[0]);
        }},
        {"attack", [&model](const std::vector<std::string> &args) -> void {
            if (args.size() != 3) throw std::invalid_argument("Usage: <falcon_name> attack <shuttle_name>");
            model.attack(args[0], args[2]);
        }},
        {"shoot", [&model](const std::vector<std::string> &args) -> void {
            if (args.size() != 4) throw std::invalid_argument("Usage: <destroy_name> shoot (<x>, <y>)");
            model.shoot(args[0], Controller::parseXY(args[2]), Controller::parseXY(args[3]));
        }},
        {"start_supply", [&model](const std::vector<std::string> &args) -> void {
            if (args.size() != 4) throw std::invalid_argument("Usage: <shuttle_name> transport <space_station_name> <fortress_star_name>");
            model.transport(args[0], args[2], args[3]);
        }},
        {"status", [&model](const std::vector<std::string> &args) -> void {
            if (args.size() != 2) throw std::invalid_argument("Usage: <spaceship_name> status");
            std::cout << *model.findSpaceship(args[0]) << std::endl;
        }},
    };
}
void Controller::run(int argc, char **argv) {
    try {
        if (argc != 2) throw std::invalid_argument("Usage: <binary_file> <sites_file>");
        open(argv[1]);
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
        return;
    }
    run();
}
void Controller::open(const std::string &path) {
    std::ifstream file = std::ifstream(path);
    if (!file) throw std::invalid_argument("Could not open file: " + path + ".");
    size_t lineNumber = 0;
    while (file) {
        ++lineNumber;
        std::string line = Utilities::getLine(file);
        sanitize(line);
        if (line.empty()) continue;
        std::vector<std::string> args = Utilities::split(line);
        if (5 <= args.size() && args.size() <= 6) {
            std::string &name = args[1];
            double x = parseXY(args[2]);
            double y = parseXY(args[3]);
            size_t crystals;
            try {
                crystals = std::stoull(args[4]);
            } catch (const std::invalid_argument &exception) {
                throw std::invalid_argument("Number of crystals has to be a non negative integer.");
            }
            if (args.size() == 5 && args[0] == "fortress") {
                Model::get().createFortressStar(name, x, y, crystals);
                continue;
            } else if (args.size() == 6 && args[0] == "station") {
                size_t rate;
                try {
                    rate = std::stoull(args[5]);
                } catch (const std::invalid_argument &exception) {
                    throw std::invalid_argument("Crystal production rate has to be a non negative integer.");
                }
                Model::get().createSpaceStation(name, x, y, crystals, rate);
                continue;
            }
        }
        throw std::invalid_argument("Failed to parse line " + std::to_string(lineNumber) + ".");
    }
}
double Controller::parseXY(const std::string &arg) {
    try {
        return std::stod(arg) * Model::scale;
    } catch (const std::invalid_argument &exception) {
        throw std::out_of_range("Coordinates must be two numbers.");
    }
}
double Controller::parseSpeed(const std::string &arg) {
    try {
        return std::stod(arg);
    } catch (const std::invalid_argument &exception) {
        throw std::out_of_range("Speed must be a number.");
    }
}
void Controller::sanitize(std::string &line) {
    auto leftPosition = line.find('(');
    if (leftPosition != std::string::npos) {
        line.erase(leftPosition, 1);
    }
    auto rightPosition = line.find(')');
    if (rightPosition != std::string::npos) {
        line.erase(rightPosition, 1);
    }
    std::replace(line.begin(), line.end(), ',', ' ');
}
void Controller::run() {
    while (true) {
        try {
            std::cout << "Time " + std::to_string(time) + ": ";
            std::string command = Utilities::getLine(std::cin);
            sanitize(command);
            std::vector<std::string> args = Utilities::split(command);
            if (args.empty()) continue;
            if (args[0] == "exit") return;
            if (modelViewCommands.find(args[0]) != modelViewCommands.end()) {
                Commands::mapped_type function;
                try {
                    function = modelViewCommands.at(args[0]);
                } catch (const std::out_of_range &exception) {
                    throw std::out_of_range("Could not find the command " + args[0]);
                }
                function(args);
            } else if (args.size() > 1 && spaceshipCommands.find(args[1]) != spaceshipCommands.end()) {
                std::shared_ptr<Spaceship> spaceship = Model::get().findSpaceship(args[0]);
                if (spaceship->status() == Spaceship::DEAD) throw std::runtime_error(spaceship->getName() + " is dead and cannot operate.");
                Commands::mapped_type function;
                try {
                    function = spaceshipCommands.at(args[1]);
                } catch (const std::out_of_range &exception) {
                    throw std::out_of_range("Could not find the command " + args[1]);
                }
                function(args);
            } else {
                throw std::invalid_argument("Failed to parse the input. Please check it and try again.");
            }
        } catch (const std::exception &exception) {
            std::cerr << exception.what() << std::endl;
        }
    }
}
