#include "Mesh.h"
#include <iostream>

Mesh::Mesh(std::vector<double> _data)
{
	/* Generate buffers */

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	SetAllData(_data);
}

Mesh::Mesh(std::vector<double> _data, std::vector<unsigned int> indices) 
{
	/* Generate buffers */

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	SetAllData(_data, indices);
}

Mesh::Mesh()
{
	// Populates this->vertexData from empty
	this->data = std::vector<double>();

	/* Generate buffers */

	// VAO
	glGenVertexArrays(1, &this->VAO);

	// VBO
	glGenBuffers(1, &this->VBO);
}

Mesh::~Mesh() 
{
	// Deletes buffers
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
}

void Mesh::SetAllData(std::vector<double> _data)
{
	this->data = _data;
	
	this->useEBO = false;
	this->UpdateMesh();
}

void Mesh::SetAllData(std::vector<double> vertexData, std::vector<unsigned int> indices)
{
	this->data = data;
	this->indices = indices;

	this->useEBO = true;
	this->UpdateMesh();
}

size_t Mesh::GetDataSize()
{
	return this->data.size();
}

std::vector<double> Mesh::GetData()
{
	return this->data;
}

unsigned int Mesh::GetVBO()
{
	return this->VBO;
}

void Mesh::UpdateMesh()
{
	if (this->useEBO)	UpdateMeshWithEBO();
	else				UpdateMeshWithoutEBO();
}

void Mesh::UpdateMeshWithEBO()
{
	// Bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	// Update or set the data in the vertex array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(double) * this->data.size(), this->data.data(), GL_DYNAMIC_DRAW);

	// Bind the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

	// Update or set the data in the element array buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * this->indices.size(), this->indices.data(), GL_DYNAMIC_DRAW);

	// Update the VAO to use this new buffer
	glBindVertexArray(this->VAO);
	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 8 * sizeof(double), (void*)0); // Vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 8 * sizeof(double), (void*)(3 * sizeof(double))); // Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_DOUBLE, GL_FALSE, 8 * sizeof(double), (void*)(6 * sizeof(double))); // Tex
	glEnableVertexAttribArray(2);

	// Unbind the buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::UpdateMeshWithoutEBO()
{
	// Bind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

	// Generate a new buffer for the vertex data
	glBufferData(GL_ARRAY_BUFFER, sizeof(double) * this->data.size(), this->data.data(), GL_DYNAMIC_DRAW);

	// Bind the EBO and clear it
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

	// Update the VAO to use this new buffer
	glBindVertexArray(this->VAO);
	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 8 * sizeof(double), (void*)0); // Vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 8 * sizeof(double), (void*)(3 * sizeof(double))); // Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_DOUBLE, GL_FALSE, 8 * sizeof(double), (void*)(6 * sizeof(double))); // Tex
	glEnableVertexAttribArray(2);

	// Unbind the buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

unsigned int Mesh::GetVAO()
{
	return this->VAO;
}
