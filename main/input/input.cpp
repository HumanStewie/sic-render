#include "input.h"
#include "GLFW/glfw3.h"
#include <algorithm>

// void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
// {
//     if (action == GLFW_PRESS) 
//         InputVariables::g_keyDown[key] = true;
//     if (action == GLFW_RELEASE)
//         InputVariables::g_keyDown[key] = false;
// }

Input::Input(GLFWwindow* window) : m_window{window} {
}

bool Input::GetKeyDown(int key) {
    if (glfwGetKey(m_window, key) == GLFW_PRESS)
        m_keyDown[key] = true;

    if (glfwGetKey(m_window, key) == GLFW_RELEASE)
        m_keyDown[key] = false;
    return m_keyDown[key];
}

void Input::UpdateMousePos(float xpos, float ypos) {
    if (m_firstMouse)
    {
        m_lastX = xpos;
        m_lastY = ypos;
        m_firstMouse = false;
    }

    xOffset = xpos - m_lastX;
    yOffset = m_lastY - ypos; // reversed since y-coordinates go from bottom to top

    m_lastX = xpos;
    m_lastY = ypos;
}

void Input::Update() {
    double xpos, ypos;
    glfwGetCursorPos(m_window, &xpos, &ypos);
    UpdateMousePos(xpos, ypos);
}

void Input::ClearKeyInputs() {
    std::ranges::fill(m_keyDown, false);
}