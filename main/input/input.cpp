#include "input.h"
#include "GLFW/glfw3.h"
#include <algorithm>
#include <array>

namespace InputVariables {
    std::array<bool, 350> g_keyDown{};
    struct MousePos {

    };
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) 
        InputVariables::g_keyDown[key] = true;
    if (action == GLFW_RELEASE)
        InputVariables::g_keyDown[key] = false;
    
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
   
}

Input::Input(GLFWwindow* window) : m_window{window} {
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
}

bool Input::GetKeyDown(int key) {
    return InputVariables::g_keyDown[key];
}

void Input::GetMousePos(float xpos, float ypos) {
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    xOffset = xpos - lastX;
    yOffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;
}

void Input::Update() {
    double xpos, ypos;
    glfwGetCursorPos(m_window, &xpos, &ypos);
    GetMousePos(xpos, ypos);
}

void Input::ClearKeyInputs() {
    std::ranges::fill(InputVariables::g_keyDown, false);
}