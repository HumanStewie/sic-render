#include "camera.h"
#include "glm/ext/quaternion_geometric.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

Camera::Camera(const glm::vec3& cameraPos, const glm::vec3& cameraFront, const glm::vec3& cameraUp, float movementSpeed, float sensitivity, float fov)
    : m_position{cameraPos}, m_front{cameraFront}, m_up{cameraUp}, m_speed{movementSpeed}, m_sensitivity{sensitivity}, m_fov{fov} {
        UpdateCameraVectors();
    }

void Camera::HandleCameraKey(CameraMovement direction, float deltaTime) {
    float movementSpeed = deltaTime * m_speed;
    if (direction == FORWARD)
        m_position += m_front * movementSpeed;
    if (direction == BACKWARD)
        m_position -= m_front * movementSpeed;
    if (direction == RIGHT)
        m_position += m_right * movementSpeed;
    if (direction == LEFT)
        m_position -= m_right * movementSpeed;
    if (direction == UP)
        m_position += m_trueUp * movementSpeed;
    if (direction == DOWN)
        m_position -= m_trueUp * movementSpeed;
}

void Camera::HandleCameraMouse(double xOffset, double yOffset) {
    xOffset *= m_sensitivity;
    yOffset *= m_sensitivity;

    m_yaw += xOffset;
    m_pitch += yOffset;
    if (m_pitch > 89.0f) m_pitch = 89.0f;
    if (m_pitch < -89.0f) m_pitch = -89.0f;
    UpdateCameraVectors();
}

void Camera::UpdateCameraVectors() {
    glm::vec3 direction{
        std::cos(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch)),
        std::sin(glm::radians(m_pitch)),
        std::sin(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch))
    };
    m_front = glm::normalize(direction);
    m_right = glm::normalize(glm::cross(m_front, m_up));
    m_trueUp = glm::normalize(glm::cross(m_right, m_front));
}
void Camera::Update(){

}