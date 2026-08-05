#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <print>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gl_rasterizer.h" 
#include "core/shader.h"
#include "glm/trigonometric.hpp"
#include "vendors/stb_image/stb_image.h"

GL_Rasterizer::GL_Rasterizer() : shader{ RESOURCES_PATH "/shaders/triangle.vert", RESOURCES_PATH "/shaders/triangle.frag" } {
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
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


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char* data{ stbi_load(RESOURCES_PATH "/assets/meowl.jpg", &width, &height, &nrChannels, 0) };
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else std::println("Cannot find image");
    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    data = stbi_load(RESOURCES_PATH "/assets/ehe.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else std::println("Cannot find image");
    stbi_image_free(data);


    shader.use();   
    shader.SetSampler2D("uTexture1", 0);
    shader.SetSampler2D("uTexture2", 1);
}

void GL_Rasterizer::Draw() {
    glClearColor(0.2f, 0.2f, 0.17f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3{ 0.5f, 0.5f, 0.0f });    
    trans = glm::scale(trans, glm::vec3(glm::abs(glm::sin((float)glfwGetTime())), glm::abs(glm::sin((float)glfwGetTime())), 1.0f));
    shader.use();
    shader.SetMat4f("uTransformMatrix", trans);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3{ -0.5f, -0.5f, 0.0f });    
    trans = glm::rotate(trans, 3.0f * glm::radians((float)glm::sin(glfwGetTime())), glm::vec3(0, 0, 1.0f));  
    shader.use();
    shader.SetMat4f("uTransformMatrix", trans);
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

GL_Rasterizer::~GL_Rasterizer() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VBO);
}