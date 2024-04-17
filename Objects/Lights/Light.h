#pragma once

#include <unordered_map>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/common.hpp>

#include "..\Data\Holder\RenderPipeline\PipelineElement.h"
struct PipelineElement;
#include "..\Data\Material\Material.h"
class Material;
#include "..\Objects\Objectoid.h"

class Light : public Objectoid
{
public:
	Light();
	~Light();

	virtual void Render(std::unordered_map<std::string, PipelineElement>& m_renderPipelineList) = 0;
	virtual int GetDepthMap() = 0;

	virtual std::size_t GetLightSpaceMatrixSize() = 0;
	virtual std::vector<glm::mat4> GetLightSpaceMatrix() = 0;
	virtual glm::mat4 GetLightProjection() = 0;
private:

};

//class Light
//{
//public:
//	Light(),
//		Light(Light&& other) noexcept;
//	~Light();
//
//	glm::uvec2 shadowResolution;
//	glm::vec2 renderPlanes;
//
//	glm::vec3 lightPosition, lightColor;
//	glm::mat4 lightProjection, lightView, lightSpaceMatrix;
//
//	void Render(std::unordered_map<std::string, RenderPipelineMaterialElement>& m_renderPipelineList);
//
//	unsigned int GetDepthMap(), GetDepthMapFBO();
//
//	bool deleteOnDestroy = true;
//
//private:
//	unsigned int depthMapFBO, depthMap;
//	std::shared_ptr<Material> depthMaterial;
//};