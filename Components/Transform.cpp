#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
}

glm::mat4 Transform::GetModel()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(this->rotation.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // x
	model = glm::rotate(model, glm::radians(this->rotation.rotation.y), glm::vec3(1.0f, 0.0f, 0.0f)); // y
	model = glm::rotate(model, glm::radians(this->rotation.rotation.z), glm::vec3(1.0f, 0.0f, 0.0f)); // z

	model = glm::scale(model, this->position.position);

	model = glm::translate(model, this->position.position);

	return model;
}

Scale::Scale()
{
	this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
}
