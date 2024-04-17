#pragma once
#include "..\RenderPipeline.h"

#include "..\Objects\Lights\PointLight.h"

class DefaultRenderPipeline : public RenderPipeline
{
public:
	DefaultRenderPipeline();

	BS_VOID Render() override;
private:
	BS_VOID RenderShadows(); // TODO 
	BS_VOID RenderColor();
};

