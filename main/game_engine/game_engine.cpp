#include "game_engine.h"

#include <GLFW/glfw3.h>

void GameEngine::Update() {
    HandleInput(m_Window.GetWindow());

    m_RenderingEngine.Draw();

    m_Window.SwapBuffer();
    m_Window.PollEvent();
}

// Somehow separate this over to Window so GameEngine doesn't have to have any GLFW library imported
void GameEngine::HandleInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}