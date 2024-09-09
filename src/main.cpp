#include <sstream>
#include "Controller.h"
#include "Spaceship.h"

int main(int argc, char *argv[]) {
    std::cout.precision(2);
    std::cout << std::fixed;
    Controller controller;
    controller.run(argc, argv);
    return 0;
}
