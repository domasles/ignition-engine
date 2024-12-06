#pragma once

#include "shaderProgram.hpp"
#include "material.hpp"

#include <vector>

#include <GLFW/glfw3.h>

namespace ignition {
    class Model {
        public:
            Model();
            ~Model();

            void setMaterial(const std::shared_ptr<Material> &material);
            void setVertices(const std::vector<float> &vertices);
            void setIndices(const std::vector<unsigned int> &indices);

            void setScale(const glm::vec3 &scale);
            void setPosition(const glm::vec3 &position);
            void setRotation(const glm::vec3 &rotation);

            void render();

        private:
            void setupBuffers();
            void updateTransform();

            std::shared_ptr<Material> material;

            GLuint VAO, VBO, EBO;

            std::vector<float> vertices;
            std::vector<unsigned int> indices;

            glm::mat4 scale{1.0f};
            glm::mat4 position{1.0f};
            glm::mat4 rotation{1.0f};

            glm::mat4 transform{1.0f};
    };
}
