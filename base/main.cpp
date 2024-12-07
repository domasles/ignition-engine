#include "include/include.hpp"

std::shared_ptr<ignition::Window> window = std::make_shared<ignition::Window>(1600, 900, "Ignition Engine");

void gameLoop(float deltaTime) {}

int main() {
    window->run(gameLoop);
    return 0;
}
