#pragma once

#include "glad/glad.h"
#include "filesystem.hpp"

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ignition {

	class ShaderProgram {
		public:
			ShaderProgram(const std::filesystem::path &shaderDir="shaders");
			~ShaderProgram();

			void use() const;

			void setUniform(const std::string &name, int value) const;
			void setUniform(const std::string &name, float value) const;
			void setUniform(const std::string &name, const glm::vec3 &value) const;
			void setUniform(const std::string &name, const glm::mat4 &value) const;

		private:
			void loadShaderIncludes(const std::filesystem::path &shadersPath);

			GLuint compileShader(const std::string &source, GLenum shaderType);

			std::string loadShaderCode(const std::filesystem::path &shaderPath);

			GLuint programID;
	};
}
