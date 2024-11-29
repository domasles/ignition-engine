#pragma once

#include "shaderProgram.hpp"

#include <glm/glm.hpp>

namespace ignition {
    class Material {
        public:
            explicit Material(const ShaderProgram &shaderProgram);
            virtual ~Material() = default;

            virtual void apply() const;

            const ShaderProgram &getShaderProgram() const { return shaderProgram; }

        protected:
            const ShaderProgram &shaderProgram;

            glm::vec4 color;
    };
}
