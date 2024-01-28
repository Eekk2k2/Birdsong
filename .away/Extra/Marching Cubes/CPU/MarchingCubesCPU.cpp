#include "MarchingCubesCPU.h"

std::vector<double> MarchingCubesCPU::GenerateFlatChunk(glm::ivec2 gridPos, uint16_t resolution, uint16_t height, std::vector<std::vector<int>> triangleTable, std::vector<int> edgeTable)
{
	std::vector<double> data;

	double lowest = 100000, highest = -10000;

	for (size_t z = 0; z < height; z++)
		for (size_t y = 0; y < resolution; y++)
			for (size_t x = 0; x < resolution; x++)
			{
				double value = SampleFlatPoint(glm::dvec3(x + gridPos.x, y, z + gridPos.y));

				if (value > highest) highest = value;
				if (value < lowest) lowest = value;

				GridCell currentGridCell = GridCell(glm::dvec4(x, y, z, value));
				std::vector<double> _data = Polygonise(currentGridCell, 0.5f, triangleTable, edgeTable);

				for (size_t i = 0; i < _data.size(); i++)
					data.push_back(_data[i]);
			}

	return data;	
}

double MarchingCubesCPU::SampleFlatPoint(glm::dvec3 point)
{
	OpenSimplexNoise::Noise noise;
	return noise.eval(point.x, point.y, point.z);
}

int MarchingCubesCPU::CalculateGridIndex(GridCell grid, float level)
{
	int gridIndex = 0;
	for (size_t i = 0; i < 8; i++) if (grid.point[i].w < level) gridIndex |= 1 << i;

	return gridIndex;
}

glm::dvec3 MarchingCubesCPU::GenerateNormal(glm::dvec3 point1, glm::dvec3 point2, glm::dvec3 point3)
{
	glm::dvec3 a = point2 - point1;
	glm::dvec3 b = point3 - point1;
	return glm::dvec3(a.y * b.z - a.z * b.y, a.z * b.x - a.y * b.z, a.x * b.y - a.y * b.x);
}

std::vector<double> MarchingCubesCPU::Polygonise(GridCell gridCell, double level, std::vector<std::vector<int>> triangleTable, std::vector<int> edgeTable)
{
	int gridIndex = CalculateGridIndex(gridCell, level);

	std::vector<int> triangulation;
	for (size_t i = 0; triangleTable[gridIndex][i] != -1; i++)
		triangulation.push_back(triangleTable[gridIndex][i]);

	std::vector<double> data;

	for (size_t i = 0; i < triangulation.size(); i++)
	{
		int edgeIndex = triangulation[i];

		int indexA = edgeIndex % 8,
			indexB = (edgeIndex == 3 ? 0 : (edgeIndex == 7 ? 4 : (edgeIndex < 8 ? edgeIndex + 1 : ((indexA + 4)))));

		glm::dvec3 pointA = gridCell.point[indexA];
		glm::dvec3 pointB = gridCell.point[indexB];

		glm::dvec3 point = (pointA + pointB) / (double)2.0f;

		// Append data
		data.push_back(point.x);
		data.push_back(point.y);
		data.push_back(point.z);

		data.push_back(0.0f);
		data.push_back(0.0f);
		data.push_back(0.0f);

		data.push_back(point.x);
		data.push_back(point.z);
	}

	glm::dvec3 normal;
	for (size_t i = 0; i < triangulation.size(); i += 24)
	{
		normal = GenerateNormal(glm::vec3(data[i], data[i + 1], data[i + 2]), glm::vec3(data[i + 8], data[i + 9], data[i + 10]), glm::vec3(data[i + 16], data[i + 17], data[i + 18]));

		data[i + 3] = normal.x;		data[i + 4] = normal.y;		data[i + 5] = normal.z;
		data[i + 11] = normal.x;	data[i + 12] = normal.y;	data[i + 13] = normal.z;
		data[i + 19] = normal.x;	data[i + 20] = normal.y;	data[i + 21] = normal.z;
	}

	return data;
}






//
//glm::dvec3 MarchingCubesCPU::InterpolatePoints(double level, glm::dvec4 point1, glm::dvec4 point2)
//{
//	if (glm::abs(level - point1.w) < 0.00001)		return glm::dvec3(point1.x, point1.z, point1.z);
//	if (glm::abs(level - point2.w) < 0.00001)		return glm::dvec3(point2.x, point2.z, point2.z);
//	if (glm::abs(point1.w - point2.w) < 0.00001)	return glm::dvec3(point1.x, point1.z, point1.z);
//
//	double mu = (level - point1.w) / (point2.w - point1.w);
//	return glm::vec3
//	(
//		point1.x + mu * (point2.x - point1.x),
//		point1.y + mu * (point2.y - point1.y),
//		point1.z + mu * (point2.z - point1.z)
//	);
//}
//

