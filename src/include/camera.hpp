#pragma once

#include "window.hpp"
#include "shaderProgram.hpp"

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace ignition {
    class Camera {
        public:
            Camera(const std::shared_ptr<Window> &window, const std::shared_ptr<ShaderProgram> &shaderProgram, float FOV=75.0f, const float &nearClipPlane=0.1f, const float &farClipPlane=100.0f);
            ~Camera() = default;
            
            void setPosition(const glm::vec3 &position);
            void update();
            void setActive(bool value) { active = value; };

        private:
            void updateView();
            void updateProjection();

            float FOV;
            float nearClipPlane;
            float farClipPlane;

            bool active = true;

            std::shared_ptr<Window> window;
            std::shared_ptr<ShaderProgram> shaderProgram;

            glm::vec3 position{0.0f, 0.0f, 0.0f};

            glm::vec3 upVector{0.0f, 1.0f, 0.0f};
            glm::vec3 frontVector{0.0f, 0.0f, -1.0f};
            glm::vec3 rightVector;

            glm::vec3 direction;
            glm::vec3 upAxis;

            glm::mat4 view;
            glm::mat4 projection;
    };
}
