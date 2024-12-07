#include "include/camera.hpp"

namespace ignition {
    Camera::Camera(const std::shared_ptr<Window> &window, const std::shared_ptr<ShaderProgram> &shaderProgram, float FOV, const float &nearClipPlane, const float &farClipPlane) : window(window), shaderProgram(shaderProgram), FOV(FOV), nearClipPlane(nearClipPlane), farClipPlane(farClipPlane), rightVector(glm::normalize(glm::cross(upVector, direction))), direction(glm::normalize(position - glm::vec3(0.0f, 0.0f, 0.0f))), upAxis(glm::cross(direction, rightVector)) {}

    void Camera::setPosition(const glm::vec3 &position) {
        this->position = position;
    }

    void Camera::updateProjection() {
        float width = window->getScreenSize().x;
        float height = window->getScreenSize().y;

        if (width != 0.0f || height != 0.0f) {
            projection = glm::mat4(1.0f);
            projection = glm::perspective(glm::radians(FOV), width / height, nearClipPlane, farClipPlane);
        }
    }

    void Camera::updateView() {
        view = glm::mat4(1.0f);
        view = glm::lookAt(position, position + frontVector, upVector);
    }

    void Camera::update() {
        if (active) {
            updateProjection();
            shaderProgram->setUniform("projection", projection);

            updateView();
            shaderProgram->setUniform("view", view);
        }
    }
}
