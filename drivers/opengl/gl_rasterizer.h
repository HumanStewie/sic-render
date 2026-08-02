#pragma once
#include <glad/gl.h>

#include "core/shader.h"


class GL_Rasterizer {
public:
    GL_Rasterizer();
    ~GL_Rasterizer();

    void Draw();

private:
    GLuint vertexShader{};
    GLuint fragmentShader{};
    GLuint VAO{};
    GLuint VBO{};
    GLuint EBO{};
    GLuint shaderProgram{};
    Shader triangleShader;
};