#pragma once

#include <glm/gtc/type_ptr.hpp>
enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

class Camera {
public:
    Camera(const glm::vec3& cameraPos, const glm::vec3& cameraFront, const glm::vec3& cameraUp, float movementSpeed = 2.5f, float sensitivity = 0.1f, float fov = 60.0f);
    void HandleCameraKey(CameraMovement direction, float deltaTime);
    void HandleCameraMouse(double xOffset, double yOffset);
    void Update();
    glm::mat4 GetLookAt() {
        return glm::lookAt(m_position, m_front + m_position, m_trueUp);
    }
    void CursorCallback(double xpos, double ypos);
    glm::vec3 GetPosition() { return m_position; }
private:
    float m_speed {2.5f};
    float m_sensitivity{};
    float m_fov{};
    float m_yaw{-90.0f};
    float m_pitch{};
    glm::vec3 m_position{};
    glm::vec3 m_front{};
    glm::vec3 m_up{};
    glm::vec3 m_trueUp{};
    glm::vec3 m_right{};
};