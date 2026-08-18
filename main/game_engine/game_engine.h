#pragma once
#include "camera/camera.h"
#include "engines/rendering_engine.h"
#include "window/window.h"
#include "input/input.h"

#include <glm/glm.hpp>

#include "core/data/draw_data.h"

class GameEngine {
public:
    GameEngine(int width, int height);
    ~GameEngine(){}
    bool GameIsOpen() { return m_Window.WindowIsOpen(); }
    void Update();
    void HandleInput(GLFWwindow* window);
    void UpdateDeltaTime();
private:
    Window m_Window;
    RenderingEngine m_RenderingEngine;
    Camera m_Camera;
    Input m_Input;

    DrawData m_DrawData{};

    float deltaTime;
    float lastFrameTime;
};