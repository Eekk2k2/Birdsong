#include "PlanetMesh.h"

std::vector<double> PlanetMesh::Generate()
{
    std::vector<glm::dvec3> vertices = std::vector<glm::dvec3>();

    // Create data vector and return
    // ...

    return std::vector<double>();
}

glm::dvec3 PlanetMesh::NormalizeDistance(glm::dvec3 from, glm::dvec3 to)
{
    return from / glm::distance(from, to);
}

glm::dvec3 PlanetMesh::PointOnSphereToPlanet(glm::dvec3 point)
{
    return glm::dvec3();
}

std::vector<glm::dvec3> PlanetMesh::CreateSide()
{
    return std::vector<glm::dvec3>();
}

std::vector<glm::dvec3> PlanetMesh::CreateSideChunk(glm::dvec2 gridPos)
{
    uint32_t chunkResolution = 16;
    uint32_t rawChunkResolution = chunkResolution + 1;

    uint32_t meshResolution = 16;
    uint32_t rawMeshResolution = meshResolution + 1;
    uint32_t quadResolution = meshResolution;

    // Create Vertices
    long amountVertices = (long)glm::pow(rawMeshResolution, 2);
    std::vector<glm::dvec3> vertices = std::vector<glm::dvec3>();
    
    // Not the final radius
    double radius = rawChunkResolution * meshResolution;
    for (unsigned long y = 0, i = 0; y < rawMeshResolution; y++)
    {
        for (unsigned long x = 0; x < rawMeshResolution; x++)
        {
            glm::dvec3 pointOnCube = glm::dvec3(
                (gridPos.x * meshResolution) + x -  radius,
                                                    radius,
                (gridPos.y * meshResolution) + y -  radius
            );

            glm::dvec3 pointOnSphere = NormalizeDistance(pointOnCube, glm::dvec3(0.0f, 0.0f, 0.0f));
            glm::dvec3 pointOnPlanet = PointOnSphereToPlanet(pointOnSphere);
            vertices.push_back(pointOnPlanet);
        }
    }

    return vertices;
}
