#include "MainRenderPipeline.h"

MainRenderPipeline::MainRenderPipeline(Holder* holder) : RenderPipeline(holder) { }

void MainRenderPipeline::Setup(std::shared_ptr<Camera> camera)
{
	this->camera = camera;
}

void MainRenderPipeline::Render()
{
	// Main pass

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& renderPipelineMaterialElement : this->renderPipelineList)
	{
		// Per Material
		renderPipelineMaterialElement.second.material->Bind();
		
		renderPipelineMaterialElement.second.material->shader->SetVec3("eyePos", camera->position);
		renderPipelineMaterialElement.second.material->shader->SetFloat("metallic", 0.5f);
		renderPipelineMaterialElement.second.material->shader->SetFloat("roughness", 0.5f);
		renderPipelineMaterialElement.second.material->shader->SetVec3("albedo", 1.0f, 0.0f, 0.0f);
		renderPipelineMaterialElement.second.material->shader->SetFloat("ao", 1.0f);
		renderPipelineMaterialElement.second.material->shader->SetVec3("lightPositions[0]", glm::vec3(1.0f, 2.0f, 1.0f));
		renderPipelineMaterialElement.second.material->shader->SetVec3("lightColors[0]", glm::vec3(1.0f, 1.0f, 1.0f));

		renderPipelineMaterialElement.second.material->shader->SetMat4("view", camera->View());
		renderPipelineMaterialElement.second.material->shader->SetMat4("projection", camera->Projection());

		for (auto& renderPipelineMeshElement : renderPipelineMaterialElement.second.meshes)
		{
			//std::cout << "Mesh" << std::endl;

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
}