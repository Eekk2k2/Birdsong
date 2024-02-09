#pragma once

#ifndef RENDERPIPELINEMESHELEMENT_S
#define RENDERPIPELINEMESHELEMENT_S
#include "../Components/Transform.h"
#include "../Data/Mesh/Mesh.h"
#include "../Identifier.h"

typedef struct RenderPipelineMeshElement {
	
	/* -structors */
	
	RenderPipelineMeshElement(Identifier meshIdentifier, Mesh* mesh) 
		: meshIdentifier(meshIdentifier), mesh(mesh) { };
	
	// Movables
	RenderPipelineMeshElement(RenderPipelineMeshElement&& other)			noexcept 
		: transforms(std::move(other.transforms)), meshIdentifier(std::move(other.meshIdentifier)), mesh(std::move(other.mesh)) { }

	RenderPipelineMeshElement& operator=(RenderPipelineMeshElement&& other) noexcept
	{
		if (this != &other) {
			transforms = std::move(other.transforms);
			meshIdentifier = std::move(other.meshIdentifier);
			mesh = std::move(other.mesh);
		}

		return *this;
	}

	/* Data */

	// The mesh
	Mesh*					mesh			= nullptr;
	Identifier				meshIdentifier	= Identifier();

	// Transforms for the mesh
	std::vector<Transform*> transforms; 

} RenderPipelineMeshElement;
#endif // !RENDERPIPELINEMESHELEMENT_S



#ifndef RENDERPIPELINEMATERIALELEMENT_S
#define RENDERPIPELINEMATERIALELEMENT_S
#include <unordered_map>

#include "../Data/Material/Material.h"
#include "../Identifier.h"

typedef struct RenderPipelineMaterialElement {
	
	/* -structors */

	RenderPipelineMaterialElement(Identifier materialIdentifier, Material* material)
		: materialIdentifier(materialIdentifier), material(material) { };

	// Movables
	RenderPipelineMaterialElement(RenderPipelineMaterialElement&& other)			noexcept
		: meshes(std::move(other.meshes)), materialIdentifier(std::move(other.materialIdentifier)), material(std::move(other.material)) { }

	RenderPipelineMaterialElement& operator=(RenderPipelineMaterialElement&& other) noexcept
	{
		if (this != &other) {
			meshes = std::move(other.meshes);
			materialIdentifier = std::move(other.materialIdentifier);
			material = std::move(other.material);
		}

		return *this;
	}

	/* Data */

	// The material
	Material*													material			= nullptr;
	Identifier													materialIdentifier  = Identifier();

	// Meshes for the material
	std::unordered_map<std::string, RenderPipelineMeshElement>	meshes;
} RenderPipelineMaterialElement;

	

#endif // !RENDERPIPELINEMATERIALELEMENT_S
