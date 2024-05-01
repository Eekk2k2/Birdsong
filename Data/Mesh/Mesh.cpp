#include "Mesh.h"

Mesh::Mesh(std::vector<float> _data)
{
	/* Generate buffers */

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	SetAllData(_data);
}

Mesh::Mesh(std::vector<float> _data, std::vector<unsigned int> indices) 
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
	this->data = std::vector<float>();

	/* Generate buffers */

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);
}

Mesh::Mesh(Mesh&& other) noexcept 
	: data(std::move(other.data)), VAO(std::move(other.VAO)), VBO(std::move(other.VBO)), 
		useEBO(std::move(other.useEBO)), EBO(std::move(other.EBO)), indices(std::move(other.indices)),
			datasetSize(std::move(other.datasetSize))
				{
					other.deleteOnDestroy = false;
				}

Mesh::Mesh(const Mesh& other) :data(other.data), VAO(other.VAO), VBO(other.VBO),
	useEBO(other.useEBO), EBO(other.EBO), indices(other.indices),
		datasetSize(other.datasetSize) {}


Mesh::~Mesh() 
{
	if (!deleteOnDestroy) { return; }

	// Deletes buffers
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
	
}

void Mesh::Use()
{
	glBindVertexArray(this->GetVAO());
}

void Mesh::SetAllData(std::vector<float> data)
{
	this->data = data;
	
	this->useEBO = false;
	this->UpdateMesh();
}

void Mesh::SetAllData(std::vector<float> data, std::vector<unsigned int> indices)
{
	this->data = data;
	this->indices = indices;

	this->useEBO = true;
	this->UpdateMesh();
}

void Mesh::AddNewVertex()
{
	data.push_back(0.0);
	data.push_back(0.0);
	data.push_back(0.0);

	data.push_back(0.0);
	data.push_back(0.0);
	data.push_back(0.0);

	data.push_back(0.0);
	data.push_back(0.0);
}

void Mesh::AddNewVertex(glm::dvec3 position, glm::dvec3 normal, glm::dvec2 texcoord)
{
	data.push_back(position.x);
	data.push_back(position.y);
	data.push_back(position.z);

	data.push_back(normal.x);
	data.push_back(normal.y);
	data.push_back(normal.z);

	data.push_back(texcoord.x);
	data.push_back(texcoord.y);
}

size_t Mesh::GetDataSize()
{
	return this->data.size();
}

void Mesh::SetAmountOfDatasets(unsigned int newDatasetAmount)
{
	this->data.resize(newDatasetAmount * 8);
}

size_t Mesh::GetAmountOfVertices()
{
	return this->data.size() / datasetSize;
}

void Mesh::SetVertex(unsigned int datasetIndex, glm::dvec3 position)
{
	if (datasetIndex >= GetAmountOfVertices()) { std::cout << "Dataset index out of bounds." << std::endl; return; }

	data[datasetIndex * datasetSize    ] = position.x;
	data[datasetIndex * datasetSize + 1] = position.y;
	data[datasetIndex * datasetSize + 2] = position.z;

	UpdateMesh();
}

void Mesh::SetNormal(unsigned int datasetIndex, glm::dvec3 normal)
{
	if (datasetIndex >= GetAmountOfVertices()) { std::cout << "Dataset index out of bounds." << std::endl; return; }

	data[datasetIndex * datasetSize     + 3] = normal.x;
	data[datasetIndex * datasetSize + 1 + 3] = normal.y;
	data[datasetIndex * datasetSize + 2 + 3] = normal.z;

	UpdateMesh();
}

void Mesh::SetTexCoord(unsigned int datasetIndex, glm::dvec2 texCoord)
{
	if (datasetIndex >= GetAmountOfVertices()) { std::cout << "Dataset index out of bounds." << std::endl; return; }

	data[datasetIndex * datasetSize     + 6] = texCoord.x;
	data[datasetIndex * datasetSize + 1 + 6] = texCoord.y;

	UpdateMesh();
}

void Mesh::SetAllVertices(std::vector<glm::dvec3> positions)
{
	// Resize
	SetAmountOfDatasets(positions.size());

	// Set data
	for (size_t i = 0; i < positions.size(); i+=datasetSize)
	{
		data[i * datasetSize]		= positions[i].x;
		data[i * datasetSize + 1]	= positions[i].y;
		data[i * datasetSize + 2]	= positions[i].z;
	}

	UpdateMesh();
}

void Mesh::SetAllNormals(std::vector<glm::dvec3> normals)
{
	// Resize
	SetAmountOfDatasets(normals.size());

	// Set data
	for (size_t i = 0; i < normals.size(); i += datasetSize)
	{
		data[i * datasetSize + 3] = normals[i].x;
		data[i * datasetSize + 1 + 3] = normals[i].y;
		data[i * datasetSize + 2 + 3] = normals[i].z;
	}

	UpdateMesh();
}

void Mesh::SetAllTexCoords(std::vector<glm::dvec2> texcoords)
{
	// Resize
	SetAmountOfDatasets(texcoords.size());

	// Set data
	for (size_t i = 0; i < texcoords.size(); i += datasetSize)
	{
		data[i * datasetSize + 6] = texcoords[i].x;
		data[i * datasetSize + 1 + 6] = texcoords[i].y;
	}

	UpdateMesh();
}

void Mesh::SetAllIndices(std::vector<unsigned int> indices)
{
	this->useEBO = true;
	this->indices = indices;

	UpdateMesh();
}

void Mesh::DeleteAllIndices()
{
	this->useEBO = false;
	this->indices.clear();

	UpdateMesh();
}

std::vector<float> Mesh::GetData()
{
	return this->data;
}

unsigned int Mesh::GetVBO()
{
	return this->VBO;
}

unsigned int Mesh::GetVAO()
{
	return this->VAO;
}

unsigned int Mesh::GetEBO()
{
	return this->EBO;
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->data.size(), this->data.data(), GL_DYNAMIC_DRAW);

	// Bind the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);

	// Update or set the data in the element array buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * this->indices.size(), this->indices.data(), GL_DYNAMIC_DRAW);

	// Update the VAO to use this new buffer
	datasetSize = 8;

	glBindVertexArray(this->VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, datasetSize * sizeof(float), (void*)0); // Vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, datasetSize * sizeof(float), (void*)(3 * sizeof(float))); // Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, datasetSize * sizeof(float), (void*)(6 * sizeof(float))); // Tex
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->data.size(), this->data.data(), GL_DYNAMIC_DRAW);

	// Bind the EBO and clear it
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

	// Update the VAO to use this new buffer
	datasetSize = 8;

	glBindVertexArray(this->VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, datasetSize * sizeof(float), (void*)0); // Vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, datasetSize * sizeof(float), (void*)(3 * sizeof(float))); // Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, datasetSize * sizeof(float), (void*)(6 * sizeof(float))); // Tex
	glEnableVertexAttribArray(2);

	// Unbind the buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
