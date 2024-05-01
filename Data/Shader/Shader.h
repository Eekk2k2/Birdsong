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

#include <glad/glad.h>

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	Shader();
	Shader(SHADER_FROM from, const char* vertex, const char* fragment);
	Shader(const Shader& other) = default;
	Shader(Shader&& other) noexcept;
	~Shader();

	void Use();

	/// <summary>
	/// "Updates"(creates a new shader program) so this shader has all the newly 
	/// set shaders.
	/// </summary>
	void LinkProgram();

	/// <summary>
	/// Call LinkProgram() to finalize changes. These functions just sets the 
	/// shaders without creating a program from them.
	/// </summary>
	void Set(SHADER_FROM from, const char* vertex, const char* fragment), 
		SetVert(SHADER_FROM from, const char* shader), 
		SetFrag(SHADER_FROM from, const char* shader), 
		SetGeom(SHADER_FROM from, const char* shader);

	void SetBool(const std::string& name, bool value) const;

	void SetInt(const std::string& name, int value) const,
		SetInt(const std::string& name, std::vector<int> values) const;

	void SetFloat(const std::string& name, float value) const,
		SetFloat(const std::string& name, std::vector<float> values) const;

	void SetVec2(const std::string& name, const glm::vec2& value) const,
		SetVec2(const std::string& name, const std::vector<glm::vec2>& values) const;

	void SetVec2(const std::string& name, float x, float y) const,
		SetVec2(const std::string& name, std::vector<float[2]> values) const;

	void SetVec3(const std::string& name, const glm::vec3& value) const,
		SetVec3(const std::string& name, const std::vector<glm::vec3>& values) const;

	void SetVec3(const std::string& name, float x, float y, float z) const,
		SetVec3(const std::string& name, std::vector<float[3]> values) const;

	void SetVec4(const std::string& name, const glm::vec4& value) const,
		SetVec4(const std::string& name, const std::vector<glm::vec4>& values) const;

	void SetVec4(const std::string& name, float x, float y, float z, float w) const,
		SetVec4(const std::string& name, std::vector<float[4]> values) const;

	void SetMat2(const std::string& name, const glm::mat2& mat) const, 
		SetMat2(const std::string& name, const std::vector<glm::mat2>& mats) const;

	void SetMat3(const std::string& name, const glm::mat3& mat) const, 
		SetMat3(const std::string& name, const std::vector<glm::mat3>& mats) const;

	void SetMat4(const std::string& name, const glm::mat4& mat) const,
		SetMat4(const std::string& name, const std::vector<glm::mat4>& mats) const;

private:
	const char* vertexShaderCodeError = R"(
		#version 430 core
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
		#version 430 core
		out vec4 FragColor;

		void main()
		{
			FragColor = vec4(0.9453125f, 0.140625f, 0.87890625f, 0.0f);
		}
		)";

	
	std::string LoadShaderCode(const char* path);

	unsigned int CreateVertexShader(const char* shaderCode),
		CreateFragmentShader(const char* shaderCode), 
		CreateGeometryShader(const char* shaderCode);

	int CreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);

	void CreateShaderFromPath(const char* vertexPath, const char* fragmentPath);
	void CreateShaderFromCode(const char* vertexCode, const char* fragmentCode);

	unsigned int fragmentShaderID, vertexShaderID, geometryShaderID, shaderProgramId;
	bool destroyOnDestruct;
};

#endif
