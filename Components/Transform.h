#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <random>
#include <sstream>

class Transform {
public:
	Transform(),
		Transform(Transform&& other) noexcept;

	void SetParent(Transform* newParent);
	Transform* GetParent();

	void AddChild(std::string UUID, Transform* child), RemoveChild(std::string UUID);

	void SetPosition(glm::vec3 position), SetLocalPosition(glm::vec3 localPosition);
	glm::vec3 GetPosition(), GetLocalPosition();

	void SetRotation(glm::quat rotation), SetLocalRotation(glm::quat localRotation);
	glm::quat GetRotation(), GetLocalRotation();

	void SetScale(glm::vec3 scale), SetLocalScale(glm::vec3 localScale);
	glm::vec3 GetScale(), GetLocalScale();

	glm::mat4 GetModel();
	glm::mat3 GetNormalMatrix();

	// Flags
	void FlagRecalculateModel();
	void FlagRecalculateNormalMatrix();
private:
	std::string UUID;
	std::string GenerateUUID(); // Merge with holder

	Transform* parent;
	std::unordered_map<std::string, Transform*> children;

	// This is the relative to the parents global
	glm::vec3 localPosition, localScale;
	glm::quat localRotation;

	// If no value is updated dont recalculateModel the model
	bool recalculateModel = true, recalculateNormalMatrix = true;
	glm::mat4 model;
	glm::mat3 normalMatrix;
};