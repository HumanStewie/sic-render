#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <print>

#include "rendering_engine.h"
#include "core/data/draw_data.h"

RenderingEngine::RenderingEngine() : m_Rasterizer{} {
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::println("Failed to initialize GLAD.");
        return;
    }
    m_Rasterizer = std::make_unique<GL_Rasterizer>();
}

void RenderingEngine::Draw(DrawData& drawData) {
    m_Rasterizer->Draw(drawData.view, drawData.project);
}
