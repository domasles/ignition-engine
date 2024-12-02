#include "include/model.hpp"

namespace ignition {
    Model::Model () : transform(glm::mat4(1.0f)) {}

    Model::~Model() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);

        if (EBO) glDeleteBuffers(1, &EBO);
    }

    void Model::setMaterial(const std::shared_ptr<Material> &material) {
        this->material = material;
    }

    void Model::setVertices(const std::vector<float> &vertices) {
        this->vertices = vertices;
        setupBuffers();
    }

    void Model::setIndices(const std::vector<unsigned int> &indices) {
        this->indices = indices;
        setupBuffers();
    }

    void Model::setScale(const glm::vec3 &scale) {
        transform = glm::scale(transform, scale);
    }

    void Model::setPosition(const glm::vec3 &position) {
        transform = glm::translate(transform, position);
    }

    void Model::setRotation(const glm::vec3 &axes, const float &angle) {
        transform = glm::rotate(transform, glm::radians(angle), axes);
    }

    void Model::render() {
        if (material) material->apply();
        
        glBindVertexArray(VAO);

        material->getShaderProgram()->setUniform("transform", transform);

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

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}
