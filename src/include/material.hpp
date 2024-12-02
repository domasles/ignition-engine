#pragma once

#include "shaderProgram.hpp"
#include "texture.hpp"

#include <glm/glm.hpp>

namespace ignition {
    class Material {
        public:
            explicit Material(const std::shared_ptr<ShaderProgram> &shaderProgram);
            ~Material() = default;

            void setTexture(const std::shared_ptr<Texture> &texture);
            void setColor(const glm::vec4 &color);

            void apply() const;

            std::shared_ptr<ShaderProgram> getShaderProgram() { return shaderProgram; };

        private:
            std::shared_ptr<ShaderProgram> shaderProgram;
            std::shared_ptr<Texture> texture;
            
            glm::vec4 color;
    };
}
