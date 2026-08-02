#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "rendering_engine.h"

RenderingEngine::RenderingEngine() : m_Rasterizer{} {
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::println("Failed to initialize GLAD.");
        return;
    }
    m_Rasterizer = std::make_unique<GL_Rasterizer>();
}

void RenderingEngine::Draw() {
    m_Rasterizer->Draw();
}
