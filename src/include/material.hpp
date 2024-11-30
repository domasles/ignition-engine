#pragma once

#include "shaderProgram.hpp"
#include "texture.hpp"

#include <glm/glm.hpp>

namespace ignition {
    class Material {
        public:
            explicit Material(const std::shared_ptr<ShaderProgram> &shaderProgram);
            virtual ~Material() = default;

            void setTexture(const std::shared_ptr<Texture> &texture);
            void setColor(const glm::vec4 &color);

            virtual void apply() const;

        protected:
            std::shared_ptr<ShaderProgram> shaderProgram;
            std::shared_ptr<Texture> texture;
            
            glm::vec4 color;
    };
}
