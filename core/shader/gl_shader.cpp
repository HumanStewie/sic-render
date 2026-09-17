#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <print>
#include <cassert>

#include "gl_shader.h"

GL_Shader::GL_Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
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

void GL_Shader::use() {
	glUseProgram(m_shaderProgram);
}

void GL_Shader::SetFloat(const std::string& name, float value) {
	glUniform1f(GL_Shader::GetLocation(name), value);
}

void GL_Shader::SetInt(const std::string& name, int value) {
	glUniform1i(GL_Shader::GetLocation(name), value);
}
void GL_Shader::SetSampler2D(const std::string& name, int value) {
	GL_Shader::SetInt(name, value);
}

// ---Vec2D--------------
void GL_Shader::SetVec2f(const std::string& name, int numberOfVectors, const glm::vec2& vectors)  {
	glUniform2fv(GL_Shader::GetLocation(name), numberOfVectors, glm::value_ptr(vectors));
}
void GL_Shader::SetVec2f(const std::string& name, const glm::vec2& vector) {
	GL_Shader::SetVec2f(name, 1, vector);
}
void GL_Shader::SetVec2f(const std::string& name, float x, float y) {
	glUniform2f(GL_Shader::GetLocation(name), x, y);
}

// ---Vec4D--------------
void GL_Shader::SetVec3f(const std::string& name, int numberOfVectors, const glm::vec3& vectors)  {
	glUniform3fv(GL_Shader::GetLocation(name), numberOfVectors, glm::value_ptr(vectors));
}
void GL_Shader::SetVec3f(const std::string& name, const glm::vec3& vector) {
	GL_Shader::SetVec3f(name, 1, vector);
}
void GL_Shader::SetVec3f(const std::string& name, float x, float y, float z) {
	glUniform3f(GL_Shader::GetLocation(name), x, y, z);
}

// ---Vec4D--------------
void GL_Shader::SetVec4f(const std::string& name, int numberOfVectors, const glm::vec4& vectors)  {
	glUniform4fv(GL_Shader::GetLocation(name), numberOfVectors, glm::value_ptr(vectors));
}
void GL_Shader::SetVec4f(const std::string& name, const glm::vec4& vector) {
	GL_Shader::SetVec4f(name, 1, vector);
}
void GL_Shader::SetVec4f(const std::string& name, float x, float y, float z, float w) {
	glUniform4f(GL_Shader::GetLocation(name), x, y, z, w);
}
// ---Mat2D--------------
void GL_Shader::SetMat2f(const std::string& name, int numberOfMatrices, GLboolean isTransposed, const glm::mat2& matrices) {
	glUniformMatrix4fv(GL_Shader::GetLocation(name), numberOfMatrices, isTransposed, glm::value_ptr(matrices));
}
void GL_Shader::SetMat2f(const std::string& name, const glm::mat4& matrices) {
	GL_Shader::SetMat2f(name, 1, GL_FALSE, matrices);
}

// ---Mat3D--------------
void GL_Shader::SetMat3f(const std::string& name, int numberOfMatrices, GLboolean isTransposed, const glm::mat3& matrices) {
	glUniformMatrix4fv(GL_Shader::GetLocation(name), numberOfMatrices, isTransposed, glm::value_ptr(matrices));
}
void GL_Shader::SetMat3f(const std::string& name, const glm::mat4& matrices) {
	GL_Shader::SetMat3f(name, 1, GL_FALSE, matrices);
}

// ---Mat4D--------------
void GL_Shader::SetMat4f(const std::string& name, int numberOfMatrices, GLboolean isTransposed, const glm::mat4& matrices) {
	glUniformMatrix4fv(GL_Shader::GetLocation(name), numberOfMatrices, isTransposed, glm::value_ptr(matrices));
}
void GL_Shader::SetMat4f(const std::string& name, const glm::mat4& matrices) {
	GL_Shader::SetMat4f(name, 1, GL_FALSE, matrices);
}
GL_Shader::~GL_Shader() {
	glDeleteProgram(m_shaderProgram);
}