#include "MainRenderPipeline.h"

MainRenderPipeline::MainRenderPipeline(Holder* holder) : RenderPipeline(holder) { }

void MainRenderPipeline::Render()
{
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
