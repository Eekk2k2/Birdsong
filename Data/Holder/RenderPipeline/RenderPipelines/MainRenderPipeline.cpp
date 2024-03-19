#include "MainRenderPipeline.h"

MainRenderPipeline::MainRenderPipeline(Holder* holder) : RenderPipeline(holder) { }

void MainRenderPipeline::Setup(std::shared_ptr<Camera> camera)
{
	this->camera = camera;

	/* Shadow mapping */

	// Material
	this->depthMaterial = std::make_shared<Material>();
	this->depthMaterial->shader->Set(SHADER_FROMPATH, ".\\Assets\\Shaders\\defaultDepth.vert", ".\\Assets\\Shaders\\defaultDepth.frag");

	// Lights
	//this->light = std::make_shared<Light>();
}

void MainRenderPipeline::Render()
{
	/* Shadows */

	for (auto& lightElement : this->renderPipelineLights)
		lightElement.second->Render(this->renderPipelineList);

	// Unbind
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindVertexArray(0);

	/* Color pass */

	glViewport(0, 0, 1920, 1080);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glCullFace(GL_BACK);
	for (auto& renderPipelineMaterialElement : this->renderPipelineList)
	{
		// Per Material
		renderPipelineMaterialElement.second.material->Bind();
		
		renderPipelineMaterialElement.second.material->shader->SetInt("shadowMaps[0]", renderPipelineMaterialElement.second.material->GetTexturesCount());
		glActiveTexture(GL_TEXTURE0 + renderPipelineMaterialElement.second.material->GetTexturesCount());
		glBindTexture(GL_TEXTURE_2D, this->renderPipelineLights.begin()->second->GetDepthMap());

		renderPipelineMaterialElement.second.material->shader->SetVec3("eyePos", camera->position);
		renderPipelineMaterialElement.second.material->shader->SetFloat("metallic", 0.5f);
		renderPipelineMaterialElement.second.material->shader->SetFloat("roughness", 0.5f);
		renderPipelineMaterialElement.second.material->shader->SetVec3("albedo", 1.0f, 0.0f, 0.0f);
		renderPipelineMaterialElement.second.material->shader->SetFloat("ao", 1.0f);
		renderPipelineMaterialElement.second.material->shader->SetVec3("lightPositions[0]", this->renderPipelineLights.begin()->second->lightPosition);
		renderPipelineMaterialElement.second.material->shader->SetVec3("lightColors[0]", glm::vec3(1.0f, 1.0f, 1.0f));

		renderPipelineMaterialElement.second.material->shader->SetMat4("view", camera->View());
		renderPipelineMaterialElement.second.material->shader->SetMat4("projection", camera->Projection());
		renderPipelineMaterialElement.second.material->shader->SetMat4("lightSpaceMatrix", this->renderPipelineLights.begin()->second->lightSpaceMatrix);

		for (auto& renderPipelineMeshElement : renderPipelineMaterialElement.second.meshes)
		{
			// Per mesh
			glBindVertexArray(renderPipelineMeshElement.second.mesh->GetVAO());
			int verticesCount = (int)renderPipelineMeshElement.second.mesh->GetAmountOfVertices();
			
			for (auto& meshTransform : renderPipelineMeshElement.second.transforms)
			{
				renderPipelineMaterialElement.second.material->shader->SetMat3("normalMatrix", meshTransform->GetNormalMatrix());
				renderPipelineMaterialElement.second.material->shader->SetMat4("model", meshTransform->GetModel());

				// Draw
				glDrawArrays(GL_TRIANGLES, 0, verticesCount);
			}
		}
	}

	// Unbind
	glBindVertexArray(0);
}