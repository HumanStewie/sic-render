#include "game_engine.h"
#include "camera/camera.h"

#include <GLFW/glfw3.h>
#include <iostream>

#include "engines/rendering_engine.h"

GameEngine::GameEngine(int width, int height)
    : m_Window{ width, height }, m_RenderingEngine{}
    , m_Camera{glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, -1.0f), glm::vec3(0, 1.0f, 0)}
    , m_Input{m_Window.GetWindow()}
    // , m_DrawData{m_Camera.GetLookAt(), 
    //           glm::perspective(glm::radians(45.0f), static_cast<float>(width) / height, 0.1f, 100.0f),
    //         m_Camera.GetPosition()}
    {
        m_RenderingEngine.DrawData.view = m_Camera.GetLookAt();
        m_RenderingEngine.DrawData.project = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / height, 0.1f, 100.0f);
        m_RenderingEngine.DrawData.viewPos = m_Camera.GetPosition();
    }

void GameEngine::Update() {
    // Input Update
    m_Input.Update();
    HandleInput();

    // Camera Update
    m_Camera.Update();

    // Data Update
    m_RenderingEngine.DrawData.view = m_Camera.GetLookAt();
    m_RenderingEngine.DrawData.viewPos = m_Camera.GetPosition();
    m_RenderingEngine.DrawData.cameraFront = m_Camera.GetFront();

    // Rendering Engine Update
    m_RenderingEngine.Draw();

    // Window Update
    m_Window.SwapBuffer();
    m_Window.PollEvent();

    UpdateDeltaTime();
}

void GameEngine::HandleInput() {
    if (m_Input.GetKeyDown(GLFW_KEY_ESCAPE)) 
        m_Window.CloseWindow();
    
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

    /* Neat Game Programming input pattern:
        - We have 2 arrays to store.
            - The first one check if we are currently pressing key
            - The second check if the key we are pressing have already been pressed/processed
        - We check if we pressed key, then check if this key has been pressed/processed
            - If not pressed/processed: Do something with this intended input, then set key as processed.
            - If pressed/processed: Skip, we don't want to repeat this key
        - This solves the problem of having a key being repeatedly pressed due to this function being called EVERY FRAME
    TODO: Feels a bit tedious to do this, make this better?
    */
    if (m_Input.GetKeyDown(GLFW_KEY_F) && !m_Input.GetKeyProcessed(GLFW_KEY_F)){
        m_RenderingEngine.InputData.seeThrough = !m_RenderingEngine.InputData.seeThrough;
        m_Input.SetKeyProcessed(GLFW_KEY_F, true);
    }

    m_Camera.HandleCameraMouse(m_Input.xOffset, m_Input.yOffset);
}

void GameEngine::UpdateDeltaTime() {
    float currentTime = glfwGetTime();
    deltaTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;
}