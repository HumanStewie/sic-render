#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include "core/shader/gl_shader.h"
#include "texture.h"
#include "vertex.h"
class Mesh {
public:
    std::vector<Vertex> Vertices{};
    std::vector<unsigned int> Indices{};
    std::vector<Texture> Textures{};

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures)
    : Vertices {vertices}
    , Indices {indices}
    , Textures {textures}
    {
        SetupMesh();
    }
    

    void Draw(GL_Shader& shader) {
        for (int i{}; i < Textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);
            std::string type = Textures[i].type;
            shader.SetSampler2D(("material." + type + "Map").c_str(), i);
            glBindTexture(GL_TEXTURE_2D, Textures[i].id);
        }
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
private:
    unsigned int VAO, VBO, EBO;
    void SetupMesh() {
        // --- CREATING AND SETTING BUFFERS (CHANGE TO NEWER DSA LATER) ---
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(Vertex), &Vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
};