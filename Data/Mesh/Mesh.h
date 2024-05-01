#pragma once

#include <vector>
#include <iostream>

#include <glm/glm.hpp>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/aabb.h>
#include <assimp/ai_assert.h>
#include <assimp/BaseImporter.h>

class Mesh
{
public:
	Mesh(std::vector<float> vertexData),
		Mesh(std::vector<float> vertexData, std::vector<unsigned int> indices),
		Mesh(),
		Mesh(Mesh&& other) noexcept,
		Mesh(const Mesh& other),
		~Mesh();

	void Use();

	void SetAllData(std::vector<float> data),
		SetAllData(std::vector<float> data, std::vector<unsigned int> indices);

	void AddNewVertex(), AddNewVertex(glm::dvec3 position, glm::dvec3 normal, glm::dvec2 texcoord);

	void SetVertex(unsigned int vertexIndex, glm::dvec3 position), 
		SetAllVertices(std::vector<glm::dvec3> positions);

	void SetNormal(unsigned int datasetIndex, glm::dvec3 normal), 
		SetAllNormals(std::vector<glm::dvec3> normal);

	void SetTexCoord(unsigned int datasetIndex, glm::dvec2 texcoord), 
		SetAllTexCoords(std::vector<glm::dvec2> texCoord);

	void SetAllIndices(std::vector<unsigned int> indices), DeleteAllIndices();

	// TODO : Getters and deleters for the above

	size_t GetDataSize(), GetAmountOfVertices();
	void SetAmountOfDatasets(unsigned int newDatasetAmount);

	std::vector<float> GetData();
	unsigned int GetVAO(), GetVBO(), GetEBO();

private:
	std::vector<float> data;
	unsigned int VAO, VBO;

	bool useEBO;
	unsigned int EBO;
	std::vector<unsigned int> indices;

	unsigned int datasetSize; // Stride
	void UpdateMesh(), UpdateMeshWithEBO(), UpdateMeshWithoutEBO();

	// When moving we do not want to destory our buffers
	bool deleteOnDestroy = true;
};