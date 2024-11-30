#pragma once

#include "shaderProgram.hpp"
#include "material.hpp"

#include <vector>

#include <GLFW/glfw3.h>

namespace ignition {
    class Model {
        public:
            explicit Model() = default;
            virtual ~Model();

            void setMaterial(const std::shared_ptr<Material> &material);
            void setVertices(const std::vector<float> &vertices);
            void setIndices(const std::vector<unsigned int> &indices);

            void render();

        protected:
            void setupBuffers();

            std::shared_ptr<Material> material;

            GLuint VAO, VBO, EBO;

            std::vector<float> vertices;
            std::vector<unsigned int> indices;
    };
}
