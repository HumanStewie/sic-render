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
    unsigned int VAO;

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures)
    : Vertices {vertices}
    , Indices {indices}
    , Textures {textures}
    {
        SetupMesh();
    }
    ~Mesh() {
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteVertexArrays(1, &VAO);
    }

    // In model.h, when ProcessMesh finishes, it constructs a new temporary mesh.
    // At this point, it will do a copy constructor, which copies over the mesh.
    // This temporary mesh will go out of scope, deleting the VAO, VBO and EBO
    Mesh(const Mesh& other) = delete;
    Mesh& operator=(const Mesh& other) = delete;

    // We can fix this by doing a move instead.
    Mesh(Mesh&& other) noexcept
    : VAO { other.VAO }
    , VBO { other.VBO }
    , EBO { other.EBO }
    , Vertices { other.Vertices }
    , Indices { other.Indices }
    , Textures { other.Textures }
    {
        other.VAO = 0;
        other.VBO = 0;
        other.EBO = 0;
    }
    Mesh& operator=(Mesh&& other) noexcept {
        if (&other == this) return *this;
        VAO = other.VAO;
        VBO = other.VBO;
        EBO = other.EBO;
        other.VAO = 0;
        other.VBO = 0;
        other.EBO = 0;

        Vertices = other.Vertices;
        Indices = other.Indices;
        Textures = other.Textures;

        return *this; 
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
    unsigned int VBO, EBO;
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

        // Vertex Pos
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
        glEnableVertexAttribArray(0);
        // Vertex Normals
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        glEnableVertexAttribArray(1);
        // Vertex TexCoords
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        glEnableVertexAttribArray(2);
        // Vertex Tangent
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
        glEnableVertexAttribArray(3);
        // Vertex Bitangent
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
        glEnableVertexAttribArray(4);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
};