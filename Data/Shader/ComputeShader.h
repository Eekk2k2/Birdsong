#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

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

	void Set(SHADER_FROM from, const char* compute);
private:
	void CreateShaderFromCode(const char* computeCode), CreateShaderFromPath(const char* computePath);
};

