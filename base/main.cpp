#include "include/include.hpp"

ignition::Window window{1600, 900, "Ignition Engine", {0.2f, 0.3f, 0.3f, 1.0f}};

void gameLoop() {}

int main() {
	window.run(gameLoop);
	return 0;
}
