#pragma once

#ifndef RENDERPIPELINE_S
#define RENDERPIPELINE_S
#include <unordered_map>
#include <vector>

#include "..\Data\Core\Identifier.h"
#include "..\Data\Material\Material.h"
#include "..\Data\Mesh\Mesh.h"
#include "..\Components\Transform.h"

struct ElementMesh {
	ElementMesh() = default;
	ElementMesh(Mesh* _mesh, std::vector<Transform*> _transforms) : mesh(_mesh), transforms(_transforms) {};
	Mesh* mesh;
	std::vector<Transform*> transforms;
};

struct PipelineElement {
	PipelineElement() = default;
	PipelineElement(Identifier m_MaterialIdentifier, Material* m_Material)
		: material(m_Material), materialIdentifier(m_MaterialIdentifier) {}

	Material* material;
	Identifier materialIdentifier;

	std::unordered_map<std::string, ElementMesh> meshes;
};
#endif // !RENDERPIPELINE_S

//ElementMesh(ElementMesh&& other) noexcept : mesh(other.mesh), transforms(std::move(other.transforms)) {}; // TODO 

//using MeshIdentifierString = std::string;
//using MeshTransforms = std::vector<Transform*>;
//using MeshPart = std::pair<Mesh*, MeshTransforms>;

//std::unordered_map<MeshIdentifierString, MeshPart> meshes;

//PipelineElement(PipelineElement&& other) noexcept = default; // This

//PipelineElement(PipelineElement&& other) noexcept
//	: material(std::move(other.material)), materialIdentifier(std::move(other.materialIdentifier)), 
//		meshes(std::move(other.meshes)) { }


//#pragma once
//
//#ifndef RENDERPIPELINEMESHELEMENT_S
//#define RENDERPIPELINEMESHELEMENT_S
//#include "../Components/Transform.h"
//#include "../Data/Mesh/Mesh.h"
//#include "../Data/Core/Identifier.h"
//
//typedef struct RenderPipelineMeshElement {
//	
//	/* -structors */
//	
//	RenderPipelineMeshElement(Identifier meshIdentifier, Mesh* mesh) 
//		: meshIdentifier(meshIdentifier), mesh(mesh) { };
//	
//	// Movables
//	RenderPipelineMeshElement(RenderPipelineMeshElement&& other)			noexcept 
//		: transforms(std::move(other.transforms)), meshIdentifier(std::move(other.meshIdentifier)), mesh(std::move(other.mesh)) { }
//
//	RenderPipelineMeshElement& operator=(RenderPipelineMeshElement&& other) noexcept
//	{
//		if (this != &other) {
//			transforms = std::move(other.transforms);
//			meshIdentifier = std::move(other.meshIdentifier);
//			mesh = std::move(other.mesh);
//		}
//
//		return *this;
//	}
//
//	/* Data */
//
//	// The mesh
//	Mesh*					mesh			= nullptr;
//	Identifier				meshIdentifier	= Identifier();
//
//	// Transforms for the mesh
//	std::vector<std::shared_ptr<Transform>> transforms; 
//
//} RenderPipelineMeshElement;
//#endif // !RENDERPIPELINEMESHELEMENT_S
//
//
//
//#ifndef RENDERPIPELINEMATERIALELEMENT_S
//#define RENDERPIPELINEMATERIALELEMENT_S
//#include <unordered_map>
//
//#include "../Data/Material/Material.h"
//#include "..\Data\Core\Identifier.h"
//
//typedef struct RenderPipelineMaterialElement {
//	
//	/* -structors */
//
//	RenderPipelineMaterialElement(Identifier materialIdentifier, Material* material)
//		: materialIdentifier(materialIdentifier), material(material) { };
//
//	// Movables
//	RenderPipelineMaterialElement(RenderPipelineMaterialElement&& other) noexcept
//		: meshes(std::move(other.meshes)), materialIdentifier(std::move(other.materialIdentifier)), material(std::move(other.material)) { }
//
//	RenderPipelineMaterialElement& operator=(RenderPipelineMaterialElement&& other) noexcept
//	{
//		if (this != &other) {
//			meshes = std::move(other.meshes);
//			materialIdentifier = std::move(other.materialIdentifier);
//			material = std::move(other.material);
//		}
//
//		return *this;
//	}
//
//	/* Data */
//
//	// The material
//	Material*	material			= nullptr;
//	Identifier	materialIdentifier  = Identifier();
//
//	// Meshes for the material
//	std::unordered_map<std::string, RenderPipelineMeshElement>	meshes;
//} RenderPipelineMaterialElement;
//
//	
//
//#endif // !RENDERPIPELINEMATERIALELEMENT_S
