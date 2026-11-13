#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "assimp/vector3.h"
#include "core/shader/gl_shader.h"
#include "core/types/mesh.h"
#include "core/types/texture.h"
#include "core/types/vertex.h"
#include "glm/ext/vector_float3.hpp"
#include <print>
#include <string>
#include <vector>
class Model {
public:
    Model(const std::string& path) {
        LoadModel(path);
    }

    void Draw(GL_Shader& shader) {
        for (Mesh mesh : m_Meshes) {
            mesh.Draw(shader);
        }
    }
private:
    std::vector<Mesh> m_Meshes{};
    std::string directory{};
    void LoadModel(const std::string& path) {
        Assimp::Importer importer{};
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs); // no need to call stbflip
        // if scene or rootnode or an incomplete data flag is raised, dont load model.
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
        {
            std::println("ERROR::ASSIMP::{}", importer.GetErrorString());
            return;
        }
        directory = path.substr(0, path.find_last_of('/'));
        ProcessNode(scene->mRootNode, scene);
    }

    void ProcessNode(aiNode* node, const aiScene* scene) {
        // process all the node's meshes (if any)
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
            m_Meshes.push_back(ProcessMesh(mesh, scene));			
        }
        // then do the same for each of its children
        // Useful for when we need a parent-child translation
        for(unsigned int i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene) {
        std::vector<Vertex> vertices{};
        std::vector<Texture> textures{};
        std::vector<unsigned int> indices{};

        for (int i {}; i < mesh->mNumVertices; i++) {
            Vertex vertex{};
            aiVector3D aiVertex = mesh->mVertices[i];
            aiVector3D aiNormal = mesh->mNormals[i];
            aiVector3D* aiTex = mesh->mTextureCoords[i];
            vertex.Position = glm::vec3{aiVertex.x, aiVertex.y, aiVertex.z};
            vertex.Normal = glm::vec3{aiNormal.x, aiNormal.y, aiNormal.z};
            vertex.TexCoords = glm::vec2{aiTex->x, aiTex->y};
            vertices.push_back(
                
            )
        }

        return Mesh {vertices, indices, textures};
    }
};