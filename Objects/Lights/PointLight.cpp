#include "PointLight.h"

PointLight::PointLight()
{
	// Settings
	/*this->shadowResolution = glm::uvec2(4096, 4096);
	this->renderPlanes = glm::uvec2(1, 15);*/

	// Depth material
	//this->depthMaterial = Material();
	//this->depthMaterial.SetShader();
	//this->depthMaterial->shader->Set(SHADER_FROMPATH, ".\\Assets\\Shaders\\defaultDepth.vert", ".\\Assets\\Shaders\\defaultDepth.frag");
	//this->depthMaterial->shader->SetVert(SHADER_FROMPATH, ".\\Assets\\Shaders\\Point\\PointDepth.vert");
	//this->depthMaterial->shader->SetGeom(SHADER_FROMPATH, ".\\Assets\\Shaders\\Point\\PointDepth.geom");
	//this->depthMaterial->shader->SetFrag(SHADER_FROMPATH, ".\\Assets\\Shaders\\Point\\PointDepth.frag");
	//this->depthMaterial->shader->LinkProgram();
	// TODO 

	// Matrices
	//this->shadowProjection = glm::perspective(glm::radians(90.0f), (float)this->shadowResolution.x / (float)this->shadowResolution.y, this->renderPlanes.x, this->renderPlanes.y);

	//shadowTransforms.push_back(this->shadowProjection * glm::lookAt(this->GetPosition(), this->GetPosition() + glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
	//shadowTransforms.push_back(this->shadowProjection * glm::lookAt(this->GetPosition(), this->GetPosition() + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0, -1.0, 0.0)));
	//shadowTransforms.push_back(this->shadowProjection * glm::lookAt(this->GetPosition(), this->GetPosition() + glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
	//shadowTransforms.push_back(this->shadowProjection * glm::lookAt(this->GetPosition(), this->GetPosition() + glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 0.0, -1.0)));
	//shadowTransforms.push_back(this->shadowProjection * glm::lookAt(this->GetPosition(), this->GetPosition() + glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, -1.0, 0.0)));
	//shadowTransforms.push_back(this->shadowProjection * glm::lookAt(this->GetPosition(), this->GetPosition() + glm::vec3(0.0, 0.0, -1.0), glm::vec3(0.0, -1.0, 0.0)));

	//// Framebuffer
	//glGenFramebuffers(1, &this->depthMapFBO);

	//// First we create the cubemap
	//glGenTextures(1, &this->depthCubemap);

	//glBindTexture(GL_TEXTURE_CUBE_MAP, this->depthCubemap);
	//for (size_t i = 0; i < 6; i++)
	//	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, this->shadowResolution.x, this->shadowResolution.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	//// Framebuffer Texture
	//glBindFramebuffer(GL_FRAMEBUFFER, this->depthMapFBO);
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, this->depthCubemap, 0);
	//glDrawBuffer(GL_NONE);
	//glReadBuffer(GL_NONE);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

PointLight::~PointLight()
{
	//if (glIsTexture(this->depthCubemap) == GL_TRUE) {
	//	glDeleteTextures(1, &this->depthCubemap);
	//}
}

void PointLight::Render(std::unordered_map<std::string, PipelineElement>& m_renderPipelineList)
{
	//glViewport(0, 0, this->shadowResolution.x, this->shadowResolution.y);
	//glBindFramebuffer(GL_FRAMEBUFFER, this->depthMapFBO);
	//glClear(GL_DEPTH_BUFFER_BIT);

	//this->depthMaterial->Bind(); // TODO : NEXT

	//this->depthMaterial->shaderResult->SetVec3("lightPos", this->GetPosition());
	//this->depthMaterial->GetShader().item->SetFloat("farPlane", this->renderPlanes.y);
	//this->depthMaterial->GetShader().item->SetMat4("shadowMatrices[0]", this->shadowTransforms[0]);
	//this->depthMaterial->GetShader().item->SetMat4("shadowMatrices[1]", this->shadowTransforms[1]);
	//this->depthMaterial->GetShader().item->SetMat4("shadowMatrices[2]", this->shadowTransforms[2]);
	//this->depthMaterial->GetShader().item->SetMat4("shadowMatrices[3]", this->shadowTransforms[3]);
	//this->depthMaterial->GetShader().item->SetMat4("shadowMatrices[4]", this->shadowTransforms[4]);
	//this->depthMaterial->GetShader().item->SetMat4("shadowMatrices[5]", this->shadowTransforms[5]);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, this->depthCubemap);

	//for (auto& renderPipelineMaterialElement : m_renderPipelineList)
	//{
	//	for (auto& renderPipelineMeshElement : renderPipelineMaterialElement.second.meshes)
	//	{
	//		// Per mesh
	//		glBindVertexArray(renderPipelineMeshElement.second.mesh->GetVAO());
	//		int verticesCount = (int)renderPipelineMeshElement.second.mesh->GetAmountOfVertices();

	//		for (auto& meshTransform : renderPipelineMeshElement.second.transforms)
	//		{
	//			this->depthMaterial->shader->SetMat4("model", meshTransform->GetModel());

	//			// Draw
	//			glDrawArrays(GL_TRIANGLES, 0, verticesCount);
	//		}
	//	}
	//}
}

int PointLight::GetDepthMap()
{
	return this->depthCubemap;
}

std::size_t PointLight::GetLightSpaceMatrixSize()
{
	return this->shadowTransforms.size();
}

std::vector<glm::mat4> PointLight::GetLightSpaceMatrix()
{
	return std::vector<glm::mat4>();
}

glm::mat4 PointLight::GetLightProjection()
{
	return this->shadowProjection;
}
