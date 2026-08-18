#pragma once
#include <memory>

#include "core/data/draw_data.h"
#include "drivers/opengl/gl_rasterizer.h"

class RenderingEngine {
protected:

public:
    RenderingEngine();
    ~RenderingEngine() {}

    void Draw(DrawData& drawData);

private:
    std::unique_ptr<GL_Rasterizer> m_Rasterizer;
};