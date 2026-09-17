#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gl_rasterizer.h" 
#include "core/shader/gl_shader.h"
#include "glm/ext/matrix_float3x3.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "vendors/stb_image/stb_image.h"

// Set up Buffers
GL_Rasterizer::GL_Rasterizer()
    : shader{ RESOURCES_PATH "/shaders/box.vert", RESOURCES_PATH "/shaders/box.frag" },
      lightShader { RESOURCES_PATH "/shaders/light.vert", RESOURCES_PATH "/shaders/light.frag" }
{
    float vertices[] {
        -0.5f, -0.5f,  0.5f, 0, 0, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f, 0, 0,
        -0.5f, -0.5f,  0.5f, 0, -1.0f, 0,

        0.5f, -0.5f,  0.5f, 0, 0, 1.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 0, 0,
        0.5f, -0.5f,  0.5f, 0, -1.0f, 0,
        
        0.5f,  0.5f,  0.5f, 0, 0, 1.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 0, 0,
        0.5f,  0.5f,  0.5f, 0, 1.0f, 0,
        
        -0.5f,  0.5f,  0.5f, 0, 0, 1.0f,
        -0.5f,  0.5f,  0.5f, -1.0f, 0, 0,
        -0.5f,  0.5f,  0.5f, 0, 1.0f, 0,

        -0.5f, -0.5f, -0.5f, 0, 0, -1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0, 0,
        -0.5f, -0.5f, -0.5f, 0, -1.0f, 0,

        0.5f, -0.5f, -0.5f, 0, 0, -1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0, 0,
        0.5f, -0.5f, -0.5f, 0, -1.0f, 0,

        0.5f,  0.5f, -0.5f,0, 0, -1.0f,
        0.5f,  0.5f, -0.5f,1.0f, 0, 0,  
        0.5f,  0.5f, -0.5f,0, 1.0f, 0, 
        
        -0.5f,  0.5f, -0.5f, 0, 0, -1.0f,
        -0.5f,  0.5f, -0.5f, -1.0f, 0, 0,
        -0.5f,  0.5f, -0.5f, 0, 1.0f, 0,
    };

    unsigned int indices[] {
        0, 3, 6, 6, 9, 0,
        15, 12, 21, 21, 18, 15,
        13, 1, 10, 10, 22, 13,
        4, 16, 19, 19, 7, 4,
        8, 20, 23, 23, 11, 8,
        14, 17, 5, 5, 2, 14
    };

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glEnable(GL_DEPTH_TEST);
    shader.use();
    shader.SetVec3f("objectColor", 1.0f, 0.5f, 0.31f);
    shader.SetVec3f("lightColor",  1.0f, 1.0f, 1.0f);
}


void GL_Rasterizer::Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& cameraPos) {
    glClearColor(0.2f, 0.2f, 0.17f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    glm::mat4 model = glm::mat4(1.0f);
    {
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.f, 0.f));
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        lightShader.use();
        lightShader.SetMat4f("model", model);
        lightShader.SetMat4f("view", view);
        lightShader.SetMat4f("projection", projection);
        glBindVertexArray(lightVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    glm::vec4 newLightPos { model * glm::vec4{ lightPos, 1.f } };
    {
        shader.use();
        model = glm::mat4(1.0f);
        shader.SetMat4f("model", model);
        shader.SetMat4f("view", view);
        shader.SetMat4f("projection", projection);
        shader.SetVec3f("lightPos", newLightPos.x, newLightPos.y, newLightPos.z);
        shader.SetVec3f("viewPos", cameraPos);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    

}

GL_Rasterizer::~GL_Rasterizer() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VBO);
}