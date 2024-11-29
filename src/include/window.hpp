#pragma once

#include "glad/glad.h"

#include <string>
#include <stdexcept>
#include <functional>

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace ignition {
    using LoopCallback = std::function<void()>;
    
    class Window {
        public:
            Window(int width, int height, bool vsync, std::string title, glm::vec4 clearColor=glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
            ~Window();

            Window(const Window &) = delete;
            Window &operator=(const Window &) = delete;

            void run(LoopCallback loopCallback);
            void triggerVsync(bool vsyncValue) { vsync = vsyncValue; }

            bool shouldClose() { return glfwWindowShouldClose(window); }

            GLFWwindow *getGLFWWindow() const { return window; }

        private:
            static void framebufferResizeCallback(GLFWwindow *window, int width, int height);

            void init();

            int width;
            int height;

            bool vsync;

            std::string title;
            
            glm::vec4 clearColor;

            GLFWwindow *window;
    };
}
