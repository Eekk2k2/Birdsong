#include "RenderPipelineHandler.h"

RenderPipelineHandler::RenderPipelineHandler(Holder* holder)
{
	this->mainRenderPipeline = std::make_shared<MainRenderPipeline>(holder);
}
