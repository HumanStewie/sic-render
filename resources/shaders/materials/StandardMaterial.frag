#version 460 core

struct StandardMaterial {
    sampler2D albedoMap;
    sampler2D normalMap;
    sampler2D specularMap;
    sampler2D roughnessMap;
};

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform StandardMaterial material;

void main() {
    FragColor = texture(material.albedoMap, TexCoords);
}
