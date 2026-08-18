#pragma once

#include <GLFW/glfw3.h>

struct Input {
    bool firstMouse{true};
    float lastX{};
    float lastY{};
    float xOffset{};
    float yOffset{};
    GLFWwindow* m_window{nullptr};

    Input(GLFWwindow* window);
    // bool GetKeyPressed(GLint keyPressed);
    bool GetKeyDown(int keyDown);
    void Update();
    void ClearKeyInputs();
    void GetMousePos(float xpos, float ypos);
};