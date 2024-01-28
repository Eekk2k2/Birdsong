#include "Object.h"

Object::Object(std::shared_ptr<Holder> holder)
{
	// Creates a weak ptr
	this->holder = holder;
}

Object::Object(Object&& other) noexcept
	: Objectoid(std::move(other)), meshes(std::move(other.meshes)), holder(std::move(other.holder))
		{ }

Object::~Object()
{

}

void Object::AddMesh(Identifier meshIdentifier, Identifier materialIdentifier) 
{
	this->meshes.push_back(&this->holder->GetHeldMesh(meshIdentifier));
	
	// The list of meshes for the material
	std::unordered_map<std::string, MeshRenderListElement>& materialRenderList = this->holder->renderList.at(materialIdentifier.UUID);

	// Checks whether this mesh already has a render list element in this current material
		// if yes we just add this transform to that list
		// if no we create our own and then add this transform
	bool alreadyExists = false;
	for (auto& renderListElement : materialRenderList)
	{
		if (renderListElement.first == meshIdentifier.UUID)
		{
			renderListElement.second.transforms.push_back(this->transform.get());
			alreadyExists = true;
			break;
		}
	}

	if (alreadyExists == false) 
	{
		materialRenderList.emplace(meshIdentifier.UUID, MeshRenderListElement());
		MeshRenderListElement& newMeshRenderListElement = materialRenderList[meshIdentifier.UUID];
		newMeshRenderListElement.mesh = this->meshes[this->meshes.size() - 1]; // Add the new mesh
		newMeshRenderListElement.transforms.push_back(this->transform.get());
	}
}

void Object::RemoveMesh(int index)
{
	if (index < this->meshes.size())	{ this->meshes.erase(this->meshes.begin() + index); }
	else								{ std::cout << "Object mesh list index out of bounds; failed to remove mesh " << index << "!"; }
}
