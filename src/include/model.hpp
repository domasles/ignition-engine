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
            void setRotation(const glm::vec3 &axes, const float &angle);

            void render();

        private:
            void setupBuffers();

            std::shared_ptr<Material> material;

            GLuint VAO, VBO, EBO;

            std::vector<float> vertices;
            std::vector<unsigned int> indices;

            glm::mat4 transform;
    };
}
