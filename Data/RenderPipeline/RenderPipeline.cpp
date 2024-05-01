#include "RenderPipeline.h"

RenderPipeline::RenderPipeline()
{
	this->heldElements = std::unordered_map<std::string, PipelineElement>();
}

RenderPipeline::~RenderPipeline()
{
}

BIRD_VOID RenderPipeline::Render()
{
	return BIRD_VOID(false, "RenderPipeline::Render() should never be called as RenderPipeline is just a base class.");
}

BIRD_VOID RenderPipeline::Setup()
{
	return BIRD_VOID(false, "RenderPipeline::Setup() should never be called as RenderPipeline is just a base class.");
}

Result<bool> RenderPipeline::isMaterialEnrolled(const Identifier& identifier)
{
	// Type is correct
	if (identifier.typeID != typeid(Material))
		return Result<bool>(false, "typeID of identifier in isMaterialEnrolled(identifier) needs to be the same as typeid(Material)");

	// Check
	if (this->heldElements.find(identifier.UUID) != this->heldElements.end())
		return Result<bool>(true);
	else
		return Result<bool>(false);
}

BIRD_VOID RenderPipeline::EnrollMaterial(const Identifier& identifier, Holder& holder)
{
	// Material isnt enrolled
	Result<bool> materialEnrolled = this->isMaterialEnrolled(identifier);
	if (!materialEnrolled.success)
		return BIRD_VOID(false, materialEnrolled.info);

	if (materialEnrolled.item)
		return BIRD_VOID(false, "material of identifier in EnrollMaterial(identifier) is already enrolled to this pipeline");

	// Material exists
	Result_Ptr<Material> materialResult = holder.GetHeldItem<Material>(identifier);
	if (!materialResult.success)
		return BIRD_VOID(false, materialResult.info);

	// Add
	this->heldElements.emplace(identifier.UUID, PipelineElement(identifier, materialResult.item));
	return BIRD_VOID(nullptr);
}

BIRD_VOID RenderPipeline::DisenrollMaterial(const Identifier& identifier)
{
	// Material does exist
	Result<bool> materialEnrolled = this->isMaterialEnrolled(identifier);
	if (!materialEnrolled.success)
		return BIRD_VOID(false, materialEnrolled.info);

	if (!materialEnrolled.item)
		return BIRD_VOID(false, "material of identifier in DisenrollMaterial(identifier) is not enrolled to this pipeline");

	// Erase
	this->heldElements.erase(identifier.UUID);
	return BIRD_VOID(nullptr);
}

Result<bool> RenderPipeline::isMeshEnrolled(const Identifier& material, const Identifier& mesh)
{
	// Type is correct
	if (mesh.typeID != typeid(Mesh))
		return Result<bool>(false, "typeID of mesh in isMeshEnrolled(material, mesh) needs to be the same as typeid(Mesh)");

	// Material is enrolled
	Result<bool> materialEnrolled = this->isMaterialEnrolled(material);
	if (!materialEnrolled.success)
		return Result<bool>(false, materialEnrolled.info);

	if (!materialEnrolled.item)
		return Result<bool>(false, "material of material in isMeshEnrolled(material, mesh, transform) is not enrolled to this pipeline");

	// Check
	if (this->heldElements[material.UUID].meshes.find(mesh.UUID) != this->heldElements[material.UUID].meshes.end())
		return Result<bool>(true);
	else
		return Result<bool>(false);
}

BIRD_VOID RenderPipeline::EnrollMesh(const Identifier& material, const Identifier& mesh, Transform* transform, Holder& holder)
{
	// Mesh isnt enrolled
	Result<bool> meshEnrolled = this->isMeshEnrolled(material, mesh);
	if (!meshEnrolled.success)
		return BIRD_VOID(false, meshEnrolled.info);

	// Mesh exist
	Result_Ptr<Mesh> meshResult = holder.GetHeldItem<Mesh>(mesh);
	if (!meshResult.success)
		return BIRD_VOID(false, meshResult.info);
	
	// Add our meshPart to the pipelineElement
	if (!meshEnrolled.item)
		this->heldElements[material.UUID].meshes.emplace(mesh.UUID, ElementMesh(meshResult.item, std::vector<Transform*>())); // Readable code

	// Add our transform to that meshPart
	// TODO : Check if transform is already added
	this->heldElements[material.UUID].meshes[mesh.UUID].transforms.push_back(transform);
	// TODO : NEXT <- I have no idea why i put this here
	
	return BIRD_VOID(nullptr);
}

BIRD_VOID RenderPipeline::DisenrollMesh(const Identifier& material, const Identifier& mesh, Transform* transform)
{
	// Mesh is enrolled
	Result<bool> meshEnrolled = this->isMeshEnrolled(material, mesh);
	if (!meshEnrolled.success)
		return BIRD_VOID(false, meshEnrolled.info);

	if (!meshEnrolled.item)
		return BIRD_VOID(false, "mesh of mesh in DisenrollMesh(material, mesh, transform) is not enrolled to this pipeline");

	// Transform is enrolled
	auto& transforms = this->heldElements[material.UUID].meshes[mesh.UUID].transforms;
	int enrolledTransform = -1;
	for (int i = 0; i < transforms.size(); i++)
		if (transforms[i] == transform)
			{ enrolledTransform = i; break; }

	if (enrolledTransform == -1)
		return BIRD_VOID(false, "transform of transform in DisenrollMesh(material, mesh, transform) is not enrolled to this pipeline");
		
	// Erase
	transforms.erase(transforms.begin() + enrolledTransform);
	return BIRD_VOID(nullptr);
}
