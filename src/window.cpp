#include "include/window.hpp"

namespace ignition {
	Window::Window(int width, int height, std::string title, glm::vec4 clearColor) : width(width), height(height), title(title), clearColor(clearColor) {
		init();
	}

	Window::~Window() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	void Window::init() {
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

		if (window == nullptr) {
			throw std::runtime_error("Failed to create GLFW window!");
		}

		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			throw std::runtime_error("Failed to initialize GLAD!");
		}

		glViewport(0, 0, width, height);
	}

	void Window::run(LoopCallback loopCallback) {
		while (!shouldClose()) {
			glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
			glClear(GL_COLOR_BUFFER_BIT);

			loopCallback();
			
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
}
