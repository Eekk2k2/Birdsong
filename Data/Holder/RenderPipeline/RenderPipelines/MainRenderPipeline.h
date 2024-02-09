#pragma once
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../RenderPipeline.h"
#include "../../Holder.h"

class MainRenderPipeline : public RenderPipeline
{
public:
    MainRenderPipeline(Holder* holder);

    void Render() override;
};
