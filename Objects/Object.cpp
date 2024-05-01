#include "Object.h"

//Object::Object(std::shared_ptr<Holder> holder)
//{
//	this->holder = holder;
//}
//
//Object::Object(Object&& other) noexcept
//	: Objectoid(std::move(other)), meshes(std::move(other.meshes)), holder(std::move(other.holder))
//		{ }
//
//Object::Object(const Object& other) 
//	: Objectoid(other), meshes(other.meshes), holder(other.holder)
//		{ }
//
//Object::~Object()
//{
//
//}
//
//void Object::AddMesh(Identifier meshIdentifier, Identifier materialIdentifier) 
//{
//	Result_Ptr<Mesh> result = this->holder->GetHeldItem<Mesh>(meshIdentifier);
//	if (!result.success)
//	{
//		result.Print();
//		return;
//	}
//
//	this->meshes.push_back(result.item);
//	//this->holder->renderPipelineHandler->mainRenderPipeline->EnrollMesh(meshIdentifier, this->transform, materialIdentifier);
//}
//
//void Object::RemoveMesh(int index)
//{
//	if (index < this->meshes.size())	{ this->meshes.erase(this->meshes.begin() + index); }
//	else								{ std::cout << "Object mesh list index out of bounds; failed to remove mesh " << index << "!"; }
//}

Object::Object()
{
}

Object::~Object()
{
}

Result<bool> Object::isMeshEnrolled(const Identifier& identifier)
{
	if (identifier.typeID != typeid(Mesh))
		return Result<bool>(false, "typeID of identifier in Object::isMeshEnrolled(identifier) need to match typeid(Mesh)");

	if (this->meshes.find(identifier.UUID) != this->meshes.end())
		return Result<bool>(true);
	else
		return Result<bool>(false);
}

BIRD_VOID Object::EnrollMesh(const Identifier& identifier, Holder& holder)
{
	// Mesh isnt enrolled
	Result<bool> meshEnrolled = this->isMeshEnrolled(identifier);
	if (!meshEnrolled.success)
		return BIRD_VOID(false, meshEnrolled.info);

	if (meshEnrolled.item)
		return BIRD_VOID(false, "mesh of identifier in EnrollMesh(identifier) is already enrolled");

	// Mesh exists
	Result_Ptr<Mesh> meshResult = holder.GetHeldItem<Mesh>(identifier);
	if (!meshResult.success)
		return BIRD_VOID(false, meshResult.info);

	// Add
	this->meshes.emplace(identifier.UUID, std::pair<const Identifier&, Mesh*>(identifier, meshResult.item));
	return BIRD_VOID(nullptr);
}

BIRD_VOID Object::DisenrollMesh(const Identifier& identifier)
{
	// Mesh is enrolled
	Result<bool> meshEnrolled = this->isMeshEnrolled(identifier);
	if (!meshEnrolled.success)
		return BIRD_VOID(false, meshEnrolled.info);

	if (!meshEnrolled.item)
		return BIRD_VOID(false, "mesh of identifier in DisenrollMesh(identifier) is not enrolled");

	// Erase
	this->meshes.erase(identifier.UUID);
	return BIRD_VOID(nullptr);
}

Result<int> Object::MeshesEnrolled()
{
	return Result<int>(this->meshes.size());
}

BIRD_VOID Object::SetMaterial(const Identifier& identifier, Holder& holder, RenderPipeline& pipeline)
{
	BIRD_VOID result = BIRD_VOID(nullptr);


	for (auto& mesh : this->meshes)
	{
		result = pipeline.DisenrollMesh(identifier, mesh.second.first, this);
		if (!result.success) result.Print();
		result = pipeline.EnrollMesh(identifier, mesh.second.first, this, holder);
		if (!result.success) result.Print();
	}

	return result; // Return the last error message if there is one
}

BIRD_VOID Object::SetMaterial(const Identifier& materialIdentifier, const Identifier& meshIdentifier, Holder& holder, RenderPipeline& pipeline)
{
	// Mesh is enrolled
	Result<bool> meshEnrolled = this->isMeshEnrolled(meshIdentifier);
	if (!meshEnrolled.success)
		return BIRD_VOID(false, meshEnrolled.info);

	if (!meshEnrolled.item)
		return BIRD_VOID(false, "mesh of meshIdentifier in SetMaterial(materialIdentifier, meshIdentifier, pipeline) is not enrolled");

	BIRD_VOID result = pipeline.DisenrollMesh(materialIdentifier, meshIdentifier, this);
	BIRD_VOID result_2 = pipeline.EnrollMesh(materialIdentifier, meshIdentifier, this, holder);
	
	return BIRD_VOID(false, result.info + "\n" + result_2.info);
}
