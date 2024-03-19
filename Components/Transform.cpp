//#include "Transform.h"
//
///*															Transform															*/
//
//
//Transform::Transform() 
//{
//	this->position			= glm::vec3(0.0, 0.0, 0.0);
//	this->lastPosition		= glm::vec3(-1.0, 0.0, -1.0);
//	this->localPosition		= glm::vec3(0.0, 0.0, 0.0);
//	this->lastLocalPosition = glm::vec3(-1.0, -1.0, -1.0);
//
//	this->scale				= glm::vec3(1.0, 1.0, 1.0);
//	this->lastScale			= glm::vec3(-1.0, -1.0, -1.0);
//	this->localScale		= glm::vec3(1.0, 1.0, 1.0);
//	this->lastLocalScale	= glm::vec3(-1.0, 1.0, -1.0);
//
//	this->model = GetModel();
//
//	updatedSinceLastFrame	= false;
//	this->normalMatrix		= GetNormalMatrix();
//}
//
//Transform::Transform(std::shared_ptr<Transform> parentTransform)
//{ 
//	this->position			= glm::vec3(0.0, 0.0, 0.0);
//	this->lastPosition		= glm::vec3(0.0, 0.0, 0.0);
//	this->localPosition		= glm::vec3(0.0, 0.0, 0.0);
//	this->lastLocalPosition = glm::vec3(0.0, 0.0, 0.0);
//
//	//this->scale				= glm::vec3(1.0, 1.0, 1.0);
//	//this->lastScale			= glm::vec3(1.0, 1.0, 1.0);
//	//this->localScale		= glm::vec3(1.0, 1.0, 1.0);
//	//this->lastLocalScale	= glm::vec3(1.0, 1.0, 1.0);
//
//	this->model = GetModel();
//
//	updatedSinceLastFrame	= false;
//	this->normalMatrix		= GetNormalMatrix();
//
//	SetParent(parentTransform);
//}
//
//Transform::~Transform() 
//{
//	// I dont really know how to handle what happens with the children. I guess I delete them too, but i feel like that should happen on the MainObject side of things?
//}
//
//void Transform::SetParent(std::shared_ptr<Transform> parentTransform)
//{
//	this->parentTransform = parentTransform;
//	this->parentTransform->AddChild(this);
//
//	// Since we now have a new parent.position to be relative 
//	// to we need to recalculate our global position. This would 
//	// also recalculate every child's global position due to the 
//	// same reason. 
//	RecalculatePosition();
//}
//
//void Transform::AddChild(Transform* childTransform) 
//{
//	this->childTransforms.push_back(childTransform);
//}
//
//glm::mat4 Transform::GetModel() 
//{
//	// If no values are updated we use the old matrix
//	
//	if (this->position == this->lastPosition || this->localPosition == this->lastLocalPosition || this->scale == this->lastScale || this->localScale == this->lastLocalScale)  
//	{
//		updatedSinceLastFrame = false; 
//		return this->model;
//	}
//	else {
//		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), this->scale);
//		this->model = glm::translate(glm::mat4(1.0f), this->position) * scaleMatrix;
//
//		this->lastPosition		= this->position;
//		this->lastLocalPosition = this->localPosition;
//		this->lastScale			= this->scale;
//		this->lastLocalScale	= this->localScale;
//
//		updatedSinceLastFrame	= true;
//		return this->model;
//	}
//}
//
///*															Position															*/
//
//void Transform::RecalculatePosition()
//{
//	if (this->parentTransform != nullptr)
//		this->position = this->parentTransform->GetPosition() + this->localPosition;
//	else { this->position = this->localPosition; }
//
//	// Since our global position has changed we need to recalculate each childs 
//	// global position too. This is because their global position is relative 
//	// to this transforms position + their local position.
//	RecalculateChildrensPosition();
//}
//
//void Transform::RecalculateLocalPosition()
//{
//	if (this->parentTransform != nullptr)
//		this->localPosition = this->position - this->parentTransform->GetPosition();
//	else this->localPosition = this->position;
//
//	// Since our local position and in return global position has changed we need 
//	// to recalculate each childs global position too. This is because their global
//	// position is relative to this transforms position + their local position.
//	RecalculateChildrensPosition();
//}
//
//void Transform::RecalculateChildrensPosition() 
//{
//	for (size_t i = 0; i < this->childTransforms.size(); i++)
//		this->childTransforms[i]->RecalculatePosition();
//}
//
//void Transform::RecalculateChildrensLocalPosition() 
//{
//	for (size_t i = 0; i < this->childTransforms.size(); i++)
//		this->childTransforms[i]->RecalculateChildrensLocalPosition();
//}
//
//void Transform::SetPosition(glm::vec3 newPosition)
//{
//	this->position = newPosition;
//
//	RecalculateLocalPosition();
//	RecalculateChildrensPosition();
//}
//
//void Transform::SetLocalPosition(glm::vec3 newLocalPosition)
//{
//	this->localPosition = newLocalPosition;
//
//	RecalculatePosition();
//}
//
//glm::vec3 Transform::GetPosition() 
//{
//	return this->position;
//}
//
//glm::vec3 Transform::GetLocalPosition() 
//{
//	return this->localPosition;
//}
//
///*															Scale															*/
//
//void Transform::RecalculateScale() 
//{
//	if (this->parentTransform != nullptr)
//		this->scale = this->localScale * this->parentTransform->scale;
//	else this->scale = this->localScale;
//
//	RecalculateChildrensScale();
//}
//
//void Transform::RecalculateLocalScale() 
//{
//	if (this->parentTransform != nullptr)
//		this->localScale = this->scale / this->parentTransform->scale;
//	else this->localScale = this->scale;
//}
//
//void Transform::RecalculateChildrensScale() 
//{
//	for (size_t i = 0; i < this->childTransforms.size(); i++)
//		this->childTransforms[i]->RecalculateScale();
//}
//
//void Transform::RecalculateChildrensLocalScale() 
//{
//	for (size_t i = 0; i < this->childTransforms.size(); i++)
//		this->childTransforms[i]->RecalculateChildrensLocalScale();
//}
//
//glm::mat3 Transform::GetNormalMatrix()
//{
//	this->normalMatrix = glm::transpose(glm::inverse(glm::mat3(glm::translate(glm::mat4(1.0f), this->GetPosition()))));
//	return this->normalMatrix;
//}
//
//void Transform::SetScale(glm::vec3 newScale)
//{
//	this->scale = newScale;
//
//	RecalculateLocalScale();
//	RecalculateChildrensScale();
//}
//
//void Transform::SetLocalScale(glm::vec3 newLocalScale)
//{
//	this->localScale = newLocalScale;
//
//	RecalculateScale();
//}

