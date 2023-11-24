#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#ifndef SHADER_FROM
#ifndef SHADER_FROMCODE
#define SHADER_FROMCODE 0
#endif // !FROMCODE

#ifndef SHADER_FROMPATH
#define SHADER_FROMPATH 1
#endif // !FROMPATH

typedef int SHADER_FROM;
#endif

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm.hpp>

class ComputeShader
{
public:
	unsigned int shaderProgramId;

	ComputeShader(SHADER_FROM from, const char* compute);
	~ComputeShader();

	void Use(GLuint x, GLuint y, GLuint z);


	void Set(SHADER_FROM from, const char* compute);

	void SetBool	(const std::string& name, bool value)							const;

	void SetInt		(const std::string& name, int value)							const;

	void SetFloat	(const std::string& name, float value)							const;

	void SetVec2	(const std::string& name, const glm::vec2& value)				const;

	void SetVec2	(const std::string& name, float x, float y)						const;

	void SetVec3	(const std::string& name, const glm::vec3& value)				const;

	void SetVec3	(const std::string& name, float x, float y, float z)			const;

	void SetVec4	(const std::string& name, const glm::vec4& value)				const;

	void SetVec4	(const std::string& name, float x, float y, float z, float w)	const;

	void SetMat2	(const std::string& name, const glm::mat2& mat)					const;

	void SetMat3	(const std::string& name, const glm::mat3& mat)					const;

	void SetMat4	(const std::string& name, const glm::mat4& mat)					const;

	
	void AddShaderStorageBuffer(std::string bufferName, GLsizeiptr size, int bufferBaseIndex), 
		AddShaderStorageBuffer(std::string bufferName, GLsizeiptr size, const void* data, int bufferBaseIndex);

	void GetShaderStorageBufferSubData(GLuint ShaderStorageBufferObject, GLintptr offset, GLsizeiptr size, void* data);

	GLuint GetShaderStorageBuffer(int index), GetShaderStorageBuffer(std::string bufferName);

private:
	void CreateShaderFromCode(const char* computeCode), CreateShaderFromPath(const char* computePath);

	std::vector<unsigned int> shaderStorageBuffers;
	std::vector<std::string> shaderStorageBufferNames;
};

