#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourPosition;
out vec3 ourColor;
out vec2 ourTexCoord;

uniform mat4 uTransformMatrix;

void main()
{
	ourColor = aColor;
	ourPosition = aPos;
	ourTexCoord = aTexCoord;
	
	gl_Position = uTransformMatrix * vec4(aPos, 1.0);
}