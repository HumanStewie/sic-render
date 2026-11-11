#pragma once
#include <memory>

#include "core/data/rendering_data.h"
#include "drivers/opengl/gl_rasterizer.h"

class RenderingEngine {
protected:

public:
    RenderData::DrawData DrawData{};
    RenderData::InputData InputData{};
    
    RenderingEngine();
    ~RenderingEngine() {}

    void Draw();

private:
    std::unique_ptr<GL_Rasterizer> m_Rasterizer;
};