#pragma once
#include "..\Data\Core\Result.h"

#include "..\RenderPipeline.h"

#include "..\Objects\Lights\PointLight.h"
#include "..\Objects\Camera\Camera.h"

class DefaultRenderPipeline : public RenderPipeline
{
public:
	DefaultRenderPipeline();
	~DefaultRenderPipeline();

	BIRD_VOID Render() override;

	Camera* camera; // TODO : REMOVE THIS IS JUST TEMPORARY
private:
	BIRD_VOID RenderShadows(); // TODO 
	BIRD_VOID RenderColor();
};

