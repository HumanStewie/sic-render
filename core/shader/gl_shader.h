#pragma once
#include <glad/gl.h>
#include <string>
#include <cassert>
#include <print>

#include <glm/gtc/type_ptr.hpp>

class GL_Shader {
public:
	GL_Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~GL_Shader();
	void use();

	void SetFloat(const std::string& name, float value);
	void SetInt(const std::string& name, int value);
	void SetSampler2D(const std::string& name, int value);

	void SetVec2f(const std::string& name, int numberOfVectors, const glm::vec2& vector);
	void SetVec2f(const std::string& name, const glm::vec2& vector);
	void SetVec2f(const std::string& name, float x, float y);
	void SetVec3f(const std::string& name, int numberOfVectors, const glm::vec3& vector);
	void SetVec3f(const std::string& name, const glm::vec3& vector);
	void SetVec3f(const std::string& name, float x, float y, float z);
	void SetVec4f(const std::string& name, int numberOfVectors, const glm::vec4& vector);
	void SetVec4f(const std::string& name, const glm::vec4& vector);
	void SetVec4f(const std::string& name, float x, float y, float z, float w);

	void SetMat2f(const std::string& name, int numberOfMatrices, GLboolean isTransposed, const glm::mat2& matrices);
	void SetMat2f(const std::string& name, const glm::mat4& matrices);
	void SetMat3f(const std::string& name, int numberOfMatrices, GLboolean isTransposed, const glm::mat3& matrices);
	void SetMat3f(const std::string& name, const glm::mat4& matrices);
	void SetMat4f(const std::string& name, int numberOfMatrices, GLboolean isTransposed, const glm::mat4& matrices);
	void SetMat4f(const std::string& name, const glm::mat4& matrices);
private:
	GLuint m_shaderProgram{};

	// Helper methods
	GLint GetLocation(const std::string& name) {
		GLint location{ glGetUniformLocation(m_shaderProgram, name.c_str()) };
		if (location == -1)
			std::println("Unable to locate {0}", name);
		assert(location != -1 && "Could not locate uniform. Did you declare an uniform in the shader?");
		return location;
	}
};