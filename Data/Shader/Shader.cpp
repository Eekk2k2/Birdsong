#include "Shader.h"

Shader::Shader() 
{ 
	this->fragmentShaderID = 0;
	this->geometryShaderID = 0;
	this->vertexShaderID = 0;
	this->shaderProgramId = 0;
	this->destroyOnDestruct = true;
}
Shader::Shader(SHADER_FROM from, const char* vertex, const char* fragment) 
{
	this->Set(from, vertex, fragment);
	this->destroyOnDestruct = true;
}

Shader::Shader(Shader&& other) noexcept
{
	this->fragmentShaderID = other.fragmentShaderID;
	this->geometryShaderID = other.geometryShaderID;
	this->vertexShaderID = other.vertexShaderID;
	this->shaderProgramId = other.shaderProgramId;

	other.destroyOnDestruct = false;
	this->destroyOnDestruct = true;
}

Shader::~Shader()
{ 
	if (this->destroyOnDestruct)
	{
		glDeleteProgram(this->shaderProgramId);
		std::cout << "Delted" << std::endl;
	}
}

void Shader::Use() { glUseProgram(this->shaderProgramId); }

void Shader::Set(SHADER_FROM from, const char* vertex, const char* fragment)
{
	if (glIsProgram(this->shaderProgramId) == GL_TRUE)
	{
		glDeleteProgram(this->shaderProgramId);
		std::cout << "Delted" << std::endl;
	}

	this->SetVert(from, vertex);
	this->SetFrag(from, fragment);
	this->LinkProgram();

	//if (from == SHADER_FROMCODE)
	//	CreateShaderFromCode(vertex, fragment);
	//else if (from == SHADER_FROMPATH)
	//	CreateShaderFromPath(vertex, fragment);
}

void Shader::LinkProgram()
{
	GLboolean isVertex		= glIsShader(this->vertexShaderID);
	GLboolean isFragment	= glIsShader(this->fragmentShaderID);
	GLboolean isGeometry	= glIsShader(this->geometryShaderID);
	
	if (isVertex || isFragment || isGeometry) {
		int success;
		char infoLog[1024];
		
		if (glIsProgram(this->shaderProgramId) == GL_TRUE) {
			std::cout << "Deleted progra" << std::endl;
			glDeleteProgram(this->shaderProgramId);
		}

		this->shaderProgramId = glCreateProgram();

		if (isVertex)	{ glAttachShader(this->shaderProgramId, this->vertexShaderID); }
		if (isFragment) { glAttachShader(this->shaderProgramId, this->fragmentShaderID); }
		if (isGeometry) { glAttachShader(this->shaderProgramId, this->fragmentShaderID); }

		glLinkProgram(this->shaderProgramId);
		glGetProgramiv(this->shaderProgramId, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(this->shaderProgramId, 1024, NULL, infoLog);
			std::cout << "Failed to link program due to the following reason :: \n" << infoLog << std::endl;
		}

		if (isVertex)	{ glDeleteShader(this->vertexShaderID); }
		if (isFragment) { glDeleteShader(this->fragmentShaderID); }
		if (isGeometry) { glDeleteShader(this->fragmentShaderID); }
	}
	else { std::cout << "Failed to link program due to there not being any new set shaders." << std::endl; }
}

void Shader::SetVert(SHADER_FROM from, const char* shader)
{
	std::string shaderCode = (from == SHADER_FROMPATH ? this->LoadShaderCode(shader) : shader);
	this->vertexShaderID = CreateVertexShader(shaderCode.c_str());
}

void Shader::SetFrag(SHADER_FROM from, const char* shader)
{
	std::string shaderCode = (from == SHADER_FROMPATH ? this->LoadShaderCode(shader) : shader);
	this->fragmentShaderID = CreateFragmentShader(shaderCode.c_str());
}

void Shader::SetGeom(SHADER_FROM from, const char* shader)
{
	std::string shaderCode = (from == SHADER_FROMPATH ? this->LoadShaderCode(shader) : shader);
	this->geometryShaderID = CreateGeometryShader(shaderCode.c_str());
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

void Shader::SetInt(const std::string& name, std::vector<int> values) const
{
	glUniform1iv(glGetUniformLocation(this->shaderProgramId, name.c_str()), values.size(), values.data());
}

void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(this->shaderProgramId, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, std::vector<float> values) const
{
	glUniform1fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), values.size(), values.data());
}

void Shader::SetVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), 1, &value[0]);
}

void Shader::SetVec2(const std::string& name, const std::vector<glm::vec2>& values) const
{
	glUniform2fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), values.size(), glm::value_ptr(values[0]));
}

void Shader::SetVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(this->shaderProgramId, name.c_str()), x, y);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), 1, &value[0]);
}

void Shader::SetVec3(const std::string& name, const std::vector<glm::vec3>& values) const
{
	glUniform3fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), values.size(), glm::value_ptr(values[0]));
}

void Shader::SetVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(this->shaderProgramId, name.c_str()), x, y, z);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), 1, &value[0]);
}

void Shader::SetVec4(const std::string& name, const std::vector<glm::vec4>& values) const
{
	glUniform4fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), values.size(), glm::value_ptr(values[0]));
}

void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(this->shaderProgramId, name.c_str()), x, y, z, w);
}

void Shader::SetMat2(const std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat2(const std::string& name, const std::vector<glm::mat2>& mats) const
{
	glUniformMatrix2fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), mats.size(), GL_FALSE, glm::value_ptr(mats[0]));
}

void Shader::SetMat3(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat3(const std::string& name, const std::vector<glm::mat3>& mats) const
{
	glUniformMatrix3fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), mats.size(), GL_FALSE, glm::value_ptr(mats[0]));
}

void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(const std::string& name, const std::vector<glm::mat4>& mats) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->shaderProgramId, name.c_str()), mats.size(), GL_FALSE, glm::value_ptr(mats[0]));
}

std::string Shader::LoadShaderCode(const char* path)
{
	std::string shaderCode;
	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		shaderFile.open(path);
		std::stringstream shaderStream;

		shaderStream << shaderFile.rdbuf();

		shaderFile.close();

		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "Failed to load shader code from " << path << " :: \n " << e.code() << std::endl;
	}

	return shaderCode;
}

unsigned int Shader::CreateVertexShader(const char* shaderCode)
{
	unsigned int shaderID;
	int success;
	char infoLog[1024];

	shaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shaderID, 1, &shaderCode, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
		std::cout << "Failed to compile a Vertex Shader :: \n " << infoLog << std::endl;
	}

	return shaderID;
}

unsigned int Shader::CreateFragmentShader(const char* shaderCode) 
{
	unsigned int shaderID;
	int success;
	char infoLog[1024];

	shaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shaderID, 1, &shaderCode, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
		std::cout << "Failed to compile a Fragment Shader :: \n " << infoLog << std::endl;
	}

	return shaderID;
}

unsigned int Shader::CreateGeometryShader(const char* shaderCode)
{
	unsigned int shaderID;
	int success;
	char infoLog[1024];

	shaderID = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(shaderID, 1, &shaderCode, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
		std::cout << "Failed to compile a Geometry Shader :: \n" << infoLog << std::endl;
	}

	return shaderID;
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
