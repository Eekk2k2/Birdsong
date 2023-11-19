#pragma once
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include "..\..\..\Libraries\OpenSimplexNoise.hpp" // Credit to Mark A. Ropper

#ifndef SIDE_FRONT
#define SIDE_FRONT		glm::vec3(90, 0, 0)
#endif // !SIDE_FRONT

#ifndef SIDE_BACK
#define SIDE_BACK		glm::vec3(-90, 0, 0)
#endif // !SIDE_BACK

#ifndef SIDE_RIGHT
#define SIDE_RIGHT		glm::vec3(0, 0, -90)
#endif // !SIDE_RIGHT

#ifndef SIDE_LEFT
#define SIDE_LEFT		glm::vec3(0, 0, 990)
#endif // !SIDE_LEFT

#ifndef SIDE_TOP
#define SIDE_TOP		glm::vec3(0, 0, 0)
#endif // !SIDE_TOP

#ifndef SIDE_BOTTOM
#define SIDE_BOTTOM		glm::vec3(180, 0, 0)
#endif // !SIDE_BOTTOM

typedef glm::vec3		SIDE;

static class PlanetMesh
{
public:
	static std::vector<double> Generate();
private:
	static glm::dvec3 NormalizeDistance(glm::dvec3 from, glm::dvec3 to);

	static glm::dvec3 PointOnSphereToPlanet(glm::dvec3 point);

	static std::vector<glm::dvec3> CreateSide();

	static std::vector<glm::dvec3> CreateSideChunk(glm::dvec2 gridPos);

};

