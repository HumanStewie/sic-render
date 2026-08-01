#pragma once

#include "drivers/opengl/gl_rasterizer.h"

class RenderingEngine {
protected:

public:
    RenderingEngine() {}
    ~RenderingEngine() {}

    void Draw();

private:
    GL_Rasterizer m_Rasterizer{};
};