#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>
#include "core/shader/shader.h"


class GL_Rasterizer {
public:
    GL_Rasterizer();
    ~GL_Rasterizer();

    void Draw(const glm::mat4& view, const glm::mat4& projection);

private:
    GLuint vertexShader{};
    GLuint fragmentShader{};
    GLuint VAO{};
    GLuint VBO{};
    GLuint EBO{};
    GLuint texture;
    GLuint texture2;
    Shader shader;
};