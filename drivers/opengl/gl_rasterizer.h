#pragma once

class GL_Rasterizer {
public:
    GL_Rasterizer();
    ~GL_Rasterizer();

    void Draw();

private:
    unsigned int vertexShader{};
    unsigned int fragmentShader{};
    unsigned int VBO{};
    unsigned int VAO{};
    unsigned int shaderProgram{};
};