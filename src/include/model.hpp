#pragma once

#include "shaderProgram.hpp"

#include <vector>

#include <GLFW/glfw3.h>

namespace ignition {
	class Model {
		public:
			Model(const ShaderProgram &shaderProgram);
			virtual ~Model();

			virtual void render();

		protected:
			void setupBuffers();

			GLuint VAO, VBO, EBO;

			std::vector<float> vertices;
			std::vector<unsigned int> indices;

			const ShaderProgram &shaderProgram;
	};
}
