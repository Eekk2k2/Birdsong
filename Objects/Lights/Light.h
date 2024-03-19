#pragma once

#include <memory>
#include <unordered_map>

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/common.hpp>

#include "..\Data\Material\Material.h"
#include "..\Data\Holder\RenderPipeline\RenderPipelineElements.h"

class Light
{
public:
	Light(),
		Light(Light&& other) noexcept;
	~Light();

	glm::uvec2 shadowResolution;
	glm::vec2 renderPlanes;

	glm::vec3 lightPosition, lightColor;
	glm::mat4 lightProjection, lightView, lightSpaceMatrix;

	void Render(std::unordered_map<std::string, RenderPipelineMaterialElement>& m_renderPipelineList);

	unsigned int GetDepthMap(), GetDepthMapFBO();

	bool deleteOnDestroy = true;

private:
	unsigned int depthMapFBO, depthMap;
	std::shared_ptr<Material> depthMaterial;
};

