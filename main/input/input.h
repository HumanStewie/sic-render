#pragma once

#include <GLFW/glfw3.h>
#include <array>

struct Input {
public:
    float xOffset{};
    float yOffset{};
    Input(GLFWwindow* window);
    // bool GetKeyPressed(GLint keyPressed);
    bool GetKeyDown(int keyDown);
    void Update();
    void ClearKeyInputs();

private:
    std::array<bool, 350> m_keyDown{};
    GLFWwindow* m_window{nullptr};
    bool m_firstMouse{true};
    float m_lastX{};
    float m_lastY{};
    void UpdateMousePos(float xpos, float ypos);
};