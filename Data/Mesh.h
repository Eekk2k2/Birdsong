#pragma once
#include <vector>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Mesh
{
public:
	Mesh(std::vector<double> vertexData),												
		Mesh(std::vector<double> vertexData, std::vector<unsigned int> indices),		
		Mesh(),																			
		~Mesh();

	void SetAllData(std::vector<double> vertexData),									
		SetAllData(std::vector<double> vertexData, std::vector<unsigned int> indices);	

	size_t GetDataSize();

	std::vector<double> GetData();
	unsigned int GetVAO(), GetVBO();

private:
	std::vector<double> data;
	unsigned int VAO, VBO;

	bool useEBO;
	unsigned int EBO;
	std::vector<unsigned int> indices;

	void UpdateMesh(), UpdateMeshWithEBO(), UpdateMeshWithoutEBO();
};

