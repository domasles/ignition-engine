#pragma once

#include "shaderProgram.hpp"
#include "material.hpp"

#include <vector>

#include <GLFW/glfw3.h>

namespace ignition {
	class Model {
		public:
			explicit Model(const Material &material);
			virtual ~Model();

			virtual void render();

		protected:
			void setupBuffers();

			const Material &material;

			GLuint VAO, VBO, EBO;

			std::vector<float> vertices;
			std::vector<unsigned int> indices;
	};
}
