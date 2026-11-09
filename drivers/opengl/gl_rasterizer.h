#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <string_view>
#include "core/shader/gl_shader.h"


class GL_Rasterizer {
public:
    GL_Rasterizer();
    ~GL_Rasterizer();

    void Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPos, const glm::vec3& cameraFront);
    GLuint LoadTexture(const std::string& path, bool flip);

private:
    GLuint vertexShader{};
    GLuint fragmentShader{};
    GLuint VAO{};
    GLuint lightVAO{};
    GLuint VBO{};
    GLuint EBO{};
    GLuint diffuseMap{};
    GLuint specularMap{};
    GLuint emissionMap{};
    GL_Shader shader;
    GL_Shader lightShader;
};