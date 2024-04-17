#include "DefaultRenderPipeline.h"

DefaultRenderPipeline::DefaultRenderPipeline()
{
	BS_VOID result = BS_VOID(nullptr);
	result = this->AddLightType<PointLight>();
	if (result.success) { result.Print(); }
}

BS_VOID DefaultRenderPipeline::Render()
{
	BS_VOID renderResult = this->Render();
	if (!renderResult.success)
		return renderResult;

	return BS_VOID(nullptr);
}

BS_VOID DefaultRenderPipeline::RenderShadows()
{
	return BS_VOID(nullptr);
}

BS_VOID DefaultRenderPipeline::RenderColor()
{
	glViewport(0, 0, 1920, 1080);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glCullFace(GL_BACK);

	// Loop through each material
	for (auto& pair : this->heldElements)
	{
		// Loop through each mesh for that material
		for (auto& mesh : pair.second.meshes)
		{
			// Loop thorugh each transform for that mesh
			for (size_t i = 0; i < mesh.second.second.size(); i++)
			{
				
			}
		}
	}

	std::cout << "Rendered Frame" << std::endl;

	return BS_VOID(nullptr);
}
