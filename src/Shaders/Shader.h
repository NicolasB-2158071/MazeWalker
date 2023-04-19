#pragma once

#include <glad/glad.h> // include glad to get the required OpenGL headers
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader();
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void use() const;
	void bindUniformBlock(const std::string& name, unsigned int bindPoint);

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec4(const std::string& name, const glm::vec4& value) const;
	void setMat3(const std::string& name, GLsizei quantity, GLboolean transpose, const glm::mat3& value) const;
	void setMat4(const std::string& name, GLsizei quantity, GLboolean transpose, const glm::mat4& value) const;

private:
	unsigned int m_pID;
	unsigned int m_vID;
	unsigned int m_fID;

	int m_success;
	char m_infoLog[512];

	struct shadersCode {
		std::string vertexCode;
		std::string fragmentCode;
	};

	shadersCode readFiles(const char* vertexPath, const char* fragmentPath) const;
	void compileShaders(const char* vShaderCode, const char* fShaderCode);
	void createProgramAndLinkProgram();
};