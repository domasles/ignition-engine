#include "include/model.hpp"

namespace ignition {
	Model::Model(const ShaderProgram &shaderProgram) : VAO(0), VBO(0), EBO(0), shaderProgram(shaderProgram) {}

	Model::~Model() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);

		if (EBO) glDeleteBuffers(1, &EBO);
	}

	void Model::render() {
		shaderProgram.use();
		glBindVertexArray(VAO);

		if (!indices.empty()) glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		else glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);

		glBindVertexArray(0);
	}

	void Model::setupBuffers() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

		if (!indices.empty()) {
			glGenBuffers(1, &EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
		}

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}
