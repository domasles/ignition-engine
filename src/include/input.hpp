#pragma once

#include "window.hpp"

#include <array>
#include <mutex>
#include <memory>
#include <unordered_set>

#include <GLFW/glfw3.h>

namespace ignition {
    class Input {
        public:
            explicit Input(const std::shared_ptr<Window> &window);
            ~Input() = default;

            Input(const Input &) = delete;
            Input &operator=(const Input &) = delete;

            void update();

            bool isKeyUp(int key) const;
            bool isKeyDown(int key) const;
            
            bool wasKeyPressed(int key) const;
            bool wasKeyReleased(int key) const;

            void trackKey(int key);
            void untrackKey(int key);

        private:
            static constexpr int keyCount = GLFW_KEY_LAST + 1;
            mutable std::mutex inputMutex;

            std::shared_ptr<Window> window;

            std::array<bool, keyCount> keyState{};
            std::array<bool, keyCount> prevKeyState{};

            std::unordered_set<int> trackedKeys;
    };
}
