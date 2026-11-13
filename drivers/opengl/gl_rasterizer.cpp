#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gl_rasterizer.h" 
#include "core/data/rendering_data.h"
#include "core/shader/gl_shader.h"
#include <glm/gtc/random.hpp>
#include "glm/ext/matrix_transform.hpp"
#include "vendors/stb_image/stb_image.h"

// Set up Buffers
GL_Rasterizer::GL_Rasterizer()
    : shader{ RESOURCES_PATH "/shaders/materials/StandardMaterial.vert", RESOURCES_PATH "/shaders/materials/StandardMaterial.frag" },
      lightShader { RESOURCES_PATH "/shaders/light.vert", RESOURCES_PATH "/shaders/light.frag" }
{
    // --- GLOBAL SETTINGS ---
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );

    float vertices[] {
        //  --- Position ---    --- Normal ---     -- UV --
        // Corner 0: (-0.5, -0.5,  0.5)
        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   0.0f, 0.0f, // Front (Bottom-Left)
        -0.5f, -0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,   1.0f, 0.0f, // Left  (Bottom-Right)
        -0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,   0.0f, 0.0f, // Bottom (Front-Left)

        // Corner 1: ( 0.5, -0.5,  0.5)
        0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   1.0f, 0.0f, // Front (Bottom-Right)
        0.5f, -0.5f,  0.5f,    1.0f,  0.0f,  0.0f,   0.0f, 0.0f, // Right (Bottom-Left)
        0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,   1.0f, 0.0f, // Bottom (Front-Right)

        // Corner 2: ( 0.5,  0.5,  0.5)
        0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   1.0f, 1.0f, // Front (Top-Right)
        0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,   0.0f, 1.0f, // Right (Top-Left)
        0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,   1.0f, 0.0f, // Top   (Front-Right)

        // Corner 3: (-0.5,  0.5,  0.5)
        -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   0.0f, 1.0f, // Front (Top-Left)
        -0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,   1.0f, 1.0f, // Left  (Top-Right)
        -0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,   0.0f, 0.0f, // Top   (Front-Left)

        // Corner 4: (-0.5, -0.5, -0.5)
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   1.0f, 0.0f, // Back  (Bottom-Right)
        -0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,   0.0f, 0.0f, // Left  (Bottom-Left)
        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,   0.0f, 1.0f, // Bottom (Back-Left)

        // Corner 5: ( 0.5, -0.5, -0.5)
        0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   0.0f, 0.0f, // Back  (Bottom-Left)
        0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,   1.0f, 0.0f, // Right (Bottom-Right)
        0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,   1.0f, 1.0f, // Bottom (Back-Right)

        // Corner 6: ( 0.5,  0.5, -0.5)
        0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   0.0f, 1.0f, // Back  (Top-Left)
        0.5f,  0.5f, -0.5f,    1.0f,  0.0f,  0.0f,   1.0f, 1.0f, // Right (Top-Right)
        0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,   1.0f, 1.0f, // Top   (Back-Right)

        // Corner 7: (-0.5,  0.5, -0.5)
        -0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   1.0f, 1.0f, // Back  (Top-Right)
        -0.5f,  0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,   0.0f, 1.0f, // Left  (Top-Left)
        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,   0.0f, 1.0f  // Top   (Back-Left)
    };

    unsigned int indices[] {
        0, 3, 6, 6, 9, 0,
        15, 12, 21, 21, 18, 15,
        13, 1, 10, 10, 22, 13,
        4, 16, 19, 19, 7, 4,
        8, 20, 23, 23, 11, 8,
        14, 17, 5, 5, 2, 14
    };

    // --- CREATING AND SETTING BUFFERS (CHANGE TO NEWER DSA LATER) ---
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    // --- SETTING TEXTURES ---
    diffuseMap = LoadTexture("/assets/container2.png", true);

    shader.use();
    shader.SetSampler2D("material.albedoMap", 0);

}


void GL_Rasterizer::Draw(const RenderData::DrawData& drawData, const RenderData::InputData& inputData) {
    glClearColor(0.2f, 0.2f, 0.17f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    glm::mat4 model = glm::mat4(1.0f);
    {
        // model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.f, 0.f));
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        lightShader.use();
        lightShader.SetMat4f("model", model);
        lightShader.SetMat4f("view", drawData.view);
        lightShader.SetMat4f("projection", drawData.project);
        lightShader.SetVec3f("lightCubeColor", glm::vec3(1));
        glBindVertexArray(lightVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    {
        glBindVertexArray(VAO);

         glm::vec3 cubePositions[] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        shader.use();
        shader.SetMat4f("view", drawData.view);
        shader.SetMat4f("projection", drawData.project);
      

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
      
        for (int i{}; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, 20.0f * i, glm::vec3(1.0f, 0.3f, 0.5f));
            shader.SetMat4f("model", model);
            
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }
        glBindVertexArray(0);
    }
    

}

GLuint GL_Rasterizer::LoadTexture(const std::string& path, bool flip) {
    GLuint texture{};

    stbi_set_flip_vertically_on_load(flip);
    int width, height, nrChannels;
    unsigned char* data{ stbi_load((RESOURCES_PATH + path).c_str(), &width, &height, &nrChannels, 0) };
    if (data) {
        int colorFormat{};
        switch (nrChannels) {
        case 2:
            colorFormat = GL_RG;
            break;
        case 3:
            colorFormat = GL_RGB;
            break;
        case 4:
            colorFormat = GL_RGBA;
            break;
        default:
            std::println("What kind of image are you using??? (Number of Color Channels too high)");
            break;
        }
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    else std::println("Cannot find image");
    stbi_image_free(data);

    return texture;
}

GL_Rasterizer::~GL_Rasterizer() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}