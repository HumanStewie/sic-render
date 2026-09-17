#include "game_engine.h"
#include "camera/camera.h"

#include <GLFW/glfw3.h>

#include "core/data/draw_data.h"

GameEngine::GameEngine(int width, int height)
    : m_Window{ width, height }, m_RenderingEngine{}
    , m_Camera{glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, -1.0f), glm::vec3(0, 1.0f, 0)}
    , m_Input{m_Window.GetWindow()}
    , m_DrawData{m_Camera.GetLookAt(), 
              glm::perspective(glm::radians(45.0f), static_cast<float>(width) / height, 0.1f, 100.0f),
            m_Camera.GetPosition()}
    {}

void GameEngine::Update() {
    // Input Update
    m_Input.Update();
    HandleInput(m_Window.GetWindow());

    // Camera Update
    m_Camera.Update();

    // Data Update
    m_DrawData.view = m_Camera.GetLookAt();
    m_DrawData.viewPos = m_Camera.GetPosition();

    // Rendering Engine Update
    m_RenderingEngine.Draw(m_DrawData);

    // Window Update
    m_Window.SwapBuffer();
    m_Window.PollEvent();

    UpdateDeltaTime();
}

// Somehow separate this over to Window so GameEngine doesn't have to have any GLFW library imported
void GameEngine::HandleInput(GLFWwindow* window) {
    if (m_Input.GetKeyDown(GLFW_KEY_ESCAPE)) 
        glfwSetWindowShouldClose(window, true);
    
    if (m_Input.GetKeyDown(GLFW_KEY_W))
        m_Camera.HandleCameraKey(CameraMovement::FORWARD, deltaTime);
    if (m_Input.GetKeyDown(GLFW_KEY_S))
        m_Camera.HandleCameraKey(CameraMovement::BACKWARD, deltaTime);
    if (m_Input.GetKeyDown(GLFW_KEY_A))
        m_Camera.HandleCameraKey(CameraMovement::LEFT, deltaTime);
    if (m_Input.GetKeyDown(GLFW_KEY_D))
        m_Camera.HandleCameraKey(CameraMovement::RIGHT, deltaTime);
    if (m_Input.GetKeyDown(GLFW_KEY_SPACE) || m_Input.GetKeyDown(GLFW_KEY_E))
        m_Camera.HandleCameraKey(CameraMovement::UP, deltaTime);
    if (m_Input.GetKeyDown(GLFW_KEY_LEFT_SHIFT) || m_Input.GetKeyDown(GLFW_KEY_Q))
        m_Camera.HandleCameraKey(CameraMovement::DOWN, deltaTime);

    m_Camera.HandleCameraMouse(m_Input.xOffset, m_Input.yOffset);
}

void GameEngine::UpdateDeltaTime() {
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;
}