#include "Transform.h"

Transform::Transform() 
{
	SetLocalPosition(glm::vec3(0.0, 0.0, 0.0));
	SetLocalScale	(glm::vec3(1.0, 1.0, 1.0));
	this->UUID = GenerateUUID();

	this->parent = nullptr;
}

Transform::Transform(Transform&& other) noexcept : children(std::move(other.children))
{
	this->localPosition = other.localPosition;
	this->localScale = other.localScale;
	this->parent = other.parent;
	this->UUID = other.UUID;
}




void Transform::SetParent(Transform* newParent)
{
	/* We also need to update localVariables as the globalVariables are
	   not relative to the origin/old parent anymore, but the parent.	*/ 

	FlagRecalculate();

	// First we store the transform data relative to the origin, aka the global verison
	glm::vec3 globalPosition	= this->GetPosition();
	glm::vec3 globalScale		= this->GetScale();

	// Update the child-parent relationships
	if (this->parent != nullptr) { this->parent->RemoveChild(this->UUID); }
	this->parent = newParent;
	newParent->AddChild(this->UUID, this);

	// Set the position with a new parent, something which will calculate the new localPosition
	this->SetPosition	(globalPosition);
	this->SetScale		(globalScale);
}

Transform* Transform::GetParent()
{
	return this->parent;
}

void Transform::AddChild(std::string UUID, Transform* child)
{
	this->children.emplace(UUID, child);
}

void Transform::RemoveChild(std::string UUID)
{
	this->children.erase(UUID);
}




void Transform::SetPosition(glm::vec3 position)
{
	FlagRecalculate();

	if (parent != nullptr)	{ this->localPosition = position - this->parent->GetPosition(); }
	else					{ this->localPosition = position; }
}

void Transform::SetLocalPosition(glm::vec3 localPosition)
{
	FlagRecalculate();

	this->localPosition = localPosition;
}

glm::vec3 Transform::GetPosition()
{
	if (this->parent != nullptr) { return (this->localPosition * this->GetScale()) + this->parent->GetPosition(); }
	else { return this->localPosition; }
}


glm::vec3 Transform::GetLocalPosition()
{
	return this->localPosition;
}




// If Slocal * Sparent = Sglobal will Sglobal / Sparent give Slocal
void Transform::SetScale(glm::vec3 scale) 
{
	FlagRecalculate();

	if (this->parent != nullptr) { this->localScale = this->GetScale() / this->parent->GetScale(); }
	else { this->localScale = scale; }
}

void Transform::SetLocalScale(glm::vec3 localScale) 
{
	FlagRecalculate();

	this->localScale = localScale;
}

glm::vec3 Transform::GetScale() 
{
	if (this->parent != nullptr) { return this->localScale * this->parent->GetScale(); }
	else { return this->localScale; }
}

glm::vec3 Transform::GetLocalScale()
{
	return this->localScale;
}




// TODO : Optimize so the model only gets calculated if any value has changed(includes any of the parent values)
glm::mat4 Transform::GetModel()
{
	bool recalculateModel = (this->parent != nullptr ? (this->recalculate || this->parent->recalculate) : this->recalculate);
	if (recalculateModel)
		{ this->model = glm::translate(glm::mat4(1.0f), this->GetPosition()) * glm::scale(glm::mat4(1.0f), this->GetScale()); recalculate = false; }

	return this->model;
}

glm::mat3 Transform::GetNormalMatrix()
{
	return glm::transpose(glm::inverse(glm::mat3(this->GetModel())));
}

void Transform::FlagRecalculate()
{
	// Flag to recalculate the model on next GetModel() because we updated 
	// some values and the model doesnt represent them anymore.
	this->recalculate = true;

	// Every child also needs updating, which is very annoying as i had to implement children logic just for this
	for (auto& child : this->children) { this->children.at(child.first)->FlagRecalculate(); }
}

std::string Transform::GenerateUUID()
{
	/* Copied from https://stackoverflow.com/questions/24365331/how-can-i-generate-uuid-in-c-without-using-boost-library */

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 15);
	std::uniform_int_distribution<> dis2(8, 11);

	std::stringstream ss;
	int i;
	ss << std::hex;
	for (i = 0; i < 8; i++) {
		ss << dis(gen);
	}
	ss << "-";
	for (i = 0; i < 4; i++) {
		ss << dis(gen);
	}
	ss << "-4";
	for (i = 0; i < 3; i++) {
		ss << dis(gen);
	}
	ss << "-";
	ss << dis2(gen);
	for (i = 0; i < 3; i++) {
		ss << dis(gen);
	}
	ss << "-";
	for (i = 0; i < 12; i++) {
		ss << dis(gen);
	};
	return ss.str();
}
