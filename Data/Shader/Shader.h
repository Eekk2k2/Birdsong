#pragma once

// endif at the end of file
#ifndef SHADER_H
#define SHADER_H

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

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	Shader();
	Shader(SHADER_FROM from, const char* vertex, const char* fragment);
	~Shader();

	unsigned int shaderProgramId;

	void Use();

	void Set(SHADER_FROM from, const char* vertex, const char* fragment);

	void SetBool(const std::string& name, bool value) const;

	void SetInt(const std::string& name, int value) const;

	void SetFloat(const std::string& name, float value) const;

	void SetVec2(const std::string& name, const glm::vec2& value) const;

	void SetVec2(const std::string& name, float x, float y) const;

	void SetVec3(const std::string& name, const glm::vec3& value) const;

	void SetVec3(const std::string& name, float x, float y, float z) const;

	void SetVec4(const std::string& name, const glm::vec4& value) const;

	void SetVec4(const std::string& name, float x, float y, float z, float w) const;

	void SetMat2(const std::string& name, const glm::mat2& mat) const;

	void SetMat3(const std::string& name, const glm::mat3& mat) const;

	void SetMat4(const std::string& name, const glm::mat4& mat) const;

private:
	const char* vertexShaderCodeError = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;

		uniform mat4 projection;
		uniform mat4 view;
		uniform mat4 model;

		out vec2 TexCoord;

		void main() {
			gl_Position = projection * view * vec4(aPos, 1.0);
		}
		)";

	const char* fragmentErrorShaderCode = R"(
		#version 330 core
		out vec4 FragColor;

		void main()
		{
			FragColor = vec4(0.9453125f, 0.140625f, 0.87890625f, 0.0f);
		}
		)";

	unsigned int CreateVertexShader(const char* vertexShaderCode);
	unsigned int CreateFragmentShader(const char* fragmetnShaderCode);

	int CreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);

	void CreateShaderFromPath(const char* vertexPath, const char* fragmentPath);

	void CreateShaderFromCode(const char* vertexCode, const char* fragmentCode);
};

#endif
