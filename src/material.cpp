#include "include/material.hpp"

namespace ignition {

	Material::Material(const ShaderProgram &shaderProgram) : shaderProgram(shaderProgram), color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) {}

	void Material::apply() const {
		shaderProgram.use();
		if (color != glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) shaderProgram.setUniform("materialColor", color);
	}
}
