#include "Transform.h"

/*															Transform															*/


Transform::Transform() 
{
	this->position			= glm::vec3(0.0, 0.0, 0.0);
	this->lastPosition		= glm::vec3(-1.0, 0.0, -1.0);
	this->localPosition		= glm::vec3(0.0, 0.0, 0.0);
	this->lastLocalPosition = glm::vec3(-1.0, -1.0, -1.0);

	this->scale				= glm::vec3(1.0, 1.0, 1.0);
	this->lastScale			= glm::vec3(-1.0, -1.0, -1.0);
	this->localScale		= glm::vec3(1.0, 1.0, 1.0);
	this->lastLocalScale	= glm::vec3(-1.0, 1.0, -1.0);

	this->model = GetModel();

	updatedSinceLastFrame	= false;
	this->normalMatrix		= GetNormalMatrix();
}

Transform::Transform(std::shared_ptr<Transform> parentTransform)
{ 
	this->position			= glm::vec3(0.0, 0.0, 0.0);
	this->lastPosition		= glm::vec3(0.0, 0.0, 0.0);
	this->localPosition		= glm::vec3(0.0, 0.0, 0.0);
	this->lastLocalPosition = glm::vec3(0.0, 0.0, 0.0);

	//this->scale				= glm::vec3(1.0, 1.0, 1.0);
	//this->lastScale			= glm::vec3(1.0, 1.0, 1.0);
	//this->localScale		= glm::vec3(1.0, 1.0, 1.0);
	//this->lastLocalScale	= glm::vec3(1.0, 1.0, 1.0);

	this->model = GetModel();

	updatedSinceLastFrame	= false;
	this->normalMatrix		= GetNormalMatrix();

	SetParent(parentTransform);
}

Transform::~Transform() 
{
	// I dont really know how to handle what happens with the children. I guess I delete them too, but i feel like that should happen on the MainObject side of things?
}

void Transform::SetParent(std::shared_ptr<Transform> parentTransform)
{
	this->parentTransform = parentTransform;
	this->parentTransform->AddChild(this);

	// Since we now have a new parent.position to be relative 
	// to we need to recalculate our global position. This would 
	// also recalculate every child's global position due to the 
	// same reason. 
	RecalculatePosition();
}

void Transform::AddChild(Transform* childTransform) 
{
	this->childTransforms.push_back(childTransform);
}

glm::mat4 Transform::GetModel() 
{
	// If no values are updated we use the old matrix
	
	if (this->position == this->lastPosition || this->localPosition == this->lastLocalPosition || this->scale == this->lastScale || this->localScale == this->lastLocalScale)  
	{
		updatedSinceLastFrame = false; 
		return this->model;
	}
	else {
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), this->scale);
		this->model = glm::translate(glm::mat4(1.0f), this->position) * scaleMatrix;

		this->lastPosition		= this->position;
		this->lastLocalPosition = this->localPosition;
		this->lastScale			= this->scale;
		this->lastLocalScale	= this->localScale;

		updatedSinceLastFrame	= true;
		return this->model;
	}
}

/*															Position															*/

void Transform::RecalculatePosition()
{
	if (this->parentTransform != nullptr)
		this->position = this->parentTransform->GetPosition() + this->localPosition;
	else { this->position = this->localPosition; }

	// Since our global position has changed we need to recalculate each childs 
	// global position too. This is because their global position is relative 
	// to this transforms position + their local position.
	RecalculateChildrensPosition();
}

void Transform::RecalculateLocalPosition()
{
	if (this->parentTransform != nullptr)
		this->localPosition = this->position - this->parentTransform->GetPosition();
	else this->localPosition = this->position;

	// Since our local position and in return global position has changed we need 
	// to recalculate each childs global position too. This is because their global
	// position is relative to this transforms position + their local position.
	RecalculateChildrensPosition();
}

void Transform::RecalculateChildrensPosition() 
{
	for (size_t i = 0; i < this->childTransforms.size(); i++)
		this->childTransforms[i]->RecalculatePosition();
}

void Transform::RecalculateChildrensLocalPosition() 
{
	for (size_t i = 0; i < this->childTransforms.size(); i++)
		this->childTransforms[i]->RecalculateChildrensLocalPosition();
}

void Transform::SetPosition(glm::vec3 newPosition)
{
	this->position = newPosition;

	RecalculateLocalPosition();
	RecalculateChildrensPosition();
}

void Transform::SetLocalPosition(glm::vec3 newLocalPosition)
{
	this->localPosition = newLocalPosition;

	RecalculatePosition();
}

glm::vec3 Transform::GetPosition() 
{
	return this->position;
}

glm::vec3 Transform::GetLocalPosition() 
{
	return this->localPosition;
}

/*															Scale															*/

void Transform::RecalculateScale() 
{
	if (this->parentTransform != nullptr)
		this->scale = this->localScale * this->parentTransform->scale;
	else this->scale = this->localScale;

	RecalculateChildrensScale();
}

void Transform::RecalculateLocalScale() 
{
	if (this->parentTransform != nullptr)
		this->localScale = this->scale / this->parentTransform->scale;
	else this->localScale = this->scale;
}

void Transform::RecalculateChildrensScale() 
{
	for (size_t i = 0; i < this->childTransforms.size(); i++)
		this->childTransforms[i]->RecalculateScale();
}

void Transform::RecalculateChildrensLocalScale() 
{
	for (size_t i = 0; i < this->childTransforms.size(); i++)
		this->childTransforms[i]->RecalculateChildrensLocalScale();
}

glm::mat3 Transform::GetNormalMatrix()
{
	this->normalMatrix = glm::transpose(glm::inverse(glm::mat3(glm::translate(glm::mat4(1.0f), this->GetPosition()))));
	return this->normalMatrix;
}

void Transform::SetScale(glm::vec3 newScale)
{
	this->scale = newScale;

	RecalculateLocalScale();
	RecalculateChildrensScale();
}

void Transform::SetLocalScale(glm::vec3 newLocalScale)
{
	this->localScale = newLocalScale;

	RecalculateScale();
}