#pragma once
// Chunk size is 32x32

#include <memory>

#include "..\..\..\..\Data\Shader\ComputeShader.h"
#include "..\..\..\..\Data\Mesh\Mesh.h"

class Heightmap_GPU
{
public:
	void GenerateChunk();

	std::vector<glm::dvec3> positions;
	std::vector<unsigned int> indices;
private:
	/// <summary>
	/// The compute shader we get the mesh data from.
	/// </summary>
	std::unique_ptr<ComputeShader> heightmapGPUComp;

	/// <summary>
	/// The compute shader we get the mesh data from.
	/// </summary>
	//std::unique_ptr<ComputeShader> erosionGPUComp;

	/// <summary>
	/// Tesselation shader for smaller height details
	/// </summary>
	//std::unique_ptr<TesselationShader> smallerHeightDetailsTess;


};

