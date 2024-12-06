#pragma once

#include "glad/glad.h"

#include <string>
#include <stdexcept>
#include <functional>

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace ignition {
    using LoopCallback = std::function<void(float)>;
    
    class Window {
        public:
            Window(int width, int height, bool vsync, std::string title, glm::vec4 clearColor=glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
            ~Window();

            Window(const Window &) = delete;
            Window &operator=(const Window &) = delete;

            void run(LoopCallback loopCallback);
            void triggerVsync(bool value) { vsync = value; }

            bool shouldClose() { return glfwWindowShouldClose(window); }

            GLFWwindow *getGLFWWindow() const { return window; }

            glm::vec2 getScreenSize() const { return glm::vec2(width, height); }

        private:
            static void framebufferResizeCallback(GLFWwindow *window, int width, int height);

            void init();

            int width, height;

            bool vsync;

            float lastFrameTime = 0.0f;

            std::string title;
            
            glm::vec4 clearColor;

            GLFWwindow *window;
    };
}
