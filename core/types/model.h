#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "assimp/material.h"
#include "assimp/types.h"
#include "assimp/vector3.h"
#include "core/shader/gl_shader.h"
#include "core/types/mesh.h"
#include "core/types/texture.h"
#include "core/types/vertex.h"
#include "glm/ext/vector_float3.hpp"
#include <print>
#include <string>
#include <vector>
#include "vendors/stb_image/stb_image.h"
class Model {
public:
    Model(const std::string& path) {
        LoadModel(path);
    }

    void Draw(GL_Shader& shader) {
        for (Mesh& mesh : m_Meshes) {
            mesh.Draw(shader);
        }
    }
private:
    std::vector<Texture> m_TextureLoaded{};
    std::vector<Mesh> m_Meshes{};
    std::string m_Directory{};
    void LoadModel(const std::string& path) {
        Assimp::Importer importer{};
        const aiScene* scene { importer.ReadFile(path, aiProcess_Triangulate) }; // no need to call stbflip
        // if scene or rootnode or an incomplete data flag is raised, dont load model.
        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
        {
            std::println("ERROR::ASSIMP::{}", importer.GetErrorString());
            return;
        }
        m_Directory = path.substr(0, path.find_last_of('/'));
        std::println("{}", path);
        ProcessNode(scene->mRootNode, scene);
    }

    void ProcessNode(aiNode* node, const aiScene* scene) {
        // process all the node's meshes (if any)
        for(unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh { scene->mMeshes[node->mMeshes[i]] }; 
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

        // Getting Vertices
        for (int i {}; i < mesh->mNumVertices; i++) {
            Vertex vertex{};
            aiVector3D aiVertex { mesh->mVertices[i] };
            vertex.Position = glm::vec3{aiVertex.x, aiVertex.y, aiVertex.z};

            if (mesh->HasNormals()) {
                aiVector3D aiNormal = mesh->mNormals[i];
                vertex.Normal = glm::vec3{aiNormal.x, aiNormal.y, aiNormal.z};
            }

            if (mesh->mTextureCoords[0])
                vertex.TexCoords = glm::vec2{mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
            else
                vertex.TexCoords = glm::vec2(0);

            if (mesh->HasTangentsAndBitangents()) {
                vertex.Tangent = glm::vec3{mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z};
                vertex.Bitangent = glm::vec3{mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z};
            }
            else {
                vertex.Tangent = glm::vec3{0};
                vertex.Bitangent = glm::vec3{0};
            }

            vertices.push_back(vertex);
        }
        // Getting Indices
        for (int i{}; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for(int i{}; i < face.mNumIndices; i++)
                indices.push_back(face.mIndices[i]);
        }
        // Getting Materials
        if (mesh->mMaterialIndex >= 0) {
            aiMaterial* material { scene->mMaterials[mesh->mMaterialIndex] };
            Texture albedoMap { LoadTexture(material, aiTextureType_DIFFUSE, "albedo") };
            if (albedoMap.success) {
                textures.push_back(albedoMap);
            }

            // Texture specularMap { LoadTexture(material, aiTextureType_SPECULAR, "specular") };
            // if (specularMap.success)
            //     textures.push_back(specularMap);

            // Texture normalMap { LoadTexture(material, aiTextureType_NORMALS, "normal")};
            // if(normalMap.success)
            //     textures.push_back(normalMap);
        }

        return Mesh {vertices, indices, textures};
    }

    Texture LoadTexture(aiMaterial* mat, aiTextureType type, const std::string& typeName) {
        aiString fileName;
        mat->GetTexture(type, 0, &fileName);
        bool skip{};
        std::string path {m_Directory + '/' + fileName.C_Str()}; // This path will now be path/to/filename.jpg
        for (int i{}; i < m_TextureLoaded.size(); i++) {
            if (m_TextureLoaded[i].path == path) {
                skip = true;
                return m_TextureLoaded[i];
            }
        }

        if (!skip) {
            // We usually DONT get an object with multiple texture for a single texture type. So we are gambling on this for a slight optimization
            Texture tex { LoadTextureFromFile(fileName.C_Str(), m_Directory), typeName, path, true };
            m_TextureLoaded.push_back(tex);
            return tex;
        }
        return Texture{.success = false};
    }
    GLuint LoadTextureFromFile(const std::string &name, const std::string& directory) {
        std::string filedir {directory + "/" + name};
        GLuint textureID{};
        glGenTextures(1, &textureID);
        // stbi_set_flip_vertically_on_load(true);
        int width, height, nrChannels;
        unsigned char* data{ stbi_load(filedir.c_str(), &width, &height, &nrChannels, 0) };
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
            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        else std::println("Cannot find image");
        stbi_image_free(data);
        return textureID;
    }
};