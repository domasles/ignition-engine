#pragma once

#include "window.hpp"

#include <unordered_map>
#include <mutex>

#include <GLFW/glfw3.h>

namespace ignition {
	class Input {
		public:
			Input(Window &window);
			~Input();

			Input(const Window &) = delete;
			Input &operator=(const Window &) = delete;
			
			void update();

			bool isKeyPressed(int key) const;

		private:
			Window &window;
			
			std::unordered_map<int, bool> keyState;
			std::unordered_map<int, bool> keyPressed;
			std::unordered_map<int, bool> keyReleased;

			mutable std::mutex inputMutex;
	};
}
