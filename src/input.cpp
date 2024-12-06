#include "include/input.hpp"

namespace ignition {
    Input::Input(const std::shared_ptr<Window> &window) : window(window) {}

    void Input::update() {
        GLFWwindow *glfwWindow = window->getGLFWWindow();

        {
            std::lock_guard<std::mutex> lock(inputMutex);

            prevKeyState = std::move(keyState);

            for (const auto &key : trackedKeys) keyState[key] = glfwGetKey(glfwWindow, key) == GLFW_PRESS;
        }
    }

    bool Input::isKeyUp(int key) const {
        if (key < 0 || key >= keyCount) return false;
        return !keyState[key];
    }

    bool Input::isKeyDown(int key) const {
        if (key < 0 || key >= keyCount) return false;
        return keyState[key];
    }

    bool Input::wasKeyPressed(int key) const {
        if (key < 0 || key >= keyCount) return false;
        return keyState[key] && !prevKeyState[key];
    }

    bool Input::wasKeyReleased(int key) const {
        if (key < 0 || key >= keyCount) return false;
        return !keyState[key] && prevKeyState[key];
    }

    void Input::trackKey(int key) {
        std::lock_guard<std::mutex> lock(inputMutex);
        trackedKeys.insert(key);
    }

    void Input::untrackKey(int key) {
        std::lock_guard<std::mutex> lock(inputMutex);
        trackedKeys.erase(key);
    }

}
