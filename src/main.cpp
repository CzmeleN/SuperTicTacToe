#include "../engine/include/engine.hpp"
#include <iostream>

int main() {
    try {
        Engine engine(800, 600);
        engine.loadStructure("resources/game_structure.json", "src/buttons.cpp");
        engine.run();
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
