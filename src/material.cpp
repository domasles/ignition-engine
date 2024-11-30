#include "include/material.hpp"

namespace ignition {

    Material::Material(const std::shared_ptr<ShaderProgram> &shaderProgram) : shaderProgram(shaderProgram), color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)), texture(nullptr) {}

    void Material::setTexture(const std::shared_ptr<Texture> &texture) {
        this->texture = texture;
    }

    void Material::setColor(const glm::vec4 &color) {
        this->color = color;
    }

    void Material::apply() const {
        shaderProgram->use();

        shaderProgram->setUniform("materialColor", color);

        if (texture && texture->isLoaded()) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            texture->bind(0);
            shaderProgram->setUniform("useTexture", true);
        } else {
            shaderProgram->setUniform("useTexture", false);
        }
    }
}
