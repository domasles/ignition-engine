#include "include/input.hpp"

namespace ignition {
	Input::Input(Window &window) : window(window) {
		for (int i = GLFW_KEY_UNKNOWN + 1; i <= GLFW_KEY_LAST; ++i) {
			keyState[i] = false;
			keyPressed[i] = false;
			keyReleased[i] = false;
		}
	}

	Input::~Input() {}

	void Input::update() {
		GLFWwindow* glfwWindow = window.getGLFWWindow();

		std::lock_guard<std::mutex> lock(inputMutex);

		for (int i = GLFW_KEY_UNKNOWN + 1; i <= GLFW_KEY_LAST; ++i) {
			bool currentlyPressed = glfwGetKey(glfwWindow, i) == GLFW_PRESS;

			if (currentlyPressed && !keyState[i]) keyPressed[i] = true;
			else if (!currentlyPressed && keyState[i]) keyReleased[i] = true;

			keyState[i] = currentlyPressed;
		}
	}

	bool Input::isKeyPressed(int key) const {
		std::lock_guard<std::mutex> lock(inputMutex);

		auto it = keyState.find(key);
		
		return it != keyState.end() && it->second;
	}
}
