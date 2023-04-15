#include "Shader.h"

Shader::Shader()
{}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	shadersCode sc{ readFiles(vertexPath, fragmentPath) };

	const char* vShaderCode = sc.vertexCode.c_str();
	const char* fShaderCode = sc.fragmentCode.c_str();

	compileShaders(vShaderCode, fShaderCode);
	createProgramAndLinkProgram();
}

Shader::~Shader()
{
	glDeleteProgram(m_pID);
}

Shader::shadersCode Shader::readFiles(const char* vertexPath, const char* fragmentPath) const
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file’s buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	return std::move(shadersCode{ vertexCode, fragmentCode });
}

void Shader::compileShaders(const char* vShaderCode, const char* fShaderCode)
{
	// vertex shader
	m_vID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vID, 1, &vShaderCode, NULL);
	glCompileShader(m_vID);

	glGetShaderiv(m_vID, GL_COMPILE_STATUS, &m_success);
	if (!m_success)
	{
		glGetShaderInfoLog(m_vID, 512, NULL, m_infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
			m_infoLog << std::endl;
	};

	// fragment shader
	m_fID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fID, 1, &fShaderCode, NULL);
	glCompileShader(m_fID);

	glGetShaderiv(m_fID, GL_COMPILE_STATUS, &m_success);
	if (!m_success)
	{
		glGetShaderInfoLog(m_fID, 512, NULL, m_infoLog);
		std::cout << "ERROR::SHADER::Fragment::COMPILATION_FAILED\n" <<
			m_infoLog << std::endl;
	};
}

void Shader::createProgramAndLinkProgram()
{
	m_pID = glCreateProgram();
	glAttachShader(m_pID, m_vID);
	glAttachShader(m_pID, m_fID);
	glLinkProgram(m_pID);

	// print linking errors if any
	glGetProgramiv(m_pID, GL_LINK_STATUS, &m_success);
	if (!m_success)
	{
		glGetShaderInfoLog(m_vID, 512, NULL, m_infoLog);
		std::cout << "ERROR::SHADER::Program::LINKING/ATTACHING_FAILED\n" <<
			m_infoLog << std::endl;
	};

	glDeleteShader(m_vID);
	glDeleteShader(m_fID);
}

void Shader::use() const
{
	glUseProgram(m_pID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_pID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_pID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_pID, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
	unsigned int vec3Location = glGetUniformLocation(m_pID, name.c_str());
	glUniform3f(vec3Location, value.x, value.y, value.z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
	unsigned int vec4Location = glGetUniformLocation(m_pID, name.c_str());
	glUniform4f(vec4Location, value.x, value.y, value.z, value.w);
}

void Shader::setMat3(const std::string& name, GLsizei quantity, GLboolean transpose, const glm::mat3& value) const
{
	unsigned int transformLoc = glGetUniformLocation(m_pID, name.c_str());
	glUniformMatrix3fv(transformLoc, quantity, transpose, glm::value_ptr(value));
}

void Shader::setMat4(const std::string& name, GLsizei quantity, GLboolean transpose, const glm::mat4& value) const
{
	unsigned int transformLoc = glGetUniformLocation(m_pID, name.c_str());
	glUniformMatrix4fv(transformLoc, quantity, transpose, glm::value_ptr(value));
}
