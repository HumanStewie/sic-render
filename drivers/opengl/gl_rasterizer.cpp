#include <glad/gl.h>

#include "gl_rasterizer.h" 
#include "core/shader.h"


GL_Rasterizer::GL_Rasterizer() : triangleShader{ RESOURCES_PATH "/shaders/triangle.vert", RESOURCES_PATH "/shaders/triangle.frag" } {
    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
   
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);


    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void GL_Rasterizer::Draw() {
    glClearColor(0.2f, 0.2f, 0.17f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    
    triangleShader.use();
    triangleShader.SetFloat("offset", 0.4f);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

}

GL_Rasterizer::~GL_Rasterizer() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VBO);
    glDeleteProgram(shaderProgram);
}