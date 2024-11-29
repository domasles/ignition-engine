#pragma once

#include "window.hpp"

#include <array>
#include <mutex>

#include <GLFW/glfw3.h>

namespace ignition {
    class Input {
        public:
            explicit Input(Window &window);
            ~Input();

            Input(const Window &) = delete;
            Input &operator=(const Window &) = delete;

            void update();

            bool isKeyPressed(int key) const;
            bool wasKeyPressed(int key) const;
            bool wasKeyReleased(int key) const;

        private:
            static constexpr int KeyCount = GLFW_KEY_LAST + 1;
            mutable std::mutex inputMutex;

            Window &window;

            std::array<bool, KeyCount> keyState{};
            std::array<bool, KeyCount> prevKeyState{};
    };
}
