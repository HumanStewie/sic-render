#pragma once

#include <glad/gl.h>
#include <string>

class Shader {
public:
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	void use();

	void SetFloat(const std::string& name, float value);
private:
	GLuint m_shaderProgram{};
};