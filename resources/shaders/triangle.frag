#version 460 core

out vec4 FragColor;

in vec3 ourPosition;
in vec2 ourTexCoord;

uniform sampler2D uTexture1;
uniform sampler2D uTexture2;

void main() {
	FragColor = mix(texture(uTexture1, ourTexCoord), texture(uTexture2, vec2(ourTexCoord.s, ourTexCoord.t)), 0.8f);
}