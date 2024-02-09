#include "RenderPipeline.h"
#include "../Data/Holder/Holder.h"

RenderPipeline::RenderPipeline(Holder* holder) : holder(holder)
	{ }

RenderPipeline::~RenderPipeline()
{

}

void RenderPipeline::EnrollMaterial(Identifier materialIdentifier)
{
	Material* material = &this->holder->GetHeldMaterial(materialIdentifier);

	this->renderPipelineList.at(materialIdentifier.UUID) = RenderPipelineMaterialElement(materialIdentifier, material);
}

// TODO
void RenderPipeline::DisenrollMaterial()
{
}

void RenderPipeline::EnrollMesh(Identifier meshIdentifier, Transform* transform, Identifier materialIdentifier)
{
	// If the material doesnt exist in the renderlist we return
	if (this->renderPipelineList.find(materialIdentifier.UUID) == renderPipelineList.end()) 
		{ std::cout << "Mesh(" << meshIdentifier.UUID << ") could not be enrolled to material(" << materialIdentifier.UUID << ") due to the material itself not being enrolled." << std::endl; return; }

	// If the mesh doesnt exist in the holder we return
	if (this->holder->heldMeshes.find(meshIdentifier.UUID) == this->holder->heldMeshes.end())
		{ std::cout << "Mesh(" << meshIdentifier.UUID << ") could not be enrolled to material(" << materialIdentifier.UUID << ") due to the mesh not existing in holder." << std::endl;  return; }

	/* Checks wether this mesh is already enrolled under the material
		* if yes then we add our transform to that element
		* if no we create a new element and then move on as if yes 
	*/
	if (this->renderPipelineList.at(materialIdentifier.UUID).meshes.find(meshIdentifier.UUID) == this->renderPipelineList.at(materialIdentifier.UUID).meshes.end()) 
		// It isnt enrolled so we need to add it
		this->renderPipelineList.at(materialIdentifier.UUID).meshes.emplace(meshIdentifier.UUID, RenderPipelineMeshElement(meshIdentifier, &this->holder->GetHeldMesh(meshIdentifier)));
	
	// Add our mesh transform to the already existing mesh
	this->renderPipelineList.at(materialIdentifier.UUID).meshes.at(meshIdentifier.UUID).transforms.push_back(transform);
}   

// TODO
void RenderPipeline::DisenrollMesh()
{
}

void RenderPipeline::Render()
{
	std::cout << "Render() function on base RenderPipeline called. This is wrong and shouldnt happen. No rendering will occur.";
}
