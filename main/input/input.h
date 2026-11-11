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
    bool GetKeyProcessed(int keyDown) {
        return m_keyProcessed[keyDown];
    }
    void SetKeyProcessed(int keyDown, bool value) {
        m_keyProcessed[keyDown] = value;
    }
private:
    std::array<bool, 350> m_keyDown{};
    std::array<bool, 350> m_keyProcessed{};
    GLFWwindow* m_window{nullptr};
    bool m_firstMouse{true};
    float m_lastX{};
    float m_lastY{};
    void UpdateMousePos(float xpos, float ypos);
};