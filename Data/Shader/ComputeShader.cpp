#include "ComputeShader.h"

ComputeShader::ComputeShader(SHADER_FROM from, const char* compute)
{
	this->shaderProgramId = 0;

	if (from == SHADER_FROMCODE)
		CreateShaderFromCode(compute);
	else if (from == SHADER_FROMPATH)
		CreateShaderFromPath(compute);
}

ComputeShader::~ComputeShader()
{
	glDeleteBuffers(this->shaderStorageBuffers.size(), this->shaderStorageBuffers.data());
	for (size_t i = 0; i < this->shaderStorageBuffers.size(); i++) this->shaderStorageBuffers[i] = 0;

	glDeleteProgram(this->shaderProgramId);
	
}

void ComputeShader::Use(GLuint x, GLuint y, GLuint z)
{
	glUseProgram(this->shaderProgramId);
	glDispatchCompute(x, y, z);
	glMemoryBarrier(GL_ALL_BARRIER_BITS);
}

void ComputeShader::Set(SHADER_FROM from, const char* compute) 
{
	glDeleteProgram(this->shaderProgramId);
	this->shaderProgramId = 0;

	if (from == SHADER_FROMCODE)
		CreateShaderFromCode(compute);
	else if (from == SHADER_FROMPATH)
		CreateShaderFromPath(compute);
}

void ComputeShader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(this->shaderProgramId, name.c_str()), (int)value);
}

void ComputeShader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(this->shaderProgramId, name.c_str()), value);
}

void ComputeShader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(this->shaderProgramId, name.c_str()), value);
}

void ComputeShader::SetVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), 1, &value[0]);
}

void ComputeShader::SetVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(this->shaderProgramId, name.c_str()), x, y);
}

void ComputeShader::SetVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), 1, &value[0]);
}

void ComputeShader::SetVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(this->shaderProgramId, name.c_str()), x, y, z);
}

void ComputeShader::SetVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), 1, &value[0]);
}

void ComputeShader::SetVec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(this->shaderProgramId, name.c_str()), x, y, z, w);
}

void ComputeShader::SetMat2(const std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ComputeShader::SetMat3(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ComputeShader::SetMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void ComputeShader::AddShaderStorageBuffer(std::string bufferName, GLsizeiptr size, int bufferBaseIndex)
{
	GLuint ssbo;
	glGenBuffers(1, &ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, size, NULL, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bufferBaseIndex, ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); // Unbind

	// Add to the registry
	this->shaderStorageBuffers.push_back(ssbo);
	this->shaderStorageBufferNames.push_back(bufferName);
}

void ComputeShader::AddShaderStorageBuffer(std::string bufferName, GLsizeiptr size, const void *data, int bufferBaseIndex)
{
	GLuint ssbo;
	glGenBuffers(1, &ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, size, data, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bufferBaseIndex, ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); // Unbind

	// Add to the registry
	this->shaderStorageBuffers.push_back(ssbo);
	this->shaderStorageBufferNames.push_back(bufferName);
}

void ComputeShader::GetShaderStorageBufferSubData(GLuint ShaderStorageBufferObject, GLintptr offset, GLsizeiptr size, void* data)
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ShaderStorageBufferObject);
	glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

GLuint ComputeShader::GetShaderStorageBuffer(int index) { return this->shaderStorageBuffers[index]; }

GLuint ComputeShader::GetShaderStorageBuffer(std::string bufferName)
{
	for (size_t i = 0; i < this->shaderStorageBufferNames.size(); i++)
		if (this->shaderStorageBufferNames[i] == bufferName) { return this->shaderStorageBuffers[i]; break; }		
	
	return -1;
}


void ComputeShader::CreateShaderFromCode(const char* computeCode)
{
	unsigned int computeShader;
	int success;
	char infoLog[512];

	computeShader = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(computeShader, 1, &computeCode, NULL);
	glCompileShader(computeShader);

	glGetShaderiv(computeShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(computeShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPUTE::COMPILATION_FAILED :: \n \n" << infoLog << std::endl;
	}

	// Shader program
	this->shaderProgramId = glCreateProgram();
	glAttachShader(this->shaderProgramId, computeShader);
	glLinkProgram(this->shaderProgramId);

	glGetProgramiv(this->shaderProgramId, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->shaderProgramId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED [:\n \n" << infoLog << "\n \n:] \n" << std::endl;
	}

	glDeleteShader(computeShader);
}

void ComputeShader::CreateShaderFromPath(const char* computePath)
{
	std::string computeCode;
	std::ifstream cShaderFile;

	cShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		cShaderFile.open(computePath);
		std::stringstream vShaderStream;

		vShaderStream << cShaderFile.rdbuf();

		cShaderFile.close();

		computeCode = vShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::COMPUTE::FILE_NOT_SUCCESFULLY_READ [:\n \n" << e.code() << "\n \n:] \n" << std::endl;
	}

	const char* cShaderCode = computeCode.c_str();

	CreateShaderFromCode(cShaderCode);
}
