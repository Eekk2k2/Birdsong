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

    void Setup(std::shared_ptr<Camera> camera) override;
    void Render() override;
private:
    //unsigned int depthMapFBO = 0, depthMap = 0;
    std::shared_ptr<Material> depthMaterial;
    std::shared_ptr<Light> light;
};
