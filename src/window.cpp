#include "include/window.hpp"

namespace ignition {
    Window::Window(int width, int height, std::string title, bool vsync, glm::vec4 clearColor) : width(width), height(height), title(title), vsync(vsync), clearColor(clearColor) {
        init();
    }

    Window::~Window() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::run(LoopCallback loopCallback) {
        while (!shouldClose()) {
            float currentFrameTime = glfwGetTime();
            float deltaTime = currentFrameTime - lastFrameTime;

            lastFrameTime = currentFrameTime;

            glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            loopCallback(deltaTime);
            
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    void Window::frameBufferResizeCallback(GLFWwindow *GLFWWindow, int width, int height) {
        glViewport(0, 0, width, height);

        Window *window = static_cast<Window *>(glfwGetWindowUserPointer(GLFWWindow));

        window->width = width;
        window->height = height;
    }

    void Window::init() {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        if (!window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window!");
        }

        glfwMakeContextCurrent(window);
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, frameBufferResizeCallback);

        if (vsync) glfwSwapInterval(1);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            glfwDestroyWindow(window);
            glfwTerminate();
            
            throw std::runtime_error("Failed to initialize GLAD!");
        }

        glViewport(0, 0, width, height);

        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
}
