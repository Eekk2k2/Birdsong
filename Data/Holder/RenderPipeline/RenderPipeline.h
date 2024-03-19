#pragma once

#include <unordered_map>
#include <iostream>
#include <memory>

#include "../Identifier.h"

//#include "..\Data\Holder\Holder.h"
class Holder;

#include "../Objects/Camera/Camera.h"

#include "..\Data\Mesh\Mesh.h"
class Mesh;

#include "..\Data\Material\Material.h"
class Material;

#include "..\Components\Transform.h"
class Transform;

#include "..\Objects\Lights\Light.h"
class Light;

#include "RenderPipelineElements.h"


class RenderPipeline
{
public:
	RenderPipeline(Holder* holder);
	~RenderPipeline();

	std::unordered_map<std::string, Light*> renderPipelineLights;
	std::unordered_map<std::string, RenderPipelineMaterialElement> renderPipelineList;

	/// <summary>
	/// Adding or removing a material from a pass, currently just the default
	/// </summary>
	void EnrollMaterial(Identifier materialIdentifier), DisenrollMaterial();

	/// <summary>
	/// Adding or removing a mesh from a pass/material
	/// </summary>
	void EnrollMesh(Identifier meshIdentifier, std::shared_ptr<Transform> transform, Identifier materialIdentifier), DisenrollMesh();

	/// <summary>
	/// Adding or removing a light
	/// </summary>
	/// <param name="lightIdentifier"></param>
	void EnrollLight(Identifier lightIdentifier), DisenrollLight();

	virtual void Setup(std::shared_ptr<Camera> camera);

	virtual void Render();

	Holder* holder;
	std::shared_ptr<Camera> camera;
};

