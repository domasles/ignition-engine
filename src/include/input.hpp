#pragma once

#include "window.hpp"

#include <array>
#include <mutex>
#include <memory>

#include <GLFW/glfw3.h>

namespace ignition {
    class Input {
        public:
            explicit Input(const std::shared_ptr<Window> &window);
            ~Input();

            Input(const Input &) = delete;
            Input &operator=(const Input &) = delete;

            void update();

            bool isKeyPressed(int key) const;
            bool wasKeyPressed(int key) const;
            bool wasKeyReleased(int key) const;

        private:
            static constexpr int KeyCount = GLFW_KEY_LAST + 1;
            mutable std::mutex inputMutex;

            std::shared_ptr<Window> window;

            std::array<bool, KeyCount> keyState{};
            std::array<bool, KeyCount> prevKeyState{};
    };
}
