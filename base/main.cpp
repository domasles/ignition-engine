#include "include/include.hpp"

std::shared_ptr<ignition::Window> window = std::make_shared<ignition::Window>(1600, 900, true, "Ignition Engine", glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

void gameLoop(float deltaTime) {}

int main() {
    window->run(gameLoop);
    return 0;
}
