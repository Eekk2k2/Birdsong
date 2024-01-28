#include "Element.h"

Element::Element()
{
	position = glm::vec2(0, 0);
	rotation = glm::vec2(0, 0);

	// Create the mesh
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	// Data
	float data[4] = { 0.0, 0.0, 0.0, 0.0 };

	// Bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	// Generate a new buffer for the vertex data
	glBufferData(GL_ARRAY_BUFFER, sizeof(double) * 4, data, GL_STATIC_DRAW);

	// Update the VAO to use this new buffer
	glBindVertexArray(this->VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(double), (void*)0); // Vertex
	glEnableVertexAttribArray(0);

	// Unbind the buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Create the shader program
	
	this->elementShader = std::make_shared<Shader>(SHADER_FROMCODE, vertexShaderCodeElement, fragmentShaderCodeElement);
}

Element::~Element() { }

void Element::Draw(int z)
{
	this->elementShader->Use();
	this->elementShader->SetMat4("model", glm::mat4(1.0f));

	float aspect = (float)1920.0f / 1080.0f;
	this->elementShader->SetMat4("perspective", glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 100.0f));

	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
