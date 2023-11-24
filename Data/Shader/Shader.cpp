#include "Shader.h"

Shader::Shader() { CreateShaderFromCode(this->vertexShaderCodeError, this->fragmentErrorShaderCode); }
Shader::Shader(SHADER_FROM from, const char* vertex, const char* fragment) 
{
	this->shaderProgramId = 0;

	if (from == SHADER_FROMCODE)
		CreateShaderFromCode(vertex, fragment);
	else if (from == SHADER_FROMPATH)
		CreateShaderFromPath(vertex, fragment);
}
Shader::~Shader() { glDeleteProgram(this->shaderProgramId); }

void Shader::Use() { glUseProgram(this->shaderProgramId); }

void Shader::Set(SHADER_FROM from, const char* vertex, const char* fragment)
{
	glDeleteProgram(this->shaderProgramId);
	this->shaderProgramId = 0;

	if (from == SHADER_FROMCODE)
		CreateShaderFromCode(vertex, fragment);
	else if (from == SHADER_FROMPATH)
		CreateShaderFromPath(vertex, fragment);
}

void Shader::CreateShaderFromCode(const char* vertexCode, const char* fragmentCode)
{
	this->shaderProgramId = CreateShaderProgram(CreateVertexShader(vertexCode), CreateFragmentShader(fragmentCode));
}

void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(this->shaderProgramId, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(this->shaderProgramId, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(this->shaderProgramId, name.c_str()), value);
}

void Shader::SetVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), 1, &value[0]);
}

void Shader::SetVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(this->shaderProgramId, name.c_str()), x, y);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), 1, &value[0]);
}

void Shader::SetVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(this->shaderProgramId, name.c_str()), x, y, z);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), 1, &value[0]);
}

void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(this->shaderProgramId, name.c_str()), x, y, z, w);
}

void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

unsigned int Shader::CreateVertexShader(const char* vertexShaderCode)
{
	unsigned int vertexShader;
	int success;
	char infoLog[512];

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED :: \n \n" << infoLog << std::endl;

		glShaderSource(vertexShader, 1, &this->vertexShaderCodeError, NULL);
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED::FALLBACK :: \n \n" << infoLog << std::endl;
		}
	}

	return vertexShader;
}

unsigned int Shader::CreateFragmentShader(const char* fragmentShaderCode) {
	unsigned int fragmentShader;
	int success;
	char infoLog[512];

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED :: \n \n" << infoLog << std::endl;

		glShaderSource(fragmentShader, 1, &this->fragmentErrorShaderCode, NULL);
		glCompileShader(fragmentShader);
	}

	return fragmentShader;
}


int Shader::CreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	unsigned int shaderProgram;
	int success;
	char infoLog[512];

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED [:\n \n" << infoLog << "\n \n:] \n" << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

void Shader::CreateShaderFromPath(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try
	{
		vShaderFile.open(vertexPath);
		std::stringstream vShaderStream;

		vShaderStream << vShaderFile.rdbuf();

		vShaderFile.close();

		vertexCode = vShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::VERTEX::FILE_NOT_SUCCESFULLY_READ [:\n \n" << e.code() << "\n \n:] \n" << std::endl;
	}
	
	try
	{
		fShaderFile.open(fragmentPath);
		std::stringstream fShaderStream;

		fShaderStream << fShaderFile.rdbuf();

		fShaderFile.close();

		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FRAGMENT::FILE_NOT_SUCCESFULLY_READ [:\n \n" << e.code() << "\n \n:] \n" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	this->shaderProgramId = CreateShaderProgram(CreateVertexShader(vShaderCode), CreateFragmentShader(fShaderCode));
}
