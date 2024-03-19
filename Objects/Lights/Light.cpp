#include "Light.h"

Light::Light()
{
	// Settings
	this->shadowResolution = glm::uvec2(4096, 4096);
	this->renderPlanes = glm::uvec2(1.0f, 15.0f);
	this->lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

	// Default settings, dont touch
	this->lightPosition = glm::vec3(0.0f, 0.0f, 0.0f);

	// Depth material
	this->depthMaterial = std::make_shared<Material>();
	this->depthMaterial->shader->Set(SHADER_FROMPATH, ".\\Assets\\Shaders\\defaultDepth.vert", ".\\Assets\\Shaders\\defaultDepth.frag");

	// Framebuffer
	glGenFramebuffers(1, &this->depthMapFBO);

	glGenTextures(1, &this->depthMap);
	glBindTexture(GL_TEXTURE_2D, this->depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, this->shadowResolution.x, this->shadowResolution.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glBindFramebuffer(GL_FRAMEBUFFER, this->depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->depthMap, 0);
	//glDrawBuffer(GL_NONE);
	//glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Light::Light(Light&& other) noexcept : depthMaterial(std::move(other.depthMaterial))
{
	other.deleteOnDestroy = false;

	this->shadowResolution = other.shadowResolution;
	this->renderPlanes = other.renderPlanes;

	this->lightPosition = other.lightPosition;
	this->lightColor = other.lightColor;

	this->lightProjection = other.lightProjection;
	this->lightView = other.lightView;
	this->lightSpaceMatrix = other.lightSpaceMatrix;

	this->depthMap = other.depthMap;
	this->depthMapFBO = other.depthMapFBO;
}

Light::~Light()
{
	if (!deleteOnDestroy) { return; }

	glDeleteFramebuffers(1, &this->depthMapFBO);
	glDeleteTextures(1, &this->depthMap);
}

void Light::Render(std::unordered_map<std::string, RenderPipelineMaterialElement> &m_renderPipelineList)
{
	this->lightProjection	= glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, this->renderPlanes.x, this->renderPlanes.y);
	this->lightView			= glm::lookAt(this->lightPosition, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); 
	this->lightSpaceMatrix	= this->lightProjection * this->lightView;
	
	this->depthMaterial->Bind();
	this->depthMaterial->shader->SetMat4("lightSpaceMatrix", this->lightSpaceMatrix);

	glViewport(0, 0, this->shadowResolution.x, this->shadowResolution.y);
	glBindFramebuffer(GL_FRAMEBUFFER, this->depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, this->depthMap);
	glCullFace(GL_FRONT);

	for (auto& renderPipelineMaterialElement : m_renderPipelineList)
	{
		for (auto& renderPipelineMeshElement : renderPipelineMaterialElement.second.meshes)
		{
			// Per mesh
			glBindVertexArray(renderPipelineMeshElement.second.mesh->GetVAO());
			int verticesCount = (int)renderPipelineMeshElement.second.mesh->GetAmountOfVertices();

			for (auto& meshTransform : renderPipelineMeshElement.second.transforms)
			{
				this->depthMaterial->shader->SetMat4("model", meshTransform->GetModel());

				// Draw
				glDrawArrays(GL_TRIANGLES, 0, verticesCount);
			}
		}
	}

	// We dont unbind here as we do that at the end in the pipeline
	// in other words remember to unbind glBindFramebuffer(GL_FRAMEBUFFER, 0); 
	// and glBindVertexArray(0); if this function is called alone
}

unsigned int Light::GetDepthMap()
{
	return this->depthMap;
}

unsigned int Light::GetDepthMapFBO()
{
	return this->depthMapFBO;
}