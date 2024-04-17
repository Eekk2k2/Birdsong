#include "RenderPipeline.h"

BS_VOID RenderPipeline::Render()
{
	return BS_VOID(false, "RenderPipeline::Render() should never be called as RenderPipeline is just a base class.");
}

BS_VOID RenderPipeline::Setup()
{
	return BS_VOID(false, "RenderPipeline::Setup() should never be called as RenderPipeline is just a base class.");
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

BS_VOID RenderPipeline::EnrollMaterial(const Identifier& identifier, const Holder& holder)
{
	// Material isnt enrolled
	Result<bool> materialEnrolled = this->isMaterialEnrolled(identifier);
	if (!materialEnrolled.success)
		return BS_VOID(false, materialEnrolled.info);

	if (materialEnrolled.item)
		return BS_VOID(false, "material of identifier in EnrollMaterial(identifier) is already enrolled");

	// Material exists
	Result_Ptr<Material> materialResult = holder.GetHeldItem<Material>(identifier);
	if (!materialResult.success)
		return BS_VOID(false, materialResult.info);

	// Add
	this->heldElements.emplace(identifier.UUID, PipelineElement(identifier, materialResult.item));
	return BS_VOID(nullptr);
}

BS_VOID RenderPipeline::DisenrollMaterial(const Identifier& identifier)
{
	// Material does exist
	Result<bool> materialEnrolled = this->isMaterialEnrolled(identifier);
	if (!materialEnrolled.success)
		return BS_VOID(false, materialEnrolled.info);

	if (!materialEnrolled.item)
		return BS_VOID(false, "material of identifier in DisenrollMaterial(identifier) is not enrolled");

	// Erase
	this->heldElements.erase(identifier.UUID);
	return BS_VOID(nullptr);
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
		return Result<bool>(false, "material of material in isMeshEnrolled(material, mesh, transform) is not enrolled");

	// Check
	if (this->heldElements[material.UUID].meshes.find(mesh.UUID) != this->heldElements[material.UUID].meshes.end())
		return Result<bool>(true);
	else
		return Result<bool>(false);
}

BS_VOID RenderPipeline::EnrollMesh(const Identifier& material, const Identifier& mesh, Transform* transform, const Holder& holder)
{
	// Mesh isnt enrolled
	Result<bool> meshEnrolled = this->isMeshEnrolled(material, mesh);
	if (!meshEnrolled.success)
		return BS_VOID(false, meshEnrolled.info);

	// Mesh exist
	Result_Ptr<Mesh> meshResult = holder.GetHeldItem<Mesh>(mesh);
	if (!meshResult.success)
		return BS_VOID(false, meshResult.info);
	
	// Add our meshPart to the pipelineElement
	if (!meshEnrolled.item)
		this->heldElements[material.UUID].meshes.emplace(mesh.UUID, std::pair<Mesh*, std::vector<Transform*>>(meshResult.item, std::vector<Transform*>())); // Readable code

	// Add our transform to that meshPart
	// TODO : Check if transform is already added
	this->heldElements[material.UUID].meshes[mesh.UUID].second.push_back(transform);
	// TODO : NEXT
	
return BS_VOID(nullptr);
}
