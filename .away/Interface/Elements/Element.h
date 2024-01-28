#pragma once
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "..\..\Shader\Shader.h"

/* 
	Each elemend DOES NOT NEED its own mesh(VAO), just create one in 
	container and pass the VAO down.
*/

class Element
{
public:
	Element(), ~Element();
	
	glm::vec2 position;
	glm::vec2 rotation;

	/// <summary>
	/// Z as a draw input as it may be dynamic
	/// </summary>
	/// <param name="z"></param>
	void Draw(int z);
private:
	GLuint VAO, VBO;
	std::shared_ptr<Shader> elementShader;

	const char* vertexShaderCodeElement = R"(
		#version 430 core

		uniform mat4 model;
		uniform mat4 perspective;

		void main() {
			vec3 position = vec3(0.0);

			if (gl_VertexID == 0) {
				position.x = 0.0;
				position.y = 0.0;				
			} else if (gl_VertexID == 1) {
				position.x = 1.0;
				position.y = 0.0;				
			} else if (gl_VertexID == 2) {
				position.x = 0.0;
				position.y = 1.0;				
			} else if (gl_VertexID == 3) {
				position.x = 1.0;
				position.y = 1.0;				
			} 


			//position.x = floor(gl_VertexID / 2.0);
			//position.y = mod(gl_VertexID, 2);

			

			gl_Position = perspective * vec4(position, 1.0);
		}
		)";

	const char* fragmentShaderCodeElement = R"(
		#version 430 core
		out vec4 FragColor;

		void main() {
			FragColor = vec4(1.0);
		}
		)";
};

