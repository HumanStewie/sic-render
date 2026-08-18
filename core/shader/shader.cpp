#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <print>
#include <cassert>

#include "shader.h"

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
	std::string vertCode{};
	std::string fragCode{};
	
	
	std::ifstream vertFile{vertexShaderPath};
	std::ifstream fragFile{fragmentShaderPath};

	if (!vertFile) {
		std::println("ERROR::VERTEX::SHADER::FILE_NOT_SUCCESFULLY_READ");
	}
	if (!fragFile) {
		std::println("ERROR::FRAGMENT::SHADER::FILE_NOT_SUCCESFULLY_READ");
	}

	std::stringstream vertStream{};
	std::stringstream fragStream{};
	vertStream << vertFile.rdbuf();
	fragStream << fragFile.rdbuf();
	vertCode = vertStream.str();
	fragCode = fragStream.str();
		
	const char* vertSource{ vertCode.c_str() };
	const char* fragSource{ fragCode.c_str() };

	int  success;
	char infoLog[512];

	GLuint vertexShader{ glCreateShader(GL_VERTEX_SHADER) };
	glShaderSource(vertexShader, 1, &vertSource, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::println("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n{}", infoLog);
	}

	GLuint fragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) };
	glShaderSource(fragmentShader, 1, &fragSource, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::println("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n{}", infoLog);
	}

	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, vertexShader);
	glAttachShader(m_shaderProgram, fragmentShader);
	glLinkProgram(m_shaderProgram);
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
		std::println("ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n{}", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() {
	glUseProgram(m_shaderProgram);
}

void Shader::SetFloat(const std::string& name, float value) {
	glUniform1f(Shader::GetLocation(name), value);
}

void Shader::SetInt(const std::string& name, int value) {
	glUniform1i(Shader::GetLocation(name), value);
}
void Shader::SetSampler2D(const std::string& name, int value) {
	Shader::SetInt(name, value);
}

// ---Vec2D--------------
void Shader::SetVec2f(const std::string& name, int numberOfVectors, const glm::vec2& vectors)  {
	glUniform2fv(Shader::GetLocation(name), numberOfVectors, glm::value_ptr(vectors));
}
void Shader::SetVec2f(const std::string& name, const glm::vec2& vector) {
	Shader::SetVec2f(name, 1, vector);
}
void Shader::SetVec2f(const std::string& name, float x, float y) {
	glUniform2f(Shader::GetLocation(name), x, y);
}

// ---Vec4D--------------
void Shader::SetVec3f(const std::string& name, int numberOfVectors, const glm::vec3& vectors)  {
	glUniform3fv(Shader::GetLocation(name), numberOfVectors, glm::value_ptr(vectors));
}
void Shader::SetVec3f(const std::string& name, const glm::vec3& vector) {
	Shader::SetVec3f(name, 1, vector);
}
void Shader::SetVec3f(const std::string& name, float x, float y, float z) {
	glUniform3f(Shader::GetLocation(name), x, y, z);
}

// ---Vec4D--------------
void Shader::SetVec4f(const std::string& name, int numberOfVectors, const glm::vec4& vectors)  {
	glUniform4fv(Shader::GetLocation(name), numberOfVectors, glm::value_ptr(vectors));
}
void Shader::SetVec4f(const std::string& name, const glm::vec4& vector) {
	Shader::SetVec4f(name, 1, vector);
}
void Shader::SetVec4f(const std::string& name, float x, float y, float z, float w) {
	glUniform4f(Shader::GetLocation(name), x, y, z, w);
}
// ---Mat2D--------------
void Shader::SetMat2f(const std::string& name, int numberOfMatrices, GLboolean isTransposed, const glm::mat2& matrices) {
	glUniformMatrix4fv(Shader::GetLocation(name), numberOfMatrices, isTransposed, glm::value_ptr(matrices));
}
void Shader::SetMat2f(const std::string& name, const glm::mat4& matrices) {
	Shader::SetMat2f(name, 1, GL_FALSE, matrices);
}

// ---Mat3D--------------
void Shader::SetMat3f(const std::string& name, int numberOfMatrices, GLboolean isTransposed, const glm::mat3& matrices) {
	glUniformMatrix4fv(Shader::GetLocation(name), numberOfMatrices, isTransposed, glm::value_ptr(matrices));
}
void Shader::SetMat3f(const std::string& name, const glm::mat4& matrices) {
	Shader::SetMat3f(name, 1, GL_FALSE, matrices);
}

// ---Mat4D--------------
void Shader::SetMat4f(const std::string& name, int numberOfMatrices, GLboolean isTransposed, const glm::mat4& matrices) {
	glUniformMatrix4fv(Shader::GetLocation(name), numberOfMatrices, isTransposed, glm::value_ptr(matrices));
}
void Shader::SetMat4f(const std::string& name, const glm::mat4& matrices) {
	Shader::SetMat4f(name, 1, GL_FALSE, matrices);
}
Shader::~Shader() {
	glDeleteProgram(m_shaderProgram);
}