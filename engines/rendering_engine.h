#pragma once
#include <memory>

#include "drivers/opengl/gl_rasterizer.h"

class RenderingEngine {
protected:

public:
    RenderingEngine();
    ~RenderingEngine() {}

    void Draw();

private:
    std::unique_ptr<GL_Rasterizer> m_Rasterizer;
};