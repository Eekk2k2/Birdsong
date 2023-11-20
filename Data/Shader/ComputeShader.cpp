#include "ComputeShader.h"

ComputeShader::ComputeShader(SHADER_FROM from, const char* compute)
{
	this->shaderProgramId = 0;

	if (from == SHADER_FROMCODE)
		CreateShaderFromCode(compute);
	else if (from == SHADER_FROMPATH)
		CreateShaderFromPath(compute);
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
