#pragma once
#include "camera/camera.h"
#include "engines/rendering_engine.h"
#include "window/window.h"
#include "input/input.h"

#include <glm/glm.hpp>

class GameEngine {
public:
    GameEngine(int width, int height);
    ~GameEngine(){}
    bool GameIsOpen() { return m_Window.WindowIsOpen(); }
    void Init();
    void Shutdown();
    void Update();
    void HandleInput();
    void UpdateDeltaTime();
private:
    Window m_Window;
    RenderingEngine m_RenderingEngine;
    Camera m_Camera;
    Input m_Input;

    float deltaTime;
    float lastFrameTime;
};