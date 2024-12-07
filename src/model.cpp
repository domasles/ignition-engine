#include "include/model.hpp"

namespace ignition {
    Model::Model () {
        setScale(glm::vec3(1.0f));
        setRotation(glm::vec3(0.0f));
        setPosition(glm::vec3(0.0f));
    }

    Model::~Model() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);

        if (EBO) glDeleteBuffers(1, &EBO);
    }

    void Model::setMaterial(const std::shared_ptr<Material> &material) {
        if (!material) throw std::runtime_error("Failed to assign a material!");
        this->material = material;
    }

    void Model::setVertices(const std::vector<float> &vertices) {
        if (vertices.empty()) throw std::runtime_error("Failed to assign an empty array of vertices!");

        this->vertices = vertices;

        setupBuffers();
    }

    void Model::setIndices(const std::vector<unsigned int> &indices) {
        if (indices.empty()) throw std::runtime_error("Failed to assign an empty array of indices!");

        this->indices = indices;

        setupBuffers();
    }

    void Model::setScale(const glm::vec3 &scale) {
        this->scale = glm::mat4(1.0f);
        this->scale = glm::scale(this->scale, scale);

        updateTransform();
    }

    void Model::setPosition(const glm::vec3 &position) {
        this->position = glm::mat4(1.0f);
        this->position = glm::translate(this->position, position);

        updateTransform();
    }

    void Model::setRotation(const glm::vec3 &rotation) {
        this->rotation = glm::mat4(1.0f);

        this->rotation = glm::rotate(this->rotation, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        this->rotation = glm::rotate(this->rotation, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        this->rotation = glm::rotate(this->rotation, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

        updateTransform();
    }

    void Model::render() {
        if (!material) throw std::runtime_error("Material cannot be unset!");

        if (vertices.empty()) throw std::runtime_error("Vertices cannot be unset!");
        if (indices.empty()) throw std::runtime_error("Indices cannot be unset!");

        if (material) material->apply();
        
        glBindVertexArray(VAO);

        material->getShaderProgram()->setUniform("transform", transform);

        if (!indices.empty()) glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        else glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);

        glBindVertexArray(0);
    }

    void Model::setupBuffers() {
        glGenVertexArrays(1, &VAO);

        if (VAO == 0) {
            std::cerr << "Failed to generate VAO!" << std::endl;
            throw std::runtime_error("Failed to generate VAO");
        }

        glGenBuffers(1, &VBO);

        if (VBO == 0) {
            std::cerr << "Failed to generate VBO!" << std::endl;
            throw std::runtime_error("Failed to generate VBO");
        }

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

    void Model::updateTransform() {
        transform = position * rotation * scale;
    }
}
