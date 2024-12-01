#include "include/input.hpp"

namespace ignition {
    Input::Input(const std::shared_ptr<Window> &window) : window(window) {}

    Input::~Input() {}

    void Input::update() {
        GLFWwindow *glfwWindow = window->getGLFWWindow();

        {
            std::lock_guard<std::mutex> lock(inputMutex);

            prevKeyState = keyState;

            for (int i = 0; i < KeyCount; ++i) keyState[i] = glfwGetKey(glfwWindow, i) == GLFW_PRESS;
        }
    }

    bool Input::isKeyUp(int key) const {
        std::lock_guard<std::mutex> lock(inputMutex);
        return key >= 0 && key < KeyCount && !keyState[key];
    }

    bool Input::isKeyDown(int key) const {
        std::lock_guard<std::mutex> lock(inputMutex);
        return key >= 0 && key < KeyCount && keyState[key];
    }

    bool Input::wasKeyPressed(int key) const {
        std::lock_guard<std::mutex> lock(inputMutex);
        return key >= 0 && key < KeyCount && keyState[key] && !prevKeyState[key];
    }

    bool Input::wasKeyReleased(int key) const {
        std::lock_guard<std::mutex> lock(inputMutex);
        return key >= 0 && key < KeyCount && !keyState[key] && prevKeyState[key];
    }
}
