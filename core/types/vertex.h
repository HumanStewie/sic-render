#pragma once

#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    // // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
	// //bone indexes which will influence this vertex
	// int m_BoneIDs[4];
	// //weights from each bone
	// float m_Weights[4];
};