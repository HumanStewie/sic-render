#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>
#include "core/data/rendering_data.h"
#include "core/shader/gl_shader.h"
#include "core/types/model.h"


class GL_Rasterizer {
public:
    GL_Rasterizer();
    ~GL_Rasterizer();

    void Draw(const RenderData::DrawData& drawData, const RenderData::InputData& inputData);
private:
    GL_Shader shader;
    GL_Shader lightShader;
    float cutOff {12.5f};
    float outer {17.5f};
    Model model;
};