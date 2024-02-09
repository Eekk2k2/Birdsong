#pragma once
#include <unordered_map>

#include "..\Data\Holder\Holder.h"
class Holder;

#include "RenderPipelines/MainRenderPipeline.h"
class MainRenderPipeline;

class RenderPipelineHandler
{
public:
	RenderPipelineHandler(Holder* holder);

	// Different pipelines
	
	std::shared_ptr<MainRenderPipeline> mainRenderPipeline;

	// ...
};

