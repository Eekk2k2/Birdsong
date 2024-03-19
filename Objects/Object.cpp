#include "Object.h"

Object::Object(std::shared_ptr<Holder> holder)
{
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
	this->holder->renderPipelineHandler->mainRenderPipeline->EnrollMesh(meshIdentifier, this->transform, materialIdentifier);
}

void Object::RemoveMesh(int index)
{
	if (index < this->meshes.size())	{ this->meshes.erase(this->meshes.begin() + index); }
	else								{ std::cout << "Object mesh list index out of bounds; failed to remove mesh " << index << "!"; }
}
