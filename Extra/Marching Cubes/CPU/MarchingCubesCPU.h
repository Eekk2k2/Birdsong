#pragma once
#include <vector>
#include <iostream>

#include <glm/glm.hpp>

#include "..\..\..\Libraries\OpenSimplexNoise.h"
#include "..\..\..\Data\Mesh.h"

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

