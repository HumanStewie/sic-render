#pragma once

#include <glad/gl.h>
#include <string>

class Shader {
public:
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~Shader();
	void use();

	void SetFloat(const std::string& name, float value);
	void SetInt(const std::string& name, int value);
	void SetSampler2D(const std::string& name, int value);
private:
	GLuint m_shaderProgram{};
};