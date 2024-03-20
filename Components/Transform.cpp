#include "Transform.h"

Transform::Transform()
{
	this->parent = nullptr;

	SetLocalPosition(glm::vec3(0.0, 0.0, 0.0));
	SetLocalScale	(glm::vec3(1.0, 1.0, 1.0));
	SetLocalRotation(glm::quat(1.0, 0.0, 0.0, 0.0));
	this->UUID = GenerateUUID();
}

Transform::Transform(Transform&& other) noexcept : children(std::move(other.children))
{
	this->localPosition = other.localPosition;
	this->localRotation = other.localRotation;
	this->localScale = other.localScale;
	this->parent = other.parent;
	this->UUID = other.UUID;
	this->model = other.model;
	this->normalMatrix = other.model;
	this->recalculateModel = other.recalculateModel;
	this->recalculateNormalMatrix = other.recalculateNormalMatrix;
}




void Transform::SetParent(Transform* newParent)
{
	/* We also need to update localVariables as the globalVariables are
	   not relative to the origin/old parent anymore, but the parent.	*/

	FlagRecalculateModel();

	// First we store the transform data relative to the origin, aka the global verison
	glm::vec3 globalPosition = this->GetPosition();
	glm::vec3 globalScale = this->GetScale();

	// Update the child-parent relationships
	if (this->parent != nullptr) { this->parent->RemoveChild(this->UUID); }
	this->parent = newParent;
	newParent->AddChild(this->UUID, this);

	// Set the position with a new parent, something which will calculate the new localPosition
	this->SetPosition(globalPosition);
	this->SetScale(globalScale);
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
	FlagRecalculateModel();

	if (parent != nullptr) { this->localPosition = position - this->parent->GetPosition(); }
	else { this->localPosition = position; }
}

void Transform::SetLocalPosition(glm::vec3 localPosition)
{
	FlagRecalculateModel();

	this->localPosition = localPosition;
}

glm::vec3 Transform::GetPosition()
{
	if (this->parent != nullptr) { return (glm::rotate(this->parent->GetRotation(), this->localPosition) * this->GetScale()) + this->parent->GetPosition(); }
	else { return this->localPosition; }
}


glm::vec3 Transform::GetLocalPosition()
{
	return this->localPosition;
}




void Transform::SetRotation(glm::quat rotation)
{
	FlagRecalculateModel();

	if (this->parent != nullptr) { this->localRotation = rotation * glm::inverse(this->parent->GetRotation()); }
	else { this->localRotation = rotation; }
}

void Transform::SetLocalRotation(glm::quat localRotation)
{
	this->localRotation = localRotation;
}

glm::quat Transform::GetRotation()
{
	if (this->parent != nullptr) { return this->localRotation * this->parent->GetRotation(); }
	else { return this->localRotation; }
}

glm::quat Transform::GetLocalRotation()
{
	return this->localRotation;
}




// If Slocal * Sparent = Sglobal will Sglobal / Sparent give Slocal
void Transform::SetScale(glm::vec3 scale)
{
	FlagRecalculateModel();

	if (this->parent != nullptr) { this->localScale = scale / this->parent->GetScale(); }
	else { this->localScale = scale; }
}

void Transform::SetLocalScale(glm::vec3 localScale)
{
	FlagRecalculateModel();

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
	if (recalculateModel) {
		glm::mat4 rotation		= glm::mat4_cast(this->GetRotation());
		glm::mat4 scale			= glm::scale(glm::mat4(1.0f), this->GetScale());
		glm::mat4 translation	= glm::translate(glm::mat4(1.0f), this->GetPosition());

		this->model = translation * scale * rotation;

		FlagRecalculateNormalMatrix();
		recalculateModel = false;
	}
	return this->model;
}

glm::mat3 Transform::GetNormalMatrix()
{
	if (recalculateNormalMatrix) {
		this->normalMatrix = glm::transpose(glm::inverse(glm::mat3(this->GetModel())));
		recalculateNormalMatrix = false;
	}
	return this->normalMatrix;
}

void Transform::FlagRecalculateModel()
{
	// Flag to recalculateModel the model on next GetModel() because we updated 
	// some values and the model doesnt represent them anymore.
	this->recalculateModel = true;

	// Every child also needs updating, which is very annoying as i had to implement children logic just for this
	for (auto& child : this->children) { this->children.at(child.first)->FlagRecalculateModel(); }
}

void Transform::FlagRecalculateNormalMatrix()
{
	this->recalculateNormalMatrix = true;
	for (auto& child : this->children) { this->children.at(child.first)->FlagRecalculateNormalMatrix(); }
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
