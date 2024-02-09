#pragma once

#include <unordered_map>
#include <iostream>
#include <memory>

#include "../Identifier.h"

//#include "..\Data\Holder\Holder.h"
class Holder;

#include "..\Data\Mesh\Mesh.h"
class Mesh;

#include "..\Data\Material\Material.h"
class Material;

#include "..\Components\Transform.h"
class Transform;

#include "RenderPipelineElements.h"

class RenderPipeline
{
public:
	RenderPipeline(Holder* holder);
	~RenderPipeline();

	std::unordered_map<std::string, RenderPipelineMaterialElement> renderPipelineList;

	/// <summary>
	/// Adding or removing a material from a pass, currently just the default
	/// </summary>
	void EnrollMaterial(Identifier materialIdentifier), DisenrollMaterial();

	/// <summary>
	/// Adding or removing a mesh from a pass/material
	/// </summary>
	void EnrollMesh(Identifier meshIdentifier, Transform* transform, Identifier materialIdentifier), DisenrollMesh();

	virtual void Render();
private:
	Holder* holder;
};
