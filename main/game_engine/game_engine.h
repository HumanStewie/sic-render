#pragma once
#include "engines/rendering_engine.h"
#include "window/window.h"

class GameEngine {
public:
    GameEngine(int width, int height) : m_Window{ width, height }, m_RenderingEngine{} {}
    ~GameEngine() {}
    bool GameIsOpen() {
        return m_Window.WindowIsOpen();
    }
    void Update();
    void HandleInput(GLFWwindow* window);
private:
    Window m_Window;
    RenderingEngine m_RenderingEngine;
};