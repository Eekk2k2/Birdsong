#include "DefaultRenderPipeline.h"

DefaultRenderPipeline::DefaultRenderPipeline()
{
	BIRD_VOID result = BIRD_VOID(nullptr);
	result = this->AddLightType<PointLight>();
	if (result.success) { result.Print(); }

	this->camera = nullptr;
}

DefaultRenderPipeline::~DefaultRenderPipeline()
{
}

BIRD_VOID DefaultRenderPipeline::Render()
{
	BIRD_VOID renderResult = this->RenderColor();
	if (!renderResult.success)
		return renderResult;

	return BIRD_VOID(nullptr);
}

BIRD_VOID DefaultRenderPipeline::RenderShadows()
{
	return BIRD_VOID(nullptr);
}

BIRD_VOID DefaultRenderPipeline::RenderColor()
{
	glViewport(0, 0, 1920, 1080);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glCullFace(GL_BACK);

	// Set up buffers
	// ...

	// Loop through each material
	for (auto& pair : this->heldElements)
	{
		PipelineElement& pipelineElement = pair.second;
		pipelineElement.material->Use();
		
		// Set material uniforms
		pipelineElement.material->GetShader().item->SetMat4("view", camera->View());
		pipelineElement.material->GetShader().item->SetMat4("projection", camera->Projection());

		// Loop through each mesh for that material
		for (auto& meshPair : pipelineElement.meshes)
		{
			Mesh* mesh = meshPair.second.mesh;
			mesh->Use();
			int vertices = mesh->GetAmountOfVertices();

			// Loop thorugh each transform for that mesh
			for (size_t i = 0; i < meshPair.second.transforms.size(); i++)
			{
				// TODO : This should be in a buffer
				//pipelineElement.material->GetShader().item->SetMat3("normalMatrix", meshPair.second.second[i]->GetNormalMatrix());
				pipelineElement.material->GetShader().item->SetMat4("model", meshPair.second.transforms[i]->GetModel());

				glDrawArrays(GL_TRIANGLES, 0, vertices);
			}
		}
	}

	return BIRD_VOID(nullptr);
}
