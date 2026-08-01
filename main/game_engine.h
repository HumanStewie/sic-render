#pragma once

#include "engines/rendering_engine.h"

class GameEngine {
public:
    GameEngine() {}
    ~GameEngine() {}

    void Draw() {
        m_RenderingEngine.Draw();
    }

private:
    RenderingEngine m_RenderingEngine{};

};