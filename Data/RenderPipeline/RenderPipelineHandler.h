#pragma once
#include <unordered_map>

#include "..\Data\RenderPipeline\RenderPipelines\DefaultRenderPipeline.h"

class RenderPipelineHandler
{
public:
	RenderPipelineHandler();

	DefaultRenderPipeline defaultRenderPipeline;
};

