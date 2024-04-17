#pragma once
#include <unordered_map>
#include <string>
#include <vector>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/common.hpp>

#include "..\Objects\Lights\Light.h"
class Light;

class PointLight : public Light
{
public:
	PointLight();
	~PointLight();

	void Render(std::unordered_map<std::string, PipelineElement>& m_renderPipelineList) override;

	int GetDepthMap() override;
	std::size_t GetLightSpaceMatrixSize() override;
	std::vector<glm::mat4> GetLightSpaceMatrix() override;
	glm::mat4 GetLightProjection() override;

	glm::uvec2 shadowResolution;
	glm::vec2 renderPlanes;
private:
	unsigned int depthMapFBO, depthCubemap;
	Material depthMaterial;
	glm::mat4 shadowProjection;
	std::vector<glm::mat4> shadowTransforms;
};

