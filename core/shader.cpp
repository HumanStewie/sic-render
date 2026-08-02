#include <glad/gl.h>
#include <string>
#include <fstream>
#include <sstream>
#include <print>

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
	glUniform1f(glGetUniformLocation(m_shaderProgram, name.c_str()), value);
}