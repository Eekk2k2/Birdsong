#pragma once
#include <vector>
#include <iostream>

#include <glm/glm.hpp>

#include "..\..\..\Libraries\OpenSimplexNoise.h"
#include "..\..\..\Data\Mesh\Mesh.h"

struct GridCell
{
public:
	GridCell(glm::dvec4 gridCellIndex) {
		point[0] = glm::dvec4(0.0f, 0.0f, 0.0f, 0.0f) + gridCellIndex;
		point[1] = glm::dvec4(1.0f, 0.0f, 0.0f, 0.0f) + gridCellIndex;
		point[2] = glm::dvec4(1.0f, 0.0f, 1.0f, 0.0f) + gridCellIndex;
		point[3] = glm::dvec4(0.0f, 0.0f, 1.0f, 0.0f) + gridCellIndex;
		point[4] = glm::dvec4(0.0f, 1.0f, 0.0f, 0.0f) + gridCellIndex;
		point[5] = glm::dvec4(1.0f, 1.0f, 0.0f, 0.0f) + gridCellIndex;
		point[6] = glm::dvec4(1.0f, 1.0f, 1.0f, 0.0f) + gridCellIndex;
		point[7] = glm::dvec4(0.0f, 1.0f, 1.0f, 0.0f) + gridCellIndex;
	}

	glm::dvec4 point[8];
};

class MarchingCubesCPU
{
public:
	// Generate Flat Chunk
	static std::vector<double> GenerateFlatChunk(glm::ivec2 gridPos, uint16_t resolution, uint16_t height, std::vector<std::vector<int>> triangleTable, std::vector<int> edgeTable);
	
	// Generate Round Chunk
private:
	static double SampleFlatPoint(glm::dvec3 point);

	static glm::dvec3 InterpolatePoints(double level, glm::dvec4 point1, glm::dvec4 point2);

	static int CalculateGridIndex(GridCell grid, float level);

	static glm::dvec3 GenerateNormal(glm::dvec3 point1, glm::dvec3 point2, glm::dvec3 point3);

	static std::vector<double> Polygonise(GridCell gridCell, double level, std::vector<std::vector<int>> triangleTable, std::vector<int> edgeTable);

};

// FOr GPU

//	// Compute Shader
//marchingCubesNoiseComputeShader = std::make_unique<ComputeShader>(SHADER_FROMPATH, ".\\Assets\\Shaders\\Compute\\MarchingCubesNoise.comp");
//marchingCubesNoiseComputeShader->AddShaderStorageBuffer("field", sizeof(float) * 32768, 0);
//marchingCubesNoiseComputeShader->Use(4, 8, 4); // Local group is 4 2 4 resulting in total: 16 16 16
//
//float field[4096][8];
//GLuint fieldBuffer = marchingCubesNoiseComputeShader->GetShaderStorageBuffer("field");
//marchingCubesNoiseComputeShader->GetShaderStorageBufferSubData(fieldBuffer, 0, sizeof(float) * 32768, field);
//
//marchingCubesMeshComputeShader = std::make_unique<ComputeShader>(SHADER_FROMPATH, ".\\Assets\\Shaders\\Compute\\MarchingCubesMesh.comp");
//// IN - Should probably be using UBOs !SSBOs
//marchingCubesMeshComputeShader->AddShaderStorageBuffer("field", sizeof(float) * 32768, field, 0);
//marchingCubesMeshComputeShader->AddShaderStorageBuffer("triangle", sizeof(int) * 4096, triangleTable, 1);
//
//// OUT
//marchingCubesMeshComputeShader->AddShaderStorageBuffer("point", sizeof(double) * 15 * 4 * 4096, 1);
//marchingCubesMeshComputeShader->AddShaderStorageBuffer("normal", sizeof(double) * 15 * 4 * 4096, 2);
//marchingCubesMeshComputeShader->AddShaderStorageBuffer("texcoord", sizeof(double) * 15 * 2 * 4096, 3);
//
//marchingCubesMeshComputeShader->Use(4, 8, 4);
//
//double* point = new double[61440 * 4];
//double* normal = new double[61440 * 4];
//double* texcoord = new double[61440 * 2];
//
//GLuint pointBuffer = marchingCubesMeshComputeShader->GetShaderStorageBuffer("point"),
//normalBuffer = marchingCubesMeshComputeShader->GetShaderStorageBuffer("normal"),
//texcoordBuffer = marchingCubesMeshComputeShader->GetShaderStorageBuffer("texcoord");
//
//marchingCubesMeshComputeShader->GetShaderStorageBufferSubData(pointBuffer, 0, sizeof(double) * 15 * 4 * 4096, point);
//marchingCubesMeshComputeShader->GetShaderStorageBufferSubData(normalBuffer, 0, sizeof(double) * 15 * 4 * 4096, normal);
//marchingCubesMeshComputeShader->GetShaderStorageBufferSubData(texcoordBuffer, 0, sizeof(double) * 15 * 2 * 4096, texcoord);
//
//camera = std::make_shared<Camera>(applicationWindow);
//mainObject = std::make_unique<MainObject>(camera);
//mainObject->transform->position.position = glm::vec3(0.0f, 0.0f, 0.0f);
//mainObject->transform->rotation.rotation = glm::vec3(0.0f, 45.0f, 0.0f);	// DOESNT WORK
//mainObject->transform->scale.scale = glm::vec3(3.0f, 1.0f, 1.0f);			// DOESNT WORK
//
//delete[] point;
//delete[] normal;
//delete[] texcoord;